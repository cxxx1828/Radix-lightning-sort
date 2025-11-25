/*
 * ============================================================================
 * HEADER: test_functions.h
 * OPIS: Interfejs za test funkcije
 * ============================================================================
 */

#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include <stdint.h>
#include <stddef.h>

void testPositiveNumbers(void);
void testNegativeNumbers(void);
void testMixedNumbers(void);
void testDuplicates(void);
void testAlreadySorted(void);
void testReverseSorted(void);
void testSingleElement(void);
void testLargeRange(void);
void testExtremeValues(void);

/* Nove test funkcije sa namernim greškama */
void testNullPointer(void);
void testZeroSize(void);
void testHugeArray(void);
void testSingleElementEdgeCase(void);
void testAlreadySortedWithNegatives(void);
void testAllSameElements(void);

void testMillionElements(void);

#endif /* TEST_FUNCTIONS_H */
