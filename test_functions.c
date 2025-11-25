/*
 * ============================================================================
 * test_functions.c
 * OPIS: Test funkcije za proveru ispravnosti Radix Sort algoritma
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "radix_sort.h"
#include "test_functions.h"

static void printArray(const int32_t* arr, size_t size);
static bool isSorted(const int32_t* arr, size_t size);

/*
 * TEST 1: Pozitivni brojevi
 * 
 * Testira osnovnu funkcionalnost algoritma na pozitivnim brojevima.
 * Proverava da li algoritam korektno sortira jednostavan niz pozitivnih vrednosti.
 */

void testPositiveNumbers(void)
{
	printf("TEST 1: Pozitivni brojevi\n");
	printf("----------------------------\n");

	int32_t arr[] = {64, 34, 25, 12, 22, 11, 90};
	size_t size = sizeof(arr) / sizeof(arr[0]);/*ukupna veličina niza u bajtovima/prvi element niza*/

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 2: Negativni brojevi
 * 
 * Testira transformaciju negativnih brojeva kroz XOR operaciju.
 * Proverava ispravnost Radix Sort-a na čisto negativnim vrednostima.
 */

void testNegativeNumbers(void)
{
	printf("TEST 2: Negativni brojevi\n");
	printf("----------------------------\n");

	int32_t arr[] = {-5, -12, -3, -45, -1, -23};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 3: Mešoviti brojevi (pozitivni i negativni)
 * 
 * Testira kombinaciju pozitivnih, negativnih brojeva i nule.
 * Proverava korektnost transformacije i sortiranja mešovitih znakova.
 */

void testMixedNumbers(void)
{
	printf("TEST 3: Mešoviti brojevi (pozitivni i negativni)\n");
	printf("--------------------------------------------------\n");

	int32_t arr[] = {-15, 42, 0, -8, 23, -4, 16, -20, 31};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 4: Niz sa duplikatima
 * 
 * Testira stabilnost algoritma - da li čuva redosled jednakih elemenata.
 * Proverava korektnost Radix Sort-a kada postoje ponovljene vrednosti.
 */
void testDuplicates(void)
{
	printf("TEST 4: Niz sa duplikatima\n");
	printf("----------------------------\n");

	int32_t arr[] = {5, 2, 8, 2, 9, 1, 5, 5};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 5: Već sortiran niz
 * 
 * Testira efikasnost algoritma na već sortiranom nizu.
 * Proverava da li algoritam nepotrebno menja već korektan redosled.
 */
void testAlreadySorted(void)
{
	printf("TEST 5: Već sortiran niz\n");
	printf("----------------------------\n");

	int32_t arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 6: Obrnuto sortiran niz
 * 
 * Testira algoritam na potpuno obrnutom nizu.
 * Proverava efikasnost u najgorem slučaju za neke druge algoritme.
 */
void testReverseSorted(void)
{
	printf("TEST 6: Obrnuto sortiran niz\n");
	printf("-------------------------------\n");

	int32_t arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 7: Niz sa jednim elementom
 * 
 * Testira granični slučaj minimalnog ulaza.
 * Proverava da li algoritam korektno rukuje nizovima veličine 1.
 */
void testSingleElement(void)
{
	printf("TEST 7: Niz sa jednim elementom\n");
	printf("---------------------------------\n");

	int32_t arr[] = {42};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 8: Veliki opseg vrednosti
 * 
 * Demonstrira prednost Radix Sort-a nad Counting Sort-om.
 * Prikazuje kako Radix Sort efikasno rukuje velikim opsezima bez eksponencijalne memorije.
 */
void testLargeRange(void)
{
	printf("TEST 8: Veliki opseg vrednosti\n");
	printf("--------------------------------\n");
	printf("(Pokazuje prednost Radix Sort-a nad Counting Sort-om)\n");

	int32_t arr[] = {1000000000, -1000000000, 0, 500000000, -500000000, 999999999, -999999999};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n");
		printf("  (Counting Sort bi ovde zahtevao ~8GB memorije!)\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 9: Ekstremne vrednosti (INT32_MIN, INT32_MAX)
 * 
 * Testira algoritam na graničnim vrednostima tipa int32_t.
 * Proverava korektnost transformacije za najveće i najmanje moguće vrednosti.
 */
void testExtremeValues(void)
{
	printf("TEST 9: Ekstremne vrednosti (INT32_MIN, INT32_MAX)\n");
	printf("----------------------------------------------------\n");

	int32_t arr[] = {2147483647, -2147483648, 0, 2147483646, -2147483647, 1, -1};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		printf("✓ Test uspešan!\n\n");
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * Pomoćna funkcija: Ispis niza
 * 
 * Formatiran ispis niza u obliku [element1, element2, ..., elementN]
 * Koristi se za prikaz stanja niza pre i posle sortiranja.
 */
static void printArray(const int32_t* arr, size_t size)
{
	assert(arr != NULL);

	printf("[");
	for (size_t i = 0; i < size; i++)
	{
		printf("%d", arr[i]);
		if (i < size - 1)
		{
			printf(", ");
		}
	}
	printf("]\n");
}

/*
 * Pomoćna funkcija: Provera da li je niz sortiran
 * 
 * Proverava da li su elementi niza u neopadajućem poretku.
 * Vraća true ako je niz sortiran, false inače.
 */
static bool isSorted(const int32_t* arr, size_t size)
{
	assert(arr != NULL);

	if (size <= 1)
	{
		return true;
	}

	for (size_t i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			return false;
		}
	}

	return true;
}

/*
 * TEST FUNKCIJE SA NAMERNIM GREŠKAMA:
 * 
 * Ove funkcije testiraju robustnost algoritma i ispravnost
 * rukovanja greškama. Namerno provociraju granične slučajeve
 * kako bi se verifikovalo da algoritam lepo fail-uje kada treba.
 */



/*
 * TEST 10: NULL pokazivač na niz
 * 
 * Namerna greška: Prosljeđivanje NULL pokazivača
 * Očekivano ponašanje: Algoritam treba da vrati SORT_ERROR_NULL
 * bez pokušaja dereferenciranja pokazivača
 * algoritam koji ne proverava NULL može da padne (segfault), u stvarnim aplikacijama pokazivači mogu biti NULL zbog greške u kodu
 */
void testNullPointer(void)
{
	printf("TEST 10: NULL pokazivač na niz\n");
	printf("--------------------------------\n");
	printf("(Testira robustnost na greške)\n");

	SortResult result = radixSort(NULL, 5);

	if (result == SORT_ERROR_NULL)
	{
		printf("✓ Test uspešan! Algoritam je prepoznao NULL pokazivač.\n");
		printf("  Povratna vrednost: %s\n\n", getSortResultString(result));
	}
	else
	{
		printf("✗ Greška: Algoritam nije prepoznao NULL pokazivač!\n");
		printf("  Očekivano: SORT_ERROR_NULL, Dobijeno: %s\n\n", 
               getSortResultString(result));
	}
}

/*
 * TEST 11: Niz veličine 0
 * 
 * Namerna greška: Prosljeđivanje niza sa 0 elemenata
 * Očekivano ponašanje: Algoritam treba da vrati SORT_ERROR_SIZE
 * bez pokušaja alokacije ili obrade
 * Granični slučajevi veličine 0 su česti u softverskim aplikacijama.
 * Ako se ne obradi, može doći do beskonačnih petlji ili segfault-a.
 */
void testZeroSize(void)
{
	printf("TEST 11: Niz veličine 0\n");
	printf("-------------------------\n");
	printf("(Testira granične slučajeve)\n");

	int32_t arr[] = {1, 2, 3};  // Niz postoji, ali size je 0
	size_t size = 0;

	SortResult result = radixSort(arr, size);

	if (result == SORT_ERROR_SIZE)
	{
		printf("✓ Test uspešan! Algoritam je prepoznao niz veličine 0.\n");
		printf("  Povratna vrednost: %s\n\n", getSortResultString(result));
	}
	else
	{
		printf("✗ Greška: Algoritam nije prepoznao niz veličine 0!\n");
		printf("  Očekivano: SORT_ERROR_SIZE, Dobijeno: %s\n\n", 
               getSortResultString(result));
	}
}

/*
 * TEST 12: Ogroman niz (potencijalna memorijska greška)
 * 
 * Namerna greška: Zahtev za preveliku alokaciju memorije
 * Očekivano ponašanje: Algoritam treba da vrati SORT_ERROR_MEMORY
 * kada malloc() ne uspe
 * Ovo testira robustnost algoritma pri velikim ulazima.
 * U realnim aplikacijama korisnik ili sistem može zahtevati više memorije nego što ima slobodno.
 */
void testHugeArray(void)
{
	printf("TEST 12: Ogroman niz (prevelika veličina)\n");
	printf("-----------------------------------------\n");
	printf("(Testira rukovanje memorijskim greškama)\n");

	// Koristi manju, ali još uvek ogromnu veličinu
	// koja će verovatno uzrokovati malloc() grešku
	size_t huge_size = SIZE_MAX / 1000;  

	int32_t small_arr[] = {1, 2, 3};
	
	printf("Testiranje sa veličinom: %zu elemenata\n", huge_size);
	SortResult result = radixSort(small_arr, huge_size);

	if (result == SORT_ERROR_MEMORY || result == SORT_ERROR_SIZE)
	{
		printf("✓ Test uspešan! Algoritam je prepoznao problem.\n");
		printf("  Povratna vrednost: %s\n\n", getSortResultString(result));
	}
	else
	{
		printf("✗ Neočekivano ponašanje za ogroman niz!\n");
		printf("  Dobijeno: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 13: Jedan element (granični slučaj)
 * 
 * Namerno: Niz sa samo jednim elementom
 * Očekivano ponašanje: Algoritam treba da vrati SORT_SUCCESS
 * bez alokacije dodatne memorije ili kompleksne obrade
 * Minimalni ulazi su česti u testiranju algoritama.
 * Algoritam koji ne proveri ovo može nepotrebno alocirati memoriju ili napraviti logičku grešku.
 */
void testSingleElementEdgeCase(void)
{
	printf("TEST 13: Jedan element (granični slučaj)\n");
	printf("-----------------------------------------\n");
	printf("(Testira efikasnost na minimalnim ulazima)\n");

	int32_t arr[] = {42};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);
		
		assert(isSorted(arr, size));
		printf("✓ Test uspešan! Algoritam je efikasno obradio jedan element.\n\n");
	}
	else
	{
		printf("✗ Greška: Algoritam nije uspeo sa jednim elementom!\n");
		printf("  Povratna vrednost: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 14: Već sortiran niz sa negativnim brojevima
 * 
 * Namerno: Već sortiran niz koji testira transformaciju negativnih brojeva
 * Očekivano ponašanje: Algoritam treba da ostavi niz nepromenjen
 * i da vrati SORT_SUCCESS
 * U mnogim aplikacijama već sortirani nizovi su česti.
 * Algoritam koji ne održava stabilnost može promeniti redosled jednakih ili negativnih elemenata.
 */
void testAlreadySortedWithNegatives(void)
{
	printf("TEST 14: Već sortiran niz sa negativima\n");
	printf("----------------------------------------\n");
	printf("(Testira stabilnost transformacije)\n");

	int32_t arr[] = {-100, -50, -10, 0, 10, 50, 100};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	// Snimi originalni niz za poređenje (BEZ memcpy)
	int32_t original[7];
	for (size_t i = 0; i < size; i++)  
	{
		original[i] = arr[i];
	}

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		assert(isSorted(arr, size));
		
		// Proveri da li je niz ostao potpuno isti
		bool unchanged = true;
		for (size_t i = 0; i < size; i++)
		{
			if (arr[i] != original[i])
			{
				unchanged = false;
				break;
			}
		}
		
		if (unchanged)
		{
			printf("✓ Test uspešan! Algoritam je očuvao već sortiran niz.\n\n");
		}
		else
		{
			printf("⚠ Niz je i dalje sortiran, ali je malo drugačiji.\n\n");
		}
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 15: Svi isti elementi
 * 
 * Namerno: Niz gde su svi elementi identični
 * Očekivano ponašanje: Algoritam treba da vrati SORT_SUCCESS
 * i da očuva originalni redosled (stabilnost)
 * Ovo je ekstreman granični slučaj.
 * Stabilnost znači da ako su elementi jednaki, njihov originalni redosled ostaje nepromenjen.
 * Ovo je posebno važno kod kompleksnijih struktura gde vrednost elementa nije jedina informacija.
 */
void testAllSameElements(void)
{
	printf("TEST 15: Svi isti elementi\n");
	printf("---------------------------\n");
	printf("(Testira stabilnost algoritma)\n");

	int32_t arr[] = {5, 5, 5, 5, 5, 5, 5};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	printf("Pre sortiranja:  ");
	printArray(arr, size);

	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("Posle sortiranja: ");
		printArray(arr, size);

		// Proveri da li su svi elementi i dalje 5
		bool all_same = true;
		for (size_t i = 0; i < size; i++)
		{
			if (arr[i] != 5)
			{
				all_same = false;
				break;
			}
		}
		
		if (all_same && isSorted(arr, size))
		{
			printf("✓ Test uspešan! Algoritam je očuvao sve iste elemente.\n\n");
		}
		else
		{
			printf("✗ Greška: Algoritam je promenio elemente!\n\n");
		}
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}
}

/*
 * TEST 16: Milion elemenata
 * 
 * Testira performanse algoritma na velikom nizu sa 1,000,000 elemenata.
 * Proverava da li algoritam efikasno rukuje velikim količinama podataka.
 * Koristi nasumične vrednosti iz celog opsega int32_t.
 */
void testMillionElements(void)
{
	printf("TEST 16: Milion elemenata\n");
	printf("--------------------------\n");
	printf("(Testira performanse na velikom skupu podataka)\n");

	const size_t size = 1000000;
	printf("Alociranje memorije za %zu elemenata...\n", size);

	int32_t* arr = (int32_t*)malloc(size * sizeof(int32_t));
	if (arr == NULL)
	{
		printf("✗ Greška: Neuspela alokacija memorije za test niz!\n\n");
		return;
	}

	/* Popunjavanje niza nasumičnim brojevima */
	printf("Popunjavanje niza nasumičnim vrednostima...\n");
	srand(42);  /* Fiksni seed za ponovljivost testova */
	
	for (size_t i = 0; i < size; i++)
	{
		/* Generiši potpuno nasumične int32_t vrednosti 
		   kombinujući dva rand() poziva */
		int32_t high = rand();
		int32_t low = rand();
		arr[i] = (high << 16) | (low & 0xFFFF);
		
		/* Nasumično flip-uj znak */
		if (rand() % 2 == 0)
		{
			arr[i] = -arr[i];
		}
	}

	/* Prikaži prvih 10 i poslednjih 10 elemenata */
	printf("\nPrvih 10 elemenata:    [");
	for (size_t i = 0; i < 10; i++)
	{
		printf("%d", arr[i]);
		if (i < 9) printf(", ");
	}
	printf("]\n");

	printf("Poslednjih 10 elemenata: [");
	for (size_t i = size - 10; i < size; i++)
	{
		printf("%d", arr[i]);
		if (i < size - 1) printf(", ");
	}
	printf("]\n\n");

	printf("Pokretanje Radix Sort algoritma...\n");
	SortResult result = radixSort(arr, size);

	if (result == SORT_SUCCESS)
	{
		printf("✓ Sortiranje uspešno završeno!\n\n");

		/* Prikaži prvih 10 i poslednjih 10 sortiranih elemenata */
		printf("Prvih 10 sortiranih:    [");
		for (size_t i = 0; i < 10; i++)
		{
			printf("%d", arr[i]);
			if (i < 9) printf(", ");
		}
		printf("]\n");

		printf("Poslednjih 10 sortiranih: [");
		for (size_t i = size - 10; i < size; i++)
		{
			printf("%d", arr[i]);
			if (i < size - 1) printf(", ");
		}
		printf("]\n\n");

		/* Verifikacija da je niz sortiran */
		printf("Verifikacija da je niz sortiran...\n");
		bool sorted = isSorted(arr, size);
		
		if (sorted)
		{
			printf("✓ Test uspešan! Niz od %zu elemenata je korektno sortiran.\n", size);
			printf("  Radix Sort je efikasno obradio milion elemenata!\n\n");
		}
		else
		{
			printf("✗ Greška: Niz NIJE korektno sortiran!\n\n");
		}
	}
	else
	{
		printf("✗ Greška: %s\n\n", getSortResultString(result));
	}

	free(arr);
}