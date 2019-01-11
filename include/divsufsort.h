/*
 * divsufsort.h for libdivsufsort
 * Copyright (c) 2003-2008 Yuta Mori All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _DIVSUFSORT_H
#define _DIVSUFSORT_H 1

#include <inttypes.h>
/*- Datatypes -*/
typedef uint8_t sauchar_t;
typedef int32_t saint_t;

/*- Prototypes -*/

/**
 * Constructs the suffix array of a given string.
 * @param T[0..n-1] The input string.
 * @param SA[0..n-1] The output array of suffixes.
 * @param n The length of the given string.
 * @return 0 if no error occurred, -1 or -2 otherwise.
 */
double**
divsufsort(const sauchar_t *T, int32_t *SA, int32_t n);
double**
divsufsort(const sauchar_t *T, int64_t *SA, int64_t n);

/**
 * Constructs the burrows-wheeler transformed string of a given string.
 * @param T[0..n-1] The input string.
 * @param U[0..n-1] The output string. (can be T)
 * @param A[0..n-1] The temporary array. (can be NULL)
 * @param n The length of the given string.
 * @return The primary index if no error occurred, -1 or -2 otherwise.
 */
//saidx_t
//divbwt(const sauchar_t *T, sauchar_t *U, saidx_t *A, saidx_t n);


/**
 * Constructs the burrows-wheeler transformed string of a given string and suffix array.
 * @param T[0..n-1] The input string.
 * @param U[0..n-1] The output string. (can be T)
 * @param SA[0..n-1] The suffix array. (can be NULL)
 * @param n The length of the given string.
 * @param idx The output primary index.
 * @return 0 if no error occurred, -1 or -2 otherwise.
 */
//saint_t
//bw_transform(const sauchar_t *T, sauchar_t *U,
//             saidx_t *SA /* can NULL */,
//             saidx_t n, saidx_t *idx);

/**
 * Inverse BW-transforms a given BWTed string.
 * @param T[0..n-1] The input string.
 * @param U[0..n-1] The output string. (can be T)
 * @param A[0..n-1] The temporary array. (can be NULL)
 * @param n The length of the given string.
 * @param idx The primary index.
 * @return 0 if no error occurred, -1 or -2 otherwise.
 */
//saint_t
//inverse_bw_transform(const sauchar_t *T, sauchar_t *U,
//                     saidx_t *A /* can NULL */,
//                     saidx_t n, saidx_t idx);

/**
 * Checks the correctness of a given suffix array.
 * @param T[0..n-1] The input string.
 * @param SA[0..n-1] The input suffix array.
 * @param n The length of the given string.
 * @param verbose The verbose mode.
 * @return 0 if no error occurred.
 */
saint_t sufcheck(const sauchar_t *T, const int32_t *SA,
		int32_t n, saint_t verbose); 
saint_t sufcheck(const sauchar_t *T, const int64_t *SA,
		int64_t n, saint_t verbose);
/**
 * Search for the pattern P in the string T.
 * @param T[0..Tsize-1] The input string.
 * @param Tsize The length of the given string.
 * @param P[0..Psize-1] The input pattern string.
 * @param Psize The length of the given pattern string.
 * @param SA[0..SAsize-1] The input suffix array.
 * @param SAsize The length of the given suffix array.
 * @param idx The output index.
 * @return The count of matches if no error occurred, -1 otherwise.
 */
//saidx_t
//sa_search(const sauchar_t *T, saidx_t Tsize,
//          const sauchar_t *P, saidx_t Psize,
//          const saidx_t *SA, saidx_t SAsize,
//          saidx_t *left);

/**
 * Search for the character c in the string T.
 * @param T[0..Tsize-1] The input string.
 * @param Tsize The length of the given string.
 * @param SA[0..SAsize-1] The input suffix array.
 * @param SAsize The length of the given suffix array.
 * @param c The input character.
 * @param idx The output index.
 * @return The count of matches if no error occurred, -1 otherwise.
 */
//saidx_t
//sa_simplesearch(const sauchar_t *T, saidx_t Tsize,
//                const saidx_t *SA, saidx_t SAsize,
//                saint_t c, saidx_t *left);

int32_t
sort_typeBstar(const sauchar_t *T, int32_t *SA,
               int32_t *bucket_A, int32_t *bucket_B,
               int32_t n);
int64_t
sort_typeBstar(const sauchar_t *T, int64_t *SA,
               int64_t *bucket_A, int64_t *bucket_B,
               int64_t n);

void
construct_SA(const sauchar_t *T, int32_t *SA,
             int32_t *bucket_A, int32_t *bucket_B,
             int32_t n, int32_t m);

void
construct_SA(const sauchar_t *T, int64_t *SA,
             int64_t *bucket_A, int64_t *bucket_B,
             int64_t n, int64_t m) ;

#endif /* _DIVSUFSORT_H */
