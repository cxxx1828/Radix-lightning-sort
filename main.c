/*
 * ============================================================================
 * Najbolja optimizacija je čitak kod koji korektno implementira algoritam.
 *
 * ZADATAK:
 *     Napisati program koji uređuje zadati niz celih brojeva u neopadajućem
 *     poretku algoritmom linearne složenosti. Napraviti od toga modul i
 *     realizovati ga kao statičku biblioteku.
 *
 * REŠENJE:
 *     Program koristi Radix Sort algoritam koji ima vremensku složenost O(d*n),
 *     gde je n broj elemenata, a d broj cifara/bajtova. Za fiksnu veličinu
 *     tipa (int32_t = 4 bajta), d je konstanta, pa je složenost O(n).
 * 
 * 
 * IZBOR int32_t TIPA:
 * 
 * 1. Obezbeđuje portabilnost i konzistentnost
 *    - int32_t garantuje tačno 32 bita na svim platformama
 *    - Izbegava se nesigurnost običnog 'int' čija veličina varira
 * 
 * 2. Eksplicitno definiče opseg i ograničenja algoritma  
 *    - Jasno pokazuje da algoritam radi sa 32-bitnim celim brojevima
 *    - Opseg vrednosti: [-2^31, 2^31-1] je eksplicitan
 *    - Broj prolaza (4) direktno proizilazi iz veličine tipa
 * 
 * 3. Olakšava razumevanje Radix Sort parametara
 *    - NUM_PASSES = 4 je očigledno (32 bita / 8 bita po prolazu)
 *    - Transformacija XOR 0x80000000 je jasna za int32_t
 *    - Veličina bafera je predvidiva i konzistentna
 * 
 * 4. Podržava C23 standard i moderne prakse
 *    - stdint.h tipovi su preporučeni u savremenom C programiranju
 *    - Izbegava se zavisnost od implementaciono-definisanog ponašanja
 * 
 * 5. Omogućava lakše testiranje i verifikaciju
 *    - Egzaktno poznat opseg vrednosti za test slučajeve
 *    - Mogućnost testiranja ekstremnih vrednosti (INT32_MIN/MAX)
 *    - Jednostavnije otkrivanje grešaka u transformaciji
 * 
 * Eksplicitnost u izboru tipova sprečava skrivene greške i čini kod samodokumentujućim.
 *
 *
 *     Radix Sort sortira brojeve cifru po cifru (ili bajt po bajt), koristeći
 *     stabilan algoritam (Counting Sort) za svaku poziciju. Ovaj pristup
 *     garantuje linearnu složenost bez obzira na opseg vrednosti.
 *
 * STRUKTURA:
 *     - main.c - glavna aplikacija (komunikacija sa korisnikom)
 *     - radix_sort.c - implementacija Radix Sort algoritma
 *     - radix_sort.h - interfejs modula
 *     - test_functions.c - test funkcije
 *     - test_functions.h - interfejs test modula
 *     - libradixsort.a - statička biblioteka (Radix Sort)
 * 
 *
 * Nina Dragićević
 * 
 *
 * VAŽNE NAPOMENE:
 *     1. Algoritam: Radix Sort LSD (Least Significant Digit)
 *        - Vremenska složenost: O(d*n) = O(n) za fiksno d
 *        - Prostorna složenost: O(n)
 *     2. Implementacija: Byte-by-byte (baza 256) za maksimalnu brzinu
 *     3. Tip podataka: int32_t za portabilnost (C23 standard)
 *     4. Ograničenja:
 *        - Maksimalan broj elemenata: 1,000,000
 *        - Opseg vrednosti: [-2^31, 2^31-1] (int32_t)
 *     5. Prednosti nad Counting Sort:
 *        - NE zavisi od opsega vrednosti (k)
 *        - Memorija O(n) umesto O(k)
 *        - Garantovano linearna za sve ulaze
 *     6. Memorija vs Brzina: Prioritet dat brzini sortiranja
 *     7. Prenosivost: Koristi stdint.h tipove (C23)
 *
 *
 * MISRA-C:2004 
 * 
    Isključena MISRA pravila:

        -(MISRA-C:2004 20.9/R)
        The input/output library <stdio.h> shall not be used in production code

            -> Uzrok:
               Korišćenje standardne izlazne funkcije "printf" iz biblioteke <stdio.h>.

            -> Obrazloženje za isključivanje:
               Funkcija printf() se u ovom projektu koristi isključivo u svrhu
               testiranja, verifikacije i prikaza rezultata rada algoritma
               (Radix Sort). Projekat nije namenjen za produkciono embedded
               okruženje, već za akademsku i razvojnu svrhu.

               Korišćenje printf-a omogućava lakšu analizu, debugovanje i
               validaciju rezultata sortiranja, bez ikakvog uticaja na
               bezbednost ili determinističnost samog algoritma.

               U stvarnom produkcionom okruženju, ove funkcije bi bile
               uklonjene ili zamenjene odgovarajućim mehanizmima (npr. UART).

            -> Pravilo je svesno i opravdano isključeno.

 *
 * KOMPAJLIRANJE:
 *     
 *     gcc -std=c23 -pedantic -Wall -c radix_sort.c
 *     ar -rs libradixsort.a radix_sort.o
 *     gcc -std=c23 -pedantic -Wall -static main.c test_functions.c -L. -lradixsort -o a.out
 *
 * TESTIRANJE:
 *     Program automatski izvršava 15 test slučajeva:
 *     1. Pozitivni brojevi
 *     2. Negativni brojevi
 *     3. Mešoviti (pozitivni i negativni)
 *     4. Niz sa duplikatima
 *     5. Već sortiran niz
 *     6. Obrnuto sortiran niz
 *     7. Jedan element
 *     8. Veliki opseg vrednosti (pokazuje prednost nad Counting Sort)
 *     9. Ekstremni slučaj (INT32_MIN i INT32_MAX)
 *     10. NULL pokazivač (testira robustnost na greške)
 *     11. Niz veličine 0 (granični slučaj)
 *     12. Ogroman niz (testira rukovanje memorijskim greškama)
 *     13. Jedan element (dodatni granični slučaj)
 *     14. Već sortiran niz sa negativima (testira stabilnost transformacije)
 *     15. Svi isti elementi (testira stabilnost algoritma)
 * 
 * Svrha testova je kompletna verifikacija:
 * - Korektnost sortiranja u različitim scenarijima
 * - Robustnost na granične slučajeve i greške
 * - Stabilnost algoritma
 * - Efikasnost na različitim vrstama ulaza
 *
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "radix_sort.h"
#include "test_functions.h"


int32_t main(void);

int32_t main(void)
{
	printf("   RADIX SORT - LINEARNO SORTIRANJE    \n");

	printf("Pokretanje test slučajeva...\n\n");

	testPositiveNumbers();
	testNegativeNumbers();
	testMixedNumbers();
	testDuplicates();
	testAlreadySorted();
	testReverseSorted();
	testSingleElement();
	testLargeRange();
	testExtremeValues();

	/*Testovi sa namernim greškama*/ 
	testNullPointer();
	testZeroSize();
	testHugeArray();
	testSingleElementEdgeCase();
	testAlreadySortedWithNegatives();
	testAllSameElements();

	/* Test za milion elemenata */
	testMillionElements();

	printf("Svi testovi uspešno završeni!\n");

	return 0;
}

/*
cd ti_tools 
source $PWD/set_env.sh #čudo što radimo da ti bash sesija skonta gde su komande
cd ..
cl6x --include_path=$TI_INCLUDE --compile_only --check_misra=all main.c
*/