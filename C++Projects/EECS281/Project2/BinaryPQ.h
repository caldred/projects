#ifndef BINARY_H
#define BINARY_H
#include <vector>

using namespace std;

#include "Eecs281PQ.h"

//A specialized version of the priority queue ADT implemented as a binary heap.

template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
public:
    //Description: Construct a priority queue out of an iterator range with an optional
    //             comparison functor.
    //Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
        BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR());

    //Description: Construct an empty priority queue with an optional comparison functor.
    //Runtime: O(1)
    BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR());

    //Description: Add a new element to the priority queue.
    //Runtime: O(log n)
    virtual void push(const TYPE& val);

    //Description: Remove the most extreme (defined by 'compare') element from
    //             the priority queue.
    //Note: We will not run tests on your code that would require it to pop an
    //element when the priority queue is empty. Though you are welcome to if you are
    //familiar with them, you do not need to use exceptions in this project.
    //Runtime: O(log n)
    virtual void pop();

    //Description: Return the most extreme (defined by 'compare') element of
    //             the priority queue.
    //Runtime: O(1)
    virtual const TYPE& top() const;

    //Description: Get the number of elements in the priority queue.
    //Runtime: O(1)
    virtual std::size_t size() const {
        //Fill this in - might be very simple depending on implementation
        return data.size();
    }

    //Description: Return true if the priority queue is empty.
    //Runtime: O(1)
    virtual bool empty() const {
        // Fill this in - might be very simple depending on implementation
        return data.empty();
    }

    //Description: Assumes that all elements in the priority queue are out of order.
    //             You must reorder the data so that the PQ invariant is restored.
    //Runtime: O(n)
    virtual void updatePriorities();

private:
    //Note: This vector *must* be used your priority queue implementation.
    std::vector<TYPE> data;
private:
    void fixUp(size_t k) {
	while(k > 0 && this->compare(data[(k - 1)/2], data[k])) {
	    swap(data[k], data[(k-1)/2]);
	    --k;
	    k /= 2;
	}
    }
    void fixDown(size_t k) {
	while(2*k < size()) {
	    size_t j = 2 * k + 1;
	    if(j < size() && this->compare(data[j], data[j+1]))
		++j;
	    if(this->compare(data[j], data[k]))
		break;
	    swap(data[k], data[j]);
	    k = j;
	}
    }
    //TODO: Add any additional member functions or data you require here.
};


//Description: Construct a priority queue out of an iterator range with an optional
//             comparison functor.
//Runtime: O(n) where n is number of elements in range.
//TODO: when you implement this function, uncomment the parameter names
template<typename TYPE, typename COMP_FUNCTOR>
template<typename InputIterator>
BinaryPQ<TYPE, COMP_FUNCTOR>::BinaryPQ(
        InputIterator start,
        InputIterator end,
        COMP_FUNCTOR comp) {
    data = vector<TYPE> (start, end);
    this->compare = comp;
    updatePriorities();
}


//Description: Construct an empty priority queue with an optional comparison functor.
//Runtime: O(1)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
BinaryPQ<TYPE, COMP_FUNCTOR>::BinaryPQ(COMP_FUNCTOR comp) {
    //TODO: Implement this function
    this->compare = comp;
}


//Description: Add a new element to the priority queue.
//Runtime: O(log n)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
void BinaryPQ<TYPE, COMP_FUNCTOR>::push(const TYPE & val) {
    data.push_back(val);
    fixUp(size()-1);
}


//Description: Remove the most extreme (defined by 'compare') element from
//             the priority queue.
//Note: We will not run tests on your code that would require it to pop an
//element when the priority queue is empty. Though you are welcome to if you are
//familiar with them, you do not need to use exceptions in this project.
//Runtime: O(log n)
template<typename TYPE, typename COMP_FUNCTOR>
void BinaryPQ<TYPE, COMP_FUNCTOR>::pop() {
    //TODO: Implement this function
    data.front() = data.back();
    data.pop_back();
    fixDown(0);
}


//Description: Return the most extreme (defined by 'compare') element of
//             the priority queue.
//Runtime: O(1)
template<typename TYPE, typename COMP_FUNCTOR>
const TYPE& BinaryPQ<TYPE, COMP_FUNCTOR>::top() const {
    return data.front();      //TODO: Delete or change this line
}


//Description: Assumes that all elements in the priority queue are out of order.
//             You must reorder the data so that the PQ invariant is restored.
//Runtime: O(n)
template<typename TYPE, typename COMP_FUNCTOR>
void BinaryPQ<TYPE, COMP_FUNCTOR>::updatePriorities() {
    //TODO: Implement this function
    for(size_t i = size()-1; i <= 0; --i) {
	fixDown(i);
    }
}


#endif //BINARY_H
