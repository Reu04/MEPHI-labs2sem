//// Для реализации необходимо использовать возможности ООП и шаблонов C++
/// Для реализации используется инкапсуляция DynamicArray и делегирование ему большей части работы.

//// Все реализованные классы и основные алгоритмы необходимо покрыть (модульными) тестами.
/// Реализацию следует оснастить пользовательским интерфейсом (консольным) для проверки корректности реализации.


#include <iostream>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>
#include "functional"

#include "ArraySequence.h"
#include "LinkedListSequence.h"

#include "UserInterface.h"
#include "UIforBaseCollections.h"

bool BasicComparatorForInt(const int& a, const int& b);
bool ReverseComparatorForInt(const int& a, const int& b);

void TestDynamicArray();
void TestLinkedList();

//////

void TestArraySequence() {
    std::cout << "\n\tTest Array Sequence:\t\n";

    //// Constructor:
    ArraySequence<int> Object1(new int[]{1, 2, 3, 4}, 4);
    ArraySequence<char>* Object2 = new ArraySequence<char>(new char[]{'R', 'e', 'n', 'a', 't', 'a'}, 6);
    ArraySequence<double>* Object3 = new ArraySequence<double>(new double[]{0, 1.1, 2.2}, 3);

    //// Copy constructor:
    ArraySequence<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object5.Print(std::cout);


    //// Move constructor:
    ArraySequence<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    //// Get:
    assert(Object1.GetFirst() == 1);
    assert(Object2->GetFirst() == 'R');
    assert(Object3->GetFirst() == 0);
    assert(Object4.GetFirst() == 1);

    assert(Object1.GetLast() == 4);
    assert(Object2->GetLast() == 'a');
    assert(Object3->GetLast() == 2.2);
    assert(Object4.GetLast() == 4);

    assert(Object1.Get(1) == 2);
    assert(Object2->Get(3) == 'a');
    assert((Object3->Get(Object3->GetLength() - 2)) == 1.1);


    {
        //// GetSubsequence:
        Sequence<int>* test1 = new ArraySequence<int>(new int[]{2, 3}, 2);
        Sequence<char>* test2 = new ArraySequence<char>(new char[]{'a', 't', 'a'}, 3);
        Sequence<double>* test3 = new ArraySequence<double>(new double[]{0, 1.1, 2.2}, 3);

        assert(*dynamic_cast<ArraySequence<int>*>(Object1.GetSubsequence(1, 2))
                == *dynamic_cast<ArraySequence<int>*>(test1));

        assert(*dynamic_cast<ArraySequence<char>*>(Object2->GetSubsequence(3, 5))
                == *dynamic_cast<ArraySequence<char>*>(test2));

        assert(*dynamic_cast<ArraySequence<double>*>(Object3->GetSubsequence(0, 2))
                == *dynamic_cast<ArraySequence<double>*>(test3));

        assert(*dynamic_cast<ArraySequence<int>*>(Object4.GetSubsequence(0, 2))
                == *dynamic_cast<ArraySequence<int>*>(Object1.GetSubsequence(0, 2)));

        std::cout << "\nTest GetSubsequence function:\n";
        Object1.GetSubsequence(1, 2)->Print(std::cout);
        Object2->GetSubsequence(3, 5)->Print(std::cout);
        Object3->GetSubsequence(0, 2)->Print(std::cout);
        Object4.GetSubsequence(0, 2)->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
    }


    assert(Object1.GetLength() == 4);
    assert(Object2->GetLength() == 6);
    assert(Object3->GetLength() == 3);
    assert(Object4.GetLength() == Object1.GetLength());

    //// Append, Prepend, InsertAt:
    Object1.Append(1000);
    Object2->Append('F');
    Object3->Append(3000.55);
    Object4.Append(4000);

    assert(Object1.GetLast() == 1000);
    assert(Object2->GetLast() == 'F');
    assert(Object3->GetLast() == 3000.55);
    assert(Object4.GetLast() == 4000);

    Object1.Prepend(0);
    Object2->Prepend('B');
    Object3->Prepend(-1.1);
    Object4.Prepend(0);

    assert(Object1.GetFirst() == 0);
    assert(Object2->GetFirst() == 'B');
    assert(Object3->GetFirst() == -1.1);
    assert(Object4.GetFirst() == 0);

    Object1.InsertAt(1, 1);
    Object2->InsertAt('P', 0);
    Object3->InsertAt(3.3, Object3->GetLength() - 1);
    Object4.InsertAt(300, 1);

    assert(Object1.Get(1) == 1);
    assert(Object2->Get(0) == 'P');
    assert(Object3->Get(Object3->GetLength() - 1) == 3.3);
    assert(Object4.Get(1) == 300);

    std::cout << "\nData after transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object4.Print(std::cout);

    {
        //// Concat:
        Sequence<int>* test1 = new ArraySequence<int>(new int[]{15, 25}, 2);
        Sequence<int>* test2 = new ArraySequence<int>(new int[]{35, 45}, 2);

        Sequence<int>* res1 = new ArraySequence<int>(new int[]{15, 25, 35, 45}, 4);

        Sequence<char>* test3 = new ArraySequence<char>(new char[]{'T', 'a', 'g'}, 3);
        Sequence<char>* test4 = new ArraySequence<char>(new char[]{'i', 'r'}, 2);

        Sequence<char>* res2 = new ArraySequence<char>(new char[]{'T', 'a', 'g', 'i', 'r'}, 5);
        assert(*dynamic_cast<ArraySequence<int>*>(test1->Concat(test2))
               == *dynamic_cast<ArraySequence<int>*>(res1));
        assert(*dynamic_cast<ArraySequence<char>*>(test3->Concat(test4))
               == *dynamic_cast<ArraySequence<char>*>(res2));

        std::cout << "\nTest Concat function:\n";
        test1->Concat(test2)->Print(std::cout);
        test3->Concat(test4)->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
        delete test4;

        delete res1;
        delete res2;
    }

    // TODO test for MergeSort for Seq = new ArraySeq

    delete Object2;
    delete Object3;
}

