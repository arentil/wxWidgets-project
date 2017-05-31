#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(Compare compare) : m_compare(compare)
{
}

void PriorityQueue::push(Square * x)
{
	p_queue.push_back(x);
	sortQ();
}

Square * PriorityQueue::top() const
{
	return p_queue.back();
}

void PriorityQueue::pop()
{
	p_queue.pop_back();
}

void PriorityQueue::sortQ()
{
	switch (m_compare)
	{
	case Compare::ASTAR:
		sort(p_queue.begin(), p_queue.end(), CompareForAStar());
		break;

	case Compare::DIJKSTRA:
		sort(p_queue.begin(), p_queue.end(), CompareForDijkstra());
		break;

	default:
		throw "INVALID COMPARE ID (PriorityQueue::sortQ())";
		break;

	}
	
}

bool PriorityQueue::empty() const
{
	return p_queue.empty();
}