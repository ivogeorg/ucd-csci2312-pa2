## CSCI 2312: Programming Assignment 2

_operator overloading and linked data structures_

* * *

### Goals

1. Practice class design with the Point and Cluster classes, which feature dynamic memory management.
2. Learn to overload operators for your own classes/types.
3. Learn to work with linked lists, one of the most basic and ubiquitous data structures.
4. Practice input/output within the streams abstraction.
5. Continue using git and Github.
6. Develop good coding style.

### Synopsis

PA2 asks you to update your 3D Point class from [PA1](https://github.com/ivogeorg/ucd-csci2312-pa1) to an arbitrary number of "dimensions", and to create a Cluster class which will hold a big number of Point objects. The Point objects held in a Cluster have to be sorted in pseudo-lexicographic order at all times. You have to write two files, <tt>Point.cpp</tt> and <tt>Cluster.cpp</tt>. See the [Detailed Instructions](https://github.com/ivogeorg/ucd-csci2312-pa2/blob/master/README.md#detailed-instructions) at the bottom of this file.

PA2 is in the test-driven-development (TDD) style, just like [PA1](https://github.com/ivogeorg/ucd-csci2312-pa1). It has 204 tests that your implementation should pass for full points. Start by creating the two files <tt>Point.cpp</tt> and <tt>Cluster.cpp</tt> so CMake will stop complaining. (Remember to <tt>git add</tt> them to your local repository.) Then start implementing the Point class incrementally. You can comment out all but the first test (<tt>test_point_smoketest(ec);</tt>) in <tt>main.cpp</tt>. When you pass this test, uncomment the next one, and so on.

PA2 is a much larger assignment than PA1. You should expect to write about 500 lines of code and spend about 30 hours on it. Therefore, it is advisable that you start early and do it in stages. If you get stuck on anything for more than **one hour**, seek help.

### Submission

You don't need to submit anything. Once you fork the repository (this is your **remote** repository on Github, aka **origin**), you will clone it to your development machine (this is your local repository), and start work on it. Commit your changes to your local repository often and push them up to the remote repository occasionally. Make sure you push at least once before the due date. At the due date, your remote repository will be cloned and tested automatically by the grading script. _**Note:** Your code should be in the **master** branch of your remote repository._

### Grading

An autograding script will run the test suite against your files. Your grade will be based on the number of tests passed. (E.g. if your code passes 3 out of 6 test cases, your score will be 50% and the grade will be the corresponding letter grade in the course's grading scale). The test suite for PA2 has __204__ tests. **Note:** The testing and grading will be done with fresh original copies of all the provided files. In the course of development, you can modify them, if you need to, but your changes will not be used. Only your <tt>Point.cpp</tt> and <tt>Cluster.cpp</tt> files will be used.

### Compiler

Your program should run on **GCC 4.9.0** or later, or **Clang 3.3** or later. No other compilers are supported.

### Due Date

The assignment is due on **Wed, Mar 2, at 23:59 Mountain time**. The last commit to your PA2 repository before the deadline will be graded.

### Honor Code

Free Github repositories are public so you can look at each other's code. Please, don't do that. You can discuss any programming topics and the assignments in general but sharing of solutions diminishes the individual learning experience of many people. Assignments might be randomly checked for plagiarism and a plagiarism claim may be raised against you.

### Use of libraries

For this assignment, no exteranal libraries should be used, except for the Standard Library minus the Standard Template Library (STD). The implementation of the linked list should be your own. We will use the STD in PA3-PA5.

### Coding style

Familiarize yourself with and start following [these coding style guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cppstyle.html). There are others on the Web. Pick one and be consistent. _**Note:** If you stumble on the Google C++ Style Guide, be advised that it has been heavily criticized by many leading C++ programmers. I don't advise you to follow it, especially the more advanced features. This Guide is for entry-level coders at Google who need to be able to work with their legacy code. It is not advisable for new projects and novice programmers._

### References

Operator overloading [guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html).

A very good [C++ tutorial](http://www.learncpp.com/), including many topics we are covering.

Two websites with C++ Reference, [here](http://en.cppreference.com/w/) and [here](http://www.cplusplus.com/).

### Detailed Instructions

#### Point class

1. The `Point` class represents a point in multidimensional Euclidean space, represented by `double` values. The number of dimensions is an argument to the `Point` constructor. The values of the point should be held in a private _dynamically allocated_ array of `double`s. To handle dynamic memory properly, you have to implement the one-argument constructor, the copy constructor, the assignment operator, and the destructor (the last three are aka _the big three_).

2. The _optional_ second constructor, which takes a number of dimensions and an array of `double`s, is not tested by the test suite. It might be useful for your own testing & debugging needs.

3. Every `Point` should have a unique _id_. The easiest way to achieve this is to use a `static` variable that holds the value of the next _id_. (A `static` variable belongs to the class, not the objects, so there is only one such variable, no matter how many objects of the class are created.) The `Point` constructor should get the current value to assign to the current point, and increment the value for the next point. 

   **Note:** The `static` variable has to be defined and initialized in the <tt>Point.cpp</tt> file as follows:
   ```C++
   unsigned int Point::__idGen = 0; // id generator
   ```

4. For the proper operation of the `Point` and `Cluster` classes, the `Point` _copy constructor_ and _assignment operator_ implementations should **copy** the _id_ of the argument, and not generate a new one like the constructor(s).

5. Modify the `distanceTo()` function to work for points of arbitrary number of dimensions. Remember that the dimensionality of the `Point` is held in a private variable.

6. Implement the overloaded member `operator*=` and `operator/=` with a single `double` argument. These operators are known as _compound assignment_.

   **Usage:** Each dimension of the current `Point` is multiplied or divided by a factor as follows:
   ```C++
   p1 *= 6.3;
   p2 /= 2.5;
   ```

7. Implement the overloaded simple arithmetic member `operator*` and `operator/` with a single `double` argument.

   **Usage:** A new `Point` is created and returned with dimensions like the current `Point` but multiplied or divided by a factor as follows:
   ```C++
   p1 = p * 6.3;
   p2 = p * 2.5;
   ```
   **Note:** The implementation of these operators is straightforward if the corresponding _compound assignment_ operators are used.
   
8. Implement the overloaded non-`const` _subscript_ member `operator[]`.

   **Usage:** Read/write access to each of a `Point`'s values:
   ```C++
   p[4] = 7.001;
   p[5] = p[1] * 1.5;
   ```

9. Implement the overloaded `friend` _compound assignment_ arithmetic `operator+=` and `operator-=` with two `const Point &` arguments. A `friend` operator is a _non-member_ function with **private** access to the class where it is declared.

   **Usage:** Dimension-wise addition/substraction of the right-hand `Point` from the left-hand `Point`:
   ```C++
   p1 += p2;
   p3 -= p1;
   ```
   **Note:** Notice that the first (or left-hand) argument is not `const`. The operators modify that `Point` and return a reference to it.

10.  Implement the overloaded `friend` simple arithmetic `operator+` and `operator-` with two `const Point &` arguments. A `friend` operator is a _non-member_ function with **private** access to the class where it is declared.

   **Usage:** Dimension-wise addition/substraction of the right-hand `Point` from the left-hand `Point` and the creation and returning of a new `const Point` with the dimension-wise sum/difference of their values:
   
   ```C++
   p1 = p2 + p3;
   p3 = p1 - p4;
   ```
   **Note:** The implementation of these operators is straightforward if the corresponding _compound assignment_ operators are used.
   **Note:** The return type is a `const` to prevent silly statements like the following:
   ```C++
   (p1 + p3) = p5; // assigns p5 to the temporary new Point object returned by operator+
   ```
   
11. Implement the overloaded `friend` `operator==` and `operator!=` with two `const Point &` arguments. A `friend` operator is a _non-member_ function with **private** access to the class where it is declared.

   **Usage:** Test two `Point`s for equality or inequality:
   
   ```C++
   if (p1 == p2) {
      // ...
   }
   if (p3 != p4) {
      // ...
   }
   ```
   **Note:** Two `Point`s are equal **iff** all values are equal dimension-wise, **and** the _id-s_ are also equal.
   **Note:** The implementation of `operator!=` is straightforward with the use of `operator==`.

12. Implement the overloaded `friend` `operator<`, `operator>`, `operator<=`, and `operator>=` with two `const Point &` arguments. A `friend` operator is a _non-member_ function with **private** access to the class where it is declared.

   **Usage:** Compare two `Point`s:
   
   ```C++
   if (p1 < p2) {
      // ...
   }
   if (p3 >= p4) {
      // ...
   }
   ```
   **Note:** One `Point` is _smaller_ than another **iff**, for a given dimension position, the value of the first point is **less** than the value of the second point, and all the values on the left, if any, are all equal. The values on the right don't matter. For example, `Point` (5.0, 5.0, 4.5, 10.1, **13.4**, 151.3) is _smaller_ than (5.0, 5.0, 4.5, 10.1, **13.5**, 15.9).
   **Note:** Implement `operator<`, then use it to implement `operator>` and `operator>=`. Finally, use `operator>` to implement `operator<=`.

13. Implement the overloaded `friend` insertion `operator<<` with a `std::ostream` and a `const Point &` arguments. A `friend` operator is a _non-member_ function with **private** access to the class where it is declared.

   **Usage:** Right out (intert) a `Point`s to an output stream:
   
   ```C++
   cout << p2 << endl;
   ```
   **Note:** A `Point` should write itself out as follows (note the _space_ after each comma):
   ```
   1.2, 4.5, 6.7, 90.12, 34.54, 0.01
   ```

14. Implement the overloaded `friend` extraction `operator>>` with a `std::istream` and a non-`const` `Point &` arguments. A `friend` operator is a _non-member_ function with **private** access to the class where it is declared.

   **Usage:** Read in (extract) a `Point`s from an input stream:
   
   ```C++
   std::string pointString("1.2, 4.5, 6.7, 90.12, 34.54, 0.01");
   std::stringstream inputStringStream(pointString);
   Point p(6);
   inputStringStream >> p;
   ```
   **Note:** Notice that the `Point` created to be read has exactly the dimensionality that is necessary to hold the values read out from the input stream.

#### Cluster class

1. The `Cluster` class represents a collection of `Point` objects. It uses a singly-linked list to hold them in **ascending pseudo-lexicographic order**. The list is composed of linked `LNode` objects defined as simple structures, each one pointing to the next one, if any, and the last one holding a `nullptr`, signifying the end of the list:

   ```C++
   typedef struct LNode *LNodePtr;

   struct LNode {
      Point point;
      LNodePtr next;
      
      LNode(const Point &p, LNodePtr n);
   };
   ```
   
2. A `Cluster` can have `Point`s added and removed. During these operations, two conditions have to be maintained:
  1. The `Point`s should **always** be in the correct _ascending pseudo-lexicographic_ order.
  2. The `size` parameter of the `Cluster` should **always** be in sync with the true number of `Points`.

3. It is helpful to employ the following two techniques in the implementation of the linked-list manipulation methods:
  1. Handle separately and in this order the cases of 
    * Empty list
    * The first element of the list
    * All the rest of the elements
  2. When traversing the list keep track of two variables
    * A pointer to the current element (e.g. `curr`)
    * A poitner to the previous element (e.g. `prev`)

4. A linked list is dynamically allocated data structure, so you need to implement _the big three_ (_cpy ctor_, _oper=_, and _dtor_) to manage it correctly. In PA2, `Cluster` has a default constructor, which initializes an _empty_ list.

5. The _optional_ private helper methods

   ```C++
   void __del();
   void __cpy(LNodePtr pts);
   bool __in(const Point &p) const;
   ```
   can be used to reuse code. `__del` is used in the destructor and overloaded assignment operator `operator=`, `__cpy` is used in the copy constructor and `operator=`, while `__in` can be helpful for testing, debugging, and even some method implementations.
   
6. Implement the members `add` and `remove` to add `Point`s to and remove `Point`s from a `Cluster`. Notice the `const Point &` arguments and return value for `remove`. The latter allows for a `Point` to be moved from one `Cluster` to another in one line of code, as follows:

   ```C++
   c5.add(c3.remove(p23));
   ```
   **Note:** `add` should create a new `Point` using the copy constructor and not add the argument directly, since it cannot have knowledge about the allocation of the referenced object. If that object is destroyed as its scope is exited, the added object will become invalid after the addition.
   
7. Implement the member `contains` to return `true` or `false` if the `Cluster` contains a `Point` equal (by `Point::operator==`) to the object referenced in the argument.

8. Implement the `const` member subscript `operator[]` to return a `const` reference to a particular `Point` in the ordered linked-list. The `Point` cannot be modified.
   **Note:** Don't overuse this operator, because it is very inefficient for a singly-linked list.

9. Implement the _compound assignment_ member `operator+=` and `operator-=` with a `const Point &` argument.

   **Usage:** Add a `Point` to or remove one from the `Cluster`:
   ```C++
   c5 += p56;
   c2 -= p98;
   ```
   **Note:** Implementation is straightforward through the use of `add` and `remove`.

10. Implement the simple arithmetic `friend` `operator+` and `operator-` with one `const Cluster &` and one `const Point &` arguments. A `friend` operator is a _non-member_ function with **private** access to the class where it is declared.

   **Usage:** Create and return a new `Cluster` with the argument `Point` added to or removed one from the argument `Cluster`:
   ```C++
   c7 = c5 + p56;
   c9 = c2 - p98;
   ```
   **Note:** Implementation is straightforward through the use of `operator+=` and `remove-=`.

11. 
_In progress..._

#### Clustering namespace

_In progress..._