void TestLinkedListSequence() {
    std::cout << "\n\tLinked List Sequence:\t\n";

    //// Constructor:
    LinkedListSequence<int> Object1(new int[]{1, 2, 3, 4}, 4);
    auto* Object2 = new LinkedListSequence<char>(new char[]{'R', 'e', 'n', 'a', 't', 'a'}, 6);
    auto* Object3 = new LinkedListSequence<double>(new double[]{0, 1.1, 2.2}, 3);

    //// Copy constructor:
    LinkedListSequence<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object5.Print(std::cout);

    //// Move constructor:
    LinkedListSequence<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    //// Get:
    assert(Object1.GetFirst() == 1);
    assert(Object2->GetFirst() == 'R');
    assert(Object3->GetFirst() == 0);
    assert(Object4.GetFirst() == 1);

    assert(Object1.GetLast() == 4);
    assert(Object2->GetLast() == 'a');
    assert(Object3->GetLast() == 2.2);
    assert(Object4.GetLast() == 4);

    assert(Object1.Get(1) == 2);
    assert(Object2->Get(3) == 'a');
    assert((Object3->Get(Object3->GetLength() - 2)) == 1.1);

    {
        //// GetSubsequence:
        Sequence<int>* test1 = new LinkedListSequence<int>(new int[]{2, 3}, 2);
        Sequence<char>* test2 = new LinkedListSequence<char>(new char[]{'a', 't', 'a'}, 3);
        Sequence<double>* test3 = new LinkedListSequence<double>(new double[]{0, 1.1, 2.2}, 3);

        assert(*dynamic_cast<LinkedListSequence<int>*>(Object1.GetSubsequence(1, 2))
               == *dynamic_cast<LinkedListSequence<int>*>(test1));

        assert(*dynamic_cast<LinkedListSequence<char>*>(Object2->GetSubsequence(3, 5))
               == *dynamic_cast<LinkedListSequence<char>*>(test2));

        assert(*dynamic_cast<LinkedListSequence<double>*>(Object3->GetSubsequence(0, 2))
               == *dynamic_cast<LinkedListSequence<double>*>(test3));

        assert(*dynamic_cast<LinkedListSequence<int>*>(Object4.GetSubsequence(0, 2))
               == *dynamic_cast<LinkedListSequence<int>*>(Object1.GetSubsequence(0, 2)));

        std::cout << "\nTest GetSubsequence function:\n";
        Object1.GetSubsequence(1, 2)->Print(std::cout);
        Object2->GetSubsequence(3, 5)->Print(std::cout);
        Object3->GetSubsequence(0, 2)->Print(std::cout);
        Object4.GetSubsequence(0, 2)->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
    }

    assert(Object1.GetLength() == 4);
    assert(Object2->GetLength() == 6);
    assert(Object3->GetLength() == 3);
    assert(Object4.GetLength() == Object1.GetLength());

    //// Append, Prepend, InsertAt:
    Object1.Append(1000);
    Object2->Append('F');
    Object3->Append(3000.55);
    Object4.Append(4000);

    assert(Object1.GetLast() == 1000);
    assert(Object2->GetLast() == 'F');
    assert(Object3->GetLast() == 3000.55);
    assert(Object4.GetLast() == 4000);

    Object1.Prepend(0);
    Object2->Prepend('B');
    Object3->Prepend(-1.1);
    Object4.Prepend(0);

    assert(Object1.GetFirst() == 0);
    assert(Object2->GetFirst() == 'B');
    assert(Object3->GetFirst() == -1.1);
    assert(Object4.GetFirst() == 0);

    Object1.InsertAt(1, 1);
    Object2->InsertAt('P', 0);
    Object3->InsertAt(3.3, Object3->GetLength() - 1);
    Object4.InsertAt(300, 1);

    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object4.Print(std::cout);

    assert(Object1.Get(1) == 1);
    assert(Object2->Get(0) == 'P');
    assert(Object3->Get(Object3->GetLength() - 2) == 3.3);
    assert(Object4.Get(1) == 300);

    std::cout << "\nData after transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object4.Print(std::cout);

    {
        //// Concat:
        Sequence<int>* test1 = new LinkedListSequence<int>(new int[]{15, 25}, 2);
        Sequence<int>* test2 = new LinkedListSequence<int>(new int[]{35, 45}, 2);

        Sequence<int>* res1 = new LinkedListSequence<int>(new int[]{15, 25, 35, 45}, 4);

        Sequence<char>* test3 = new LinkedListSequence<char>(new char[]{'T', 'a', 'g'}, 3);
        Sequence<char>* test4 = new LinkedListSequence<char>(new char[]{'i', 'r'}, 2);

        Sequence<char>* res2 = new LinkedListSequence<char>(new char[]{'T', 'a', 'g', 'i', 'r'}, 5);

        assert(*dynamic_cast<LinkedListSequence<int>*>(test1->Concat(test2))
               == *dynamic_cast<LinkedListSequence<int>*>(res1));
        assert(*dynamic_cast<LinkedListSequence<char>*>(test3->Concat(test4))
               == *dynamic_cast<LinkedListSequence<char>*>(res2));

        std::cout << "\nTest Concat function:\n";
        test1->Concat(test2)->Print(std::cout);
        test3->Concat(test4)->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
        delete test4;

        delete res1;
        delete res2;
    }

    delete Object2;
    delete Object3;
}

