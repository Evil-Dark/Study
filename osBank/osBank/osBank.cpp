// osBank.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<fstream>
#include<iostream>
#include "oslib.h"

int p,*pro;

int *Available;
int **Max;
int **Allocation;
int **Need;

int Source;
int Count;

int initAvailable() {
	FILE *fp;
	if ((fp = fopen("Available_list.txt", "r")) == NULL)	//读取Available
		return 0;
	else
	{
		int m = 0;
		fscanf(fp, "%d ", &Source);		//获得资源种数
		Available = new int[Source];
		for (int i = 0; i<Source; i++) {
			fscanf(fp, "%d ", &Available[m]);
			m++;
		}
		fclose(fp);
		return 1;
	}
}

int initMax()
{
	FILE* fp;
	if ((fp = fopen("Max_list.txt", "r")) == NULL)		//读取Max
		return 0;
	else
	{
		fscanf(fp, "%d ", &Count);		//获得进程数
		Max = new int *[Count];
		for (int k = 0; k<Count; k++)
			Max[k] = new int[Source];
		for (int i = 0; i<Count; i++)
			for (int j = 0; j<Source; j++)
			{
				fscanf(fp, "%d ", &Max[i][j]);
			}
		fclose(fp);
		return 1;
	}
}

int initAllocaion()
{
	FILE* fp;
	if ((fp = fopen("Allocation_list.txt", "r")) == NULL)	//读取Allocation
		return 0;
	else
	{
		Allocation = new int *[Count];
		for (int k = 0; k<Count; k++)
			Allocation[k] = new int[Source];
		for (int i = 0; i<Count; i++)
			for (int j = 0; j<Source; j++)
			{
				fscanf(fp, "%d ", &Allocation[i][j]);
			}
		fclose(fp);

		Need = new int*[Count];
		for (int i = 0; i<Count; i++)
			Need[i] = new int[Source];

		for (int i = 0; i<Count; i++)
			for (int j = 0; j<Source; j++) {
				Need[i][j] = Max[i][j] - Allocation[i][j];
				Available[j] -= Allocation[i][j];
			}

		return 1;
	}
}

void printArray()
{
	int i, j;
	std::cout << "进程个数：" << bank->Count << "\t资源个数：" << bank->Source << std::endl;
	
	std::cout << "进程" << "\t"
		<< "Max" << "\t" << "\t" << "\t"
		<< "Allocation" << "\t" << "\t" 
		<< "Need" << "\t" << "\t" << "\t"
		<< "Available" << std::endl;

	std::cout << "P0" << "\t";
	for (i = 0; i<bank->Source; i++)
		std::cout << bank->Max[0][i] << "\t";
	for (i = 0; i<bank->Source; i++)
		std::cout << bank->Allocation[0][i] << "\t";
	for (i = 0; i<bank->Source; i++)
		std::cout << bank->Need[0][i] << "\t";
	for (i = 0; i<bank->Source; i++)
		std::cout << bank->Available[i] << "\t";
	std::cout << std::endl;

	for (i = 1; i < bank->Count; i++)
	{
		std::cout << "P" << i << "\t";
		for (j = 0; j<bank->Source; j++)
		{
			std::cout << bank->Max[i][j] << "\t";

		}
		for (j = 0; j<bank->Source; j++)
		{
			std::cout << bank->Allocation[i][j] << "\t";
		}
		for (j = 0; j<bank->Source; j++)
		{
			std::cout << bank->Need[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < 30; i++)
		std::cout << "*";
	std::cout << std::endl;
}

void printSafe() {
	std::cout << "当前时刻安全序列:" << std::endl << "P" << Race[0];
	for (int j = 1; j<bank->Count; j++) {
		std::cout << "--->P" << Race[j];
	}
	std::cout << std::endl;
	for (int i = 0; i < 30; i++)
		std::cout << "*";
	std::cout << std::endl;
}

void newRequest() {
	std::cout << "输入线程i的请求向量Request（i x y ... z）";
	std::cin >> p;
	pro = new int[Source];
	for (int i = 0; i < Source; i++)
		std::cin >> pro[i];
	if (reCheck(p, pro))
	{
		printSafe();
		printArray();
	}
	else
		std::cout << "当前请求向量导致系统处于不安全状态，系统分配失败" << std::endl;

	for (int i = 0; i < 30; i++)
		std::cout << "*";
	std::cout << std::endl;
}

void Set() {
	if (initAvailable() == 1 && initMax() == 1 && initAllocaion() == 1)
	{
		Bank bankORG = { Count, Source, Available, Max, Allocation, Need };
		initData(bankORG);
		if (safeCheck())
		{
			printArray();
			printSafe();
		}
		bool flag = true;
		while (flag)
		{
			newRequest();
			char temp;
			std::cout << "是否继续？ y/n" << std::endl;
			std::cin >> temp;
			if (temp == 'n')
				flag = false;
			else
				Set();
		}
	}
}

int main()
{
	Set();
	system("pause");
    return 0;
}

