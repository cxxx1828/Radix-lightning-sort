# LightningSort - Radix Sort Implementation

A Radix Sort LSD implementation in C that achieves O(n) time complexity for sorting 32-bit integers.

## Why Use This

Most sorting algorithms like QuickSort and MergeSort are limited by O(n log n) complexity. Radix sort breaks past this using a different approach - it sorts by processing digits instead of comparing values. For large arrays of integers, this means linear time instead of linearithmic.

The catch is it only works for integers (or things that can be treated like integers), and it needs O(n) extra memory.

## Performance

On 1 million elements:
- LightningSort: ~100ms
- QuickSort: ~180ms  
- MergeSort: ~200ms

The advantage grows with larger datasets since it's truly O(n) while comparison sorts are O(n log n).

## Project Files

```
lightning-sort/
├── main.c                  # Test runner
├── radix_sort.h            # API header
├── radix_sort.c            # Implementation
├── test_functions.h
├── test_functions.c        # 16 test cases
└── libradixsort.a          # Static library (built)
```

## Building

Compile and create the static library:
```bash
gcc -std=c23 -pedantic -Wall -c radix_sort.c
ar -rs libradixsort.a radix_sort.o
```

Build the test suite:
```bash
gcc -std=c23 -pedantic -Wall -static main.c test_functions.c -L. -lradixsort -o lightning_sort
```

Run tests:
```bash
./lightning_sort
```

## Usage

```c
#include "radix_sort.h"
#include <stdio.h>
#include <stdint.h>

int main(void) {
    int32_t numbers[] = {64, 34, 25, 12, 22, 11, 90};
    size_t count = 7;
    
    SortResult result = radixSort(numbers, count);
    
    if (result == SORT_SUCCESS) {
        for (size_t i = 0; i < count; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    } else {
        printf("Error: %s\n", getSortResultString(result));
    }
    
    return 0;
}
```

Output: `11 12 22 25 34 64 90`

## API

```c
SortResult radixSort(int32_t* arr, size_t size);
```

Returns:
- `SORT_SUCCESS` - sorted successfully
- `SORT_ERROR_NULL` - null pointer
- `SORT_ERROR_SIZE` - size is zero
- `SORT_ERROR_MEMORY` - allocation failed

Helper function:
```c
const char* getSortResultString(SortResult result);
```

## How It Works

Radix sort processes integers digit-by-digit (or in this case, byte-by-byte). It makes 4 passes through the data, sorting by one byte at a time starting from the least significant.

**Step 1: Transform signed to unsigned**

Flip the sign bit with XOR so negative numbers map to the lower range:
```c
uint32_t transformed = (uint32_t)value ^ 0x80000000U;
```

**Step 2: Sort byte-by-byte**

Four passes, one for each byte of the 32-bit integer. Each pass uses counting sort (which is stable) on that byte's values (0-255).

**Step 3: Transform back**

Flip the sign bit again to get the original signed representation:
```c
int32_t result = (int32_t)(transformed ^ 0x80000000U);
```

Example:
```
Original:     [170, -45, 75, -200]
Transform:    [0x800000AA, 0x7FFFFD3, 0x8000004B, 0x7FFFFF38]
Sort by bytes (4 passes)
Sorted (hex): [0x7FFFFF38, 0x7FFFFD3, 0x8000004B, 0x800000AA]
Transform back: [-200, -45, 75, 170]
```

The byte-by-byte approach processes 8 bits at a time (base-256), which is more efficient than digit-by-digit (base-10).

## Time Complexity

For n elements with d bytes:
```
T(n) = d × O(n + k)
     = d × O(n + 256)
     = d × O(n)

For int32_t: d = 4 (constant)
Therefore: T(n) = O(n)
```

Space: O(n) for temporary buffers

For n = 1,000,000:
- O(n) = 1,000,000 operations
- O(n log n) ≈ 20,000,000 operations

That's why radix sort is faster on large datasets.

## When to Use This

Good for:
- Large arrays (>100k elements)
- Integer data with wide value ranges
- When you need stable sorting
- When speed is critical

Not good for:
- Small arrays (<100 elements) - cache effects matter more
- Floating-point or string data
- Very limited memory
- Extremely skewed distributions (use counting sort)

## Test Coverage

16 test cases including:
- Basic positive/negative/mixed numbers
- Duplicates and already sorted data
- Edge cases (single element, null pointer, zero size)
- Extreme values (INT32_MIN, INT32_MAX)
- Large range values
- Performance test with 1 million elements

## Benchmarks

On Intel i7 with 16GB RAM:

| Array Size | LightningSort | QuickSort | MergeSort |
|-----------|---------------|-----------|-----------|
| 10,000     | 2ms          | 3ms       | 4ms       |
| 100,000    | 18ms         | 35ms      | 42ms      |
| 1,000,000  | 105ms        | 180ms     | 210ms     |
| 10,000,000 | 950ms        | 2100ms    | 2400ms    |

*Average of 10 runs with random int32_t values*

## What Could Be Added

- Multi-threaded version for multi-core systems
- SIMD optimizations (AVX2/AVX-512)
- Support for 64-bit integers
- Python bindings
- GPU acceleration experiments
- Adaptive algorithm selection based on input characteristics

## Author

Nina Dragićević

## License

MIT
