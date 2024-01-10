#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

template<typename T>
struct Node {
    T data_;
    Node<T>* next_ = nullptr;
    Node<T>* prev_ = nullptr;
};
template<typename T>
class LinkedList {
private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;

    void Merge(LinkedList<T>& res, LinkedList<T>& list1, LinkedList<T>& list2, bool (*comp)(const T&, const T&)) {
        res.Clear();

        Iterator lhs1 = list1.begin();
        Iterator lhs2 = list2.begin();

        Iterator rhs1 = list1.end();
        Iterator rhs2 = list2.end();

        while (lhs1 != rhs1 && lhs2 != rhs2) {
            if (comp(lhs1.curr_->data_, lhs2.curr_->data_)) { // it1.curr_->data_ < it2.curr_->data_
                res.Append(lhs1.curr_->data_);
                ++lhs1;
            } else {
                res.Append(lhs2.curr_->data_);
                ++lhs2;
            }
        }

        while (lhs1 != rhs1) {
            res.Append(lhs1.curr_->data_);
            ++lhs1;
        }
        while (lhs2 != rhs2) {
            res.Append(lhs2.curr_->data_);
            ++lhs2;
        }
    }

public:
    class Iterator {
    private:
        friend class LinkedList<T>;
        Node<T>* curr_ = nullptr;
    public:
        explicit Iterator(Node<T>* node) : curr_(std::move(node)) {}
        T& operator *() const {
            return curr_->data_;
        }

        Iterator& operator ++() {
            if (curr_->next_ == nullptr) {
                throw std::runtime_error("IndexOutOfRange");
            }
            curr_ = curr_->next_;
            return *this;
        }

        Iterator& operator --() {
            if (curr_->prev_ == nullptr) {
                throw std::runtime_error("IndexOutOfRange");
            }
            curr_ = curr_->prev_;
            return *this;
        }

        Iterator operator+(int n) {
            if (n < 0) {
                throw std::runtime_error("Summand must be positive");
            }
            for (size_t i = 0; i < n; i++) {
                curr_ = curr_->next_;
            }
            return *this;
        }

        bool operator ==(const Iterator& rhs) const {
            return curr_ == rhs.curr_;
        }

        bool operator !=(const Iterator& rhs) const {
            return !(curr_ == rhs.curr_);
        }

        bool operator<(const Iterator& rhs) const {
            return curr_->data_ < rhs.curr_->data_;
        }

        bool operator>(const Iterator& rhs) const {
            return curr_->data_ > rhs.curr_->data_;
        }

        bool operator<=(const Iterator& rhs) const {
            return curr_->data_ <= rhs.curr_->data_;
        }

        bool operator>=(const Iterator& rhs) const {
            return curr_->data_ >= rhs.curr_->data_;
        }

    };

    Iterator begin() const {
        return Iterator(head_);
    }
    Iterator end() const {
        return Iterator(tail_);
    }

    LinkedList();
    LinkedList(T* item, size_t count);
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other);

    LinkedList(Iterator lhs, Iterator rhs); // for MergeSort


    bool operator <(const LinkedList& other) const;
    bool operator >(const LinkedList& other) const;
    bool operator ==(const LinkedList& other) const;
    bool operator !=(const LinkedList& other) const;
    bool operator <=(const LinkedList& other) const;
    bool operator >=(const LinkedList& other) const;

    void Clear();

    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    LinkedList<T>* GetSubList(int startIndex, int endIndex) const;
    size_t GetLength() const;


    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(T item, int index);

    void Insert(T item, Iterator it);
    LinkedList<T>* Concat(LinkedList<T>* other);

    void MergeSort(LinkedList<T>& origin, bool (*comp)(const T&, const T&));

    void Print(std::ostream& buff) const;

    ~LinkedList();
};