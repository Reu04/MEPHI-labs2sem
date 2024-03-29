#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#include "LinkedList.h"

template<typename T>
LinkedList<T>::LinkedList() : head_(new Node<T>()), tail_(new Node<T>()), size_(0) {};

template<typename T>
LinkedList<T>::LinkedList(T *item, size_t count) : head_(new Node<T>()), tail_(new Node<T>()), size_(count) {
    Iterator it = begin();
    it.curr_->data_ = item[0];
    for (size_t i = 1; i < count; i++) {
        auto *newNode = new Node<T>;
        it.curr_->next_ = newNode;
        newNode->prev_ = it.curr_;
        newNode->data_ = item[i];
        ++it;
    }
    it.curr_->next_ = tail_;
    tail_->prev_ = it.curr_;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList &other) : head_(new Node<T>()), tail_(new Node<T>()), size_(other.size_) {
    Iterator it1 = begin();
    Iterator it2 = other.begin();
    it1.curr_->data_ = it2.curr_->data_;
    for (size_t i = 1; i < other.size_; i++) {
        ++it2;
        auto *newNode = new Node<T>;
        it1.curr_->next_ = newNode;
        newNode->prev_ = it1.curr_;
        newNode->data_ = it2.curr_->data_;
        ++it1;
    }
    it1.curr_->next_ = tail_;
    tail_->prev_ = it1.curr_;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList &&other) : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

template<typename T>
LinkedList<T>::LinkedList(Iterator lhs, Iterator rhs) : head_(new Node<T>()), tail_(new Node<T>()) {
    if (lhs == rhs) {
        return;
    }
    head_->data_ = lhs.curr_->data_;
    size_t elemCount = 1;

    Iterator itPrev = begin();
    ++lhs;
    while (lhs != rhs) {
        auto *newNode = new Node<T>;
        newNode->data_ = lhs.curr_->data_;
        newNode->prev_ = itPrev.curr_;
        elemCount++;

        itPrev.curr_->next_ = newNode;
        ++itPrev;
        ++lhs;
    }
    tail_->prev_ = itPrev.curr_;
    itPrev.curr_->next_ = tail_;

    size_ = elemCount;
}

//////////

template<typename T>
bool LinkedList<T>::operator<(const LinkedList &other) const {
    Iterator it1 = begin();
    Iterator it2 = other.begin();
    for (size_t i = 0; i < std::min(size_, other.size_); i++) {
        if (it1.curr_->data_ < it2.curr_->data_) {
            return true;
        }
        if (it1.curr_->data_ > it2.curr_->data_) {
            return false;
        }
        ++it1;
        ++it2;
    }
    return GetLength() < other.GetLength();
}

template<typename T>
bool LinkedList<T>::operator>(const LinkedList &other) const {
    return other < *this;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList &other) const {
    return !(*this < other) && !(*this > other);
}

template<typename T>
bool LinkedList<T>::operator!=(const LinkedList &other) const {
    return !(*this == other);
}

template<typename T>
bool LinkedList<T>::operator<=(const LinkedList &other) const {
    return (*this < other || *this == other);
}

template<typename T>
bool LinkedList<T>::operator>=(const LinkedList &other) const {
    return (*this > other || *this == other);
}

//////////

template<typename T>
void LinkedList<T>::Clear() {
    Node<T>* current = head_;
    while (current != nullptr) {
        Node<T>* next = current->next_;
        delete current;
        current = next;
    }

    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

/////////

template<typename T>
T LinkedList<T>::GetFirst() const {
    if (head_ == nullptr) {
        throw std::runtime_error("IndexOutOfRange");
    }
    return head_->data_;
}

template<typename T>
T LinkedList<T>::GetLast() const {
    if (tail_->prev_ == nullptr) {
        throw std::runtime_error("IndexOutOfRange");
    }
    return tail_->prev_->data_;
}

template<typename T>
T LinkedList<T>::Get(int index) const {
    Iterator it = begin();
    for (int i = 0; i < index; i++) {
        if (it.curr_ == nullptr || it.curr_->next_->next_ == nullptr) {
            throw std::runtime_error("IndexOutOfRange");
        }
        ++it;
    }
    return it.curr_->data_;
}

template<typename T>
LinkedList<T> *LinkedList<T>::GetSubList(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex < 0 || startIndex >= GetLength() || endIndex >= GetLength()) {
        throw std::runtime_error("IndexOutOfRange");
    }
    size_t size = endIndex - startIndex + 1;
    size_t index = 0;
    T *arr = new T[size];
    Iterator it = begin();
    for (int i = 0; i <= endIndex; i++) {
        if (i >= startIndex) {
            arr[index] = it.curr_->data_;
            index++;
        }
        ++it;
    }
    auto *res = new LinkedList<T>(arr, size);
    return res;
}

