#ifndef HEAP_H
#define HEAP_H
#include <memory.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "heap/IHeap.h"
#include "list/XArrayList.h"
using namespace std;
/*
 * function pointer: int (*comparator)(T& lhs, T& rhs)
 *      compares objects of type T given in lhs and rhs.
 *      return: sign of (lhs - rhs)
 *              -1: lhs < rhs
 *              0 : lhs == rhs
 *              +1: ls > rhs
 *
 * function pointer: void (*deleteUserData)(Heap<T>* pHeap)
 *      remove user's data in case that T is a pointer type
 *      Users should pass &Heap<T>::free for "deleteUserData"
 *
 */
template <class T>
class Heap : public IHeap<T>
{
public:
  class Iterator; // forward declaration

protected:
  T *elements;                            // a dynamic array to contain user's data
  int capacity;                           // size of the dynamic array
  int count;                              // current count of elements stored in this heap
  int (*comparator)(T &lhs, T &rhs);      // see above
  void (*deleteUserData)(Heap<T> *pHeap); // see above

public:
  Heap(int (*comparator)(T &, T &) = 0, void (*deleteUserData)(Heap<T> *) = 0);

  Heap(const Heap<T> &heap);               // copy constructor
  Heap<T> &operator=(const Heap<T> &heap); // assignment operator

  ~Heap();

  // Inherit from IHeap: BEGIN
  void push(T item);
  T pop();
  const T peek();
  void remove(T item, void (*removeItemData)(T) = 0);
  bool contains(T item);
  int size();
  void heapify(T array[], int size);
  void clear();
  bool empty();
  string toString(string (*item2str)(T &) = 0);
  void heapsort(XArrayList<T> &arrayList);
  // Inherit from IHeap: END

  void println(string (*item2str)(T &) = 0)
  {
    cout << toString(item2str) << endl;
  }

  Iterator begin() { return Iterator(this, true); }
  Iterator end() { return Iterator(this, false); }

public:
  /* if T is pointer type:
   *     pass the address of method "free" to Heap<T>'s constructor:
   *     to:  remove the user's data (if needed)
   * Example:
   *  Heap<Point*> heap(&Heap<Point*>::free);
   *  => Destructor will call free via function pointer "deleteUserData"
   */
  static void free(Heap<T> *pHeap)
  {
    for (int idx = 0; idx < pHeap->count; idx++)
      delete pHeap->elements[idx];
  }

private:
  bool aLTb(T &a, T &b) { return compare(a, b) < 0; }
  int compare(T &a, T &b)
  {
    if (comparator != 0)
      return comparator(a, b);
    else
    {
      if (a < b)
        return -1;
      else if (a > b)
        return 1;
      else
        return 0;
    }
  }

  void ensureCapacity(int minCapacity);
  void swap(int a, int b);
  void reheapUp(int position);
  void reheapDown(int position);
  int getItem(T item);

  void removeInternalData();
  void copyFrom(const Heap<T> &heap);

  //////////////////////////////////////////////////////////////////////
  ////////////////////////  INNER CLASSES DEFNITION ////////////////////
  //////////////////////////////////////////////////////////////////////

public:
  // Iterator: BEGIN
  class Iterator
  {
  private:
    Heap<T> *heap;
    int cursor;

  public:
    Iterator(Heap<T> *heap = 0, bool begin = 0)
    {
      this->heap = heap;
      if (begin && (heap != 0))
        cursor = 0;
      if (!begin && (heap != 0))
        cursor = heap->size();
    }
    Iterator &operator=(const Iterator &iterator)
    {
      this->heap = iterator.heap;
      this->cursor = iterator.cursor;
      return *this;
    }

