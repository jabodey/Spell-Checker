// HashSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"
#include <iostream>



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    int hash_size;
    int capacity = DEFAULT_CAPACITY;
    HashFunction hashFunction;
    struct Node
    {
    T key;
    Node* next = nullptr;
    };
    Node** hash;
};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
hash = new Node* [capacity];
//capacity = DEFAULT_CAPACITY;
for(int i = 0; i < capacity; ++i)
    {
    hash[i] = new Node;
    hash[i]->next = nullptr;
    }
hash_size = 0;
}


template <typename T>
HashSet<T>::~HashSet()
{
for(int x = 0; x < capacity; ++x)
    delete hash[x];
delete hash;
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{nullptr}
{
hash = new Node*[capacity];

for(int i = 0; i < capacity; ++i)
    {
    Node* temp = s.hash[i];

    if(temp == nullptr)
    {
    hash[i] = nullptr;
    continue;
    }

    hash[i] = new Node;
    hash[i]->key = temp->key;

    while(temp->next != nullptr)
    {
    temp = temp->next;
    hash[i]->next = new Node;
    hash[i] = hash[i]->next;
    hash[i]->key = temp->key;
    }

    hash[i]->next = nullptr;
    }
}


template <typename T>
HashSet<T>::HashSet(HashSet&& s)
    : hashFunction{nullptr}
{
std::swap(s.hash, hash);
std::swap(s.hashFunction, hashFunction);
//std::swap(temp.hash_size, hash_size);
//std::swap(temp.capacity, capacity);
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
if(this != &s)
{
HashSet temp(s);
std::swap(temp.hashFunction, hashFunction);
std::swap(temp.hash, hash);
std::swap(temp.hash_size, hash_size);
std::swap(temp.capacity, capacity);
//hashFunction = s.hashFunction;
//hash = s.hash;
}
return *this;
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(HashSet&& s)
{   
std::swap(hash, s.hash);
std::swap(hashFunction, s.hashFunction);
std::swap(capacity, s.capacity);
std::swap(hash_size, s.hash_size);
return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
if((hash_size/capacity) > 0.8)
    {
    int old_capacity = capacity;
    Node** old_hash = hash;
    capacity = (capacity * 2);
    hash = new Node* [capacity];
    for(int i = 0; i < old_capacity; ++i)
        {
        for(Node* ptr = old_hash[i]; ptr->next != nullptr; ptr = ptr->next)
            {
            hash[i]->key = ptr->key;
            hash[i]->next = ptr->next;
            hash[i] = hash[i]->next;
            }
        }
    }
int index = hashFunction(element) % capacity;
Node* temp = hash[index];
if (temp == nullptr)
    {
    temp = new Node{element};
    }
else
    {
    while (temp != nullptr)
        {
        temp = temp->next;
        }
    temp = new Node{element};
    }

}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{   
    int index = (hashFunction(element)) % capacity;
    for(Node* hashList = hash[index]; hashList->next != nullptr; hashList = hashList->next)
        {
        if (hashList->key == element)
            return true;
        }
    return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return hash_size;
}



#endif // HASHSET_HPP

