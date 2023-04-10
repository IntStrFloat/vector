//
// Copyright 2023 by Dmitry Bereznev
//

#ifndef INCLUDE_VECTOR_HPP_
#define INCLUDE_VECTOR_HPP_


#include <iostream>
#include <cstddef>
#include <iterator>
#include <initializer_list>
#include <algorithm>
#include <utility>

template <class T>
class vector {
 public:
  class iterator {
   public:
    using iterator_concept = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    explicit iterator(pointer ptr = nullptr) : m_ptr(ptr) {}
    iterator(const iterator&) = default;
    iterator& operator=(const iterator&) = default;

    reference operator*() const { return *m_ptr; }
    pointer operator->() const { return m_ptr; }

    iterator& operator++() {
      ++m_ptr;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      ++m_ptr;
      return tmp;
    }

    iterator& operator--() {
      --m_ptr;
      return *this;
    }

    iterator operator--(int) {
      iterator tmp(*this);
      --m_ptr;
      return tmp;
    }

    iterator& operator+=(difference_type n) {
      m_ptr += n;
      return *this;
    }

    iterator operator+(difference_type n) const {
      iterator tmp(*this);
      return tmp += n;
    }

    friend iterator operator+(difference_type n, const iterator& it) {
      iterator tmp(it);
      return tmp += n;
    }

    iterator& operator-=(difference_type n) {
      m_ptr -= n;
      return *this;
    }

    iterator operator-(difference_type n) const {
      iterator tmp(*this);
      return tmp -= n;
    }

    difference_type operator-(const iterator& other) const {
      return m_ptr - other.m_ptr;
    }

    bool operator==(const iterator& other) const {
      return m_ptr == other.m_ptr;
    }
    bool operator!=(const iterator& other) const {
      return m_ptr != other.m_ptr;
    }
    bool operator<(const iterator& other) const {
      return m_ptr < other.m_ptr;
    }
    bool operator>(const iterator& other) const {
      return m_ptr > other.m_ptr;
    }
    bool operator<=(const iterator& other) const {
      return m_ptr <= other.m_ptr;
    }
    bool operator>=(const iterator& other) const {
      return m_ptr >= other.m_ptr;
    }

   private:
    pointer m_ptr;
  };
  vector();
  vector(const vector<T>&);
  explicit vector(int);
  vector(std::initializer_list<T>);
  vector(int, const T&);
  ~vector();

  vector<T>& operator=(const vector<T>&);
  constexpr T& operator[](int index);

  constexpr T& at(size_t);
  constexpr T& front();
  constexpr T& back();
  constexpr T* data();

  constexpr iterator begin() {
    return iterator(m_data);
  }

  constexpr iterator end() {
    return iterator(m_data + m_size);
  }

  constexpr vector<T>::iterator insert(const vector::iterator, const T&);

  constexpr bool empty();
  constexpr size_t size();
  constexpr void reserve(int);
  constexpr size_t capacity();
  constexpr void clear();
  constexpr void resize(int);
  constexpr void push_back(const T&);
  constexpr void pop_back();
  constexpr void swap(vector<T>&);

 private:
  int m_capacity;
  int m_size;
  T* m_data;
};

template<class T>
vector<T>::vector() {
  m_capacity = 3;
  m_size = 0;
  m_data = new T[m_capacity];
}


template<class T>
vector<T>::vector(int size) {
  m_size = size;
  m_capacity = size*2;
  m_data = new T[m_capacity];
  for (int i = 0; i < m_size; ++i) {
    m_data[i] = 0;
  }
}

template <class T>
vector<T>::vector(std::initializer_list<T> init) : m_capacity(init.size()*2),
                                                   m_size(init.size()) {
  m_data = new T[m_capacity];
  int i = 0;
  for (auto it = init.begin(); it != init.end(); ++it) {
    m_data[i++] = *it;
  }
}


