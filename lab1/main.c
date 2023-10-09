#include <stdio.h>

#include "Funcs.h"

//// 26. Динамический массив.
// Типы хранимых элементов: вещественные числа, строки.
// Операции: сортировка; map, where; конкатенация.

Ring RealNumberRing = {.objSize = sizeof(double),
        .comparator = &RealNumberComparator};

Ring StringRing = {.objSize = sizeof(char*), // sizeof(char*) потому что массив состоит из char*, т.е. char** <- наш массив строк
        .comparator = &StringComparator};

int main() {
    Array RNumberArray1;
    Array RNumberArray2;
    Array StringArray1;
    Array StringArray2;

    ArrayInitialization(&RNumberArray1, &RealNumberRing);
    ArrayInitialization(&RNumberArray2, &RealNumberRing);
    ArrayInitialization(&StringArray1, &StringRing);
    ArrayInitialization(&StringArray2, &StringRing);

    //// Set:
    // 1. Add
    double num1[5] = {1.2, 0, 10, 4.125, 0.5};
    double num2[5] = {5, -1.4, 100.7, 1.0, 7.8};
    char* str1[5] = {"one", "two", "three", "four", "five"};
    char* str2[5] = {"aaaaa", "ccc", "aBbC", "aab", "abbc"};

    for (int i = 0; i < 5; i++) {
        Set(&RNumberArray1, i, &num1[i]);
        Set(&RNumberArray2, i, &num2[i]);
        Set(&StringArray1, i, &str1[i]);
        Set(&StringArray2, i, &str2[i]);
    }

    printf("\nData before transformations:\n");
    for (int i = 0; i < Size(&RNumberArray1); i++) {
        printf("%lf\t", *((double*)(RNumberArray1.ptr + i * RNumberArray1.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&RNumberArray2); i++) {
        printf("%lf\t", *((double*)(RNumberArray2.ptr + i * RNumberArray2.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&StringArray1); i++) {
        printf("%s\t", *((char**)(StringArray1.ptr + i * StringArray1.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&StringArray2); i++) {
        printf("%s\t", *((char**)(StringArray2.ptr + i * StringArray2.objInfo->objSize)));
    }
    printf("\n");
    printf("\n");

    // 2. Changes
    double val1 = 1000.1;
    double val2 = 2000.2;
    char* val3 = "AAA";
    char* val4 = "BBB";

    Set(&RNumberArray1, 1, &val1);
    Set(&RNumberArray2, 2, &val2);
    Set(&StringArray1, 3, &val3);
    Set(&StringArray2, 4, &val4);

    printf("\nData after transformations:\n");
    for (int i = 0; i < Size(&RNumberArray1); i++) {
        printf("%lf\t", *((double*)(RNumberArray1.ptr + i * RNumberArray1.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&RNumberArray2); i++) {
        printf("%lf\t", *((double*)(RNumberArray2.ptr + i * RNumberArray2.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&StringArray1); i++) {
        printf("%s\t", *((char**)(StringArray1.ptr + i * StringArray1.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&StringArray2); i++) {
        printf("%s\t", *((char**)(StringArray2.ptr + i * StringArray2.objInfo->objSize)));
    }
    printf("\n");
    printf("\n");
    printf("\n");


    //// Size and Capacity:
    printf("Size of RNumberArray1: %zu\n", Size(&RNumberArray1));
    printf("Size of RNumberArray2: %zu\n", Size(&RNumberArray2));
    printf("Size of StringArray1: %zu\n", Size(&StringArray1));
    printf("Size of StringArray2: %zu\n", Size(&StringArray2));
    printf("\n");

    printf("Capacity of RNumberArray1: %zu\n", Capacity(&RNumberArray1));
    printf("Capacity of RNumberArray2: %zu\n", Capacity(&RNumberArray2));
    printf("Capacity of StringArray1: %zu\n", Capacity(&StringArray1));
    printf("Capacity of StringArray2: %zu\n", Capacity(&StringArray2));
    printf("\n");


    //// Sort:
    Sort(&RNumberArray1);
    Sort(&RNumberArray2);
    Sort(&StringArray1);
    Sort(&StringArray2);

    printf("\nData after sort:\n");
    for (int i = 0; i < Size(&RNumberArray1); i++) {
        printf("%lf\t", *((double*)(RNumberArray1.ptr + i * RNumberArray1.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&RNumberArray2); i++) {
        printf("%lf\t", *((double*)(RNumberArray2.ptr + i * RNumberArray2.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&StringArray1); i++) {
        printf("%s\t", *((char**)(StringArray1.ptr + i * StringArray1.objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(&StringArray2); i++) {
        printf("%s\t", *((char**)(StringArray2.ptr + i * StringArray2.objInfo->objSize)));
    }
    printf("\n");
    printf("\n");


    //// Map:
    Array* MapRNumberArray1 = Map(&RNumberArray1, &mapRNumberFunction);
    Array* MapRNumberArray2 = Map(&RNumberArray2, &mapRNumberFunction);
    Array* MapStringArray1 = Map(&StringArray1, &mapStringFunction);
    Array* MapStringArray2 = Map(&StringArray2, &mapStringFunction);

    printf("\nData after Map:\n");
    for (int i = 0; i < Size(MapRNumberArray1); i++) {
        printf("%lf\t", *((double*)(MapRNumberArray1->ptr + i * MapRNumberArray1->objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(MapRNumberArray2); i++) {
        printf("%lf\t", *((double*)(MapRNumberArray2->ptr + i * MapRNumberArray2->objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(MapStringArray1); i++) {
        printf("%s\t", *((char**)(MapStringArray1->ptr + i * MapStringArray1->objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(MapStringArray2); i++) {
        printf("%s\t", *((char**)(MapStringArray2->ptr + i * MapStringArray2->objInfo->objSize)));
    }
    printf("\n");
    printf("\n");

    freeMallocedStringsInArray(MapStringArray1);
    freeMallocedStringsInArray(MapStringArray2);


    //// Where:
    Array* WhereRNumberArray1 = Where(&RNumberArray1, &whereRealFunction);
    Array* WhereRNumberArray2 = Where(&RNumberArray2, &whereRealFunction);
    Array* WhereStringArray1 = Where(&StringArray1, &whereStringFunction);
    Array* WhereStringArray2 = Where(&StringArray2, &whereStringFunction);

    printf("\nData after Where:\n");
    for (int i = 0; i < Size(WhereRNumberArray1); i++) {
        printf("%lf\t", *((double*)(WhereRNumberArray1->ptr + i * WhereRNumberArray1->objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(WhereRNumberArray2); i++) {
        printf("%lf\t", *((double*)(WhereRNumberArray2->ptr + i * WhereRNumberArray2->objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(WhereStringArray1); i++) {
        printf("%s\t", *((char**)(WhereStringArray1->ptr + i * WhereStringArray1->objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(WhereStringArray2); i++) {
        printf("%s\t", *((char**)(WhereStringArray2->ptr + i * WhereStringArray2->objInfo->objSize)));
    }
    printf("\n");
    printf("\n");


    //// Concatenation:
    Array* ConcatRNumberArray1 = Concatenation(&RNumberArray1, &RNumberArray2);
    Array* ConcatStringArray1 = Concatenation(&StringArray1, &StringArray2);

    printf("\nData after Concatenation:\n");
    for (int i = 0; i < Size(ConcatRNumberArray1); i++) {
        printf("%lf   ", *((double*)(ConcatRNumberArray1->ptr + i * ConcatRNumberArray1->objInfo->objSize)));
    }
    printf("\n");
    for (int i = 0; i < Size(ConcatStringArray1); i++) {
        printf("%s   ", *((char**)(ConcatStringArray1->ptr + i * ConcatStringArray1->objInfo->objSize)));
    }
    printf("\n");
    printf("\n");


    //// Frees:
    Clear(&RNumberArray1);
    Clear(&RNumberArray2);
    Clear(&StringArray1);
    Clear(&StringArray2);

    Delete(MapRNumberArray1);
    Delete(MapRNumberArray2);
    Delete(MapStringArray1);
    Delete(MapStringArray2);

    Delete(WhereRNumberArray1);
    Delete(WhereRNumberArray2);
    Delete(WhereStringArray1);
    Delete(WhereStringArray2);

    Delete(ConcatRNumberArray1);
    Delete(ConcatStringArray1);


    return 0;
}
