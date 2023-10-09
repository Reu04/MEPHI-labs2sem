#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

// test function 1 (multiply the number by 3)
void* mapRNumberFunction(void* value) {
    double* newValue = (double*) malloc(sizeof(double));
    *newValue = *((double*) value) * 3;
    return newValue;
}

// test function 2 (change the register)
void* mapStringFunction(void* value) { // value -> char**
    char* str = *((char**) value);
    char* newStr = (char*) malloc(sizeof(char) * (strlen(str) + 1)); // + 1 for '\0'
    char** newPtr = (char**) malloc(sizeof(char*));
    for (int i = 0; i < strlen(str); i++) {
        if ((int) str[i] >= 32 && (int) str[i] <= 90) {
            newStr[i] = (char) ((int) str[i] + 32);
        } else if ((int) str[i] >= 97 && (int) str[i] <= 122) {
            newStr[i] = (char) ((int) str[i] - 32);
        } else {
            newStr[i] = str[i];
        }
    }
    newStr[strlen(str)] = '\0';
    *newPtr = newStr;
    return newPtr;
}

// for test
void freeMallocedStringsInArray(Array* object){
    for (size_t i = 0; i < Size(object); ++i) {
        free(*(((char**) (object->ptr)) + i));
    }
}

// test function 3
int whereRealFunction(void* value) {
    return *((double*) value) > 5;
}

// test function 4
int whereStringFunction(void* value) {
    return strlen(*((char**) value)) < 4;
}

int RealNumberComparator(const void* value1, const void* value2) {
    return (int) (*((double*) value1) - *((double*) value2));
}

int StringComparator(const void* value1, const void* value2) {
    return strcmp(*((char**) value1), *((char**) value2)); // получаем char*, что и является началом строки
}