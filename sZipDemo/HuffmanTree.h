#pragma once

template <class T>
struct HuffmanTreeNode{
	T data;                                                                         //数据
	unsigned int count;                                                             //权值
	char code[128];                                                                   //结点的哈弗曼编码
	HuffmanTreeNode<T> *leftChild;                                                  //左子女
	HuffmanTreeNode<T> *rightChild;                                                 //右子女
	HuffmanTreeNode<T> *parent;                                                     //父节点
	HuffmanTreeNode():leftChild(NULL),rightChild(NULL),parent(NULL){}               //构造函数

	bool operator <=(HuffmanTreeNode &R){return count <= R.count;}                  //重载<=和>运算符
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
	int getWPL();                                                                            //获取WPL                                                                //打开文件
	void creat(char str[],char data[],unsigned int count[]);                            //哈弗曼的建立
	void creat(char data[],unsigned int count[]);                                                //重载
	
	template <class T>
	friend void findKey(HuffmanTreeNode<T> *subTree,T key,char code[]){                    //寻找结点的code
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
	void census(unsigned int count[],char data[],char str[],unsigned int &size);       //建立哈弗曼树时统计各字符出现的次数
	void deleteTree(HuffmanTreeNode<T> *subTree);                                      //删除subTree结点的所有子结点
	void encode(HuffmanTreeNode<T> *subTree,char code[] ,char m = 0);                //编码
	void calculateWPL(HuffmanTreeNode<T> *subTree,int i = 0);                          //计算WPL
	void printCode(HuffmanTreeNode<T> *subTree);                                       //输出哈弗曼编码的子函数
	void printData(HuffmanTreeNode<T> *subTree);                                       //输出所有结点data和权值的子函数
};