//////

struct PersonID {
    int series;
    int number;
    std::string name_;
    std::string surname_;
    std::string patronymic_;

    std::string getPassport() const{
        return std::to_string(series) + " " + std::to_string(number);
    }
};

class Student{
private:
    PersonID id_;
    std::string university_;
    std::string group_;
    size_t year_;
    size_t age_;
    size_t recordBookID_;
public:
    Student() = default;
    Student(const PersonID& id, std::string&& university, std::string&& group, size_t year, size_t age, size_t recordBookID) :
            id_(id), university_(std::move(university)), group_(std::move(group)), year_(year), age_(age), recordBookID_(recordBookID) {};
    Student(const Student& other): id_(other.id_), university_(other.university_), group_(other.group_), year_(other.year_), age_(other.age_), recordBookID_(other.recordBookID_) {};

    PersonID getID() const {
        return id_;
    }
    std::string getName() const {
        return id_.name_;
    }
    std::string getSurname() const {
        return id_.surname_;
    }
    std::string getPatronymic() const {
        return id_.patronymic_;
    }
    std::string getGroup() const {
        return group_;
    }
    size_t getYear() const {
        return year_;
    }
    size_t getAge() const {
        return age_;
    }
    size_t getRecordBookID() const {
        return recordBookID_;
    }
    std::string getPassport() const {
        return id_.getPassport();
    }
    void setID(PersonID&& id) {
        id_ = std::move(id);
    }

    void setGroup(std::string&& group) {
        group_ = std::move(group);
    }

