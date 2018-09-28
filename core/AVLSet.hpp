// AVLSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node
    {
    T key;
    Node* left = nullptr;
    Node* right = nullptr;
    };
    int AVL_size;
    Node* head;
public:
    void destroyAll(Node* curr);
    Node* copy(Node* t);
};

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::copy(Node* t)
{
if (t == nullptr)
    return nullptr;
AVL_size++;
return new Node{t->key, copy(t->left), copy(t->right)};
}

template <typename T>
void AVLSet<T>::destroyAll(Node* curr)
{
if (curr != nullptr)
    {
    destroyAll(curr->left);
    destroyAll(curr->right);
    delete curr;
    }
curr = nullptr;
}

template <typename T>
AVLSet<T>::AVLSet()
{
AVL_size = 0;
head = nullptr;
}


template <typename T>
AVLSet<T>::~AVLSet()
{
destroyAll(head);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
head = nullptr;
head = copy(s.head);
}


template <typename T>
AVLSet<T>::AVLSet(AVLSet&& s)
{
head = nullptr;
std::swap(head, s.head);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    if (this != &s)
        {
        destroyAll(head);
        head = nullptr;
        head = copy(s.head);
        AVL_size = s.size();
        }
    return *this;
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(AVLSet&& s)
{
    std::swap(head, s.head);
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{   
    Node* curr = head;
    while (curr != nullptr)
    {
    if (curr->key == element)
        {
        return true;
        }
    if (curr->key < element)
        {
        curr = curr->right;
        }
    if (curr->key > element)
        {
        curr = curr->left;
        }
    }
    return false;
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return AVL_size;
}



#endif // AVLSET_HPP

