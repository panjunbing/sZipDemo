// sZipDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "HuffmanTree.cpp"
#include "sZip.h"
#include <fstream>
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
	char str1[5000];
	ifstream in;
	in.open("text.txt",ios::in|ios::binary);
	in.read(str1,1000);
		in>>str1;
	cout<<"�ɹ���ȡtext.txt��"<<endl;
	int num = in.gcount();
	str1[0] = 'M';
	str1[num] = 0;
	in.close();
	
	char tempstr[5000];
	for(int i = 0;i <= num;i++)
		tempstr[i] = str1[i];
	tempstr[num] = 0;

	unsigned int count[128];
	char data[128];
	
	HuffmanTree<char> Tree;
	Tree.creat(tempstr,data,count);

	char charCount[256];
	for(int i = 0;count[i] != 0;i++){
		static int n = -1;
		if(count[i] < 10){                                                //��λ
			charCount[++n] = count[i]+48;
			charCount[++n] = '#';
		}
		else if(count[i] >= 10 && count[i] < 100){                        //ʮλ
			charCount[++n] = count[i]/10+48;
			charCount[++n] = count[i]%10+48;
			charCount[++n] = '#';
		}
		else if(count[i] >= 100 && count[i] < 1000){                      //��λ
			charCount[++n] = count[i]/100+48;
			charCount[++n] = count[i]%100/10+48;
			charCount[++n] = count[i]%10+48;
			charCount[++n] = '#';
		}
		else{                                                             //ǧλ
			charCount[++n] = count[i]/1000+48;
			charCount[++n] = count[i]%1000/100+48;
			charCount[++n] = count[i]%100/10+48;
			charCount[++n] = count[i]%10+48;
			charCount[++n] = '#';

		}
		charCount[n+1] = 0;
	}

	ofstream out;
	out.open("text1.txt",ios::out|ios::binary|ios::trunc);

	char tempData[128];
	for(int i = 0;i <= 128;i++)
		tempData[i] = data[i];
	sZip zip;
	char str2[5000];
	int size = 0;
	zip.zip(str1,str2,Tree.root,size,tempData);


	out<<data<<'#'<<'#'<<charCount<<'#'<<'#'<<str2;
	out.close();
	cout<<"�ɹ�ѹ��text.txt�ļ���ѹ���ļ�Ϊtext1.doc"<<endl;
	cout<<"------------------------------------------------------------------------"<<endl;

	char str3[5000];
	char str4[5000];
	in.open("text1.txt",ios::in|ios::binary);
	in.read(str3,1000);
	in.close();
    str3[in.gcount()] = 0;
	zip.unzip(str3,str4);
	
	cout<<"�ɹ���ѹtext1.txt�ļ���ѹ���ļ�Ϊtext2.doc"<<endl;
	out.open("text2.txt",ios::out|ios::binary);
	out<<str4;
	out.close();
	return 0;
}

