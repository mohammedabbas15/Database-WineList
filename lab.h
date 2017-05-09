#include <iostream>
#include <string>
#include <typeinfo>
#include <iomanip>
#include <cstdio>
using namespace std;

/* 
 * Example of Linked List in template format
 * 
 * You must implement function:void insertAtBack( const NODETYPE &, int);
 * 
 * */

#include "wine.h"
 

template< typename T > class List; // forward declaration

template< typename NODETYPE  >
class ListNode 
{

public:
   friend class List< NODETYPE >; // make List a friend
   ListNode( const NODETYPE & ); // constructor
   NODETYPE getData() const; // return the data in the node

   // set nextPtr to nPtr
   void setNextPtr( ListNode *nPtr ) 
   { 
      nextPtr = nPtr; 
   } // end function setNextPtr
   
   // return nextPtr
   ListNode *getNextPtr() const 
   { 
      return nextPtr; 
   } // end function getNextPtr

private:
   NODETYPE data; // data
   int key; // used for key for the list
   ListNode *nextPtr; // next node in the list
}; // end class ListNode

// constructor
template< typename NODETYPE >
ListNode< NODETYPE >::ListNode( const NODETYPE &info )
{
   data = info;
   nextPtr = 0;
} // end constructor

// return a copy of the data in the node
template< typename NODETYPE >
NODETYPE ListNode< NODETYPE >::getData() const 
{ 
   return data; 
} // end function getData


template< typename NODETYPE  >
class List 
{
public:
   List(); // default constructor
   List( const List< NODETYPE > & ); // copy constructor
   ~List(); // destructor

   void insertAtFront( const NODETYPE &, int );
   void insertAtBack( const NODETYPE &, int );
   bool removeFromFront( NODETYPE &value );
   bool removeFromBack( NODETYPE &value );
   bool isEmpty() const;
   void print() const;
   void printPtrFunc();
   void clear();
   bool empty();
   int size();
   NODETYPE * getInfo(int myKey);
      // return nextPtr
   ListNode< NODETYPE >  *getFirstPtr() const 
   { 
      return firstPtr; 
   } // end function getNextPtr
   
 protected:
   ListNode< NODETYPE > *firstPtr; // pointer to first node
   ListNode< NODETYPE > *lastPtr; // pointer to last node

   // Utility function to allocate a new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE &, int );
}; // end class template List

// size function
template< typename NODETYPE >
int List< NODETYPE >::size() 
{ 
	int size = 0;
	ListNode< NODETYPE >  *currentPtr = getFirstPtr();
	while(currentPtr)
	{
		size++;
		currentPtr = currentPtr->getNextPtr();
	}
	return size;
}

template< typename NODETYPE >
bool List< NODETYPE >::empty() 
{ 
	return size() == 0;
}

// clear function
template< typename NODETYPE >
void List< NODETYPE >::clear() 
{ 
	NODETYPE value;
	while(!isEmpty())
	{
		removeFromBack(value);
	}
}

// default constructor
template< typename NODETYPE >
List< NODETYPE >::List() 
{ 
   firstPtr = lastPtr = 0; 
} // end constructor

// copy constructor
template< typename NODETYPE >
List< NODETYPE >::List( const List<NODETYPE> &copy )
{
   firstPtr = lastPtr = 0; // initialize pointers

   ListNode< NODETYPE > *currentPtr = copy.firstPtr;

   // insert into the list
   while ( currentPtr != 0 ) 
   {
      insertAtBack( currentPtr->data );
      currentPtr = currentPtr->nextPtr;
   } // end while
} // end List copy constructor

// destructor
template< typename NODETYPE >
List< NODETYPE >::~List()
{
   if ( !isEmpty() ) // List is not empty
   {
      ListNode< NODETYPE > *currentPtr = firstPtr;
      ListNode< NODETYPE > *tempPtr;

      while ( currentPtr != 0 ) // delete remaining nodes
      {
         tempPtr = currentPtr;
//         cout << tempPtr->data << ' ';
         currentPtr = currentPtr->nextPtr;
         delete tempPtr;
      } // end while
   } // end if
} // end destructor

