#include "MultiMapIterator.h"
#include "MultiMap.h"

//best case: Theta(n)
//worst case: Theta(n)
// avg case: Theta(n)
// Total case: Theta(n)
MultiMapIterator::MultiMapIterator(MultiMap& c): col(c) {
    this->elems = new TElem[this->col.actualSize];
    this->index = 0;
    while(this->index < this->col.capacity && this->col.elements[this->index] <= NULL_TELEM) {
        this->index++;
    }
    for (int i = 0; i < this->col.actualSize; ++i){
        this->elems[i] = this->col.elements[this->index];
        this->index++;
        while(this->index < this->col.capacity && this->col.elements[this->index] <= NULL_TELEM) {
            this->index++;
        }

    }
    //this->sort(this->elems, this->col.actualSize);
	this->first();
}

//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
// if the iterator is not valid, throws an exception
TElem MultiMapIterator::getCurrent() const{
    if(!this->valid())
        throw std::exception();
	return this->elems[this->index];
}

//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
bool MultiMapIterator::valid() const {
	return this->index < this->col.actualSize;
}

//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
void MultiMapIterator::next() {
    if(!this->valid())
        throw std::exception();
    this->index++;
}

// sets the iterator to point to the first non-empty element in the hash table
// if the hash table is empty, the iterator becomes invalid
//best case: Theta(1)
//worst case: Theta(1)
// avg case: Theta(1)
// Total case: Theta(1)
void MultiMapIterator::first() {
	this->index = 0;
}






//best case: Theta(nlogn)
//worst case: Theta(nlogn)
// avg case: Theta(nlogn)
// Total case: Theta(nlogn)
void MultiMapIterator::sort(TElem *start, int l) {
    if(l==1){
        return;
    }
    if(l>1){
        int m = l/2;
        this->sort(start,m);
        this->sort(start+m+1,m);
        mergeForSort(start,0,l,m);
    }
}


//best case: Theta(nlogn)
//worst case: Theta(nlogn)
// avg case: Theta(nlogn)
// Total case: Theta(nlogn)
void MultiMapIterator::mergeForSort(TElem *arr, int low, int high, int mid) {
    int i, j, k;
    TElem  c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j < high) {
        if (arr[i].first < arr[j].first) {
            c[k] = arr[i];
            k++;
            i++;
        }
        else  {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j < high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < low; i++)  {
        arr[i] = c[i];
    }
}



