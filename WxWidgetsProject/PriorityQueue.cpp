#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
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
	sort(p_queue.begin(), p_queue.end(), Compare());
}

bool PriorityQueue::empty() const
{
	return p_queue.empty();
}