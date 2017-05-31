#pragma once

#include "Square.h"
#include <vector>
#include <algorithm>


enum class Compare : short
{
	ASTAR = 0,
	DIJKSTRA
};


class PriorityQueue
{
public:
	PriorityQueue(Compare compare);
	void push(Square * x);
	Square * top() const;
	void pop();
	void sortQ();
	bool empty() const;

private:
	std::vector<Square *> p_queue;
	Compare m_compare;
};