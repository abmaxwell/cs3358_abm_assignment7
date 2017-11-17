// FILE: DPQueue.cpp
// IMPLEMENTS: p_queue (see DPQueue.h for documentation.)
//
// INVARIANT for the p_queue class:
//   1. The number of items in the p_queue is stored in the member
//      variable used.
//   2. The items themselves are stored in a dynamic array (partially
//      filled in general) organized to follow the usual heap storage
//      rules.
//      2.1 The member variable heap stores the starting address
//          of the array (i.e., heap is the array's name). Thus,
//          the items in the p_queue are stored in the elements
//          heap[0] through heap[used - 1].
//      2.2 The member variable capacity stores the current size of
//          the dynamic array (i.e., capacity is the maximum number
//          of items the array currently can accommodate).
//          NOTE: The size of the dynamic array (thus capacity) can
//                be resized up or down where needed or appropriate
//                by calling resize(...).
// NOTE: Private helper functions are implemented at the bottom of
// this file along with their precondition/postcondition contracts.

#include <cassert>   // provides assert function
#include <iostream>  // provides cin, cout
#include <iomanip>   // provides setw
#include <cmath>     // provides log2
#include "DPQueue.h"

using namespace std;

namespace CS3358_FA17A7
{
   // EXTRA MEMBER FUNCTIONS FOR DEBUG PRINTING
   void p_queue::print_tree(const char message[], size_type i) const
   // Pre:  (none)
   // Post: If the message is non-empty, it has first been written to
   //       cout. After that, the portion of the heap with root at
   //       node i has been written to the screen. Each node's data
   //       is indented 4*d, where d is the depth of the node.
   //       NOTE: The default argument for message is the empty string,
   //             and the default argument for i is zero. For example,
   //             to print the entire tree of a p_queue p, with a
   //             message of "The tree:", you can call:
   //                p.print_tree("The tree:");
   //             This call uses the default argument i=0, which prints
   //             the whole tree.
   {
      const char NO_MESSAGE[] = "";
      size_type depth;

      if (message[0] != '\0')
         cout << message << endl;

      if (i >= used)
         cout << "(EMPTY)" << endl;
      else
      {
         depth = size_type( log( double(i+1) ) / log(2.0) + 0.1 );
         if (2*i + 2 < used)
            print_tree(NO_MESSAGE, 2*i + 2);
         cout << setw(depth*3) << "";
         cout << heap[i].data;
         cout << '(' << heap[i].priority << ')' << endl;
         if (2*i + 1 < used)
            print_tree(NO_MESSAGE, 2*i + 1);
      }
   }

   void p_queue::print_array(const char message[]) const
   // Pre:  (none)
   // Post: If the message is non-empty, it has first been written to
   //       cout. After that, the contents of the array representing
   //       the current heap has been written to cout in one line with
   //       values separated one from another with a space.
   //       NOTE: The default argument for message is the empty string.
   {
      if (message[0] != '\0')
         cout << message << endl;

      if (used == 0)
         cout << "(EMPTY)" << endl;
      else
         for (size_type i = 0; i < used; i++)
            cout << heap[i].data << ' ';
   }

   // CONSTRUCTORS AND DESTRUCTOR

   p_queue::p_queue(size_type initial_capacity) : capacity(initial_capacity),
                                                  used(0)
   {
      // Adjust capacity based on user specified initial_capacity. Any attempt
      // to specify a value <= 0 will be set to default capacity.
      if(initial_capacity < 1){capacity = DEFAULT_CAPACITY;}

      // Allocate new dynamic array based on specified capacity.
      heap = new ItemType[capacity];
   }

   p_queue::p_queue(const p_queue& src) : capacity(src.capacity), used(src.used)
   {
      // Create a new dynamic array based on src capacity.
      heap = new ItemType[capacity];

      // Deep copy each item src to the new dynamic array.
      for(size_type index = 0; index < capacity; ++index)
         heap[index] = src.heap[index];
   }

   p_queue::~p_queue()
   {
      delete [] heap;
   }

