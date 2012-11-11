#ifndef __MYSOCK_H
#define __MYSOCK_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <winsock2.h>
#pragma   comment(lib, "Ws2_32.lib ") 

#define BUFF_SIZE 4096

bool InitSocklib();				//����sock��
void DestorySocklib();		//�ر�sock��

void sockError(const char *format,...);		//����sock����

SOCKET connectSock(const char *host, const char *service , const char *transType);           //�����׽���

SOCKET connectTCP(const char *host , const char *service);										//����TCP�׽���
SOCKET connectUDP(const char *host , const char *service);										//����UDP�׽���

SOCKET passiveSock(const char *service , const char *transType , int qlen);						//���������׽���

SOCKET passiveTCP(const char *service ,int qlen);														//��������TCP�׽��ֲ�����
SOCKET passiveUDP(const char *service);																	//��������UDP�׽���

int readChar(SOCKET s ,char *ptr );																	//��SOCKET�ж�һ���ֽ�
int readLine(SOCKET s ,char FAR *buff ,int maxSize);													//��SOCKET�ж�һ��

int writeSocket(SOCKET s , char FAR *buff ,int n);										//��SOCKET��дn���ֽ�
int readSocket(SOCKET s , char FAR *buff , int n);
#endif