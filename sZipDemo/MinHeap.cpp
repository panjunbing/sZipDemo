#pragma once
#include "StdAfx.h"
#include "MinHeap.h"

template<class E>
minHeap<E>::minHeap(int size){
	maxHeapSize = (DafaultSize<size)? size:DafaultSize;

	heap = new E[maxHeapSize];
	if(heap == NULL){
		//cout<<"�Ѵ洢����ʧ��"<<endl;
	}
	currentSize = 0;
};

template<class E>
minHeap<E>::~minHeap(){
	delete heap;
}

template<class E>
void minHeap<E>::siftDown(int start, int m){
	int i = start;                       //��ʼλ��
	int j = 2*i+1;                       //j��i������Ůλ��
	E temp = heap[i];   
	while(j <= m){ 
		if(j<m && heap[j] > heap[j+1])   //����Ů��������Ůʱ��jָ������Ů
			j++;
		if(temp <= heap[j])
			break;
		else{                            //����������
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
	int i = (j-1)/2;                //i������Ů��j
	E temp = heap[j];
	while(j>0){
		if(heap[i] <= temp)        //������ڵ��
			break;
		else{                      //������ڵ�С,�ϻ�
			heap[j] = heap[i];     
			j = i;
			i = (i-1)/2;
		}
	}
	heap[j] = temp;
};

template<class E>
bool minHeap<E>::insert(const E& x){
	if(currentSize == maxHeapSize){     //����ʱ
	//	cout<<"������"<<endl;
		return false;
	}
	heap[currentSize] = x;              //��heapβ����x
	siftUp(currentSize);                //��x�����ϻ��ж�
	currentSize++;
	return true;
};

template<class E>
bool minHeap<E>::removeMin(E& x){
	if(currentSize == 0){                  //�ѿ�ʱ
	//	cout<<"��Ϊ�գ���"<<endl;
		return false;
	}
	x = heap[0];                           //��heapͷ��ȡremove������
	heap[0] = heap[currentSize-1];         //��heapβ��ȡԪ�ز���heapͷ��λ��
	currentSize--;                         //Ԫ�ظ�����һ
	siftDown(0,currentSize-1);             //�ٶ�heap��ͷ��β�����»��ж�
	return true;
};
