/*!
 * Implementation of class 'vector'
 * @author Vladyslav Tytov
 * @version 1.0.0
 */

#ifndef MY_VEC_H
#define MY_VEC_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using std::size_t;

/*!
 * @brief Custom class "MyVector"
 *
 * Class "MyVector" consist basic methods such as push_back, getSize, at. This class is a simple analog of the c++ class <vector>.
 *
 * @return template <class element> class MyVector
 */

template <class element>
class MyVector
{
 private:
  size_t size; /*!< initial size of vector */
  size_t capacity; /*!< current capacity */
  element* vector; /*!< pointer to items */

  const static int initSize = 64;
  const static int sizeMult = 2;

  void resize();

 public:
/*!
 * Initialization constructor.
 */
  MyVector();

/*!
 * Initialization destructor.
 */
  ~MyVector();

/*!
 * Initialization of method push_back().
 * @param item is a address of element.
 */
  void push_back(element &item);

/*!
 * Initialization of method getSize().
 */
  size_t getSize();

/*!
 * Initialization of method at().
 * @param index is a current index of element in vector.
 */
  element& at(size_t index); 

/*!
 *Initialization of the operator[].
 * @param index is a current index of element in vector.
 */
  element& operator[] (size_t index);
};

/*!
 * @brief Constructor of vector.
 *
 * Creates vector with initial size.
 * @return template <class element>.
 */
template <class element>
MyVector<element>::MyVector()
{
  size = 0;
  capacity = initSize;
  vector = new element[capacity];
}

/*!
 * @brief Destructor of vector.
 */
template <class element>
MyVector<element>::~MyVector()
{
  if(vector)
    {
      delete[] vector;
    }
}

/*!
 * @brief Method resize().
 *
 * Increases size of current internal array by sizeMult factor (by default 2).
 */
template <class element>
void MyVector<element>::resize()
{
  capacity *= sizeMult;
  element *newVector = new element[capacity];

  for(size_t i = 0; i < size; i++)
    {
      newVector[i] = vector[i];
    }
  delete[] vector;
  vector = newVector;
}

/*!
 * @brief Method push_back();
 *
 * Adds element to the end of vector. Calls resize() method, if not enough space in current internal array.
 */
template <class element>
void MyVector<element>::push_back(element &item)
{
  if(size >= capacity){
    resize();
  }
  vector[size] = item;
  ++size;
}

/*!
 * @brief Method getSize().
 *
 * Returns current number of elements in the vector.
 *
 * @return template <class element> size_t.
 */
template <class element>
size_t MyVector<element>::getSize()
{
  return size;
}


/*!
 * @brief Method at().
 *
 * Returns element of vector with a given index.
 * @throw std::out_of_range If given index more than size of the vector.
 * @return element
 */
template <class element>
element& MyVector<element>::at(size_t index)
{
  try
    {
      if(!(index < size))
	{
	  //std::string exc = "Out of range";

	  throw std::out_of_range("Index out of range!");
	}
      return vector[index];
      /*
      if(index < size)
	return vector[index];
      */
  }
  //catch (const std::out_of_range& e)
  catch (std::exception &e)
   {
     //std::cout << e.what() << std::endl;
      std::cerr << "Out of range error: " << e.what() << '\n';
   }
}

/*!
 * @brief Operator[].
 *
 * Returns element of vector with a given index.
 * @throw std::out_of_range If given index more than size of the vector.
 * @return element
 */
template <class element>
element& MyVector<element>::operator[] (size_t index)
{
  try
    {
      if(!(index < size))
	throw std::out_of_range("Index out of range!");
  /*
  if(index < size)
    return vector[index];
  else
    std::cout << "Index out of range!" << std::endl;
  */
      return vector[index];
    }
    
  catch(std::exception &exc)
    {
      std::cerr << exc.what() << std::endl;
    }
    
}

#endif
