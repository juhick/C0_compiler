#pragma once
template<typename T>
class Stack {
private:
	T* data;
	int size;
	int Top;
public:
	Stack(int size, T t);
	Stack(int size);
	T top();
	void pop();
	void push(T t);
	T get(int i);
	void set(int i, T t);
	bool isFull();
	bool isEmpty();
	int getTop();
	void setTop(int i);
};