#include "p2.h"
#include "recursive.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int add(int x, int y)
{
    return x+y;
}

int multiply(int x, int y)
{
    return x*y;
}

int sum_helper(list_t list, int result)
{
    result += list_first(list);
    if (list_isEmpty(list_rest(list))) return result;
    return sum_helper(list_rest(list), result);
}

int sum(list_t list)
{
    if (list_isEmpty(list)) return 0;
    return sum_helper(list, 0);
}

int product_helper(list_t list, int result)
{
    result *= list_first(list);
    if (list_isEmpty(list_rest(list))) return result;
    return sum_helper(list_rest(list), result);
}

int product(list_t list)
{
    if (list_isEmpty(list)) return 0;
    return accumulate(list, multiply, 1);
}

int accumulate(list_t list, int (*fn)(int, int), int identity)
{
    if (list_isEmpty(list)) return identity;
    identity = fn(identity, list_first(list));
    return accumulate(list_rest(list), fn, identity);
}

const int list_length(list_t list, int len)
{
    if (list_isEmpty(list))
    {
        return len;
    }
    else
    {
        len++;
        return list_length(list_rest(list), len);
    }
}

const int list_nthElt(list_t list, int n, int x, int result)
{
    result = list_first(list);
    if(n==x) return result;
    return list_nthElt(list_rest(list), n, x+1, result);
}

list_t reverse_helper(list_t list, list_t newList)
{
    if (list_isEmpty(list)) return newList;
    newList = list_make(list_first(list), newList);
    list_t result = reverse_helper(list_rest(list), newList);
    return result;
}


list_t reverse(list_t list)
{
    return reverse_helper(list, list_make());
}

list_t append_helper(list_t first, list_t second)
{
    if (list_isEmpty(first)) return second;
    second = list_make(list_first(first), second);
    return append_helper(list_rest(first), second);
}

list_t append(list_t first, list_t second)
{
    return append_helper(reverse(first), second);
}

const list_t odd_helper(list_t list, list_t result)
{
    if (list_isEmpty(list)) return result;
    int next = list_first(list);
    if (next%2==0)
    {
        return odd_helper(list_rest(list), result);
    }
    else
    {
        result = list_make(next, result);
        return odd_helper(list_rest(list), result);
    }
}

const list_t even_helper(list_t list, list_t result)
{
    if (list_isEmpty(list)) return result;
    int next = list_first(list);
    if (next%2==0)
    {
        result = list_make(next, result);
        return even_helper(list_rest(list), result);
    }
    else
    {
        return even_helper(list_rest(list), result);
    }
}

list_t filter_even(list_t list)
{
    return reverse(even_helper(list, list_make()));
}

list_t filter_odd(list_t list)
{
    return reverse(odd_helper(list, list_make()));
}

list_t filter_helper(list_t list, bool (*fn)(int), list_t newList)
{
    if (list_isEmpty(list)) return reverse(newList);
    if(fn(list_first(list))) newList = list_make(list_first(list), newList);
    return filter_helper(list_rest(list), fn, newList);
}

list_t filter(list_t list, bool (*fn)(int))
{
    return filter_helper(list, fn, list_make());
}

const list_t rotate_helper(list_t list, int n, int end, list_t result)
{
    int next = list_nthElt(list, n, 1, 0);
    result = list_make(next, result);
    if (n==end) return result;
    return rotate_helper(list, n+1, end, result);
}

list_t rotate(list_t list, int n)
{
    if (list_isEmpty(list)) return list;
    int len = list_length(list, 0);
    n = n%len;
    if (n == 0) return list;
    list_t second = rotate_helper(reverse(list), len - n + 1, len, list_make());
    list_t first = rotate_helper(reverse(list), 1, len - n, list_make());
    return append(first, second);
}

list_t insert_list(list_t first, list_t second, int n)
{
    if (n==0) return append(second, first);
    int len  = list_length(first, 0);
    if (n==len) return append(first, second);
    list_t beg = rotate_helper(first, 1, n, list_make());
    beg = reverse(beg);
    list_t end = rotate_helper(first, n+1, len, list_make());
    end = reverse(end);
    beg = append(beg, second);
    return append(beg, end);
}

const int fib_help(int n, int a, int b)
{
    if (n==0) return 0;
    if (n==1) return 1;
    if (n==2) return a+b;
    else return fib_help(n-1, b, a+b);
}

int fib(int n)
{
    if (n==0) return 0;
    if (n==1) return 1;
    return fib(n-2) + fib(n-1);
}

int fib_tail(int n)
{
    return fib_help(n, 0, 1);
}


list_t chop(list_t list, int n)
{
    int len = list_length(list, 0);
    return rotate_helper(list, 1, len - n, list_make());
}

int tree_sum_help(tree_t tree, int result)
{
    if (tree_isEmpty(tree)) return result;
    result += tree_elt(tree);
    result = tree_sum_help(tree_left(tree), result);
    result = tree_sum_help(tree_right(tree), result);
    return result;
}

int tree_sum(tree_t tree)
{
    return tree_sum_help(tree, 0);
}

list_t traversal_help(tree_t tree, list_t result)
{
    if (tree_isEmpty(tree)) return result;
    result = traversal_help(tree_right(tree), result);
    result = list_make(tree_elt(tree), result);
    result = traversal_help(tree_left(tree), result);
    return result;
}

list_t traversal(tree_t tree)
{
    return traversal_help(tree, list_make());
}

bool covered_by(tree_t A, tree_t B, bool result)
{
    if (tree_isEmpty(A)) return true;
    if (tree_isEmpty(B)) return false;
    if (tree_elt(A) == tree_elt(B))
    {
        result = covered_by(tree_left(A), tree_left(B), result);
        result = covered_by(tree_right(A), tree_right(B), result);
    }
    else return false;
    return result;
}

bool contained_help(tree_t A, tree_t B, bool result)
{
    result = covered_by(A, B, result);
    if (result) return result;
    else
    {
        result = contained_help(A, tree_right(B), result);
        result = contained_help(A, tree_left(B), result);
    }
    return result;
}

bool contained_by(tree_t A, tree_t B)
{
    bool result = false;
    if (tree_isEmpty(A)) return true;
    if (tree_isEmpty(B)) return false;
    result = covered_by(A, B, result);
    if (result) return result;
    else
    {
        result = contained_by(A, tree_right(B));
        result = contained_by(A, tree_left(B));
    }
    return result;
}


tree_t insert_tree(int elt, tree_t tree)
{
    if (tree_isEmpty(tree)) return tree_make(elt, tree_make(), tree_make());
    else if (elt < tree_elt(tree))
    {
        tree_t tree_l = insert_tree(elt, tree_left(tree));
        tree_t tree_r = tree_right(tree);
        return tree_make(tree_elt(tree), tree_l, tree_r);
    }
    else
    {
        tree_t tree_r = insert_tree(elt, tree_right(tree));
        tree_t tree_l = tree_left(tree);
        return tree_make(tree_elt(tree), tree_l, tree_r);
    }
}
