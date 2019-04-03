/**
 * \file Stack.cpp
 * \author Shivam Taneja
 * \brief Implementation of stack.h i.e. API for stack 
 */
// Implementation here
#include <iostream>
#include "Stack.h"
#include "CardTypes.h"

#include <vector>
#include <stdexcept>

using std::vector;

template <class T>
Stack<T>::Stack(vector<T> s) : S({}) {
	this->S = s;
	//details
}

template <class T>
Stack<T> Stack<T>::push(T a)
{
	vector<T> vec = this->S;
	vec.push_back(a);
	Stack<T> new1(vec);
	return new1;
}

template <class T>
Stack<T> Stack<T>::pop()
{
	if (this->S.empty())
		{
			throw std::out_of_range("Stack is empty");
		}


		vector<T> vec = this->S;
		// this->S = this->S.pop_back();
		vec.pop_back();
		Stack<T> new1(vec);
		return new1;

}

template <class T>
T Stack<T>::top(){
	if (this->S.empty()){
		throw std::out_of_range("Stack is empty");
		}
	return (this->S).back();
}

template <class T>
unsigned int Stack<T>::size()
{
	return this->S.size();
}

template <class T>
vector<T> Stack<T>::toSeq(){
	return this->S;
}

// Keep this at bottom
template class Stack<CardT>;