template<typename T>
size_t LinkedList<T>::GetLength() const {
    return size_;
}

//////////

template<typename T>
void LinkedList<T>::Append(const T &item) {
    auto *newTail = new Node<T>;
    newTail->data_ = item;
    if (tail_ == nullptr) {
        tail_ = new Node<T>;
    }
    newTail->next_ = tail_;
    if (head_ == nullptr) {
        head_ = newTail;
        tail_->prev_ = newTail;
    } else {
        newTail->prev_ = tail_->prev_;
        tail_->prev_->next_ = newTail;
        tail_->prev_ = newTail;
    }
    size_++;
}

template<typename T>
void LinkedList<T>::Prepend(const T &item) {
    if (head_ == nullptr) {
        Append(item);
        size_++;
        return;
    }
    auto *newHead = new Node<T>();
    newHead->next_ = head_;
    newHead->data_ = item;
    head_->prev_ = newHead;
    head_ = newHead;
    size_++;
}

template<typename T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0) {
        throw std::runtime_error("IndexOutOfRange");
    }
    Iterator it = begin();
    for (int i = 0; i < index; i++) {
        if (it.curr_->next_->next_ == nullptr) {
            throw std::runtime_error("IndexOutOfRange");
        }
        ++it;
    }
    auto *newNode = new Node<T>;
    newNode->data_ = item;
    if (it == begin()) {
        newNode->next_ = it.curr_;
        it.curr_->prev_ = newNode;
        head_ = newNode;
        return;
    }
    newNode->prev_ = it.curr_->prev_;
    (it.curr_->prev_)->next_ = newNode;

    newNode->next_ = it.curr_;
    it.curr_->prev_ = newNode;

    size_++;
}

template<typename T>
void LinkedList<T>::Insert(T item, Iterator it) {
    if (it == static_cast<const Iterator>(nullptr)) {
        return;
    }
    if (it.curr_ == head_) { // push front
        if (head_ == nullptr) {
            it.curr_->data_ = item;
            it.curr_->next_ = tail_;
            tail_->prev_ = it.curr_;
            head_ = it.curr_;
            size_++;
            return;
        }
        auto *newNode = new Node<T>;
        newNode->data_ = item;
        newNode->next_ = head_;
        head_->prev_ = newNode;
        head_ = newNode;
        size_++;
    } else if (it.curr_ == tail_) { // push back
        auto *newNode = new Node<T>;
        newNode->data_ = item;
        newNode->next_ = tail_;
        newNode->prev_ = tail_->prev_;
        tail_->prev_->next_ = newNode;
        tail_->prev_ = newNode;
        size_++;
    } else { // insert in the middle
        auto *newNode = new Node<T>;
        newNode->data_ = item;
        newNode->prev_ = it.curr_->prev_;
        (it.curr_->prev_)->next_ = newNode;
        newNode->next_ = it.curr_;
        it.curr_->prev_ = newNode;
        size_++;
    }
}

template<typename T>
LinkedList<T> *LinkedList<T>::Concat(LinkedList<T> *other) {
    T *resArr = new T[size_ + other->size_];
    size_t index = 0;
    for (size_t i = 0; i < size_; i++) {
        resArr[index] = Get(i);
        index++;
    }
    for (size_t i = 0; i < other->size_; i++) {
        resArr[index] = other->Get(i);
        index++;
    }
    auto *res = new LinkedList(resArr, size_ + other->size_);
    delete[] resArr;
    return res;
}

template<typename T>
void LinkedList<T>::Print(std::ostream &buff) const {
    Iterator it = begin();
    for (size_t i = 0; i < size_; i++) {
        buff << it.curr_->data_ << "\t";
        ++it;
    }
    buff << std::endl;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Iterator it = begin();
    if (it.curr_ != nullptr) {
        while (it.curr_->next_ != nullptr) {
            auto *temp = it.curr_;
            ++it;
            delete temp;
        }
        delete it.curr_;
    }
}

template<typename T>
void LinkedList<T>::MergeSort(LinkedList<T> &origin, bool (*comp)(const T &, const T &)) {
    if (origin.GetLength() > 1) {
        LinkedList<T> list1(origin.begin(), origin.begin() + (origin.GetLength() / 2));
        MergeSort(list1, comp);
        LinkedList<T> list2(origin.begin() + (origin.GetLength() / 2), origin.end());
        MergeSort(list2, comp);
        Merge(origin, list1, list2, comp);
    }
}

template
class LinkedList<int>;

template
class LinkedList<double>;

template
class LinkedList<std::string>;

template
class LinkedList<char>;