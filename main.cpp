#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "tchar.h"
#include <vector> 


int main()
{
	HANDLE hCom;
	hCom = CreateFile(_T("COM3"),//COM3��
		GENERIC_READ | GENERIC_WRITE,//�������д
		0,//��ռ��ʽ
		NULL,
		OPEN_EXISTING,//�򿪶����Ǵ���
		0,//ͬ����ʽ
		NULL);
	if(hCom == (HANDLE)-1)
	{
		printf("��COMʧ��!\n");
		return FALSE;
	}
	else
	{
		printf("COM�򿪳ɹ���\n");
	}
	SetupComm(hCom, 20480, 20480);//���뻺����������������Ĵ�С����1024

	COMMTIMEOUTS TimeOuts;//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = 100;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	TimeOuts.WriteTotalTimeoutMultiplier = 500;//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &TimeOuts);//���ó�ʱ

	DCB dcb1;
	GetCommState(hCom, &dcb1);
	dcb1.BaudRate = 115200;//������Ϊ115200
	dcb1.ByteSize = 8;//ÿ���ֽ���8λ
	dcb1.Parity = NOPARITY;//����żУ��λ
	dcb1.StopBits = TWOSTOPBITS;//����ֹͣλ
	dcb1.fParity = FALSE;
	dcb1.fNull = FALSE;
	SetCommState(hCom, &dcb1);
	int wCount = 256;//��ȡ���ֽ���
	int wCount1;
	PurgeComm(hCom, PURGE_TXCLEAR|PURGE_RXCLEAR);//��ջ�����
	while(1)
	{
		int i = 0;
		FILE *fp1;
		unsigned char str[256];
		if(!ReadFile(hCom, str, wCount, &wCount1, NULL))
		{
			printf("������ʧ��!");
			return FALSE;
		}
		fp1 = fopen("���ڷ��͵���.txt", "a+");
		printf("�����ڳɹ�!\n");
		if(wCount1 > 0)
		{

		}
		else
		{

		}
		printf("��ȡ����Ϊ:%d\n", wCount1);
		printf("��ȡ����Ϊ:\n");
		for(i=0; i< wCount1; i++)
		{
			printf("%02X ", str[i]);
			fprintf(fp1, "%02X ", str[i]);
		}
		printf("\n");
		fclose(fp1);
	}

	CloseHandle(hCom);

    std::cout << "Hello World!\n";

	return 0;
}


