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
    // Конструкторы
    String();
    String(const char* cstr);
    String(const String& other);
    String(String&& other) noexcept;

    // Деструктор
    ~String();

    // Операторы присваивания
    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;
    String& operator=(const char* cstr);

    // Оператор +=
    String& operator+=(const String& other);
    String& operator+=(const char* cstr);

    // Методы доступа
    const char* c_str() const;
    size_t length() const;
    bool empty() const;

    // Операторы сравнения
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    bool operator<(const String& other) const;
    bool operator>(const String& other) const;

    // Внешние дружественные операторы
    friend String operator+(const String& lhs, const String& rhs);
    friend String operator+(const String& lhs, const char* rhs);
    friend String operator+(const char* lhs, const String& rhs);
};

// Внешние операторы
String operator+(const String& lhs, const String& rhs);
String operator+(const String& lhs, const char* rhs);
String operator+(const char* lhs, const String& rhs);

// Функция для сравнения без учета регистра (для использования в примере)
bool case_insensitive_compare(const String& a, const String& b);

#endif // STRING_H