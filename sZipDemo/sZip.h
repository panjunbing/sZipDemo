#pragma once
#include "HuffmanTree.cpp"
class sZip
{
public:
	sZip(void);
	~sZip(void);
	void zip(char str1[],char str2[],HuffmanTreeNode<char>* subTree,int &size,char data[]);
	void unzip(char str1[],char str2[]);
private:
	bool codeEqual(char code1[],char code2[][128],int &num);
	void getHuffCode(HuffmanTreeNode<char>* subTree,char code[][128],char data[]);
	void strBinary(char str[],int &size);
	void binaryStr(char str1[]);
};