    T &operator*() { return this->heap->elements[cursor]; }
    bool operator!=(const Iterator &iterator)
    {
      return this->cursor != iterator.cursor;
    }
    // Prefix ++ overload
    Iterator &operator++()
    {
      cursor++;
      return *this;
    }
    // Postfix ++ overload
    Iterator operator++(int)
    {
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }
    void remove(void (*removeItemData)(T) = 0)
    {
      this->heap->remove(this->heap->elements[cursor], removeItemData);
    }
  };
  // Iterator: END
};

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
Heap<T>::Heap(int (*comparator)(T &, T &), void (*deleteUserData)(Heap<T> *))
{
  this->comparator = comparator;
  this->deleteUserData = deleteUserData;
  this->capacity = 10; 
  this->count = 0;
  this->elements = new T[this->capacity];
}

template <class T>
Heap<T>::Heap(const Heap<T> &heap)
{
  this->deleteUserData = nullptr;
  this->copyFrom(heap);
}

template <class T>
Heap<T> &Heap<T>::operator=(const Heap<T> &heap)
{
  if (this != &heap) {
    this->removeInternalData();
    this->copyFrom(heap);
  }
  return *this;
}

template <class T>
Heap<T>::~Heap()
{
  this->removeInternalData();
  this->count = 0;
  this->capacity = 0;
}

template <class T>
void Heap<T>::push(T item)
{         
  ensureCapacity(count + 1);
  elements[count] = item;
  
  if (count > 0) {
    int current = count;
    int parent = (current - 1) / 2;
    
    T tempItem = elements[current];
    
    while (current > 0 && aLTb(tempItem, elements[parent])) {
      elements[current] = elements[parent];
      current = parent;
      parent = (current - 1) / 2;
    }
    
    elements[current] = tempItem;
  }
  
  count++;
}

template <class T>
T Heap<T>::pop()
{
  if (count == 0)
    throw std::underflow_error("Calling to peek with the empty heap.");

  T root = elements[0];
  
  count--;
  
  if (count > 0) {
    elements[0] = elements[count];
    
    int current = 0;
    int child;
    T temp = elements[0];
    
    while ((child = 2 * current + 1) < count) {
      if (child + 1 < count && aLTb(elements[child + 1], elements[child]))
        child++;
        
      if (!aLTb(elements[child], temp))
        break;
        
      elements[current] = elements[child];
      current = child;
    }
    
    elements[current] = temp;
  }

  return root;
}

template <class T>
const T Heap<T>::peek()
{
  if (count == 0)
    throw std::underflow_error("Calling to peek with the empty heap.");
  return elements[0];
}

template <class T>
bool Heap<T>::empty()
{
  return count == 0;
}

template <class T>
bool Heap<T>::contains(T item)
{
  for (int i = 0; i < count; i++) {
    if (compare(elements[i], item) == 0) {
      return true;
    }
  }
  return false;
}

template <class T>
int Heap<T>::size() {
  return count;
}

template <class T>
void Heap<T>::remove(T item, void (*removeItemData)(T))
{
  int pos = -1;
  for (int i = 0; i < count; i++) {
    if (compare(elements[i], item) == 0) {
      pos = i;
      break;
    }
  }
  
  if (pos < 0) return;

  if (removeItemData)
    removeItemData(elements[pos]);

  count--;
  
  if (pos == count) return;
  
  elements[pos] = elements[count];
  
  int parent = (pos - 1) / 2;
  
  if (pos > 0 && aLTb(elements[pos], elements[parent])) {
    T temp = elements[pos];
    while (pos > 0 && aLTb(temp, elements[parent])) {
      elements[pos] = elements[parent];
      pos = parent;
      parent = (pos - 1) / 2;
    }
    elements[pos] = temp;
  } else {
    T temp = elements[pos];
    int child;
    
    while ((child = 2 * pos + 1) < count) {
      if (child + 1 < count && aLTb(elements[child + 1], elements[child]))
        child++;
        
      if (!aLTb(elements[child], temp))
        break;
        
      elements[pos] = elements[child];
      pos = child;
    }
    
    elements[pos] = temp;
  }
}

