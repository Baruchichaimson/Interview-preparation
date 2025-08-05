/************************************
 * Exercise: sorting (bubble, insertion, selection)
 * Date: 05/08/25
 * Developer: Baruch Haimson
 * Reviewer: guy
 * Status: 
 ************************************/

#ifndef __ILRD_SORTING_H__
#define __ILRD_SORTING_H__

#include <stddef.h> /* size_t */

/*
 * Description:
 *     Sorts an array of integers in ascending order 
 *     using the iterative Bubble Sort algorithm.
 *
 * Parameters:
 *     arr  - pointer to the integer array to sort
 *     size - number of elements in the array
 *
 * Return Value:
 *     void
 *
 * Undefined Behavior:
 *     - arr is NULL
 *     - size < 2
 *
 * Time Complexity:
 *     Best Case:    O(n)     
 *     Average Case: O(n^2)
 *     Worst Case:   O(n^2)
 */
void SortingBubble(int* arr, size_t size);

/*
 * SortingSelection
 * -----------------
 * Description:
 *     Sorts an array of integers in ascending order 
 *     using the iterative Selection Sort algorithm.
 *
 * Parameters:
 *     arr  - pointer to the integer array to sort
 *     size - number of elements in the array
 *
 * Return Value:
 *     void
 *
 * Undefined Behavior:
 *     - arr is NULL
 *     - size < 2
 *
 * Time Complexity:
 *     Best Case:    O(n^2)
 *     Average Case: O(n^2)
 *     Worst Case:   O(n^2)
 */
 
void SortingSelection(int* arr, size_t size);

/*
 * Description:
 *     Sorts an array of integers in ascending order 
 *     using the iterative Insertion Sort algorithm.
 *
 * Parameters:
 *     arr  - pointer to the integer array to sort
 *     size - number of elements in the array
 *
 * Return Value:
 *     void
 *
 * Undefined Behavior:
 *     - arr is NULL
 *     - size < 2
 *
 * Time Complexity:
 *     Best Case:    O(n)       
 *     Average Case: O(n^2)
 *     Worst Case:   O(n^2)
 */
void SortingInsertion(int* arr, size_t size);

#endif /* __ILRD_SORTING_H__ */