    bool operator==(const Student& other) const {
        return id_.series == other.id_.series && id_.number == other.id_.number;
    }
    bool operator!=(const Student& other) const {
        return !(*this == other);
    }
    bool operator<(const Student& other) const {
        return id_.series < other.id_.series || (id_.series == other.id_.series && id_.number < other.id_.number);
    }
    bool operator>(const Student& other) const {
        return id_.series > other.id_.series || (id_.series == other.id_.series && id_.number > other.id_.number);
    }
    bool operator<=(const Student& other) const {
        return !(*this > other);
    }
    bool operator>=(const Student& other) const {
        return !(*this < other);
    }
};

class Teacher{
private:
    PersonID id_;
    std::string university_;
    std::string position_;
    size_t age_;
public:
    Teacher() = default;
    Teacher(const PersonID& id, std::string&& university, std::string&& position, size_t age) :
            id_(id), university_(std::move(university)), position_(std::move(position)), age_(age) {};
    Teacher(const Teacher& other): id_(other.id_), university_(other.university_), position_(other.position_), age_(other.age_) {};

    PersonID getID() const {
        return id_;
    }
    std::string getName() const {
        return id_.name_;
    }
    std::string getSurname() const {
        return id_.surname_;
    }
    std::string getPatronymic() const {
        return id_.patronymic_;
    }
    std::string getPosition() const {
        return position_;
    }
    size_t getAge() const {
        return age_;
    }
    std::string getPassport() const {
        return id_.getPassport();
    }
    void setID(PersonID&& id) {
        id_ = std::move(id);
    }
    void setPosition(std::string&& position) {
        position_ = std::move(position);
    }
    bool operator==(const Teacher& other) const {
        return id_.series == other.id_.series && id_.number == other.id_.number;
    }
    bool operator!=(const Teacher& other) const {
        return !(*this == other);
    }
    bool operator<(const Teacher& other) const {
        return id_.series < other.id_.series || (id_.series == other.id_.series && id_.number < other.id_.number);
    }
    bool operator>(const Teacher& other) const {
        return id_.series > other.id_.series || (id_.series == other.id_.series && id_.number > other.id_.number);
    }
    bool operator<=(const Teacher& other) const {
        return !(*this > other);
    }
    bool operator>=(const Teacher& other) const {
        return !(*this < other);
    }
};

struct MyFunction {
    std::function<void()> function;
    std::string name;
    MyFunction() = default;
    MyFunction(std::function<void()>  func, const std::string& funcName) : function(std::move(func)), name(funcName) {}
    MyFunction(const MyFunction& other) : function(other.function), name(other.name) {}

    void operator()() {
        function();
    }

    friend std::ostream& operator<<(std::ostream& os, const MyFunction& func) {
        os << "Function Name: " << func.name;
        return os;
    }

    bool operator==(const MyFunction& other) const {
        return name == other.name;
    }
    bool operator!=(const MyFunction& other) const {
        return !(*this == other);
    }
    bool operator<(const MyFunction& other) const {
        return name < other.name;
    }
    bool operator>(const MyFunction& other) const {
        return name > other.name;
    }
    bool operator<=(const MyFunction& other) const {
        return !(*this > other);
    }
    bool operator>=(const MyFunction& other) const {
        return !(*this < other);
    }
};

//////

int testMapFunc1(int obj) {
    return obj * 20;
}

double testMapFunc2(double obj) {
    return obj * -1.0;
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
    return obj % 2 == 0;
}

bool testWhereFunc2(double obj) {
    return obj < 3.0;
}

bool testWhereFunc3(char obj) {
    return ((int) obj >= 97 && (int) obj <= 122);
}

int testReduceFunc1(int a, int b) {
    return a * 2 + b * 3;
}

double testReduceFunc2(double a, double b) {
    return a / 2 + b;
}

char testReduceFunc3(char a, char b) {
    return (a < b ? a : b);
}

//////