template <class T>
void Heap<T>::heapify(T array[], int size)
{
  this->clear();
  ensureCapacity(size);
  for (int i = 0; i < size; ++i) {
      this->elements[i] = array[i];
  }
  this->count = size;

  for (int i = size / 2 - 1; i >= 0; --i) {
      reheapDown(i);
  }
}

template <class T>
void Heap<T>::clear()
{
  this->removeInternalData();

  this->count = 0;
  this->capacity = 10;
  this->elements = new T[this->capacity];
}

template <class T>
string Heap<T>::toString(string (*item2str)(T &))
{
  stringstream os;
  if (item2str != 0)
  {
    os << "[";
    for (int idx = 0; idx < count - 1; idx++)
      os << item2str(elements[idx]) << ",";
    if (count > 0)
      os << item2str(elements[count - 1]);
    os << "]";
  }
  else
  {
    os << "[";
    for (int idx = 0; idx < count - 1; idx++)
      os << elements[idx] << ",";
    if (count > 0)
      os << elements[count - 1];
    os << "]";
  }
  return os.str();
}

//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
void Heap<T>::ensureCapacity(int minCapacity)
{ 
  if (minCapacity > capacity) {
    int old_capacity = capacity;
    int new_capacity = max(minCapacity, old_capacity + (old_capacity >> 1));
    try {
        T *newData = new T[new_capacity];
        memcpy(newData, elements, count * sizeof(T));
        delete[] elements;
        elements = newData;
        capacity = new_capacity;
    }
    catch (const std::bad_alloc &e) {
        e.what();
    }
  }
}


template <class T>
void Heap<T>::swap(int a, int b)
{
  T temp = this->elements[a];
  this->elements[a] = this->elements[b];
  this->elements[b] = temp;
}

template <class T>
void Heap<T>::reheapUp(int position)
{
  T temp = elements[position];
  int current = position;
  int parent = (current - 1) / 2;
  
  while (current > 0 && aLTb(temp, elements[parent])) {
    elements[current] = elements[parent];
    current = parent;
    parent = (current - 1) / 2;
  }
  
  elements[current] = temp;
}

template <class T>
void Heap<T>::reheapDown(int position)
{
  bool heapified = false;
  while (!heapified) {
    int left = 2 * position + 1;
    int right = 2 * position + 2;
    int smallest = position;

    if (left < count && aLTb(elements[left], elements[smallest]))
        smallest = left;

    if (right < count && aLTb(elements[right], elements[smallest]))
        smallest = right;

    if (smallest != position) {
        swap(position, smallest);
        position = smallest;
    } else {
        heapified = true;
    }
  }
}

template <class T>
int Heap<T>::getItem(T item)
{
  for (int i = 0; i < count; ++i) {
    if (compare(elements[i], item) == 0) { return i;}
  }
  return -1;
}

template <class T>
void Heap<T>::removeInternalData()
{
  if (deleteUserData != nullptr) {
    deleteUserData(this);
  }
  
  if (elements != nullptr) {
    delete[] elements;
    elements = nullptr;
  }
}

template <class T>
void Heap<T>::copyFrom(const Heap<T> &heap)
{
  capacity = heap.capacity;
  count = heap.count;
  elements = new T[capacity];
  this->comparator = heap.comparator;

  for (int idx = 0; idx < count; idx++) {
    this->elements[idx] = heap.elements[idx];
  }
}

template <class T>
void Heap<T>::heapsort(XArrayList<T> &arrayList)
{
  this->clear();  // Đảm bảo heap trống
  ensureCapacity(arrayList.size());

  for (int i = 0; i < arrayList.size(); ++i) {
      this->push(arrayList.get(i));
  }

  for (int i = 0; i < arrayList.size(); ++i) {
      T popped = this->pop();
      arrayList.removeAt(i);
      arrayList.add(i, popped);
      arrayList.println();
  }
}

#endif /* HEAP_H */