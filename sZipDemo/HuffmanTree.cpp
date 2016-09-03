#pragma once
#include "StdAfx.h"
#include "HuffmanTree.h"
#include "MinHeap.cpp"
#include <fstream>

template <class T>
HuffmanTree<T>::HuffmanTree(){
	WPL = 0;
	root = new HuffmanTreeNode<T>;

};

template <class T>
HuffmanTree<T>::~HuffmanTree(){
	deleteTree(root);                                           //ɾ����������
}

template <class T>
void HuffmanTree<T>::creat(char str[],char data[],unsigned int count[]){
    unsigned int size;                                          //�ַ��ĸ���
	for(unsigned int i = 0; i < 128; i++)                       //count�ĳ�ʼ��
		count[i] = 0;         

	census(count,data,str,size);
	minHeap<HuffmanTreeNode<T>> hp;
	HuffmanTreeNode<T> *parent, *first, *second;
	HuffmanTreeNode<T>  *work;

	for(unsigned int i = 0; i < size; i++){                                      //��ÿ��Ԫ�ض�������С����
		work = new HuffmanTreeNode<T>;
		work->data = data[i];
		work->count = count[i];
		work->leftChild = NULL;
		work->rightChild = NULL;
		work->parent = NULL;
		hp.insert(*work);
	}

	for(unsigned int i = 0; i < size-1; i++){
		parent = new HuffmanTreeNode<T>;
		first = new HuffmanTreeNode<T>;
		second = new HuffmanTreeNode<T>;
		hp.removeMin(*first);                                         //ÿ�δ���С����ȡ��������С����
		hp.removeMin(*second);
		
		parent->leftChild = first;                                    //parent��Ϊ���ǵĸ��ڵ�
		parent->rightChild = second;
		parent->count = first->count + second->count;
		parent->data = '#';                                           //parent���Ǹ�������԰�����data��Ϊ'#'
		first->parent = parent;
		second->parent = parent;
		hp.insert(*parent);                                           //�ٰ�parent������С���У�����ѭ���ж�

	}
	root = parent;                                                    //���һ��parent���Ǹ����

	char code[128];
	for(unsigned int i = 0;i < 128; i++)
		code[i] = 0;
	encode(root,code);                                                //�Խ����й��������루�յĵط�ȡ0��

};

template <class T>
void HuffmanTree<T>::creat(char data[],unsigned int count[]){
	unsigned int size = 0;
	for(unsigned int i = 0; count[i] != 0; i++)
		size++;

	minHeap<HuffmanTreeNode<T>> hp;
	HuffmanTreeNode<T> *parent, *first, *second;
	HuffmanTreeNode<T>  *work;

	for(unsigned int i = 0; i < size; i++){                                      //��ÿ��Ԫ�ض�������С����
		work = new HuffmanTreeNode<T>;
		work->data = data[i];
		work->count = count[i];
		work->leftChild = NULL;
		work->rightChild = NULL;
		work->parent = NULL;
		hp.insert(*work);
	}

	for(unsigned int i = 0; i < size-1; i++){
		parent = new HuffmanTreeNode<T>;
		first = new HuffmanTreeNode<T>;
		second = new HuffmanTreeNode<T>;
		hp.removeMin(*first);                                         //ÿ�δ���С����ȡ��������С����
		hp.removeMin(*second);
		
		parent->leftChild = first;                                    //parent��Ϊ���ǵĸ��ڵ�
		parent->rightChild = second;
		parent->count = first->count + second->count;
		parent->data = '#';                                           //parent���Ǹ�������԰�����data��Ϊ'#'
		first->parent = parent;
		second->parent = parent;
		hp.insert(*parent);                                           //�ٰ�parent������С���У�����ѭ���ж�

	}
	root = parent;                                                    //���һ��parent���Ǹ����

	char code[128];
	for(unsigned int i = 0;i < 128; i++)
		code[i] = 0;
	encode(root,code);                                                //�Խ����й��������루�յĵط�ȡ0��
}

template <class T>
void HuffmanTree<T>::deleteTree(HuffmanTreeNode<T> *subTree){
	if(subTree != NULL){
		deleteTree(subTree->leftChild);                          //���������ɾ�����
		deleteTree(subTree->rightChild);
		delete subTree;
	}
}

template <class T>
void HuffmanTree<T>::census(unsigned int count[],char data[],char str[],unsigned int &size){
	//����ͳ���ַ����ֵĴ���

	for(int i = 0; str[i] != 0;i++){
		if(str[i] == '#')                        //�����ֵ����ѳ��ֹ����ַ�ʱ��ִ���´�ѭ��
			continue;

		static int n = 0;
		count[n]++;                               //��һ�γ���ʱ��һ
		data[n] = str[i];
		for(int j = 0; str[j] != 0;j++){
			if(str[i] == str[j] && i != j){
				count[n]++;                    //ÿ�γ����ظ���ʱ���һ����
				str[j] = '#';                     //�����ѳ��ֹ�
			}
		}
		data[++n] = 0;
		size = n;
	}
}

template <class T>
void HuffmanTree<T>::encode(HuffmanTreeNode<T> *subTree,char code[] ,char m = 0){

	if(subTree != NULL){
		int j;
		for(j = 0;code[j] != 0;j++){
			subTree->code[j] = code[j];
		}
		for(j = 0;code[j] != 0;j++){
		}
		subTree->code[j] = m;
		subTree->code[j+1] = 0;
		encode(subTree->leftChild,subTree->code,'0');
		encode(subTree->rightChild,subTree->code,'1');
	}
}

template <class T>
void HuffmanTree<T>::calculateWPL(HuffmanTreeNode<T> *subTree,int i = 0){
	if(subTree != NULL){
		if(subTree->data != '#')
			WPL += i*subTree->count;                     //iΪ��ǰ����,countΪ���Ȩֵ
		calculateWPL(subTree->leftChild,++i);            //ǰ�����
		i--;
		calculateWPL(subTree->rightChild,++i);
		i--;
	}
}

template <class T>
int HuffmanTree<T>::getWPL(){
	return WPL;
}
