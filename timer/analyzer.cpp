// A driver program that analyzes the parallel-divsufsort library. This isn't
// the cleanest C++ you'll ever see. Please forgive my inevitable blasphemies.

// Written by Tiger Sachse.

#include <cmath>
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string.h>
#include <divsufsort.h>
#include <cilk/cilk_api.h>

// Run timed divsufsort tests for a string using a range of thread counts.
double**
run_tests(const std::string& text, int max_threads, int max_runs) {
    auto size = text.size();
    auto suffix_array = new int64_t[size];

    auto total_times = new std::chrono::milliseconds*[max_threads]();
    for (int index = 0; index < max_threads; index++) {
        total_times[index] = new std::chrono::milliseconds[3];
    }

    // For each run, test the function and its pieces using a range of thread caps.
    for (int run = 0; run < max_runs; run++) {
        for (int thread = 1; thread <= max_threads; thread++) {

            // Write a character array version of the thread number to the buffer.
            auto buffer = new char[(int) std::log10(max_threads) + 2]();
            sprintf(buffer, "%d", thread);

            // Set the number of threads for this function call.
            __cilkrts_end_cilk();
            __cilkrts_set_param("nworkers", buffer);

            delete[] buffer;

            // Test the pieces of the function and save the runtimes in the
            // first two cells of total_times.
            timeableDivsufsort(
                (sauchar_t*) text.data(),
                suffix_array,
                size,
                total_times[thread - 1],
                total_times[thread - 1] + 1
            );
          
            total_times[thread - 1][2] = (
                total_times[thread - 1][0]
                + total_times[thread - 1][1]
            );
        }
    }

      auto averages = new double*[max_threads];
      for (int thread = 1; thread <= max_threads; thread++) {
          averages[thread - 1] = new double[3];
          averages[thread - 1][0] = total_times[thread - 1][0].count() / 1000.0 / max_runs;
          averages[thread - 1][1] = total_times[thread - 1][1].count() / 1000.0 / max_runs;
          averages[thread - 1][2] = total_times[thread - 1][2].count() / 1000.0 / max_runs;
      }
  
    // Clean up after yourself!
    for (int index = 0; index < max_threads; index++) {
        delete[] total_times[index];
    }
    delete[] total_times;
    delete[] suffix_array;

    return averages;
}

// Write the averages array to a data output file.
void
write_averages(double** averages, int max_threads, char* input_name) {
    if (averages == NULL || input_name == NULL) {
        std::cout << "Passed NULL to write_averages!\n";

        return;
    }

    // Create the output file name string.
    std::string input_string(input_name);
    auto start = input_string.find_last_of("/");
    auto stop = input_string.find_last_of(".");
    start = (start == std::string::npos) ? 0 : start + 1;
    stop = (stop == std::string::npos) ? input_string.length() : stop - 1;
    std::string output_name = input_string.substr(start, stop - start + 1) + ".out";

    // Open the output file.
    std::ofstream output_file(output_name);
    if (output_file.fail()) {
        std::cout << "File '" << output_name << "' could not be written.\n";

        return;
    }

    // Write the results to the output file.
    output_file << "Results for '" << input_name << "'\n";
    for (int thread = 1; thread <= max_threads; thread++) {
        output_file << "Threads: " << thread;
        output_file << " | Sort Type B*: " << averages[thread - 1][0] << "s";
        output_file << " | Construct SA: " << averages[thread - 1][1] << "s";
        output_file << " | Divsufsort: " << averages[thread - 1][2] << "s";
        output_file << "\n";
    }

    output_file.close();
}

// Main function and entry point of the program.
int
main(int argument_count, char* arguments[]) {

    // If the user has not entered enough arguments, scream about it.
    if (argument_count < 4) {
        std::cout << "Usage: ./analyzer [file] [max threads] [max runs]\n";

        return -1;
    }

    // Attempt to open the text file.
    std::ifstream input(arguments[1]);
    if (input.fail()) {
        std::cout << "File '" << arguments[1] << "' could not be read.\n";

        return -1;
    }

    // Parse max_threads and max_runs from the input vector.
    auto max_threads = std::stoi(arguments[2], NULL, 10);
    auto max_runs = std::stoi(arguments[3], NULL, 10);

    // Create a string from the text file.
    std::string text;
    input.seekg(0, std::ios::end);   
    text.reserve(input.tellg());
    input.seekg(0, std::ios::beg);
    text.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    // Capture averages for different thread counts from the tests.
    // Write these averages to a data file, then free the averages array.
    auto averages = run_tests(text, max_threads, max_runs);
   
    write_averages(averages, max_threads, arguments[1]);
    
    // Clean up after yourself!
    for (int average = 0; average < max_threads; average++) {
        delete[] averages[average];
    }
    delete[] averages;

    return 0;
}
