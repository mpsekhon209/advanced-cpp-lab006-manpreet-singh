#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
struct SNode {
    T value;
    SNode* next;

    explicit SNode(const T& v, SNode* n = nullptr) : value(v), next(n) {}
};

template <typename T>
class SLinkedList {
public:
    SLinkedList();
    ~SLinkedList();
    SLinkedList(const SLinkedList& other);
    SLinkedList& operator=(const SLinkedList& other);

    void push_front(const T& value);
    void push_back(const T& value);
    bool pop_front();
    bool pop_back();

    T& front();
    const T& front() const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;
    bool contains(const T& value) const;
    std::vector<T> to_vector() const;
    void clear();

private:
    SNode<T>* head_;
    std::size_t size_;
};

template <typename T>
SLinkedList<T>::SLinkedList() : head_(nullptr), size_(0) {}

template <typename T>
SLinkedList<T>::~SLinkedList() {
    clear();
}

template <typename T>
SLinkedList<T>::SLinkedList(const SLinkedList& other) : head_(nullptr), size_(0) {
    for (SNode<T>* current = other.head_; current != nullptr; current = current->next) {
        push_back(current->value);
    }
}

template <typename T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& other) {
    if (this != &other) {
        clear();
        for (SNode<T>* current = other.head_; current != nullptr; current = current->next) {
            push_back(current->value);
        }
    }
    return *this;
}

template <typename T>
void SLinkedList<T>::push_front(const T& value) {
    head_ = new SNode<T>(value, head_);
    ++size_;
}

template <typename T>
void SLinkedList<T>::push_back(const T& value) {
    if (empty()) {
        push_front(value);
        return;
    }

    SNode<T>* current = head_;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = new SNode<T>(value, nullptr);
    ++size_;
}

template <typename T>
bool SLinkedList<T>::pop_front() {
    if (empty()) {
        return false;
    }

    SNode<T>* old_head = head_;
    head_ = head_->next;
    delete old_head;
    --size_;
    return true;
}

template <typename T>
bool SLinkedList<T>::pop_back() {
    if (empty()) {
        return false;
    }

    if (size_ == 1) {
        return pop_front();
    }

    SNode<T>* current = head_;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
    --size_;
    return true;
}

template <typename T>
T& SLinkedList<T>::front() {
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    }
    return head_->value;
}

template <typename T>
const T& SLinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    }
    return head_->value;
}

template <typename T>
std::size_t SLinkedList<T>::size() const noexcept {
    return size_;
}

template <typename T>
bool SLinkedList<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
bool SLinkedList<T>::contains(const T& value) const {
    for (SNode<T>* current = head_; current != nullptr; current = current->next) {
        if (current->value == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
std::vector<T> SLinkedList<T>::to_vector() const {
    std::vector<T> values;
    values.reserve(size_);
    for (SNode<T>* current = head_; current != nullptr; current = current->next) {
        values.push_back(current->value);
    }
    return values;
}

template <typename T>
void SLinkedList<T>::clear() {
    while (head_ != nullptr) {
        SNode<T>* next = head_->next;
        delete head_;
        head_ = next;
    }
    size_ = 0;
}
