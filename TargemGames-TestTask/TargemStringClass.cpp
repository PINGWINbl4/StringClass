#include "TargemStringClass.h"
#include <cstdlib>
#include <algorithm>
#include <cctype>

// private methods

void String::ensure_capacity(size_t required_capacity) {
	if (required_capacity >= capacity_) {

		if (required_capacity >= SIZE_MAX / 2) {
			capacity_ = required_capacity + 1;
		}
		else {
			capacity_ = (capacity_ == 0) ? 16 : capacity_;
			while (capacity_ <= required_capacity) capacity_ *= 2;
		}

		resize(capacity_);

	}
}



void String::resize(size_t new_capacity) {
	char* resized_data = new char[new_capacity];
	if (data_) {
		std::memcpy(resized_data, data_, length_ + 1); // +1 for '/0'
		delete[] data_;
	}
	data_ = resized_data;
	capacity_ = new_capacity;
}

// constructors

String::String() : data_(nullptr), length_(0), capacity_(0) {}

String::String(const char* c_str) : data_(nullptr), length_(0), capacity_(0) {
	if (c_str) {
		length_ = std::strlen(c_str);
		capacity_ = length_ + 1;
		data_ = new char[capacity_]; // it can throw bad_alloc, but I think it's better to fail-fast concept
		std::memcpy(data_, c_str, capacity_);
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

// destructor

String::~String() {
	delete[] data_;
}

// operators
String& String::operator = (const String& other) {
	if (this == &other) return *this;

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

	return *this;
}

String& String::operator = (String&& other) noexcept {
	if (this == &other) return *this;

	delete[] data_;
	data_ = other.data_;
	length_ = other.length_;
	capacity_ = other.capacity_;

	other.data_ = nullptr;
	other.length_ = 0;
	other.capacity_ = 0;
	return *this;
}

String& String::operator = (const char* cstr) {
	if (!cstr) {
		delete[] data_;
		data_ = nullptr;
		length_ = 0;
		capacity_ = 0;
		return *this;
	}

	size_t new_length = std::strlen(cstr);
	if (new_length + 1 > capacity_) {
		delete[] data_;
		capacity_ = new_length + 1;
		data_ = new char[capacity_];
	}

	std::memcpy(data_, cstr, new_length + 1);
	length_ = new_length;
	return *this;
}

String& String::operator += (const String& other) {
	if (other.length_ <= 0)return *this;

	ensure_capacity(length_ + other.length_ + 1);
	std::memcpy(data_ + length_, other.data_, other.length_);
	length_ += other.length_;
	data_[length_] = '\0';
	return *this;
}

String& String::operator += (const char* c_str) {
	if (!c_str) return *this;

	size_t add_length = std::strlen(c_str);
	ensure_capacity(length_ + add_length + 1);
	std::memcpy(data_ + length_, c_str, add_length);
	length_ += add_length;
	data_[length_] = '\0';
	return *this;
}

String operator + (const String& lhs, const String& rhs) {
	String result(lhs);
	result += rhs;
	return result;
}

String operator + (const String& lhs, const char* rhs) {
	String result(lhs);
	result += rhs;
	return result;
}

String operator + (const char* lhs, const String& rhs) {
	String result(lhs);
	result += rhs;
	return result;
}

bool String::operator == (const String& other) const {
	if (length_ != other.length_) return false;
	if (data_ == other.data_) return true;
	return std::memcmp(data_, other.data_, length_) == 0;
}

bool String::operator != (const String& other) const {
	return !(*this == other);
}

bool String::operator < (const String& other) const {
	if (data_ == other.data_) return false;
	if (!data_) return true;
	if (!other.data_) return false;

	size_t min_len = std::min(length_, other.length_);
	int cmp = std::memcmp(data_, other.data_, min_len);

	return cmp < 0 || (cmp == 0 && length_ < other.length_);
}


bool String::operator > (const String& other) const {
	return other < *this;
}

// methods
const char* String::data() const {
	return data_ ? data_ : "";
}

size_t String::length() const {
	return length_;
}

bool String::empty() const {
	return length_ == 0;
}

bool case_insensitive_compare(const String& a, const String& b) {
	const char* a_str = a.data();
	const char* b_str = b.data();

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