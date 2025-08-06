/************************************
 * Exercise: linear sorting (counting, radix)
 * Date: 06/08/25
 * Developer: Baruch Haimson
 * Reviewer: guy
 * Status: 
 ************************************/

#ifndef __ILRD_SORTING_H__
#define __ILRD_SORTING_H__

#include <stddef.h> /* size_t */

/* ----------------------------------------------------------------------------
 * Description:
 *     Sorts an array of non-negative integers using Counting Sort algorithm.
 * Parameters:
 *     arr  - pointer to an array of integers (non-negative only)
 *     size - number of elements in the array
 * Returns:
 *     void (the array is sorted in-place)
 * Assumptions:
 *     - All values in the array are non-negative integers.
 *     - The input array is mutable (not const).
 * Time Complexity:
 *     O(n + k), where n is the number of elements and k is the range of input.
 *     Efficient when the range k is not significantly greater than n.
 * Notes:
 *     - The function is only declared (not implemented) in this header.
 *     - Defined elsewhere, typically in a corresponding .c file.
 * -------------------------------------------------------------------------- */
void SortCounting(int* arr, size_t size);

/* ----------------------------------------------------------------------------
 * Description:
 *     Sorts an array of non-negative integers using the Radix Sort algorithm.
 * Parameters:
 *     arr  - pointer to an array of integers (non-negative only)
 *     size - number of elements in the array
 * Returns:
 *     void (the array is sorted in-place)
 * Assumptions:
 *     - All values in the array are non-negative integers.
 *     - The input array is mutable (not const).
 * Time Complexity:
 *     O(n * d), where n is the number of elements and d is the number of digits
 *     in the largest number (base-10).
 * Notes:
 *     - Radix sort is stable and works best when all values are of similar length.
 *     - The function is only declared (not implemented) in this header.
 * -------------------------------------------------------------------------- */
void SortRadix(int* arr, size_t size);


#endif /* __ILRD_SORTING_H__ */

