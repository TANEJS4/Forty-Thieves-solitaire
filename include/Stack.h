/**
 * \file Stack.h
 * \author Shivam Taneja
 * \brief API for stack with prototypes of functions and state variables
 */
#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>
#include <iostream>

using std::vector;

/**
 *  \brief Class representing Stack (i.e. vector) of class T
 *  \details Data structure (stack) and its components
 */
template <class T>
class Stack
{
  private:

/**
 *  \brief Creates a vector for the stack to work on
 */
    vector<T> S;

  public:
/**
*  \brief Constructor for new Stack
*  \param in The input stack for the new Stack
*/
	Stack(vector<T> in);

/**
*  \brief inserts element at the back of the stack
*  \param a The card that will be added
*  \return the Stack where element went
*/
     Stack push(T a);

/**
*  \brief removes element from the stack
*  \return the Stack where element came from
*/
	Stack pop();

/**
*  \brief gets the top element in the stack
*  \return The top element in the Stack
*/
	T top();

/**
*  \brief get the size of the Stack
*  \return natural number from (0 to n) 
*/
	unsigned int size();

/**
*  \brief returns the Stack in form of vector
*  \return vector form of the Stack
*/
	vector<T> toSeq();
};
#endif
