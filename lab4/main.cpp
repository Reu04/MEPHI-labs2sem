#include "UI.h"

void BasicFunctionsTest() {
    std::cout << "\n\tBasic Functions Test:\n\n";

    BinarySearchTree<double>* test1 = new BinarySearchTree<double>();

    //// Insert:
    test1->Insert(4.5);
    test1->Insert(1.5);
    test1->Insert(6.5);
    test1->Insert(2.0);
    test1->Insert(3.0);
    test1->Insert(5);
    test1->Insert(7.1);
    test1->Insert(0);

    std::cout << "Size of the test1 tree: " << test1->GetSize() << std::endl;
    std::cout << "The elements of the test1 tree: ";
    test1->Print(std::cout);
    std::cout << std::endl << std::endl;

    BinarySearchTree<double>* test2 = new BinarySearchTree<double>(*test1);
    //assert(*test1 == *test2);

    size_t size1 = 5;
    int* arr1 = new int[]{34, 12, 20, 48, 15};
    BinarySearchTree<int>* test3 = new BinarySearchTree<int>(size1, arr1);
    std::cout << "Size of the test3 tree: " << test3->GetSize() << std::endl;
    std::cout << "The elements of the test3 tree: ";
    test3->Print(std::cout);
    std::cout << std::endl << std::endl;

    //// Find:
    assert(test1->Find(1.5));
    assert(!(test1->Find(10)));
    assert(test3->Find(15));
    assert(!(test3->Find(21)));

    //// Delete:
    std::cout << "Pointers to the root of the test1 tree after deletions: "
              << test1->Delete(5) << "\t" << test1->Delete(3) << std::endl;
    std::cout << "Items of the test1 after deletion: ";
    test1->Print(std::cout);
    std::cout << std::endl << std::endl;

    std::cout << "Pointer to the root of the test3 tree after deletion: " << test3->Delete(20) << std::endl;
    std::cout << "Items of the test3 after deletion: ";
    test3->Print(std::cout);
    std::cout << std::endl << std::endl;

    BinarySearchTree<double>* res1 = new BinarySearchTree<double>(6, new double[]{4.5, 1.5, 6.5, 2.0, 7.1, 0});
    assert(*test1 == *res1);

    BinarySearchTree<int>* res2 = new BinarySearchTree<int>(4,  new int[]{34, 12, 48, 15});
    assert(*test3 == *res2);


    delete test1;
    delete test2;
    delete test3;
    delete res1;
    delete res2;
}

int testMapFunc1(int obj) {
    return obj * 20;
}

double testMapFunc2(double obj) {
    return obj * 3.0;
}

char testMapFunc3(char obj) {
    if ((int) obj >= 65 && (int) obj <= 90) {
        return (char) ((int) obj + 32);
    } else if ((int) obj >= 97 && (int) obj <= 122) {
        return (char) ((int) obj - 32);
    } else {
        return obj;
    }
}

bool testWhereFunc1(int obj) {
    return obj % 3 == 0;
}

bool testWhereFunc2(double obj) {
    return obj < 15.0;
}

bool testWhereFunc3(char obj) {
    return (obj >= 'A' && obj <= 'C');
}

void BinarySearchTreeTest() {
    std::cout << "\n\tOther Functions Test:\n";

    BinarySearchTree<int>* test1 = new BinarySearchTree<int>(4,  new int[]{30, 10, 20, 40});
    BinarySearchTree<double>* test2 = new BinarySearchTree<double>(6, new double[]{4.5, 1.5, 6.5, 2.0, 7.1, 0});
    BinarySearchTree<char>* test3 = new BinarySearchTree<char>(5, new char[]{'c', 'a', 'b', 'e', 'd'});

    std::cout << "\nData before transformations:\n";
    test1->Print(std::cout);
    std::cout << std::endl;
    test2->Print(std::cout);
    std::cout << std::endl;
    test3->Print(std::cout);
    std::cout << std::endl;

    //// Map:

    BinarySearchTree<int>* testMap1 = test1->Map(&testMapFunc1, test1->GetSize());
    BinarySearchTree<double>* testMap2 = test2->Map(&testMapFunc2, test2->GetSize());
    BinarySearchTree<char>* testMap3 = test3->Map(&testMapFunc3, test3->GetSize());

    BinarySearchTree<int>* res1 = new BinarySearchTree<int>(4,  new int[]{600, 200, 400, 800});
    BinarySearchTree<double>* res2 = new BinarySearchTree<double>(6, new double[]{13.5, 4.5, 19.5, 6.0, 21.3, 0});
    BinarySearchTree<char>* res3 = new BinarySearchTree<char>(5, new char[]{'C', 'A', 'B', 'E', 'D'});

    assert(*testMap1 == *res1);
    assert(*testMap3 == *res3);

    std::cout << "\nData after Map:\n";
    testMap1->Print(std::cout);
    std::cout << std::endl;
    testMap2->Print(std::cout);
    std::cout << std::endl;
    testMap3->Print(std::cout);
    std::cout << std::endl;

    //// Where:

    BinarySearchTree<int>* testWhere1 = res1->Where(&testWhereFunc1);
    BinarySearchTree<double>* testWhere2 = res2->Where(&testWhereFunc2);
    BinarySearchTree<char>* testWhere3 = res3->Where(&testWhereFunc3);

    std::cout << "\nData after Where:\n";
    testWhere1->Print(std::cout);
    std::cout << std::endl;
    testWhere2->Print(std::cout);
    std::cout << std::endl;
    testWhere3->Print(std::cout);
    std::cout << std::endl;

    std::cout << "\nData after Concat:\n";
    BinarySearchTree<int>* testConcat = new BinarySearchTree<int>(4,  new int[]{1, 2, 3, 4});
    testMap1->Concat(testConcat);
    testMap1->Print(std::cout);
    std::cout << std::endl;

    //// GetNodeSize:
    std::cout << "\nGetNodeSize:\n";
    std::cout << test1->GetSize() << std::endl;
    std::cout << BinarySearchTree<int>::getNodeSize(test1->getRoot()) << std::endl;

    delete test1;
    delete test2;
    delete test3;

    delete testMap1;
    delete testMap2;
    delete testMap3;

    delete res1;
    delete res2;
    delete res3;

    delete testWhere1;
    delete testWhere2;
    delete testWhere3;

    delete testConcat;
}

int main() {
    BasicFunctionsTest();
    BinarySearchTreeTest();

    UserInterface();

    return 0;
}