   // MODIFICATION MEMBER FUNCTIONS
   p_queue& p_queue::operator=(const p_queue& rhs)
   {
      // Self-assignment fail safe. Check for self-assignment.
      // If self-assignment is present then return invoking object.
      if (this == &rhs)
         return *this;

      // Create temporary dynamic array to safely assign contents
      // of array.
      ItemType *temp_heap = new ItemType[rhs.capacity];

      // Moved contents of rhs array to temp
      for (size_type index = 0; index < rhs.used; ++index) {
         temp_heap[index] = rhs.heap[index];
      }

      // Deallocate old dynamic array.
      delete [] heap;

      // Start assigning member variables from rhs.
      heap = temp_heap;
      capacity = rhs.capacity;
      used = rhs.used;
      return *this;
   }

   void p_queue::push(const value_type& entry, size_type priority)
   {
      // Check to see if we need to resize the dynamic array. If
      // we do the multiple current capacity by 1.25 and add +1 to
      // satisfy the resize rule seen in previous assignments.
      if(used == capacity){resize(size_type (1.25 * capacity)+1);}

      // Copy new items into heap and update used.
      heap[used].data = entry;
      heap[used].priority = priority;
      ++used;

      // While the new entry has a priority that is higher than its parent,
      // swap the new entry with the parent.
      for(size_type index = used; index != 0; index = parent_index(index)){
         if(heap[index].priority > parent_priority(index)){
            swap_with_parent(index);
         } else { break;}
      }
   }

   void p_queue::pop()
   {
      cerr << "pop() not implemented yet" << endl;
   }

   // CONSTANT MEMBER FUNCTIONS

   p_queue::size_type p_queue::size() const
   {
      cerr << "size() not implemented yet" << endl;
      return 0; // dummy return value
   }

   bool p_queue::empty() const
   {
      cerr << "empty() not implemented yet" << endl;
      return false; // dummy return value
   }

   p_queue::value_type p_queue::front() const
   {
      cerr << "front() not implemented yet" << endl;
      return value_type(); // dummy return value
   }

   // PRIVATE HELPER FUNCTIONS
   void p_queue::resize(size_type new_capacity)
   // Pre:  (none)
   // Post: The size of the dynamic array pointed to by heap (thus
   //       the capacity of the p_queue) has been resized up or down
   //       to new_capacity, but never less than used (to prevent
   //       loss of existing data).
   //       NOTE: All existing items in the p_queue are preserved and
   //             used remains unchanged.
   {
      cerr << "resize(size_type) not implemented yet" << endl;
   }

   bool p_queue::is_leaf(size_type i) const
   // Pre:  (i < used)
   // Post: If the item at heap[i] has no children, true has been
   //       returned, otherwise false has been returned.
   {
      cerr << "is_leaf(size_type) not implemented yet" << endl;
      return false; // dummy return value
   }

   p_queue::size_type
   p_queue::parent_index(size_type i) const
   // Pre:  (i > 0) && (i < used)
   // Post: The index of "the parent of the item at heap[i]" has
   //       been returned.
   {
      assert((i > 0) && (1 < used));
      return ((i/2)-1);
   }

   p_queue::size_type
   p_queue::parent_priority(size_type i) const
   // Pre:  (i > 0) && (i < used)
   // Post: The priority of "the parent of the item at heap[i]" has
   //       been returned.
   {
      assert((i > 0) && (1 < used));
      return heap[parent_index(i)].priority;
   }

   p_queue::size_type
   p_queue::big_child_index(size_type i) const
   // Pre:  is_leaf(i) returns false
   // Post: The index of "the bigger child of the item at heap[i]"
   //       has been returned.
   //       (The bigger child is the one whose priority is no smaller
   //       than that of the other child, if there is one.)
   {
      cerr << "big_child_index(size_type) not implemented yet" << endl;
      return 0; // dummy return value
   }

   p_queue::size_type
   p_queue::big_child_priority(size_type i) const
   // Pre:  is_leaf(i) returns false
   // Post: The priority of "the bigger child of the item at heap[i]"
   //       has been returned.
   //       (The bigger child is the one whose priority is no smaller
   //       than that of the other child, if there is one.)
   {
      cerr << "big_child_priority(size_type) not implemented yet" << endl;
      return 0; // dummy return value
   }

   void p_queue::swap_with_parent(size_type i)
   // Pre:  (i > 0) && (i < used)
   // Post: The item at heap[i] has been swapped with its parent.
   {
      cerr << "swap_with_parent(size_type) not implemented yet" << endl;
   }
}

