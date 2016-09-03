#pragma once

#define DafaultSize 50

template<class E>
class minHeap{
public:
	minHeap(int size = DafaultSize);
	~minHeap();

	bool insert(const E& x);
	bool removeMin(E& x);

private:
	E *heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
};