void TestDeque() {

    std::cout << "\n\tTest Deque:\t\n";

    size_t size1 = 5, size2 = 7, size3 = 3;
    int arr1[] = {2, 4, 3, 5, 6};
    char arr2[7] = {'b', 'd', 'c', 'e', 'f', 'g', 'h'};
    double arr3[] = {2.2, 0.0, 4.4};

    //// Constructor:
    Deque<int> Object1(size1, arr1);
    Deque<char> Object2(size2, arr2);
    Deque<double> Object3(size3, arr3);

    //// Copy constructor:
    Deque<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2.Print(std::cout);
    Object3.Print(std::cout);
    Object5.Print(std::cout);

    //// Move constructor:
    Deque<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    //// Get:
    assert(Object1.GetSize() == 5);
    assert(Object2.GetSize() == 7);
    assert(Object3.GetSize() == 3);
    assert(Object4.GetSize() == Object1.GetSize());

    assert(Object1.Front() == 2);
    assert(Object2.Front() == 'b');
    assert((Object3.Front()) == 2.2);

    assert(Object1.Back() == 6);
    assert(Object2.Back() == 'h');
    assert(Object3.Back() == 4.4);

    //// PushBack, PushFront:
    Object1.PushBack(7);
    Object2.PushBack('J');
    Object3.PushBack(5.5);
    Object4.PushBack(7);

    assert(Object1.Back() == 7);
    assert(Object2.Back() == 'J');
    assert(Object3.Back() == 5.5);
    assert(Object4.Back() == 7);

    Object1.PushFront(1);
    Object2.PushFront('A');
    Object3.PushFront(-1.1);
    Object4.PushFront(-1);

    assert(Object1.Front() == 1);
    assert(Object2.Front() == 'A');
    assert(Object3.Front() == -1.1);
    assert(Object4.Front() == -1);

    std::cout << "\nData after ~first~ transformations:\n";
    Object1.Print(std::cout);
    Object2.Print(std::cout);
    Object3.Print(std::cout);
    Object4.Print(std::cout);

    //// PopFront and the correct logic of the ring buffer operation:

    Object1.PopFront();
    Object2.PopFront();
    Object3.PopFront();
    Object4.PopFront();

    Object1.PushBack(1000);
    Object2.PushBack('Z');
    Object3.PushBack(1.1111);
    Object4.PushBack(1000);

    std::cout << "\nData after ~second~ transformations:\n";
    Object1.Print(std::cout);
    Object2.Print(std::cout);
    Object3.Print(std::cout);
    Object4.Print(std::cout);

    //// Empty:
    assert(!Object1.Empty());
    assert(!Object2.Empty());
    assert(!Object3.Empty());
    assert(!Object4.Empty());

    //// Sort:
    Object1.Sort();
    Object2.Sort();
    Object3.Sort();
    Object4.Sort();

    std::cout << "\nData after Sort:\n";
    Object1.Print(std::cout);
    Object2.Print(std::cout);
    Object3.Print(std::cout);
    Object4.Print(std::cout);

    {
        //// Map:
        Deque<int>* res1 = Object1.Map(&testMapFunc1);
        Deque<char>* res2 = Object2.Map(&testMapFunc3);
        Deque<double>* res3 = Object3.Map(&testMapFunc2);
        Deque<int>* res4 = Object4.Map(&testMapFunc1);

        std::cout << "\nData after Map:\n";
        res1->Print(std::cout);
        res2->Print(std::cout);
        res3->Print(std::cout);
        res4->Print(std::cout);

        delete res1;
        delete res2;
        delete res3;
        delete res4;
    }

    {
        //// Where:
        Deque<int>* res1 = Object1.Where(&testWhereFunc1);
        Deque<char>* res2 = Object2.Where(&testWhereFunc3);
        Deque<double>* res3 = Object3.Where(&testWhereFunc2);
        Deque<int>* res4 = Object4.Where(&testWhereFunc1);

        std::cout << "\nData after Where:\n";
        res1->Print(std::cout);
        res2->Print(std::cout);
        res3->Print(std::cout);
        res4->Print(std::cout);

        delete res1;
        delete res2;
        delete res3;
        delete res4;
    }

    {
        //// Reduce:
        int a1[] = {1, 2, 3};
        char a2[] = {'b', 'a', 'c', 'v'};
        double a3[] = {1.1, 2.2, 3.3, 4.4, 5.5};

        Deque<int>* test1 = new Deque<int>(3, a1);
        Deque<char>* test2 = new Deque<char>(4, a2);
        Deque<double>* test3 = new Deque<double>(5, a3);

        assert(test1->Reduce(&testReduceFunc1, 4) == 144);
        assert(test2->Reduce(&testReduceFunc3, 'a') == 'a');
        assert(test3->Reduce(&testReduceFunc2, 2.5) == 10.75);

        delete test1;
        delete test2;
        delete test3;
    }

    {
        //// Concat:
        Deque<int>* test1 = new Deque<int>(2, new int[]{15, 25});
        Deque<int>* test2 = new Deque<int>(2, new int[]{35, 45});

        Deque<int>* res1 = new Deque<int>(4, new int[]{15, 25, 35, 45});

        Deque<char>* test3 = new Deque<char>(3, new char[]{'T', 'a', 'g'});
        Deque<char>* test4 = new Deque<char>(2, new char[]{'i', 'r'});

        Deque<char>* res2 = new Deque<char>(5, new char[]{'T', 'a', 'g', 'i', 'r'});
//            assert(*dynamic_cast<Deque<int>*>(test1->Concat(test2))
//                   == *dynamic_cast<ArraySequence<int>*>(res1));
//            assert(*dynamic_cast<ArraySequence<char>*>(test3->Concat(test4))
//                   == *dynamic_cast<ArraySequence<char>*>(res2));

        std::cout << "\nTest Concat function:\n";
        test1->Concat(test2)->Print(std::cout);
        test3->Concat(test4)->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
        delete test4;

        delete res1;
        delete res2;
    }

    {
        //// GetSubsequence:
        Deque<int>* test1 = new Deque<int>(4, new int[]{15, 25, 35, 45});
        Deque<int>* test2 = new Deque<int>(10, new int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

        Deque<int>* res1 = new Deque<int>(2, new int[]{25, 35});
        Deque<int>* res2 = new Deque<int>(3, new int[]{7, 8, 9});

        std::cout << "\nTest GetSubsequence function:\n";
        test1->GetSubsequence(1, 2)->Print(std::cout);
        test2->GetSubsequence(7, 9)->Print(std::cout);

        delete test1;
        delete test2;

        delete res1;
        delete res2;
    }

    {
        //// Find:
        Deque<int>* test1 = new Deque<int>(6, new int[]{0, 1, 2, 3, 4, 5});
        Deque<int>* sub1 = new Deque<int>(2, new int[]{4, 5});

        Deque<char>* test2 = new Deque<char>(7, new char[]{'o', 'h','s', 'u', 'n', 'n', 'y'});
        Deque<char>* sub2 = new Deque<char>(3, new char[]{'s', 'u', 'n'});

        assert(test1->Find(sub1));
        assert(test2->Find(sub2));
        assert(Object1.Find(sub1));

        delete test1;
        delete test2;
        delete sub1;
        delete sub2;
    }

    {
        //// MergeFunc:
        Deque<int>* test1 = new Deque<int>(3, new int[]{1, 2, 3});
        Deque<int>* test2 = new Deque<int>(4, new int[]{2, 3, 4, 5});

        Deque<char>* test3 = new Deque<char>(3, new char[]{'a', 'b', 'c'});
        Deque<char>* test4 = new Deque<char>(4, new char[]{'b', 'c', 'd', 'e'});

        std::cout << "\nTest Merge function:\n";
        test1->MergeFunc(test2)->Print(std::cout);
        test3->MergeFunc(test4)->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
        delete test4;
    }

    {
        //// Deque<MyFunction>:

        std::cout << "\nTest Deque<MyFunction>:\n";

        MyFunction func1([]() {
            std::cout << "Hello from Function 1!" << std::endl;
        }, "a");
        MyFunction func2([]() {
            std::cout << "Hello from Function 2!" << std::endl;
        }, "b");
        MyFunction func3([]() {
            std::cout << "Hello from Function 3!" << std::endl;
        }, "c");
        MyFunction func4([]() {
            std::cout << "Hello from Function 4!" << std::endl;
        }, "d");
        MyFunction func5([]() {
            std::cout << "Hello from Function 5!" << std::endl;
        }, "e");
        MyFunction func6([]() {
            std::cout << "Hello from Function 6!" << std::endl;
        }, "f");

        Deque<MyFunction> fdeque;
        fdeque.PushBack(func5);
        fdeque.PushBack(func3);
        fdeque.PushBack(func6);
        fdeque.PushBack(func4);
        fdeque.PushBack(func1);
        fdeque.PushBack(func2);

        fdeque.Print(std::cout);

        fdeque.Sort();

        fdeque.Print(std::cout);
    }

}

int main() {
    TestDynamicArray();

//    TestArraySequence();
//    TestLinkedListSequence();

//    TestDeque();

    {
        std::cout << "\nIf you want to create a Sequence object - enter 1,\nIf you want to create DynamicArray or other base collection - enter 2: " << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            UserInterface();
        } else if (choice == 2) {
            UIforBaseCollections();
        } else {
            std::cout << "Incorrect input!" << std::endl;
        }
    }

    return 0;
}
