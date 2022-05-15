    #pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
    private:
    struct Node{
        int key;
        int size, capacity;
        TValue *values;
        Node* next;

        Node(); //Theta(1)
    };
    int dict_size; // number of elements
    int capacity;
    Node** dict;
    Relation comp;

    //hash function for the hash table
    //Complexity: Theta(1)
    int hash_function_1(int key) const {
        return key% this->capacity;
    }

    //hash function for the hash table
    //Complexity: Theta(1)
    int hash_function_2(int key) const {
        return (104729 - key % 104729);
    }

    //resize the hash table by doubling its capacity
    void resize();  //Theta(n)

    //resize the dynamic array in Node
    static void resize(Node *node); //Theta(n), n is the number of links in the list

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
