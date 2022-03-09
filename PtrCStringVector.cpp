#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdexcept>
#include "PtrCStringVector.h"

using namespace std;

PtrCStringVector::PtrCStringVector() {
    this->data_ = nullptr;
    this->size_ = this->capacity_ = 0;
}

PtrCStringVector::PtrCStringVector(const PtrCStringVector &srcPtrCStringVector) {
    this->data_ = nullptr;
    this->size_ = this->capacity_ = 0;
    this->copy(srcPtrCStringVector);
}

PtrCStringVector::~PtrCStringVector() {
    this->free();
}

PtrCStringVector &PtrCStringVector::operator=(const PtrCStringVector &source) {
    this->free();
    this->copy(source);
    return *this;
}

PtrCStringVector &PtrCStringVector::operator=(PtrCStringVector &&source) {
    this->move(source);
    return *this;
}

void PtrCStringVector::push_back(const char *text2Add) {
    if (this->size_ == this->capacity_) {
        this->reserve(this->capacity_ + 1);
    }
    this->data_[this->size_] = new char[strlen(text2Add) + 1];
    strcpy(this->data_[this->size_], text2Add);
    this->size_++;
}

PtrCStringVector PtrCStringVector::operator+(const PtrCStringVector &anotherVector) const {
    PtrCStringVector ret = *this;
    for (int i = 0; i < anotherVector.size_; i++) {
        ret.push_back(anotherVector[i]);
    }
    return ret;
}

char *PtrCStringVector::operator[](size_t index) {
    if (index >= this->size_) {
        throw out_of_range("");
    }
    return this->data_[index];
}

const char *PtrCStringVector::operator[](size_t index) const noexcept {
    if (index >= this->size_) {
        return "";
    }
    return this->data_[index];
}

PtrCStringVector PtrCStringVector::operator&(const PtrCStringVector &rhs) const {
    PtrCStringVector ret;
    for (int i = 0; i < max(this->size_, rhs.size_); i++) {
        char *sum = new char[strlen((*this)[i]) + strlen(rhs[i]) + 1];
        strcpy(sum, (*this)[i]);
        strcat(sum, rhs[i]);
        ret.push_back(sum);
        delete[] sum;
    }
    return ret;
}

void PtrCStringVector::free() {
    for (int i = 0; i < this->size_; i++) {
        delete[] this->data_[i];
    }
    this->size_ = this->capacity_ = 0;
    delete[] this->data_;
    this->data_ = nullptr;
}

void PtrCStringVector::copy(const PtrCStringVector &other) {
    if (this != &other) {
        this->free();
        for (int i = 0; i < other.size_; i++) {
            this->push_back(other[i]);
        }
    }
}

void PtrCStringVector::move(PtrCStringVector &other) {
    if (this != &other) {
        this->free();
        this->data_ = other.data_;
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }
}

void PtrCStringVector::reserve(size_t new_capacity) {
    size_t total_new_capacity = this->capacity_ + new_capacity;
    char **new_data = new char *[total_new_capacity];
    if (this->data_ == nullptr) {
        delete[] this->data_;
        this->data_ = new_data;
    } else {
        for (int i = 0; i < this->size_; i++) {
            new_data[i] = this->data_[i];
        }
        delete[] this->data_;
        this->data_ = new_data;
    }

    this->capacity_ = total_new_capacity;
}
