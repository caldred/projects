#ifndef POORMANPQ_H
#define POORMANPQ_H

#include "Eecs281PQ.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

//A bad priority queue that linearly searches for the maximum element every
//time it is needed. You do not need to implement this; it is already done
//for you.

template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PoorManPQ  : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
public:
    //Description: Construct a priority queue out of an iterator range with an optional
    //             comparison functor.
    //Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PoorManPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR())
        : data(start, end)
    {
        this->compare = comp;
    } // PoorManPQ()


    //Description: Construct an empty priority queue with an optional comparison functor.
    //Runtime: O(1)
    PoorManPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) {
        this->compare = comp;
    } // PoorManPQ()


    //Description: Add a new element to the priority queue.
    //Runtime: O(1)
    virtual void push(const TYPE& val) {
        data.push_back(val);
    } // push()


    //Description: Remove the most extreme (defined by 'compare') element from
    //             the priority queue.
    //Runtime: O(1) if the highest priority element is already known, O(n) otherwise
    virtual void pop() {
        assert(!data.empty());

        // Use the STL to return an iterator to the highest priority element
        auto it = std::max_element(data.begin(), data.end(), this->compare);

        // Swap that element with the last one in the data vector, then remove it.
        std::swap(*it, data.back());
        data.pop_back();
    } // pop()


    //Description: Return the most extreme (defined by 'compare') element of
    //             the priority queue.
    //Runtime: O(1) if the highest priority element is already known, O(n) otherwise
    virtual const TYPE& top() const {
        // Use the STL to return an iterator to the highest priority element
        auto it = std::max_element(data.begin(), data.end(), this->compare);

        return *it;
    } // top()


    //Description: Get the number of elements in the priority queue.
    //Runtime: O(1)
    virtual std::size_t size() const {
        return data.size();
    } // size()


    //Description: Return true if the priority queue is empty.
    //Runtime: O(1)
    virtual bool empty() const {
        return data.empty();
    } // empty()


    //Description: Assumes that all elements in the priority queue are out of order.
    //             For PoorManPQ, there is no reordering of the data to be done.
    //Runtime: O(1)
    virtual void updatePriorities() {
    } // updatePriorities()

private:
    std::vector<TYPE> data;
};

#endif // POORMANPQ_H
