#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//��������ʽ�ṹ����
struct _Deter2
{
	float a;
	float b;
	float c;
	float d;
};

typedef struct _Deter2 Deter2;

//����һ����������ʽ
int createDeter2(float val1,float val2,float val3,float val4,Deter2 **p);

//�ͷŶ�������ʽ
int freeDeter2(Deter2 *p);

//�����������ʽ��ֵ
float calDeter2(Deter2 *p);

//��ʾ��������ʽ
void printDeter2(Deter2 *p);

//�������ʽ����
struct _Determiant
{
	int n;//����ʽ����
	float *data;//����ʽ����
};

typedef struct _Determiant Determiant;

//���������������ʽ
int createDetermiant(int demision,float *src,Determiant **p);

//�ͷ�����ʽ����
int freeDetermiant(Determiant *p);

//��ӡ���������ʽ
void printDeterminant(Determiant *p);

//�������������ʽ
float calDetermiant(Determiant *p);
//=====================Head ==================

float calDeter2(Deter2 *p)
{
	if(p == NULL)
		return 0;

	return p->a * p->d - p->c * p->b;
}

//��ʾ��������ʽ
void printDeter2(Deter2 *p)
{
	if(p == NULL)
	{
		printf("Determiant is NULL\n");
		return;
	}

	printf("%4.4f \t%4.4f\n%4.4f \t%4.4f\n",p->a,p->b,p->c,p->d);
}

//����һ����������ʽ
int createDeter2(float val1,float val2,float val3,float val4,Deter2 **p)
{
	if(p == NULL)
		return -1;

	Deter2 *pD = NULL;
	pD = (Deter2 *)malloc( 4 * sizeof(float) );
	if(pD == NULL)
		return -1;

	pD->a = val1;
	pD->b = val2;
	pD->c = val3;
	pD->d = val4;

	*p = pD;

	return 1;
}

//�ͷŶ�������ʽ
int freeDeter2(Deter2 *p)
{
	if(p == NULL)
	{
		return -1;
	}

	free(p);
	return 1;
}

int createDetermiant(int demision,float *src,Determiant **p)
{
	if(p == NULL)
		return -1;

	Determiant *pD = (Determiant *)malloc(sizeof(Determiant));
	if(pD == NULL)
		return -1;

	pD->n = demision;
	int offset = pD->n * pD->n; 
	pD->data = (float *)malloc(offset * sizeof(float));
	if(pD->data==NULL)
		return -1;

	int i = 0;
	for(i = 0;i < offset; i++)
	{
		pD->data[i] = src[i];
	}//end for i

	*p = pD;

	return 1;
}

void printDeterminant(Determiant *p)
{
	if(p == NULL)
		return;

	int demision = p->n;
	//printf(" n = %d \n",p->n);
	int i;
	int len = demision * demision;
	for(i = 0; i < len ;i++)
	{
		printf("%4.4f \t",p->data[i]);
		if( (i+1) % demision == 0)
		{
			printf("\n");
		}
	}//end for i
}

//�ͷ�����ʽ����
int freeDetermiant(Determiant *p)
{
	if(p == NULL)
		return -1;

	if(p->data!=NULL)
	{
		free(p->data);
	}

	free(p);
}

int copyArray2Dst(int banLine,int offset,float *src,float *dst)
{
	if(src == NULL || dst ==NULL)
		return -1;

	int m,n;
	int index = 0;
	for(m = 1;m < offset; m++)
	{
		for( n = 0 ;n < offset ; n++)
		{
			if(n != banLine)
			{
				dst[index++] = src[m * offset + n];
			}
		}//end for n
	}//end for m
	return 1;
}

//�������������ʽ
float calDetermiant(Determiant *p)
{
	if(p==NULL)
	{
		printf("Determiant is NULL \n");
		return 0;
	}

	float result = 0;
	if(p->n == 2)
	{
		Deter2 *pDeter2;
		createDeter2(p->data[0],p->data[1],p->data[2],p->data[3],&pDeter2);
		result = calDeter2(pDeter2);
		freeDeter2(pDeter2);
		return result;
	}else{
		int i = 0;
		int len = p->n - 1;
	
		for(;i < p->n ; i++)
		{
			Determiant *pSubDeter;

			float *srcData;
			//malloc
			srcData = (float *)malloc( len * len * sizeof(float) );
			copyArray2Dst(i,p->n,p->data,srcData);
			createDetermiant(p->n - 1,srcData,&pSubDeter);
			//printf("---------------------sub m:\n");
			//printDeterminant(pSubDeter);
			float subResultVal = ((i+2) % 2 == 0?1:-1) *(p->data[i]) * calDetermiant(pSubDeter);
			//printf("sub value  = %4.4f\n",subResultVal);
			//printf("---------------------sub end ----------------------\n");
			result += subResultVal;
			freeDetermiant(pSubDeter);
			free(srcData);
		}//end for i
	}
	return result;
}


int main()
{
	/*Deter2 deter = {2,2,
		3,4};
	printDeter2(&deter);
	printf("r = %4.4f \n", calDeter2(&deter) );

	Deter2 deter2 = {2,2,
		3,4};


	Deter2 *pD = NULL;
	createDeter2(2,1,3,4,&pD);
	printDeter2(pD);
	printf("r = %4.4f \n", calDeter2(pD) );
	freeDeter2(pD);

	float src[] = {1,2,3,8,
		5,6,8,1,
		7,8,9,3,
		1,1,1,1}; 
	Determiant *pNormal;
	int d = (int)sqrt((double)sizeof(src) / sizeof(float));
	createDetermiant(d,src,&pNormal);
	printDeterminant(pNormal);
	freeDetermiant(pNormal);*/


	printf("===============\n");
	//float src2[] = {3,1,-1,2,
	//						-5,1,3,-4,
	//					    2,0,1,-1,
	//						1,-5,3,-3};
	//float src2[] = {3,1,1,1,
	//						1,3,1,1,
	//					    1,1,3,1,
	//						1,1,1,3};

	float src2[] = {2,1,4,1,
							3,-1,2,1,
							1,2,3,2,
							5,0,6,2};

	Determiant *p1;
	int d = (int)sqrt((double)sizeof(src2) / sizeof(float));
	createDetermiant(d,src2,&p1);
	printDeterminant(p1);
	printf("r = %4.4f \n", calDetermiant(p1) );
	freeDetermiant(p1);

	printf("===== The end ====\n");
	return 0;
}