template <class T>
vector<T>::vector(const vector<T>& other) {
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_data = new T[other.m_capacity];
  for (int i = 0; i < other.m_size; ++i) {
    m_data[i] = other.m_data[i];
  }
}

template <class T>
vector<T>::vector(int size, const T& value) {
  m_size = size;
  m_capacity = size;
  for (int i = 0; i < size; ++i) {
    m_data[i] = value;
  }
}

template <class T>
vector<T>::~vector() {
  delete[] m_data;
  m_data = nullptr;
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
  if (this != &other) {
    delete[] m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new T[other.m_capacity];
    std::copy(other.m_data, other.m_data + other.m_size, m_data);
  }
  return *this;
}

template <class T>
constexpr T& vector<T>::operator[](int index) {
  if (index < m_capacity) {
    if (index >= m_size) {
      m_size = index + 1;
    }
    return m_data[index];
  } else {
    reserve(m_capacity*2);
    return m_data[index];
  }
}

template <class T>
constexpr T& vector<T>::front() {
  if (m_size == 0) {
    throw "vector::front(): Vector is empty";
  }
  return m_data[0];
}

template <class T>
constexpr T& vector<T>::back() {
  if (m_size == 0) {
    throw "vector::front(): Vector is empty";
  }
  return m_data[m_size-1];
}

template <class T>
constexpr T* vector<T>::data() {
  return m_data;
}

template <class T>
constexpr bool vector<T>::empty() {
  return m_size == 0;
}

template <class T>
constexpr size_t vector<T>::size() {
  return m_size;
}

template <class T>
constexpr size_t vector<T>::capacity() {
  return m_capacity;
}

template <class T>
constexpr void vector<T>::reserve(int size) {
  if (m_capacity != size) {
    T* new_data = new T[size];
    std::copy(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_data = new_data;
    m_capacity = size;
  }
}

template <class T>
constexpr void vector<T>::clear() {
  m_size = 0;
  delete[] m_data;
  m_data = nullptr;
}

template <class T>
constexpr void vector<T>::resize(int elem) {
  if (elem < m_size) {
    m_size = elem;
  } else if (elem > m_size && elem <= m_capacity) {
    for (int i = m_size; i < elem; ++i) {
      m_data[i] = 0;
    }
    m_size = elem;
  } else if (elem > m_capacity) {
    reserve(elem);
    for (int i = m_size; i < elem; ++i) {
      new (m_data + i) T();
    }
    m_size = elem;
  }
}

template <class T>
constexpr void vector<T>::push_back(const T& elem) {
  if (m_size < m_capacity) {
    m_data[m_size++] = elem;
  } else if (m_size == m_capacity) {
    reserve(m_capacity*2);
    m_data[m_size++] = elem;
  }
}

template <class T>
constexpr void vector<T>::pop_back() {
  if (m_size == 0) {
    throw "vector::pop_back(): Vector is empty";
  }
  --m_size;
}

template <class T>
constexpr void vector<T>::swap(vector<T>& vec) {
  int temp_size = m_size;
  int temp_capacity = m_capacity;
  T* temp_data = new T[m_capacity];
  std::copy(m_data, m_data + m_size, temp_data);
  delete[] m_data;
  m_data = new T[vec.m_capacity];
  m_size = vec.m_size;
  m_capacity = vec.m_capacity;
  std::copy(vec.m_data, vec.m_data + vec.m_size, m_data);
  vec.m_size = temp_size;
  vec.m_capacity = temp_capacity;
  delete[] vec.m_data;
  vec.m_data = temp_data;
}

template <class T>
constexpr typename vector<T>::iterator
vector<T>::insert(const vector<T>::iterator pos, const T& value) { // NOLINT
  size_t index = pos - begin();
  if (m_size == m_capacity) {
    reserve(m_capacity * 2);
  }
  for (size_t i = m_size; i > index; --i) {
    m_data[i] = m_data[i - 1];
  }
  m_data[index] = value;
  ++m_size;
  return begin() + index;
}

#endif // INCLUDE_VECTOR_HPP_
