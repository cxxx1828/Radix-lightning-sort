/*
 * ============================================================================
 * HEADER: radix_sort.h
 * OPIS: Interfejs za Radix Sort modul
 * ============================================================================
 */

#ifndef RADIX_SORT_H /*MISRA Rule 19.15 ispostovano sa indef, sprecava visestruko includeovanje*/
#define RADIX_SORT_H

#include <stdint.h>
#include <stddef.h>

typedef enum
{
	SORT_SUCCESS = 0,
	SORT_ERROR_NULL = -1,
	SORT_ERROR_SIZE = -2,
	SORT_ERROR_MEMORY = -3
} SortResult;
/*MISRA Rule 8.12 i Rule 8.1 ispostovani jer su enumm definicije u headeru*/

/*
 * Funkcija: radixSort
 * 
 * Sortira niz celih brojeva u neopadajućem poretku koristeći
 * Radix Sort LSD algoritam linearne složenosti O(d*n).
 *
 * Za int32_t tip, d = 4 bajta (konstanta), pa je složenost O(n).
 *
 * Parametri:
 *   arr  - pokazivač na niz int32_t vrednosti (menja se in-place)
 *   size - broj elemenata u nizu
 *
 * Povratna vrednost:
 *   SORT_SUCCESS      - uspešno sortiranje
 *   SORT_ERROR_NULL   - arr je NULL
 *   SORT_ERROR_SIZE   - size je 0
 *   SORT_ERROR_MEMORY - neuspela alokacija memorije
 *
 * Napomena:
 *   - Funkcija modifikuje ulazni niz direktno (in-place sortiranje)
 *   - Stabilan algoritam (čuva relativni redosled jednakih elemenata)
 *   - Radi odlično za bilo koji opseg vrednosti
 *   - Koristi byte-by-byte pristup (baza 256) za optimalnu brzinu
 */
SortResult radixSort(int32_t* arr, size_t size); /*MISRA Rule 8.1 ispostovano, deklarisana funkcija*/

/*
 * Funkcija: getSortResultString
 * 
 * Vraća string opis rezultata sortiranja.
 *
 * Parametri:
 *   result - SortResult kod
 *
 * Povratna vrednost:
 *   Pokazivač na konstantan string sa opisom
 */
const char* getSortResultString(SortResult result);
/*MISRA Rule 11.5 Rule 20.1/20.2 ispostovano const char**/

#endif /* RADIX_SORT_H */
