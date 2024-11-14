# How is memory management done at low level? Methods
- Allocation: malloc/calloc
- Deallocation: free
---
# Simple example of how malloc is used 

```c
void integer_allocation() {
        printf("Hi guys!\n"
               "Let's try to allocate some memory "
               "(for an array of size 10 of int elements).\n");

        int *demo_pointer = (int *)malloc(sizeof(int) * 10);
        for (int i = 0; i < 10; i++) {
                printf("We have the memory address: %p for element  at "
                       "position: %d\n",
                       demo_pointer + sizeof(int) * i, i);
                demo_pointer[i] = (i + 1) * 10;
        }

        printf("We have succesfully allocated the memory");
        free(demo_pointer);
}
```
---
# How does malloc work?
- Standard practice: `malloc` allocates exactly the number of bytes requested, no extra bytes per element, such as an `int`. 

---

### Cases Where `malloc` May Allocate Additional Bytes Beyond Requested Size

- Certain situations may result in additional bytes allocation or within the allocated block.
- *BEWARE*: typically not tied to each individual `int`. 
## Here’s an overview of such scenarios:

---

### 1. Memory Alignment and Padding
   - Modern systems often require **memory alignment** to ensure efficient access. 
     This means memory allocated for certain data types often starts at specific boundaries (e.g., addresses that are multiples of 4 or 8 bytes).
   - Although `malloc` returns a block that is generally aligned, it doesn’t always add padding between each element within the allocated block.
   - **Example**: When you allocate `10 * sizeof(int)`, the entire block will be aligned according to the system’s requirements, but no padding may be allocated between each integer.
   - **Example**: This is observable on the `char` type, especially when trying to allocate too many items of this type.
      - Below, malloc adds padding for all the `char` elements, although they are exactly 1 byte each. To align it in memory, it allocates 4 bytes/char.
      - Because of that we get very slow results (same as if we had that number of integers).
```c
void char_allocation() {
        printf("Let's try to do this for long long too.\n");
        char *demo_pointer = (char *)malloc(sizeof(char) * 10000000000000000);

        for (long long i = 0; i < 10000000000000000; i++) {
                if (i == 0 || i == 10000000000000000 - 1) {
                        printf("We have the memory address: %p for element  at "
                               "position: %lld\n",
                               demo_pointer + sizeof(int) * i, i);
                }
        }
        printf("Now what?\n");
}
```
---

### 2. Overhead from `malloc` Management Metadata
   - To manage memory efficiently, `malloc` often includes **metadata** about the allocated blocks, such as size and other management details.
   - This metadata is usually stored just before or after the allocated block, so it doesn’t affect the usable space in the allocated block itself.
   - Thus, this metadata doesn’t increase the space allocated per `int`, but it can increase the overall memory used.

---

### 3. Memory Allocator Rounding
   - Some memory allocators **round up** the requested allocation size to fit their internal memory management strategies. 
     Many allocators use sizes in powers of two (e.g., 16 bytes, 32 bytes) to enhance performance and reduce fragmentation.
   - For example, if you request an odd number of bytes (like 37 bytes), `malloc` might round up to the nearest multiple, such as 40 bytes. 
     However, for requests like `10 * sizeof(int)` (40 bytes), no rounding usually occurs, as it’s already a multiple of 8.

---

### 4. Debugging and Guard Bytes
   - In debugging environments, `malloc` may add **guard bytes** around allocated blocks. These bytes help detect buffer overflows or underflows by placing markers around your data.
   - These extra bytes aren’t part of the requested allocation but are added by debugging tools or runtime environments specifically for memory safety.

---

#### Summary

To sum up, `malloc` does not add extra bytes per `int` in a straightforward allocation. 
However, alignment requirements, metadata, rounding, and debugging safeguards might slightly increase the overall memory allocated around the requested block.
