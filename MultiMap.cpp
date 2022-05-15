#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>

using namespace std;

//best case: Theta(n)
//worst case: Theta(n)
// avg case: Theta(n)
// Total case: Theta(n)
MultiMap::MultiMap() {
	this->capacity = INITIAL_SIZE;
	this->actualSize = 0;

	//allocate space for the array
	this->elements = new TElem[this->capacity];

	//initialize array with NULL_TELEM
	for(int i = 0; i < this->capacity; i++)
	    this->elements[i] = NULL_TELEM;
}

//best case: Theta(1)
//worst case: Theta(n)
// avg case: Theta(n)
// Total case: O(n)
void MultiMap::add(TKey c, TValue v) {
    // if the load factor reaches a given value, we resize and rehash
    if(this->loadFactor() >= LOAD_FACTOR)
        this->resize();
    int i, position;
    // with i we will generate positions for the element (i - probe number)
	i = 0;
	position = this->hashingFunction(c, i);
	// we find first available position - deleted element or null element
    // our hashing function returns a permutation of the indexes of the array, so it is sure it'll find an empty
    // position.
	while(i < this->capacity && this->elements[position] > NULL_TELEM) {
        i++;
        position = this->hashingFunction(c, i);
    }
	this->elements[position] = TElem(c,v);
	this->actualSize++;
	}

//best case: Theta(1)
//worst case: Theta(n)
// avg case: Theta(n)
// Total case: O(n)
bool MultiMap::remove(TKey c, TValue v) {
	int i, position;
	i = 0;
    position = this->hashingFunction(c, i);
    // we hash the key until we find a NULL_TELEM. If we find it, means that the hasing didn't get that far, so
    // we don't need to check further.
    while(i < this->capacity && this->elements[position] != NULL_TELEM) {
        if(this->elements[position] == TElem(c, v))
        {
            // mark the element as deleted
            this->elements[position] = DELETED_TELEM;
            this->actualSize--;
            return true;
        }
        i++;
        position = this->hashingFunction(c, i);
    }
	return  false;
}

//best case: Theta(1)
//worst case: Theta(n)
// avg case: O(n)
// Total case: O(n)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> elementsMatchingKey {};
    int i, position;
    i = 0;
    position = this->hashingFunction(c, i);
    // if we get to NULL_TELEM, means hashing didn't get that far, so we don't have to look further
    while(i < this->capacity && this->elements[position] != NULL_TELEM) {
	    if(this->elements[position].first == c)
	        elementsMatchingKey.push_back(this->elements[position].second);
	    i++;
        position = this->hashingFunction(c, i);
    }
	return elementsMatchingKey;
}


//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
int MultiMap::size() const {
    return this->actualSize;
}



//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
bool MultiMap::isEmpty() const {
    return this->actualSize == 0;
}

//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
MultiMapIterator MultiMap::iterator() {
	return MultiMapIterator(*this);
}


//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
MultiMap::~MultiMap() {
	delete [] this->elements;
}

//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
int MultiMap::firstHash(TKey key) const{
    return abs(key) % this->capacity;
}

//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
int MultiMap::secondHash(TKey key) const{
    return 1 + (abs(key) % (this->capacity -1));
}

//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
int MultiMap::hashingFunction(TKey key, int i) const{
    long long result = ((long long) this->firstHash(key) + (long long) i * (long long)this->secondHash(key)) % (long long) this->capacity;
    return (int) result;
}

// resizes the hash table to one of at least double the size, whose capacity is a prime number
//best case: Theta(n)
//worst case: Theta(n)
// avg case: Theta(n)
// Total case: Theta(n)
void MultiMap::resize() {
    // compute the new capacity - at least double the old one, and a prime number
    int newCapacity = this->nextPrime(this->capacity * 2 + 1);
    // save the old array
    TElem* oldArray = this->elements;
    // create a new array
    this->elements = new TElem[newCapacity];

    // set null telem on every position in the new array
    for(int i=0; i< newCapacity; i++)
        this->elements[i] = NULL_TELEM;

    int oldCapacity = this->capacity;
    this->capacity = newCapacity;
    // set the old size to 0, because we will rehash
    this->actualSize = 0;
    // add back the old elements
    for(int i=0; i< oldCapacity; i++)
        if(oldArray[i] > NULL_TELEM)
            this->add(oldArray[i].first, oldArray[i].second);
    delete [] oldArray;
}

//checks if a number is prime
//best case: Theta(1)
//worst case: O(sqrt(n)/2) -> O(n)
//average case: O(n)
//Total case: O(n)
bool MultiMap::isPrime(int number) {
    if(number <= 1)
        return false;
    if(number == 2)
        return true;
    if(number % 2 == 0)
        return false;
    for(int divisor = 3; divisor * divisor <= number; divisor+= 2)
        if(number % divisor == 0)
            return false;
    return true;
}

// returns the next prime number >= than the number given as parameter
// complexity: O(gap * number), where gap is the gap between two prime numbers. The first gap of 233 is after 492113,
// so we can approximate the complexity to O(number) since the gap is relatively small
//best case: Theta(1)
//worst case: Theta(n)
// avg case: Theta(n)
// Total case: O(n)
int MultiMap::nextPrime(int number) {
    if(number % 2 == 0)
        number++;
    while(!this->isPrime(number))
        number+=2;
    return number;
}

// computes the load factor of the hash table:
//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
double MultiMap::loadFactor() {
    return (double) this->actualSize / (double) this->capacity;
}

