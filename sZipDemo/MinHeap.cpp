#pragma once
#include "StdAfx.h"
#include "MinHeap.h"

template<class E>
minHeap<E>::minHeap(int size){
	maxHeapSize = (DafaultSize<size)? size:DafaultSize;

	heap = new E[maxHeapSize];
	if(heap == NULL){
		//cout<<"堆存储分配失败"<<endl;
	}
	currentSize = 0;
};

template<class E>
minHeap<E>::~minHeap(){
	delete heap;
}

template<class E>
void minHeap<E>::siftDown(int start, int m){
	int i = start;                       //初始位置
	int j = 2*i+1;                       //j是i的左子女位置
	E temp = heap[i];   
	while(j <= m){ 
		if(j<m && heap[j] > heap[j+1])   //左子女大于右子女时，j指向右子女
			j++;
		if(temp <= heap[j])
			break;
		else{                            //大则向上移
			heap[i] = heap[j];
			i = j;
			j = 2*j+1;
		}
	}
	heap[i] = temp;
};

template<class E>
void minHeap<E>::siftUp(int start){
	int j = start;
	int i = (j-1)/2;                //i的左子女是j
	E temp = heap[j];
	while(j>0){
		if(heap[i] <= temp)        //如果父节点大
			break;
		else{                      //如果父节点小,上滑
			heap[j] = heap[i];     
			j = i;
			i = (i-1)/2;
		}
	}
	heap[j] = temp;
};

template<class E>
bool minHeap<E>::insert(const E& x){
	if(currentSize == maxHeapSize){     //堆满时
	//	cout<<"堆已满"<<endl;
		return false;
	}
	heap[currentSize] = x;              //在heap尾插入x
	siftUp(currentSize);                //对x进行上滑判断
	currentSize++;
	return true;
};

template<class E>
bool minHeap<E>::removeMin(E& x){
	if(currentSize == 0){                  //堆空时
	//	cout<<"堆为空！！"<<endl;
		return false;
	}
	x = heap[0];                           //从heap头获取remove的数据
	heap[0] = heap[currentSize-1];         //从heap尾获取元素补到heap头的位置
	currentSize--;                         //元素个数减一
	siftDown(0,currentSize-1);             //再对heap从头到尾进行下滑判断
	return true;
};
