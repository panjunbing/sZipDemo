#include "StdAfx.h"
#include "sZip.h"
#include <iostream>
using namespace std;

sZip::sZip(void){

}


sZip::~sZip(void)
{
}

void sZip::zip(char str1[],char str2[],HuffmanTreeNode<char>* subTree,int &size,char data[]){
	char code[128][128];
	
	getHuffCode(subTree,code,data);                                            //��ȡsubTree�Ĺ���������
	unsigned int i = 0;
    unsigned int n = -1;
	for(; str1[i] != 0 ;i++){                                                //����str1����������ַ�ת��Ϊ�������������str2��
		int j = 0;
		while(data[j] != str1[i]){
			j++;
			if(data[j] == 0)
				break;
		}
		if(data[j] == str1[i]){
				for(int count = 0;code[j][count] != 0;count++)
					str2[++n] = code[j][count];
			str2[n+1]=0;
		}
	}
		strBinary(str2,size);                                                   //��str2��ÿһ���ַ����ÿһ��bit��8��bit�ϳ�һ���ַ�
}

void sZip::unzip(char str1[],char str2[]){

	unsigned int count[128];
	for(int i = 0;i < 127;i++)
		count[i] = 0;
	char code[128][128];
	char data[128];
	for(int i = 0;i < 128;i++)
		code[i][0] = 0;
	int i = 0;

	for(;str1[i] != '#';i++)
		data[i] = str1[i];
	data[i] = 0;
	int j = i+2;
	i = -1;
	while(1){
		if(str1[j] != '#' && str1[j+1] == '#')                                                    //��λ
			count[++i] = str1[j]-48;
		else if(str1[j+1] != '#' && str1[j+2] == '#'){                                            //ʮλ
			count[++i] = int(str1[j]-48)*10+int(str1[j+1]-48);
			j++;
		}
		else if(str1[j+1] != '#' && str1[j+2] != '#' && str1[j+3] == '#'){                        //��λ
			count[++i] = int(str1[j]-48)*100+int(str1[j+1]-48)*10+int(str1[j+2]-48);
			j = j+2;
		}
		else if(str1[j+1] != '#' && str1[j+2] != '#' && str1[j+3] != '#'&& str1[j+4] =='#'){      //ǧλ
			count[++i] = int(str1[j]-48)*1000+int(str1[j+1]-48)*100+int(str1[j+2]-48)*10+int(str1[j+3]-48);
		}
		else if(str1[j] == '#' && str1[j+1] == '#')                                               //����
			break;
		else
			cout<<"��ȡ����"<<endl; 
		j = j+2;
	}

	HuffmanTree<char> tree;
	tree.creat(data,count);
	getHuffCode(tree.root,code,data);

	j = j+2;
	i = -1;
	char tempchar[100000];
	for(;str1[j] != 0;j++)
		tempchar[++i] = str1[j];
	tempchar[i+1] = 0;
	binaryStr(tempchar);                                       //��ѹ���ļ�ת��Ϊ�����Ʊ���

	char tempcode[128];
	j = -1;
	int num;
	int n = -1;
	i = 0;
	for(;tempchar[i] != 0;i++){                            //����tempchar�������ӹ���������ת��Ϊ��Ӧ���ַ�
		tempcode[++n] = tempchar[i];
		tempcode[n+1] = 0;
		if(codeEqual(tempcode,code,num)){
			str2[++j] = data[num];
			for(n = 0;tempcode[n] != 0;n++)               //����tempcode
				tempcode[n] = 0;
			n = -1;
		}
		else
			continue;
	}
	str2[++j] = 0;
}

void sZip::getHuffCode(HuffmanTreeNode<char>* subTree,char code[][128],char data[]){
     for(int i = 0;data[i] != 0;i++)
		 findKey(subTree,data[i],code[i]);
}

void sZip::strBinary(char str[],int &size){
	char str2[100000];
	char bit[8];
	int n = 0;
	int count = 0;
	while(str[n] == '1' || str[n] == '0'){
		for(int i = 0;i < 8 ;i++){
			if(str[n] == 0){
				str[n] = '0';
				str[n+1] = 0;
			}
			bit[i] = str[n];
			n++;
		}
		str2[count] = 0;
		for(int i = 0;i < 8 ;i++){
			if(bit[i] == '1'){
				char temp = 1;
				str2[count] = (str2[count]<<1)|temp;                  //�������һλ����һ��������һλ��Ȼ���00000001���
			}
			else
				str2[count] = (str2[count]<<1);
		}
		count++;
	}
	for(int i = 0;i <= count;i++)
		str[i] = str2[i];
	for(int i = count;str[i] != 0;i++)
		str[i] = 0;
	size = count;
}

void sZip::binaryStr(char str1[]){
	char str2[100000];
	int i = -1;
	int n = 0;
	while(str1[n] != 0){
		int temp[8];
		int tempchar = abs(str1[n]);
		for(int count = 0;count < 8;count++){
			temp[count] = tempchar%2;
			tempchar /= 2;
		}
		if(str1[n]<0 && str1[n] > -128){                           //��Ϊ����ʱ��������Ϊ������һλΪ1������λ���ķ������һλ��һ�����룩
			temp[7] = 1;
			for(int count = 0;count < 7;count++){                  //����
				if(temp[count] == 0)
					temp[count] = 1;
				else
					temp[count] = 0;
			}
			int x = 1;                                            //��λ��
			for(int count = 0;count < 8;count++){                 //ĩλ��һ                                             
				if(temp[count] == 0){
					if(x == 1){
						temp[count] = 1;
						x = 0;
					}
				}
				else
					if(x == 1)
						temp[count] = 0;
			}
		}
		for(int count = 7;count != -1;count--)                    
			str2[++i] = char(temp[count]+48);
		n++;
	}
	str2[++i] = 0;
	for(int count = 0;count <= i;count++)
		str1[count] = str2[count];
}

bool sZip::codeEqual(char code1[],char code2 [][128],int &num){
	unsigned int size1 = 0;
	unsigned int size2 = 0;
	for(int i = 0;code1[i] != 0;i++)
		size1++;
	for(int i = 0;code2[i][0] != 0;i++)
		size2++;

	for(int i = 0;i < size2;i++){
		int j = 0;
		int size3 = 0;
		for(int n = 0;code2[i][n] != 0;n++)
		size3++;
		for(;j < size1;j++){
			if(code1[j] != code2[i][j])
			break;                                          //��һλ�����ھ�ֱ������
		}
		if(j == size1 && j == size3){
			num = i;
			return true;
		}
	}
	return false;
}