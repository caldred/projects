#include "p2.h"
#include "recursive.h"
#include "test_helpers.h"

#include <cstdlib>
#include <iostream>
#include <cassert>

using namespace std;

// YOU MUST EXTEND THE MAIN FUNCTION IN THIS FILE SO THAT IT TESTS EVERY
// PUBLIC FUNCTION YOU IMPLEMENT IN P2.CPP!
//
// Protip #1: Write tests for the functions BEFORE you implement them!
// (i.e. Write tests for sum() first, and then write sum())
// It sounds like a pain, but it helps make sure that you are never under the
// illusion that your code works when it's actually full of bugs.
//
// Protip #2: Instead of putting all your tests in main() (and making life)
// more difficult--especially for the graders), put each test case in a
// function!
//
//
// We recommend using the functions in test_helpers.h when
// writing your test cases.
//

int t_add(int x, int y)
{
    return x+y;
}

int t_multiply(int x, int y)
{
    return x*y;
}

bool is_even(int x)
{
    return -(x%2)+1;
}

bool is_odd(int x)
{
    return x%2;
}

bool test_reverse(list_t list, list_t expected, list_t actual)
{
    actual = reverse(list);
    return list_equal(actual, expected);
}

bool test_append(list_t first, list_t second, list_t expected, list_t actual)
{
    actual = append(first, second);
    return list_equal(actual, expected);
}

bool test_filter_odd(list_t list, list_t expected, list_t actual)
{
    actual = filter_odd(list);
    return list_equal(actual, expected);
}

bool test_filter_even(list_t list, list_t expected, list_t actual)
{
    actual = filter_even(list);
    return list_equal(actual, expected);
}

bool test_filter(list_t list, bool (*fn)(int), list_t expected, list_t actual)
{
    actual = filter(list, fn);
    return list_equal(expected, actual);
}

bool test_rotate(list_t list, int n, list_t expected, list_t actual)
{
    actual =  rotate(list, n);
    return list_equal(actual, expected);
}

bool test_insert_list(list_t first, list_t second, int n, list_t expected, list_t actual)
{
    actual  = insert_list(first, second, n);
    return list_equal(actual, expected);
}

bool test_chop(list_t list, int n, list_t expected, list_t actual)
{
    actual = chop(list, n);
    return list_equal(actual, expected);
}

bool test_fib(int n, int expected, int actual)
{
    actual  =  fib(n);
    if (expected == actual) return true;
    else return false;
}

bool test_fib_tail(int n, int expected, int actual)
{
    actual  =  fib_tail(n);
    if (expected == actual) return true;
    else return false;
}

bool test_tree_sum(tree_t tree, int expected, int actual)
{
    actual  =  tree_sum(tree);
    if (expected == actual) return true;
    else return false;
}

bool test_traversal(tree_t tree, list_t expected, list_t actual)
{
    actual  =  traversal(tree);
    return list_equal(expected, actual);
}

bool test_contained_by(tree_t tree1, tree_t tree2, bool expected, bool actual)
{
    actual = contained_by(tree1, tree2);
    if(actual==expected)  return true;
    else return false;
}

int test_insert_tree()
{
    tree_t start = tree_make(2,
			     tree_make(1, tree_make(), tree_make()),
			     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
			   tree_make(1, tree_make(), tree_make()),
			   tree_make(4,
				     tree_make(3, tree_make(), tree_make()),
				     tree_make()));
    tree_t end1 = tree_make(3, tree_make(), tree_make());
    tree_t candidate = insert_tree(3, start);
    tree_t candidate1 = insert_tree(3, tree_make());
    tree_print(end);
    cout << endl;

    tree_print(candidate);
    cout << endl;

    if (tree_equal(candidate, end) && tree_equal(candidate1, end1))
    {
	   cout << "Success!\n";
	   return 0;
    }
	cout << "Failed\n";
	return -1;
}

