#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
struct DNode {
    T value;
    DNode* prev;
    DNode* next;

    explicit DNode(const T& v, DNode* p = nullptr, DNode* n = nullptr)
        : value(v), prev(p), next(n) {}
};

template <typename T>
class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();
    DLinkedList(const DLinkedList& other);
    DLinkedList& operator=(const DLinkedList& other);

    void push_front(const T& value);
    void push_back(const T& value);
    bool pop_front();
    bool pop_back();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;
    bool contains(const T& value) const;
    std::vector<T> to_vector() const;
    void clear();

private:
    DNode<T>* header_;
    DNode<T>* trailer_;
    std::size_t size_;
};

template <typename T>
DLinkedList<T>::DLinkedList() : size_(0) {
    header_ = new DNode<T>(T(), nullptr, nullptr);
    trailer_ = new DNode<T>(T(), nullptr, nullptr);
    header_->next = trailer_;
    trailer_->prev = header_;
}

template <typename T>
DLinkedList<T>::~DLinkedList() {
    clear();
    delete header_;
    delete trailer_;
}

template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList& other) : size_(0) {
    header_ = new DNode<T>(T(), nullptr, nullptr);
    trailer_ = new DNode<T>(T(), nullptr, nullptr);
    header_->next = trailer_;
    trailer_->prev = header_;

    for (DNode<T>* current = other.header_->next; current != other.trailer_; current = current->next) {
        push_back(current->value);
    }
}

template <typename T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList& other) {
    if (this != &other) {
        DLinkedList<T> copy(other);
        std::swap(header_, copy.header_);
        std::swap(trailer_, copy.trailer_);
        std::swap(size_, copy.size_);
    }
    return *this;
}

template <typename T>
void DLinkedList<T>::push_front(const T& value) {
    DNode<T>* new_node = new DNode<T>(value, header_, header_->next);
    header_->next->prev = new_node;
    header_->next = new_node;
    ++size_;
}

template <typename T>
void DLinkedList<T>::push_back(const T& value) {
    DNode<T>* new_node = new DNode<T>(value, trailer_->prev, trailer_);
    trailer_->prev->next = new_node;
    trailer_->prev = new_node;
    ++size_;
}

template <typename T>
bool DLinkedList<T>::pop_front() {
    if (empty()) {
        return false;
    }

    DNode<T>* node = header_->next;
    header_->next = node->next;
    node->next->prev = header_;
    delete node;
    --size_;
    return true;
}

template <typename T>
bool DLinkedList<T>::pop_back() {
    if (empty()) {
        return false;
    }

    DNode<T>* node = trailer_->prev;
    trailer_->prev = node->prev;
    node->prev->next = trailer_;
    delete node;
    --size_;
    return true;
}

template <typename T>
T& DLinkedList<T>::front() {
    if (empty()) {
        throw std::out_of_range("DLinkedList is empty");
    }
    return header_->next->value;
}

template <typename T>
const T& DLinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("DLinkedList is empty");
    }
    return header_->next->value;
}

template <typename T>
T& DLinkedList<T>::back() {
    if (empty()) {
        throw std::out_of_range("DLinkedList is empty");
    }
    return trailer_->prev->value;
}

template <typename T>
const T& DLinkedList<T>::back() const {
    if (empty()) {
        throw std::out_of_range("DLinkedList is empty");
    }
    return trailer_->prev->value;
}

template <typename T>
std::size_t DLinkedList<T>::size() const noexcept {
    return size_;
}

template <typename T>
bool DLinkedList<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
bool DLinkedList<T>::contains(const T& value) const {
    for (DNode<T>* current = header_->next; current != trailer_; current = current->next) {
        if (current->value == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
std::vector<T> DLinkedList<T>::to_vector() const {
    std::vector<T> values;
    values.reserve(size_);
    for (DNode<T>* current = header_->next; current != trailer_; current = current->next) {
        values.push_back(current->value);
    }
    return values;
}

template <typename T>
void DLinkedList<T>::clear() {
    while (header_->next != trailer_) {
        DNode<T>* node = header_->next;
        header_->next = node->next;
        node->next->prev = header_;
        delete node;
    }
    size_ = 0;
}
