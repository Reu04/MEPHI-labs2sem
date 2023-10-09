#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

size_t Size(Array* object) {
    return object->size;
}

size_t Capacity(Array* object) {
    return object->capacity;
}

void ArrayInitialization(Array* object, Ring* ring) {
    object->size = 0;
    object->capacity = 2;
    object->objInfo = ring; // чтобы знать, какой тип данных хранится в массиве
    object->ptr = malloc(object->objInfo->objSize * object->capacity);
}

int Resize(Array* object, size_t newCapacity) {
    if (object == NULL || object->ptr == NULL) {
        return -1;
    }
    if (Capacity(object) >= newCapacity) {
        return -1;
    }

    void* oldPtr = object->ptr;
    void* newPtr = malloc(object->objInfo->objSize * newCapacity);
    if (newPtr == NULL) { // если malloc не смог выделить память - возвращает NULL
        return -1;
    }
    memcpy(newPtr, oldPtr, object->objInfo->objSize * Size(object));
    free(oldPtr);

    object->capacity = newCapacity;
    object->ptr = newPtr;
    return 1;
}

void Set(Array* object, int index, void* value) { // Задать элемент по индексу
    if (object == NULL || object->ptr == NULL) {
        return;
    }
    if (index > Size(object)) {
        return;
    }
    if (index < Size(object)) {
        memcpy(object->ptr + index * object->objInfo->objSize, value, 1 * object->objInfo->objSize);
    } else if (index == Size(object)) {
        if (Size(object) + 1 > Capacity(object)) {
            if (Resize(object, Size(object) * 2) == -1) {
                return;
            }
        }
        memcpy(object->ptr + index * object->objInfo->objSize, value, 1 * object->objInfo->objSize);
        object->size++;
    }
}

void Clear(Array* object) {
    free(object->ptr);
    object->size = 0;
    object->capacity = 2;
}

void Delete(Array* object) {
    free(object->ptr);
    free(object);
}

////

void Sort(Array* object) {
    if (object == NULL || object->ptr == NULL) {
        return;
    }
    qsort(object->ptr, object->size,
          object->objInfo->objSize, object->objInfo->comparator);
}

Array* Map(Array* object, void* (*func)(void*)) {
    Array* mapArr = NULL;
    if (object != NULL && object->ptr != NULL) {
        mapArr = (Array*) malloc(sizeof(Array));
        ArrayInitialization(mapArr, object->objInfo); // object->objInfo !!!
        for (int i = 0; i < (int) Size(object); i++) {
            Set(mapArr, i, func(object->ptr + i * object->objInfo->objSize));
        }
    }
    return mapArr;
}

Array* Where(Array* object, int (*func)(void*)) {
    Array* whereArr = NULL;
    if (object != NULL && object->ptr != NULL) {
        whereArr = (Array*) malloc(sizeof(Array));
        ArrayInitialization(whereArr, object->objInfo);
        int newSize = 0;
        for (size_t i = 0; i < Size(object); i++) {
            if (func(object->ptr + i * object->objInfo->objSize)) {
                Set(whereArr, newSize, object->ptr + i * object->objInfo->objSize);
                newSize++;
            }
        }
    }
    return whereArr;
}

Array* Concatenation(Array* object1, Array* object2) {
    Array* result = NULL;
    if (object1 != NULL && object2 != NULL) {
        if (object1->objInfo == object2->objInfo) {
            result = (Array*) malloc(sizeof(Array));
            ArrayInitialization(result, object1->objInfo);
            int newSize = 0;
            for (size_t i = 0; i < Size(object1); i++) {
                Set(result, newSize, object1->ptr + i * object1->objInfo->objSize);
                newSize++;
            }
            for (size_t i = 0; i < Size(object2); i++) {
                Set(result, newSize, object2->ptr + i * object2->objInfo->objSize);
                newSize++;
            }
        }
    }
    return result;
}