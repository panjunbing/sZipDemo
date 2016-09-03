#pragma once

template <class T>
struct HuffmanTreeNode{
	T data;                                                                         //����
	unsigned int count;                                                             //Ȩֵ
	char code[128];                                                                   //���Ĺ���������
	HuffmanTreeNode<T> *leftChild;                                                  //����Ů
	HuffmanTreeNode<T> *rightChild;                                                 //����Ů
	HuffmanTreeNode<T> *parent;                                                     //���ڵ�
	HuffmanTreeNode():leftChild(NULL),rightChild(NULL),parent(NULL){}               //���캯��

	bool operator <=(HuffmanTreeNode &R){return count <= R.count;}                  //����<=��>�����
	bool operator >(HuffmanTreeNode &R){return count > R.count;}

};

template <class T>
class HuffmanTree
{
public:
	HuffmanTree();
	HuffmanTree(HuffmanTree<T> &t);
	~HuffmanTree(void);

	void printData();
	int getWPL();                                                                            //��ȡWPL                                                                //���ļ�
	void creat(char str[],char data[],unsigned int count[]);                            //�������Ľ���
	void creat(char data[],unsigned int count[]);                                                //����
	
	template <class T>
	friend void findKey(HuffmanTreeNode<T> *subTree,T key,char code[]){                    //Ѱ�ҽ���code
		static T firstNodeData = subTree->data;
		if(subTree != NULL){
			if(subTree->data != key){
				findKey(subTree->leftChild,key,code);
				findKey(subTree->rightChild,key,code);
			}
			else{
				int i = 0;
				for(;subTree->code[i] != 0;i++)
					code[i] = subTree->code[i];
				code[i] = 0;
			}
		}
	}
	HuffmanTreeNode<T> *root;
protected:
	
private:
	int WPL;
	void census(unsigned int count[],char data[],char str[],unsigned int &size);       //������������ʱͳ�Ƹ��ַ����ֵĴ���
	void deleteTree(HuffmanTreeNode<T> *subTree);                                      //ɾ��subTree���������ӽ��
	void encode(HuffmanTreeNode<T> *subTree,char code[] ,char m = 0);                //����
	void calculateWPL(HuffmanTreeNode<T> *subTree,int i = 0);                          //����WPL
	void printCode(HuffmanTreeNode<T> *subTree);                                       //���������������Ӻ���
	void printData(HuffmanTreeNode<T> *subTree);                                       //������н��data��Ȩֵ���Ӻ���
};

