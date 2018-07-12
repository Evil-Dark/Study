#pragma once

int *Request;
int *Race;

struct Bank
{
	int Count; //������
	int Source;//��Դ����

	int *Available;
	int **Max;
	int **Allocation;
	int **Need;
};
Bank * bank;
void initData(Bank &bankORG)
{
	bank = &bankORG;
	Race = new int[bank->Count];
}

bool safeCheck() {	//��ȫ���㷨
	int i, j, k;
	int m = 0;
	int *Work = new int[bank->Source];
	for (j = 0; j<bank->Source; j++)
		Work[j] = bank->Available[j];

	bool *Finish = new bool[bank->Count];
	for (i = 0; i<bank->Count; i++)
		Finish[i] = false;

	int FinishCount = 0;
	bool found = true;
	int c;
	while (found)//����
	{
		found = false;
		for (i = 0; i<bank->Count; i++)
		{
			if (!Finish[i])//����������
			{
				c = 0;
				for (j = 0; j<bank->Source; j++)
				{
					if (bank->Need[i][j] <= Work[j]) {
						c++;
					}
				}
				if (c == bank->Source)//����������
				{
					for (k = 0; k<bank->Source; k++)
					{
						Work[k] += bank->Allocation[i][k];
					}
					Finish[i] = true;
					Race[m++] = i;
					FinishCount++;
					found = true;
				}
			}
		}
	}
	if (FinishCount == bank->Count)
		return true;
	else
		return false;
};
int bankAlgorithm(int i) {			//���м��㷨
	int m = 0;
	int j;
	for (j = 0; j<bank->Source; j++)
		if (Request[j]>bank->Need[i][j])
			return 1;//������Դ�������ֵ

	for (j = 0; j<bank->Source; j++)
		if (Request[j]>bank->Available[j])
			return 2;//ϵͳ�����㹻����Դ

	for (j = 0; j<bank->Source; j++)		//�Է���
	{
		bank->Available[j] -= Request[j];
		bank->Allocation[i][j] += Request[j];
		bank->Need[i][j] -= Request[j];
	}
	if (safeCheck())
		return 3;	//���ڰ�ȫ���У�����ɹ�
	else {
		for (j = 0; j<bank->Source; j++)
		{
			bank->Available[j] += Request[j];
			bank->Allocation[i][j] -= Request[j];
			bank->Need[i][j] += Request[j];
		}
		return 4;//�����ڰ�ȫ���У�����ʧ��
	}
};

bool reCheck(int i, int *j) {//�߳�i������Դa,b,c
	Request = j;
	if (bankAlgorithm(i) == 3)
		return true;
	else
		return false;
};

/*class bank {
public:
	int *Available;
	int **Max;
	int **Allocation;
	int **Need;

	int Count; //������
	int Source;//��Դ����

	int *Request;
	int *Race;

	void initData(int s, int c, int *Ava, int **Ma, int **All)
	{
		Source = s;
		Count = c;
		Available = Ava;
		Max = Ma;
		Allocation = All;

		Race = new int[Count];
		Need = new int *[Count];
		for (int i = 0; i<Count; i++)
			Need[i] = new int[Source];

		for (int  i = 0; i<Count; i++)
			for (int j = 0; j<Source; j++) {
				Need[i][j] = Max[i][j] - Allocation[i][j];
				Available[j] -= Allocation[i][j];
			}
	}

/*	int initData()
	{
		m = 0;
		FILE *fp;
		if ((fp = fopen("Available_list.txt", "r")) == NULL)	//��ȡAvailable
			return 0;
		else
		{
			fscanf(fp, "%d ", &Source);		//�����Դ����
			Available = new int[Source];
			for (int i = 0; i<Source; i++) {
				fscanf(fp, "%d ", &Available[m]);
				m++;
			}
			fclose(fp);
		}

		int i = 0;
		int j = 0;
		if ((fp = fopen("Max_list.txt", "r")) == NULL)		//��ȡMax
			return 0;
		else
		{
			fscanf(fp, "%d ", &Count);		//��ý�����
			Max = new int *[Count];
			for (int k = 0; k<Count; k++)
				Max[k] = new int[Source];
			for (i = 0; i<Count; i++)
				for (j = 0; j<Source; j++)
				{
					fscanf(fp, "%d ", &Max[i][j]);
				}
			fclose(fp);
		}

		if ((fp = fopen("Allocation_list.txt", "r")) == NULL)	//��ȡAllocation
			return 0;
		else
		{
			Allocation = new int *[Count];
			for (int k = 0; k<Count; k++)
				Allocation[k] = new int[Source];
			for (i = 0; i<Count; i++)
				for (j = 0; j<Source; j++)
				{
					fscanf(fp, "%d ", &Allocation[i][j]);
				}
			fclose(fp);
		}

		Race = new int[Count];
		Need = new int *[Count];
		for (i = 0; i<Count; i++)
			Need[i] = new int[Source];

		for (i = 0; i<Count; i++)
			for (j = 0; j<Source; j++) {
				Need[i][j] = Max[i][j] - Allocation[i][j];
				Available[j] -= Allocation[i][j];
			}

		return 1;
	}
	
	bool safeCheck() {	//��ȫ���㷨
		int i, j, k;
		int m = 0;
		int *Work = new int[Source];
		for (j = 0; j<Source; j++)
			Work[j] = Available[j];

		bool *Finish = new bool[Count];
		for (i = 0; i<Count; i++)
			Finish[i] = false;

		int FinishCount = 0;
		bool found = true;
		int c;
		while (found)//����
		{
			found = false;
			for (i = 0; i<Count; i++)
			{
				if (!Finish[i])//����������
				{
					c = 0;
					for (j = 0; j<Source; j++)
					{
						if (Need[i][j] <= Work[j]) {
							c++;
						}
					}
					if (c == Source)//����������
					{
						for (k = 0; k<Source; k++)
						{
							Work[k] += Allocation[i][k];
						}
						Finish[i] = true;
						Race[m++] = i;
						FinishCount++;
						found = true;
					}
				}
			}
		}
		if (FinishCount == Count)
			return true;
		else
			return false;
	};
	
	int bankAlgorithm(int i) {			//���м��㷨
		int m = 0;
		int j;
		for (j = 0; j<Source; j++)
			if (Request[j]>Need[i][j])
				return 1;//������Դ�������ֵ

		for (j = 0; j<Source; j++)
			if (Request[j]>Available[j])
				return 2;//ϵͳ�����㹻����Դ

		for (j = 0; j<Source; j++)		//�Է���
		{
			Available[j] -= Request[j];
			Allocation[i][j] += Request[j];
			Need[i][j] -= Request[j];
		}
		if (safeCheck())
			return 3;	//���ڰ�ȫ���У�����ɹ�
		else {
			for (j = 0; j<Source; j++)
			{
				Available[j] += Request[j];
				Allocation[i][j] -= Request[j];
				Need[i][j] += Request[j];
			}
			return 4;//�����ڰ�ȫ���У�����ʧ��
		}
	};
	
	bool reCheck(int i, int *j) {//�߳�i������Դa,b,c
		Request = j;
		if (bankAlgorithm(i) == 3)
			return true;
		else
			return false;
	};
};
*/