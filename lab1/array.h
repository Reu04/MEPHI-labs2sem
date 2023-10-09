#include <stdio.h>

typedef struct ring {
    size_t objSize;
    int (*comparator)(const void* value1, const void* value2);
} Ring;

typedef struct array {
    size_t size;
    size_t capacity;
    Ring* objInfo; // Информация о типе данных!
    void* ptr;
} Array;

size_t Size(Array* object);

size_t Capacity(Array* object);

void ArrayInitialization(Array* object, Ring* ring);

int Resize(Array* object, size_t newCapacity);

void Set(Array* object, int index, void* value);

void Clear(Array* object);

void Delete(Array* object);

void Sort(Array* object);

Array* Map(Array* object, void* (*func)(void*));

Array* Where(Array* object, int (*func)(void*));

Array* Concatenation(Array* object1, Array* object2);