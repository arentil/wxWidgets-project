#pragma once

#include "Square.h"
#include <vector>
#include <algorithm>

class PriorityQueue
{
public:
	PriorityQueue();
	void push(Square * x);
	Square * top() const;
	void pop();
	void sortQ();
	bool empty() const;

private:
	std::vector<Square *> p_queue;
};