// Insert a node at the front of the list
template< typename NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value,
  int key)
{
   ListNode<NODETYPE> *newPtr = getNewNode( value, key );

   if ( isEmpty() ) // List is empty
      firstPtr = lastPtr = newPtr;
   else // List is not empty
   {
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;
   } // end else
} // end function insertAtFront

// Insert a node at the back of the list
template< typename NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value,
  int key)
{
  ListNode<NODETYPE> *newPtr = getNewNode(value, key);
	if(isEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
} // end function insertAtBack

// Delete a node from the front of the list
template< typename NODETYPE >
bool List< NODETYPE >::removeFromFront(NODETYPE &value)
{
   if ( isEmpty() ) // List is empty
      return false; // delete unsuccessful
   else 
   {
      ListNode< NODETYPE > *tempPtr = firstPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else
         firstPtr = firstPtr->nextPtr;

      value = tempPtr->data; // data being removed

      delete tempPtr;
      return true; // delete successful
   } // end else
} // end function removeFromFront

// delete a node from the back of the list
template< typename NODETYPE >
bool List< NODETYPE >::removeFromBack(NODETYPE &value)
{
	/*
	 * Implement this function.  Use removeFromFront as an
	 * example in implemeting this function
	 * */
	 
   if ( isEmpty() )
      return false; // delete unsuccessful
   else 
   {
      ListNode< NODETYPE > *tempPtr = lastPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else 
      {
		  
         ListNode< NODETYPE > *currentPtr = firstPtr;

	/*  this is where you need add more code
	 * First, you need to start from the beginning of the linked list,
	 * and traverse until the node before the last node.
	 * 
	 * Once you got to the node before the last node, you need to 
	 * point the node before last node to the last node so you can 
	 * remove the last node
	 * 
	 * */
	 while(currentPtr->nextPtr != lastPtr)
	 {		 currentPtr = currentPtr->nextPtr;
	 }
	 
	 lastPtr = currentPtr;
	 currentPtr->nextPtr = NULL;
	 
      // your codes here
      // more codes
  
      } // end else
      
      delete tempPtr;
      //currentPtr->nextPtr = NULL;
      return true; // delete successful
   } // end else
} // end function removeFromBack

// Is the List empty?
template< typename NODETYPE >
bool List< NODETYPE >::isEmpty() const 
{ 
   return firstPtr == 0; 
} // end function isEmpty

// Return a pointer to a newly allocated node
template< typename NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode(
   const NODETYPE &value, int)
{
   ListNode< NODETYPE > *ptr = new ListNode< NODETYPE >( value );
   return ptr;
} // end function getNewNode

// Display the contents of the List
template< typename NODETYPE >
void List< NODETYPE >::print() const
{
   if ( isEmpty() ) // empty list
   {
      cout << "The list is empty\n\n";
      return;
   } // end if

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) // display elements in list
   {
       int i;
       string s;
       double d;
       char c;
       if (typeid(currentPtr->data).name() == typeid(i).name() ||
           typeid(currentPtr->data).name() == typeid(d).name() ||
           typeid(currentPtr->data).name() == typeid(s).name() ||
           typeid(currentPtr->data).name() == typeid(c).name())
       {
        // data value is a simple data type and can be printed
        cout << currentPtr->data << ' ';
       }
       else {
         cout <<"Can't print - Not a simple data type (int, string, char, double)\n";
       }
      currentPtr = currentPtr->nextPtr;
   } // end while

   cout << "\n\n";
} // end function print

   
// Display the contents of the List
template< typename NODETYPE >
NODETYPE * List< NODETYPE >::getInfo(int myKey)
{
   if ( isEmpty() ) // empty list
   {
      cout << "The list is empty\n\n";
      return NULL;
   } // end if

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) // display elements in list
   {
        if (currentPtr->key == myKey )  // found
           return (& currentPtr->data);
 
      currentPtr = currentPtr->nextPtr;
   } // end while

   return NULL;  // can't find
} // end function print



template< typename NODETYPE >
void printNoteInfo (  List< NODETYPE > & nodeList)
{        
   cout << "The node list is : " << endl;

    ListNode < NODETYPE > *currentPtr = nodeList.getFirstPtr();   
   while (currentPtr)
   {
      cout << currentPtr->getData() << endl;
      currentPtr = currentPtr->getNextPtr();
   }
}   
         


