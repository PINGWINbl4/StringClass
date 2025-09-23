#ifndef STRING_H
#define STRING_H

#include <cstddef>
#include <cstring>
#include <utility>

class String {
private:
	char* data_;
	size_t length_;
	size_t capacity_;

	void ensure_capacity(size_t required_capacity);
	void resize(size_t new_capacity);

public:
	// constructor
	String();
	String(const char* cstr);
	String(const String& other);
	String(String&& other) noexcept;

	// destructor
	~String();

	// operators
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	String& operator=(const char* cstr);

	String& operator+=(const String& other);
	String& operator+=(const char* cstr);

	bool operator==(const String& other) const;
	bool operator!=(const String& other) const;
	bool operator<(const String& other) const;
	bool operator>(const String& other) const;

	friend String operator+(const String& lhs, const String& rhs);
	friend String operator+(const String& lhs, const char* rhs);
	friend String operator+(const char* lhs, const String& rhs);

	//methods
	const char* c_str() const;
	size_t length() const;
	bool empty() const;

};

String operator+(const String& lhs, const String& rhs);
String operator+(const String& lhs, const char* rhs);
String operator+(const char* lhs, const String& rhs);

bool case_insensitive_compare(const String& a, const String& b);

#endif // STRING_H