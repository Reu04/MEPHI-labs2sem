#include "DynamicArray.h"

bool BasicComparatorForInt(const int& a, const int& b) {
    return a < b;
}

bool ReverseComparatorForInt(const int& a, const int& b) {
    return a >= b;
}

void TestDynamicArray() {
    std::cout << "\n\tTest Dynamic Array:\t\n";

    size_t size1 = 5, size2 = 7, size3 = 3;
    auto arr1 = new int[]{2, 5, 13, 7, 4};
    auto arr2 = new char[]{'a', 'b', 'c', '%', 'd', 'e', 'f'};
    auto arr3 = new double[]{1.3, 4.5, 10.99};

    //// Constructor:
    DynamicArray<int> Object1(arr1, size1);
    DynamicArray<char> Object2(arr2, size2);
    DynamicArray<double> Object3(arr3, size3);

    //// Copy constructor:
    DynamicArray<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2.Print(std::cout);
    Object3.Print(std::cout);
    Object5.Print(std::cout);

    //// Move constructor:
    DynamicArray<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    //// Get:
    assert(Object1.GetSize() == 5);
    assert(Object2.GetSize() == 7);
    assert(Object3.GetSize() == 3);
    assert(Object4.GetSize() == Object1.GetSize());

    assert(Object1.Get(0) == 2);
    assert(Object2.Get(3) == '%');
    assert((Object3.Get(Object3.GetSize() - 1)) == 10.99);

    //// Set:
    Object1.Set(0, 1000);
    Object2.Set(Object2.GetSize() - 1, 'F');
    Object3.Set(Object3.GetSize(), 3000.55);
    Object4.Set(2, 4000);

    assert(Object1[0] == 1000);
    assert(Object2[Object2.GetSize() - 1] == 'F');
    assert(Object3[Object3.GetSize() - 1] == 3000.55);
    assert(Object4[2] == 4000);

    std::cout << "\nData after transformations:\n";
    Object1.Print(std::cout);
    Object2.Print(std::cout);
    Object3.Print(std::cout);
    Object4.Print(std::cout);

    //// Operators:
    assert(Object1[0] == 1000 && Object1[1] == 5 && Object1[2] == 13 && Object1[3] == 7 && Object1[4] == 4);
    assert(Object4 < Object1);
    assert(Object1 > Object4);
    assert(Object1 != Object4);
    {
        size_t size = Object3.GetSize();
        auto arr = new double[]{1.3, 4.5, 10.99, 3000.55};
        DynamicArray<double> Object(arr, size);

        assert(Object == Object3);
        assert(Object <= Object3);
        assert(Object >= Object3);

        delete[] arr;
    }

    // MergeSort:
    Object1.MergeSort(Object1, &BasicComparatorForInt);
    Object4.MergeSort(Object4, &ReverseComparatorForInt);

    std::cout << "\nData after MergeSort:\n";
    Object1.Print(std::cout);
    Object4.Print(std::cout);

    // QuickSort:
    Object1.QuickSort(Object1, 0, Object1.GetSize() - 1, &ReverseComparatorForInt);
    Object4.QuickSort(Object4, 0, Object4.GetSize() - 1, &BasicComparatorForInt);

    std::cout << "\nData after QuickSort:\n";
    Object1.Print(std::cout);
    Object4.Print(std::cout);
    std::cout << "\n";


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
}

