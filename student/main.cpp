//���߹���ϵͳ 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;
#include <list>	//C++�µ�
#include <stdlib.h>

typedef struct reader {
	char code[20];		//֤����
	char name[30];		//����
	char sex[5];		//�Ա�
	char dept[50];		//ϵ��
	int tag;			//֤��״̬
	int num;			//�±꣬���ͨ��r:L���������ģ�ֻ�ܵ������ʣ����ܸı�ֵ
}reader;

list<reader> L;					//ÿ���ڵ㶼��reader����
list<reader>::iterator it;		//������
reader line;					//��ȡ�ļ�ʱ��ÿһ�ж���һ��reader
reader temp;
reader findit;					//���Ҷ���ʱ����¼����					
int flag = 0;

void menu();
void show();
void UpdateFile();
void BrowseReader();
void ModifyReader();
void in(reader r);
int SelectMenu();
int cmp(char a[], char b[]);

//���Ӷ���
void InputReader();				//¼�������Ϣ������������Ϣ������
void SaveReader();				//��������Ϣ�������浽reader.txt�ļ���

//��ѯ����
int Find_Code();				//����֤���Ų���
int Find_Name();				//������������

int main()
{
	FILE* fp = fopen("reader.txt", "r");		//rȨ��
	for (int i=0; ;i++ )
	{	//ÿ�������൱��һ����㣬����������
		if (~fscanf(fp, "%s%s%s%s%d", line.code, line.name, line.sex, line.dept, &line.tag))	//�����ļ��������Ϊ�գ����ȡ�����
		{
			line.num = i;		//�±�
			L.push_back(line);	//��line��ֵ���ٲ�������
		}
		else break;
	}
	fclose(fp);

	for (;;)
	{
		menu();		//��ʾ�˵�

		int key;
		scanf("%d", &key);

		switch (key)
		{
		case 1: BrowseReader(); break;					//���
		case 2: InputReader(); SaveReader(); break;		//����
		case 3: SelectMenu(); break;					//����
		case 4: flag = 1; ModifyReader(); break;		//�޸�
		case 5: flag = 2; ModifyReader(); break;		//��ʧ
		case 0:	return 0;
		default:break;
		}
	}
	return 0;
}

void menu()
{
	printf("****************�˵�****************\n");
	printf("1��������ж���\n");
	printf("2�����Ӷ���\n");
	printf("3����ѯ����\n");
	printf("4���޸Ķ���\n");
	printf("5��֤����ʧ\n");
	printf("0�������˵�\n");
	printf("������ѡ��");
}

void BrowseReader()			//right
{
	for (reader r : L)		//����L���ÿ�����
		printf("%s\t%s\t%s\t%s\t%d\n", r.code, r.name, r.sex, r.dept, r.tag);
}

//���Ӷ��ߣ�¼�������Ϣ������������Ϣ��������ʵ������������һ��fprintf()�Ϳ��Ը㶨�Ƿ񣿷�
void InputReader()
{
	show();
	temp.num = L.size()+1;
	L.push_back(temp);	//��temp��ֵ���ٲ�������
}

//���Ӷ��ߣ���������Ϣ�������浽reader.txt�ļ���
void SaveReader()
{	//д��reader.txt��
	FILE* f= fopen("reader.txt", "w+");	//w+Ȩ�ޣ�
	fprintf(f, "\n%s\t%s\t%s\t%s\t%d", temp.code, temp.name, temp.sex, temp.dept, temp.tag);
	fclose(f);
}

int SelectMenu()
{
	printf("1������֤����\n2����������\n��ѡ��");
	int s;
	scanf("%d", &s);
	if (s == 1)
		return Find_Code();
	else
		return Find_Name();
}

int Find_Code()	//��ѯ���ߣ�����֤���Ų���
{
	char Code[20] = { 0 };
	printf("������֤���ţ�");
	scanf("%s", Code);
	for (reader r : L)		//����L���ÿ�����
	{
		if (cmp(r.code, Code))
		{
			printf("�ö�����Ϣ��%s\t%s\t%s\t%s\t%d\n", r.code, r.name, r.sex, r.dept, r.tag);

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

			return r.num;	//���ض��ߵ��±�
		}
	}
	printf("û�ҵ���\n");
	return 0;
}

int Find_Name()
{
	char Name[20] = { 0 };		//�����ַ�����Ƚϣ�
	printf("������������");
	scanf("%s", Name);
	for (reader r : L)		//����L���ÿ�����
	{
		if (cmp(r.name, Name))
		{
			printf("�ö�����Ϣ��%s\t%s\t%s\t%s\t%d\n", r.code, r.name, r.sex, r.dept, r.tag);
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

			return r.num;	//���ض��ߵ��±�
		}
	}
	printf("û�ҵ���\n");
	return 0;
}

void ModifyReader()
{
		int pos=SelectMenu();//Ԫ�ص��±�
		int cnt = 0;
		for (it = L.begin(); it != L.end(); it++)
		{
			if (cnt != pos)
				cnt++;
			else
			{	//�����Ҫ�޸ĵĽ�㣬ɾ����㣬������
				L.erase(it);			//ɾ�����
				if (flag==1)
				{
					printf("����������֤���ţ��������Ա�ϵ��֤��״̬\n");
					scanf("%s%s%s%s%d", temp.code, temp.name, temp.sex, temp.dept, &temp.tag);
					in(temp);
				}
				if (flag==2)
				{//������޸���
					findit.tag = 1;
					in(findit);
				}
				//���ˣ������Ѿ����³ɹ���������β��
				//����reader.txt�ļ�
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

int cmp(char a[], char b[])	//�����ַ�����
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
	printf("����������֤���ţ��������Ա�ϵ��֤��״̬\n");
	scanf("%s%s%s%s%d", temp.code, temp.name, temp.sex, temp.dept, &temp.tag);
}

void UpdateFile()
{
	FILE* f = fopen("reader.txt", "w+");	//w+Ȩ��
	for (reader g : L)
		fprintf(f, "%s\t%s\t%s\t%s\t%d\n", g.code, g.name, g.sex, g.dept, g.tag);
	fclose(f);
}

