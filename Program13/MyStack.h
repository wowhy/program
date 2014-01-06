#pragma once

#include <functional>

#define MAX_STACK_SIZE 100

template<class T>
class MyStack
{
public:
	MyStack(std::function<void(T)> dispose) :count(0), dispose(dispose)
	{
	}

	~MyStack()
	{
		if (dispose != nullptr)
		{
			for (int i = 0; i < count; ++i)
				dispose(elements[i]);
		}
	}

public:
	bool IsFull() const
	{
		return count == MAX_STACK_SIZE;
	}

	void Push(T element)
	{
		if (IsFull())
			throw "Stack size exceeded";

		elements[count++] = element;
	}

	T Pop()
	{
		if (IsEmpty())
			throw "Pop of an empty stack";
		return elements[--count];
	}

	bool IsEmpty() const
	{
		return count == 0;
	}

	int Depth() const
	{
		return count;
	}

	T GetElement(int index) const
	{
		if (index < 0 || index >= count)
			throw "Non-existent stack element";

		return elements[count - index - 1];
	}

private:
	T elements[MAX_STACK_SIZE];
	int count;
	std::function<void(T)> dispose;
};

