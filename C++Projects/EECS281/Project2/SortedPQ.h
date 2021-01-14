#ifndef SORTED_PQ_H
#define SORTED_PQ_H
#include "Eecs281PQ.h"

#include<algorithm>

//A specialized version of the priority queue ADT that is implemented with an
//underlying sorted array-based container.
//Note: The most extreme element should be found at the back end of the
//'data' container, such that traversing the iterators yields the elements in
//sorted order.

template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class SortedPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
public:
    //Description: Construct a priority queue out of an iterator range with an optional
    //             comparison functor.
    //Runtime: O(n log n) where n is number of elements in range.
    template<typename InputIterator>
        SortedPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR());

    //Description: Construct an empty priority queue with an optional comparison functor.
    //Runtime: O(1)
    SortedPQ(COMP_FUNCTOR comp = COMP_FUNCTOR());

    //Description: Add a new element to the priority queue.
    //Runtime: O(n)
    virtual void push(const TYPE& val);

    //Description: Remove the most extreme (defined by 'compare') element from
    //             the priority queue.
    //Note: We will not run tests on your code that would require it to pop an
    //element when the priority queue is empty. Though you are welcome to if you are
    //familiar with them, you do not need to use exceptions in this project.
    //Runtime: Amortized O(1)
    virtual void pop();

    //Description: Return the most extreme (defined by 'compare') element of
    //             the priority queue.
    //Runtime: O(1)
    virtual const TYPE& top() const;

    //Description: Get the number of elements in the priority queue.
    //             This has been implemented for you.
    //Runtime: O(1)
    virtual std::size_t size() const { return data.size(); }

    //Description: Return true if the priority queue is empty.
    //             This has been implemented for you.
    //Runtime: O(1)
    virtual bool empty() const { return data.empty(); }

    //Description: Assumes that all elements in the priority queue are out of order.
    //             You must reorder the data so that the PQ invariant is restored.
    //Runtime: O(n log n)
    virtual void updatePriorities();

private:
    //Note: This vector *must* be used by your priority queue implementation.
    std::vector<TYPE> data;
private:
    //TODO: Add any additional member functions or data you require here.
};


//Description: Construct a priority queue out of an iterator range with an optional
//             comparison functor.
//Runtime: O(n log n) where n is number of elements in range.
//TODO: when you implement this function, uncomment the parameter names
template<typename TYPE, typename COMP_FUNCTOR>
template<typename InputIterator>
SortedPQ<TYPE, COMP_FUNCTOR>::SortedPQ(
        InputIterator start,
        InputIterator end,
        COMP_FUNCTOR comp) 
    : data(start, end) 
{
    std::sort(data.begin(), data.end(), comp);
    this->compare = comp;
}


//Description: Construct an empty priority queue with an optional comparison functor.
//Runtime: O(1)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
SortedPQ<TYPE, COMP_FUNCTOR>::SortedPQ(COMP_FUNCTOR comp) {
    this->compare = comp;
}


//Description: Add a new element to the priority queue.
//Runtime: O(n)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
void SortedPQ<TYPE, COMP_FUNCTOR>::push(const TYPE & val) {
    data.push_back(val);
    if(size() == 1)
	return;
    size_t i = size() - 1;
    size_t j = size() - 2;
    while(i > 0 && this->compare(data[i], data[j]))
    {
	std::swap(data[i--], data[j--]);
    }
}


//Description: Remove the most extreme (defined by 'compare') element from
//             the priority queue.
//Note: We will not run tests on your code that would require it to pop an
//element when the priority queue is empty. Though you are welcome to if you are
//familiar with them, you do not need to use exceptions in this project.
//Runtime: Amortized O(1)
template<typename TYPE, typename COMP_FUNCTOR>
void SortedPQ<TYPE, COMP_FUNCTOR>::pop() {
    data.pop_back();
}


//Description: Return the most extreme (defined by 'compare') element of
//             the priority queue.
//Runtime: O(1)
template<typename TYPE, typename COMP_FUNCTOR>
const TYPE& SortedPQ<TYPE, COMP_FUNCTOR>::top() const {
    //TODO: Implement this function
    return data.back();      //TODO: Delete or change this line
}


//Description: Assumes that all elements in the priority queue are out of order.
//             You must reorder the data so that the PQ invariant is restored.
//Runtime: O(n log n)
template<typename TYPE, typename COMP_FUNCTOR>
void SortedPQ<TYPE, COMP_FUNCTOR>::updatePriorities() {
    std::sort(data.begin(), data.end(), this->compare);
}


#endif //SORTED_H
