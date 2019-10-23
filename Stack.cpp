#include"Stack.h"


template<typename T>
Stack<T>::Stack(int size, T t) {
	data = new T[size];
	for (int i = 0; i < size; i++)
		data[i] = t;
	this->size = size;
	Top = 0;
}

template<typename T>
Stack<T>::Stack(int size) {
	data = new T[size];
	this->size = size;
	Top = 0;
}

template<typename T>
T Stack<T>::top()
{
	return data[Top - 1];
}

template<typename T>
void Stack<T>::pop()
{
	data[Top - 1] = 0;
	Top--;
}

template<typename T>
void Stack<T>::push(T t)
{
	data[Top++] = t;
}

template<typename T>
T Stack<T>::get(int i)
{
	return data[i];
}

template<typename T>
void Stack<T>::set(int i, T t)
{
	data[i] = t;
}

template<typename T>
bool Stack<T>::isFull()
{
	return Top == size;
}

template<typename T>
bool Stack<T>::isEmpty()
{
	return Top == 0;
}

template<typename T>
int Stack<T>::getTop()
{
	return Top;
}

template<typename T>
void Stack<T>::setTop(int i)
{
	Top = i;
}

