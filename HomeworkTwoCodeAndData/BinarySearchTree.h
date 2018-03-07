/*******************************************************************************
  Title          : BinarySearchTree.h
  Author         : Wei Lian
  Created on     : March 7, 2018
  Description    : Implementation to the binary search tree class with interface
  Purpose        : 
  Usage          : 
  Build with     : 
  Modifications  : 

*******************************************************************************/
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove_call++;
        remove( x, root );
    }
    //get the numbers of nodes
    int get_num_nodes()
    {
        //initialize the value to 0 everytime it is called
        num_nodes=0;
        return get_num_nodes(root);
    }
    //get the numbers of path length
    int get_internal_length()
    {
         //initialize the value to 0 everytime it is called
        internal_length=0;
        return get_internal_length(internal_length,root);
    }
    //the find function that call the recursive function
    void find(const Comparable & x)
    {
        //counter to record the the number of time the find function has been called
        find_call++;
        find(x,root);
    }
    //the function return the number of successfully found
    int find_success()
    {
        return found;
    }
    //the total number of recursive calls
    int find_total()
    {
        return find_num;
    }
    //the number of find function has been called
    int find_calla()
    {
        return find_call;
    }
    //the number of remove function has been called
    int remove_calla()
    {
        return remove_call;
    }
    //total number of recursive function has been called
    int remove_total()
    {
        return total_remove;
    }
    //the number of successfully calls
    int remove_success()
    {
        return removed;
    }


  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;
    int num_nodes=0;
    int internal_length=0;
    int find_num =0;
    int find_call=0;
    int found =0;
    int total_remove=0;
    int remove_call=0;
    int removed=0;

    //the recursive function that finds the internal path length
    int get_internal_length(int internal_length,BinaryNode * & t)
    {
        if(t==nullptr)
            return 0;
        return(internal_length+get_internal_length(internal_length+1,t->right)+get_internal_length(internal_length+1,t->left));
    }
    //the recursive function that get the total number of nodes
    int get_num_nodes(BinaryNode * & t)
    {
        if(t==nullptr)
            return 0;
        if(t->left!=nullptr)
        {
            num_nodes=num_nodes+1;
            num_nodes=get_num_nodes(t->left);
        }
        if(t->right!=nullptr)
        {
            num_nodes=num_nodes+1;
            num_nodes=get_num_nodes(t->right);
        }
        return num_nodes;
    }
    //the find recursive function
    //x is the element we want to find
    //t is the position of the node
    void find( const Comparable & x, BinaryNode * & t )
    {
        find_num=find_num+1;
        if( t == nullptr )
        {
            ;
        }
        else if( x < t->element )
         {
            find( x, t->left );
         }   
        else if( t->element < x )
            find( x, t->right );
        else
        {
            found=found+1;   // Match
            find_call++;
        }
    }
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            t->element.Merge(x);  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x);  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        total_remove++;
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            removed++;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
        {
            cout<<"not found"<<endl;
            return false;
        }
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
        {
            cout<<t->element<<endl;
            return true;    // Match
        }
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif
