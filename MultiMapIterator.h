#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	MultiMap& col;
	MultiMapIterator(MultiMap& c);

    // our iterator is an index in the array of elements
    TElem *elems;
    int index;

    void sort(TElem *start, int l);
    void mergeForSort(TElem *arr, int low, int high, int mid);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
};