int main()
{
    tree_t start = tree_make(2,
			     tree_make(1, tree_make(), tree_make()),
			     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
			   tree_make(1, tree_make(), tree_make()),
			   tree_make(4,
				     tree_make(3, tree_make(), tree_make()),
				     tree_make()));

    list_t start_list = list_make(1,
                   list_make(2,
                   list_make(4, list_make())));
    // Here's a free test case! You can model your tests after this one.
    list_t listA = list_make();
    list_t mtList = list_make();
    list_t bigList = list_make();
    tree_t treeA = tree_make();
    tree_t treeB = tree_make();
    list_t list1 = list_make(1, list_make());

    tree_t tree0 = tree_make(0, tree_make(), tree_make());
    tree_t tree1 = tree_make(1, tree_make(), tree_make());
    tree_t tree2 = tree_make(2, tree_make(), tree_make());

    for (int i = 0; i < 5; i++)
    {
        if(i%2) treeA = tree_make(0,treeA, treeA);
        else treeA = tree_make(1, treeA, treeA);
    }
    for (int i = 0; i < 3; i++)
    {
        if(i%2) treeB = tree_make(0,treeB, treeB);
        else treeB = tree_make(1, treeB, treeB);
    }
    tree_t tree101 = tree_make(0, tree1, tree1);

    tree_print(treeB);

    for (int i = 1; i < 5; ++i)
    {
    	listA = list_make(i, listA);
    }

    list_t listB;
    for (int i =5; i<10; i++)
    {
        listB = list_make(i, listB);
    }
    list_t listBA;
    for (int i = 1; i<10; i++)
    {
        listBA = list_make(i, listBA);
    }

    list_t listAR;
    for (int i = 4; i>0; i--)
    {
        listAR = list_make(i, listAR);
    }
    list_t listAO;

    for (int i = 1; i<5; i+=2)
    {
        listAO = list_make(i, listAO);
    }
    list_t listAE;

    for (int i  = 2; i < 5; i+=2)
    {
        listAE = list_make(i, listAE);
    }

    list_t listAR1 = list_make(4, list_make());
    for (int i = 1; i < 4; i++)
    {
        listAR1 = list_make(i, listAR1);
    }

    for (int i = 30; i>0; i--)
    {
        bigList = list_make(2, bigList);
    }
    list_t listIAB2 =    list_make(4,
                         list_make(3,
                         list_make(9,
                         list_make(8,
                         list_make(7,
                         list_make(6,
                         list_make(5,
                         list_make(2,
                         list_make(1,
                         list_make())))))))));

    list_t list101 = list_make(1,list_make(0, list_make(1, list_make())));
    int EXPECTED_SUM = 10;
    int actual_sum = sum(listA);
    assert(EXPECTED_SUM == actual_sum);

    EXPECTED_SUM = 0;
    actual_sum = sum(mtList);
    assert(EXPECTED_SUM == actual_sum);

    EXPECTED_SUM = 60;
    actual_sum = sum(bigList);
    assert(EXPECTED_SUM == actual_sum);

    int EXPECTED_PRODUCT = 24;
    int actual_product = product(listA);
    assert(EXPECTED_PRODUCT == actual_product);

    EXPECTED_PRODUCT = 0;
    actual_product = product(mtList);
    assert(EXPECTED_PRODUCT == actual_product);

    EXPECTED_PRODUCT = 1073741824;
    actual_product = product(bigList);
    assert(EXPECTED_PRODUCT == actual_product);

    int EXPECT_ACCUM_ADD = 10;
    int actual_accum_add = accumulate(listA, t_add, 0);
    assert(EXPECT_ACCUM_ADD == actual_accum_add);


    EXPECT_ACCUM_ADD = 0;
    actual_accum_add = accumulate(mtList, t_add, 0);
    assert(EXPECT_ACCUM_ADD == actual_accum_add);

    EXPECT_ACCUM_ADD = 60;
    actual_accum_add = accumulate(bigList, t_add, 0);
    assert(EXPECT_ACCUM_ADD == actual_accum_add);

    int EXPECTED_ACCUMULATE = 24;
    int actual_accumulate = accumulate(listA, t_multiply, 1);
    assert(EXPECTED_ACCUMULATE == actual_accumulate);

    EXPECTED_ACCUMULATE = 1;
    actual_accumulate = accumulate(mtList, t_multiply, 1);
    assert(EXPECTED_ACCUMULATE == actual_accumulate);

    EXPECTED_ACCUMULATE = 1073741824;
    actual_accumulate = accumulate(bigList, t_multiply, 1);
    assert(EXPECTED_ACCUMULATE == actual_accumulate);

    assert(test_reverse(listA, listAR, list_make()));
    assert(test_reverse(list_make(),list_make(),list_make()));
    assert(test_reverse(list1, list1, list_make()));

    assert(test_append(listB, listA, listBA, list_make()));
    assert(test_append(listB, list_make(), listB, list_make()));
    assert(test_append(list_make(), listB, listB, list_make()));

    assert(test_filter_odd(listA, listAO, list_make()));
    assert(test_filter_odd(list_make(), list_make(), list_make()));

    assert(test_filter_even(listA, listAE, list_make()));
    assert(test_filter_even(list_make(), list_make(), list_make()));

    assert(test_filter(listA,is_odd,listAO,list_make()));
    assert(test_filter(list_make(), is_odd, list_make(), list_make()));
    assert(test_filter(listA, is_even, listAE, list_make()));

    assert(test_rotate(listA, 1, listAR1, list_make()));
    assert(test_rotate(list_make(), 1, list_make(), list_make()));

    assert(test_insert_list(listA, listB, 0, append(listB, listA), list_make()));
    assert(test_insert_list(listA, listB, 4, append(listA, listB), list_make()));
    assert(test_insert_list(listA, list_make(), 2, listA, list_make()));
    assert(test_insert_list(list_make(), listA, 0, listA, list_make()));
    assert(test_insert_list(listA, listB, 2, listIAB2, list_make()));

    assert(test_fib(0,0,0));
    assert(test_fib(1,1,0));
    assert(test_fib(2,1,0));
    assert(test_fib(17, 1597, 0));

    assert(test_fib_tail(0,0,0));
    assert(test_fib_tail(1,1,0));
    assert(test_fib_tail(2,1,0));
    assert(test_fib_tail(17, 1597, 0));

    assert(test_tree_sum(start, 7, 0));
    assert(test_tree_sum(end, 10, 0));
    assert(test_tree_sum(tree_make(), 0, 0));

    assert(test_traversal(start, start_list, list_make()));
    assert(test_traversal(treeB, append(list101, append(list1, list101)), list_make()));
    assert(test_traversal(tree_make(), list_make(), list_make()));

    assert(test_contained_by(treeB, treeA, true, false));
    assert(test_contained_by(treeA, treeB, false, true));
    assert(test_contained_by(treeA, treeA, true, true));
    assert(test_contained_by(tree101, treeA, true, false));
    assert(test_contained_by(tree2, treeB, false, true));

    int i = test_insert_tree();

    cout << "PASS!" << endl;
    return i;
}
