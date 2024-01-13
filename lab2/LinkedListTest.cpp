#include "LinkedList.h"

bool BasicComparatorForInt(const int& a, const int& b) {
    return a < b;
}

bool ReverseComparatorForInt(const int& a, const int& b) {
    return a >= b;
}

void TestLinkedList() {
    std::cout << "\n\tTest Linked List:\t\n";

    size_t size1 = 6, size2 = 4, size3 = 3;
    auto arr1 = new int[]{0, 11, 22, 33, 44, 55};
    auto arr2 = new std::string[]{"Renata", "Dora", "Tatty", "Maria"};
    auto arr3 = new double[]{1.3, 4.5, 5.21};

    //// Constructor:
    LinkedList<int> Object1(arr1, size1);
    auto* Object2 = new LinkedList<std::string>(arr2, size2);
    auto* Object3 = new LinkedList<double>(arr3, size3);

    //// Copy constructor:
    LinkedList<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object5.Print(std::cout);

    //// Move constructor:
    LinkedList<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    std::cout << std::endl;

    //// Get:
    assert(Object1.GetFirst() == 0);
    assert(Object2->GetFirst() == "Renata");
    assert(Object3->GetFirst() == 1.3);
    assert(Object4.GetFirst() == Object1.GetFirst());

    assert(Object1.GetLast() == 55);
    assert(Object2->GetLast() == "Maria");
    assert(Object3->GetLast() == 5.21);
    assert(Object4.GetLast() == Object1.GetLast());

    assert(Object1.Get(1) == 11);
    assert(Object2->Get(2) == "Tatty");
    assert(Object3->Get(1) == 4.5);
    assert(Object4.Get(4) == Object1.Get(4));

    assert(Object1.GetLength() == 6);
    assert(Object2->GetLength() == 4);
    assert(Object3->GetLength() == 3);
    assert(Object4.GetLength() == Object1.GetLength());

    {
        std::cout << "Test GetSubList function:\n";
        LinkedList<int> list1test(new int[]{11, 22, 33, 44}, 4);
        LinkedList<std::string>* list2test = new LinkedList<std::string>(new std::string[]{"Dora", "Tatty"}, 2);
        LinkedList<double>* list3test = new LinkedList<double>(new double[]{1.3, 4.5, 5.21}, 3);
        LinkedList<int> list4test(new int[]{55}, 1);

        LinkedList<int>* list1 = Object1.GetSubList(1, (int) Object1.GetLength() - 2);
        list1->Print(std::cout);

        LinkedList<std::string>* list2 = Object2->GetSubList(1, 2);
        list2->Print(std::cout);

        LinkedList<double>* list3 = Object3->GetSubList(0, 2);
        list3->Print(std::cout);

        LinkedList<int>* list4 = Object4.GetSubList(5, 5);
        list4->Print(std::cout);

        assert(*Object1.GetSubList(1, Object1.GetLength() - 2) == list1test);
        assert(*Object2->GetSubList(1, 2) == *list2test);
        assert(*Object3->GetSubList(0, Object3->GetLength() - 1) == *list3test);
        assert(*Object4.GetSubList(5, 5) == list4test);

        delete list2test;
        delete list3test;
    }
    //// Append, Prepend, InsertAt:
    Object1.Append(100);
    Object2->Append("Tagir");
    Object3->Append(7.34);
    Object4.Append(123);

    Object1.Prepend(300);
    Object2->Prepend("Tatiana Innokentievna");
    Object3->Prepend(100.125);
    Object4.Prepend(700);

    Object1.InsertAt(-150, 3);
    Object2->InsertAt("kitten", 2);
    Object3->InsertAt(900.1, 4);
    Object4.InsertAt(800, 1);

    assert(Object1.GetFirst() ==  300 && Object1.Get(3) == -150 && Object1.GetLast() == 100 && Object1.GetLength() == 9);
    assert(Object2->GetFirst() == "Tatiana Innokentievna" && Object2->Get(2) == "kitten" && Object2->GetLast() == "Tagir" && Object2->GetLength() == 7);
    assert(Object3->GetFirst() == 100.125 && Object3->Get(4) == 900.1 && Object3->GetLast() == 7.34 && Object3->GetLength() == 6);
    assert(Object4.GetFirst() == 700 && Object4.Get(1) == 800 && Object4.GetLast() == 123 && Object4.GetLength() == 9);

    Object1.Insert(299, Object1.begin());
    Object2->Insert("Varya", Object2->end());
    Object3->Insert(29.9, ++(++Object3->begin()));
    Object4.Insert(24, --Object4.end());

    assert(Object1.GetFirst() == 299);
    assert(Object2->GetLast() == "Varya");
    assert(Object3->Get(2) == 29.9);
    assert(Object4.Get(8) == 24);

    std::cout << "\nData after Append, Prepend, InsertAt and Insert functions:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object4.Print(std::cout);

    {
        LinkedList<int>* test1 = new LinkedList<int>(new int[]{1, 2, 3}, 3);
        LinkedList<int>* test2 = new LinkedList<int>(new int[]{4,  5}, 2);

        LinkedList<int>* res1 = new LinkedList<int>(new int[]{1, 2, 3, 4,  5}, 5);

        LinkedList<char>* test3 = new LinkedList<char>(new char[]{'a', 'b', 'c'}, 3);
        LinkedList<char>* test4 = new LinkedList<char>(new char[]{'x', 'y', 'z', 'w'}, 4);

        LinkedList<char>* res2 = new LinkedList<char>(new char[]{'a', 'b', 'c', 'x', 'y', 'z', 'w'}, 7);

        std::cout << "\nTest Concat function:\n";

        assert(*test1->Concat(test2) == *res1);
        assert(*test3->Concat(test4) == *res2);

        test1->Print(std::cout);
        test3->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
        delete test4;

        delete res1;
        delete res2;
    }

    {
        // MergeSort:
        std::cout << "\nData for test MergeSort function:\n";

        LinkedList<int> list1 = LinkedList<int>(new int[]{4, 7, 2, 1, 8, 9, 3, 6, 5}, 9);
        LinkedList<int> list2 = LinkedList<int>(new int[]{33, 0, -1, -100, 67, 51, 105}, 6);

        list1.Print(std::cout);
        list2.Print(std::cout);

        list1.MergeSort(list1, &BasicComparatorForInt);
        list2.MergeSort(list2, &ReverseComparatorForInt);

        std::cout << "\nData after MergeSort:\n";
        list1.Print(std::cout);
        list2.Print(std::cout);
    }

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    delete Object2;
    delete Object3;

    std::cout<< std::endl;
}