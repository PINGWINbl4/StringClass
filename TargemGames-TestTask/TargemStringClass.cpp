#include "TargemStringClass.h"
#include <cstdlib>
#include <algorithm>
#include <cctype>

// Приватные методы

void String::ensure_capacity(size_t required_capacity) {
    if (required_capacity >= capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 16 : capacity_ * 2;
        while (new_capacity <= required_capacity) {
            new_capacity *= 2;
        }
        resize(new_capacity);
    }
}

void String::resize(size_t new_capacity) {
    char* new_data = new char[new_capacity];
    if (data_) {
        std::memcpy(new_data, data_, length_ + 1); // +1 для нулевого терминатора
        delete[] data_;
    }
    data_ = new_data;
    capacity_ = new_capacity;
}

// Конструкторы

String::String() : data_(nullptr), length_(0), capacity_(0) {}

String::String(const char* cstr) : data_(nullptr), length_(0), capacity_(0) {
    if (cstr) {
        length_ = std::strlen(cstr);
        capacity_ = length_ + 1;
        data_ = new char[capacity_];
        std::memcpy(data_, cstr, capacity_);
    }
}

String::String(const String& other) : data_(nullptr), length_(other.length_), capacity_(other.capacity_) {
    if (other.data_) {
        data_ = new char[capacity_];
        std::memcpy(data_, other.data_, capacity_);
    }
}

String::String(String&& other) noexcept
    : data_(other.data_), length_(other.length_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.length_ = 0;
    other.capacity_ = 0;
}

// Деструктор

String::~String() {
    delete[] data_;
}

// Операторы присваивания

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] data_;
        length_ = other.length_;
        capacity_ = other.capacity_;
        if (other.data_) {
            data_ = new char[capacity_];
            std::memcpy(data_, other.data_, capacity_);
        }
        else {
            data_ = nullptr;
        }
    }
    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        length_ = other.length_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.length_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

String& String::operator=(const char* cstr) {
    if (cstr) {
        size_t new_length = std::strlen(cstr);
        if (new_length + 1 > capacity_) {
            delete[] data_;
            capacity_ = new_length + 1;
            data_ = new char[capacity_];
        }
        std::memcpy(data_, cstr, new_length + 1);
        length_ = new_length;
    }
    else {
        delete[] data_;
        data_ = nullptr;
        length_ = 0;
        capacity_ = 0;
    }
    return *this;
}

// Оператор +=

String& String::operator+=(const String& other) {
    if (other.length_ > 0) {
        ensure_capacity(length_ + other.length_ + 1);
        std::memcpy(data_ + length_, other.data_, other.length_);
        length_ += other.length_;
        data_[length_] = '\0';
    }
    return *this;
}

String& String::operator+=(const char* cstr) {
    if (cstr) {
        size_t add_length = std::strlen(cstr);
        if (add_length > 0) {
            ensure_capacity(length_ + add_length + 1);
            std::memcpy(data_ + length_, cstr, add_length);
            length_ += add_length;
            data_[length_] = '\0';
        }
    }
    return *this;
}

// Методы доступа

const char* String::c_str() const {
    return data_ ? data_ : "";
}

size_t String::length() const {
    return length_;
}

bool String::empty() const {
    return length_ == 0;
}

// Операторы сравнения

bool String::operator==(const String& other) const {
    if (length_ != other.length_) return false;
    if (data_ == other.data_) return true;
    return std::memcmp(data_, other.data_, length_) == 0;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

bool String::operator<(const String& other) const {
    if (data_ == other.data_) return false;
    if (data_ == nullptr) return true;
    if (other.data_ == nullptr) return false;
    return std::memcmp(data_, other.data_, std::min(length_, other.length_)) < 0 ||
        (std::memcmp(data_, other.data_, std::min(length_, other.length_)) == 0 && length_ < other.length_);
}

bool String::operator>(const String& other) const {
    return other < *this;
}

// Внешние операторы

String operator+(const String& lhs, const String& rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

String operator+(const String& lhs, const char* rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

String operator+(const char* lhs, const String& rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

// Функция для сравнения без учета регистра
bool case_insensitive_compare(const String& a, const String& b) {
    const char* a_str = a.c_str();
    const char* b_str = b.c_str();

    while (*a_str && *b_str) {
        char a_char = std::tolower(static_cast<unsigned char>(*a_str));
        char b_char = std::tolower(static_cast<unsigned char>(*b_str));

        if (a_char != b_char) {
            return a_char < b_char;
        }

        a_str++;
        b_str++;
    }

    return *a_str == '\0' && *b_str != '\0';
}