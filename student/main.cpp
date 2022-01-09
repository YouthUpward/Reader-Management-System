//读者管理系统 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;
#include <list>	//C++下的
#include <stdlib.h>

typedef struct reader {
	char code[20];		//证件号
	char name[30];		//姓名
	char sex[5];		//性别
	char dept[50];		//系别
	int tag;			//证件状态
	int num;			//下标，如果通过r:L是做不到的，只能迭代访问，不能改变值
}reader;

list<reader> L;					//每个节点都是reader类型
list<reader>::iterator it;		//迭代器
reader line;					//读取文件时，每一行都是一个reader
reader temp;
reader findit;					//查找读者时，记录读者					
int flag = 0;

void menu();
void show();
void UpdateFile();
void BrowseReader();
void ModifyReader();
void in(reader r);
int SelectMenu();
int cmp(char a[], char b[]);

//增加读者
void InputReader();				//录入读者信息，建立读者信息的链表
void SaveReader();				//将读者信息链表，保存到reader.txt文件中

//查询读者
int Find_Code();				//按照证件号查找
int Find_Name();				//按照姓名查找

int main()
{
	FILE* fp = fopen("reader.txt", "r");		//r权限
	for (int i=0; ;i++ )
	{	//每个读者相当于一个结点，读入链表中
		if (~fscanf(fp, "%s%s%s%s%d", line.code, line.name, line.sex, line.dept, &line.tag))	//对于文件，如果不为空，则读取到结点
		{
			line.num = i;		//下标
			L.push_back(line);	//给line赋值后再插入链表
		}
		else break;
	}
	fclose(fp);

	for (;;)
	{
		menu();		//显示菜单

		int key;
		scanf("%d", &key);

		switch (key)
		{
		case 1: BrowseReader(); break;					//浏览
		case 2: InputReader(); SaveReader(); break;		//增加
		case 3: SelectMenu(); break;					//查找
		case 4: flag = 1; ModifyReader(); break;		//修改
		case 5: flag = 2; ModifyReader(); break;		//挂失
		case 0:	return 0;
		default:break;
		}
	}
	return 0;
}

void menu()
{
	printf("****************菜单****************\n");
	printf("1、浏览所有读者\n");
	printf("2、增加读者\n");
	printf("3、查询读者\n");
	printf("4、修改读者\n");
	printf("5、证件挂失\n");
	printf("0、结束菜单\n");
	printf("请输入选择：");
}

void BrowseReader()			//right
{
	for (reader r : L)		//对于L里的每个结点
		printf("%s\t%s\t%s\t%s\t%d\n", r.code, r.name, r.sex, r.dept, r.tag);
}

//增加读者：录入读者信息，建立读者信息的链表，其实这两个函数，一个fprintf()就可以搞定是否？否
void InputReader()
{
	show();
	temp.num = L.size()+1;
	L.push_back(temp);	//给temp赋值后再插入链表
}

//增加读者：将读者信息链表，保存到reader.txt文件中
void SaveReader()
{	//写入reader.txt中
	FILE* f= fopen("reader.txt", "w+");	//w+权限，
	fprintf(f, "\n%s\t%s\t%s\t%s\t%d", temp.code, temp.name, temp.sex, temp.dept, temp.tag);
	fclose(f);
}

int SelectMenu()
{
	printf("1、按照证件号\n2、按照名字\n请选择：");
	int s;
	scanf("%d", &s);
	if (s == 1)
		return Find_Code();
	else
		return Find_Name();
}

int Find_Code()	//查询读者：按照证件号查找
{
	char Code[20] = { 0 };
	printf("请输入证件号：");
	scanf("%s", Code);
	for (reader r : L)		//对于L里的每个结点
	{
		if (cmp(r.code, Code))
		{
			printf("该读者信息：%s\t%s\t%s\t%s\t%d\n", r.code, r.name, r.sex, r.dept, r.tag);

			for(int i=0;r.code[i]!=0;i++)
				findit.code[i]=r.code[i];
			for (int i = 0; r.name[i] != 0; i++)
				findit.name[i] = r.name[i];
			for (int i = 0; r.sex[i] != 0; i++)
				findit.sex[i] = r.sex[i];
			for (int i = 0; r.dept[i] != 0; i++)
				findit.dept[i] = r.dept[i];
			findit.tag = r.tag;
			findit.num = r.num;

			return r.num;	//返回读者的下标
		}
	}
	printf("没找到！\n");
	return 0;
}

int Find_Name()
{
	char Name[20] = { 0 };		//两个字符数组比较？
	printf("请输入姓名：");
	scanf("%s", Name);
	for (reader r : L)		//对于L里的每个结点
	{
		if (cmp(r.name, Name))
		{
			printf("该读者信息：%s\t%s\t%s\t%s\t%d\n", r.code, r.name, r.sex, r.dept, r.tag);
			for (int i = 0; r.code[i] != 0; i++)
				findit.code[i] = r.code[i];
			for (int i = 0; r.name[i] != 0; i++)
				findit.name[i] = r.name[i];
			for (int i = 0; r.sex[i] != 0; i++)
				findit.sex[i] = r.sex[i];
			for (int i = 0; r.dept[i] != 0; i++)
				findit.dept[i] = r.dept[i];
			findit.tag = r.tag;
			findit.num = r.num;

			return r.num;	//返回读者的下标
		}
	}
	printf("没找到！\n");
	return 0;
}

void ModifyReader()
{
		int pos=SelectMenu();//元素的下标
		int cnt = 0;
		for (it = L.begin(); it != L.end(); it++)
		{
			if (cnt != pos)
				cnt++;
			else
			{	//如果是要修改的结点，删掉结点，插入结点
				L.erase(it);			//删除结点
				if (flag==1)
				{
					printf("请依次输入证件号，姓名，性别，系别，证件状态\n");
					scanf("%s%s%s%s%d", temp.code, temp.name, temp.sex, temp.dept, &temp.tag);
					in(temp);
				}
				if (flag==2)
				{//如果是修改码
					findit.tag = 1;
					in(findit);
				}
				//至此，链表已经更新成功，并不是尾插
				//更新reader.txt文件
				UpdateFile();
				break;
			}
		}
}

void in(reader r)
{
	int cnt = 0;
	for (it = L.begin(); it != L.end(); it++)
	{
		if (cnt == findit.num)
			L.insert(it, r);
		cnt++;
	}
}

int cmp(char a[], char b[])	//都是字符类型
{
	int i;
	for (i = 0; a[i] != 0 || b[i] != 0; i++)
	{
		if (a[i] != b[i])
			return 0;
	}
	if (a[i + 1] != 0 || b[i + 1] != 0)
		return 0;
	return 1;
}

void show()
{
	printf("请依次输入证件号，姓名，性别，系别，证件状态\n");
	scanf("%s%s%s%s%d", temp.code, temp.name, temp.sex, temp.dept, &temp.tag);
}

void UpdateFile()
{
	FILE* f = fopen("reader.txt", "w+");	//w+权限
	for (reader g : L)
		fprintf(f, "%s\t%s\t%s\t%s\t%d\n", g.code, g.name, g.sex, g.dept, g.tag);
	fclose(f);
}

