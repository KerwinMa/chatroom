#include <winsock2.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <windows.h>
#pragma   comment(lib, "Ws2_32.lib ") 

#define BUFFER_SIZE    2048
#define MAX_CONNECTION_COUNT	FD_SETSIZE

typedef struct SocketUsername
{
	char				username[20];
	SOCKET*	s;
}SocketUsername;



int  MainServer(SOCKET* s);
SOCKET     SocketArr[MAX_CONNECTION_COUNT];											
//SocketUsername  SocketUsernameArr[MAX_CONNECTION_COUNT];
char				username[MAX_CONNECTION_COUNT][50];
char userlist[1024];																											//�û����б�
unsigned 	serverCount = 0 ;

int main(int argc,char *argv[])
{
	WORD wVersionRequested= MAKEWORD(2,2);
	WSADATA									wsaData;
	int												PORT=3204; 
	SOCKET										server_socket;
	SOCKADDR_IN							server_addr;
	fd_set											 fdread;
	int												Ret;

	if (WSAStartup(wVersionRequested,&wsaData) != NO_ERROR)
	{
		printf("error at WSAStartup()\n");
		return 1;
	}
	
	//����һ��SOCKET�����󶨺ͼ�����
	server_socket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server_socket == INVALID_SOCKET)
	{
		printf("���ܴ��������׽���! \n");
		WSACleanup();
		return 1;
	}
	
	server_addr.sin_family=AF_INET;
	if (argc==1)
	{
		server_addr.sin_addr.s_addr=INADDR_ANY;
	}
	else if (argc==2)
	{
		server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	}

	else
	{
		printf ("��������������������");
		WSACleanup();
		return 1;
	}

	server_addr.sin_port=htons(PORT);
	
	if (bind(server_socket,(SOCKADDR *)&server_addr,sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("IP��ַ��������������  \n");
		WSACleanup();
		return 1;
	}
	
	if( listen(server_socket,5) ==SOCKET_ERROR)
	{
		printf("error at listen the socket! \n") ;
		WSACleanup();
		return 1;
	}

	else
	{
		printf("�������ѿ����˿ڲ�������  \n");
	}

	//��ʼ������
	for ( int i = 0 ; i <MAX_CONNECTION_COUNT ; i++ )
	{
		SocketArr[i] = -1;
		//SocketUsernameArr[i].s = &(SocketArr[i]);
		//memset( SocketUsernameArr[i].username , 0, sizeof( SocketUsernameArr[i].username ) );
	}
	//memset( userlist , 0, sizeof( userlist ) );

	while(!kbhit())
	{
		FD_ZERO(&fdread);
		FD_SET(server_socket , &fdread);
		for( i = 0 ; i < MAX_CONNECTION_COUNT ; i++)
			if(SocketArr[i] != -1)
				FD_SET(SocketArr[i] , &fdread);

		if((Ret = select(0,&fdread,NULL,NULL,NULL)) == SOCKET_ERROR)
		{
			printf("select errror");
			break;
		}

		if( Ret > 0)
		{	

			if (FD_ISSET(server_socket , &fdread))
			{

				for(i = 0;i < MAX_CONNECTION_COUNT; i++)
					if(SocketArr[i] == -1)
						break;

				if ((SocketArr[i] = accept(server_socket, NULL , NULL )) == INVALID_SOCKET)
				{
					printf("Accept socket failed! ");
					break;
				}
				serverCount++;
				printf("%d.    ���û����ӵ���������\n" , serverCount);
			}

			for(i = 0;i < MAX_CONNECTION_COUNT; i++)
				if((SocketArr[i] != -1) && (FD_ISSET(SocketArr[i] , &fdread )))
				{
				  MainServer(&SocketArr[i]);						
				}
		}
	}
	return 0;
}

int  MainServer(SOCKET* s)
{
	SOCKET client_socket = *s;
	char receive_buff[BUFFER_SIZE];														//���ջ�����
	char send_buff[BUFFER_SIZE];															//���ͻ�����
	int Ret;
	int i;

		
    Ret=recv(client_socket , receive_buff , sizeof(receive_buff) , 0);


	//�˳�������
	if (Ret <= 0)
	{
		closesocket(*s);
		*s = -1;
		
		//֪ͨ�����û�ĳ���û��뿪������
		for ( i = 0 ; i < MAX_CONNECTION_COUNT ; i++ )
		{
			if(&(SocketArr[i]) == s)
			{
				sprintf(send_buff , "%s\n%s\n%s\n%s%s", "13" ,  "SERVER" , "0"  , username[i] , " �뿪��������!");
				serverCount++;
				printf("%d.    %s �뿪��������!\n" , serverCount , username[i]);
				break;
			}
		}
		for(i = 0 ; i < MAX_CONNECTION_COUNT ; i++)
		{
			if (SocketArr[i] != -1)
			{
				send(SocketArr[i] , send_buff , strlen(send_buff)+1, 0);
			}
		}
		
		//����û���
		for ( i = 0 ; i < MAX_CONNECTION_COUNT ; i++ )
		{
			if(&(SocketArr[i]) == s)
			{
				memset( username[i] , 0, sizeof( username[i] ) );
				break;
			}
		}

		//�����û��б�
		memset( userlist , 0, sizeof( userlist ) );
		for ( i = 0 ; i < MAX_CONNECTION_COUNT ; i++ )
		{
			if (SocketArr[i] != -1)
			{
				sprintf(userlist , "%s%s\n" , userlist , username[i]);
			}
		}
		
		//�����û��б�
		sprintf(send_buff , "%s\n%s\n%s\n%s" , "12" ,  "SERVER" , "0" , userlist);
		serverCount++;
		printf("%d.    �û��б��и��£����û��б�Ϊ��\n%s\n" , serverCount ,userlist);
		for(i = 0 ; i < MAX_CONNECTION_COUNT ; i++)
		{
			if (SocketArr[i] != -1)
			{
				send(SocketArr[i] , send_buff , strlen(send_buff)+1 , 0);
			}
		}

		return Ret;
	}

	
	receive_buff[Ret] = '\0';
	int type=1000;
	char fromuser[20];
	char touser[20];
	char data[1024];
	sscanf(receive_buff  , "%d\n%[^\n]\n%[^\n]\n%[^\0]", &type , fromuser , touser , data);
	
	//type == 0 Ϊ����ע��
	if (type == 0)
	{
		//�����ж�����ע����û����Ƿ�ע��
		bool isRegistered = false;
		for ( i = 0 ; i < MAX_CONNECTION_COUNT ; i++ )
		{
			if (strcmp(username[i] , fromuser) == 0)
			{
				isRegistered = true;
				break;
			}
		}
		if (isRegistered == false)
		{
			//д���û���
			for ( i = 0 ; i < MAX_CONNECTION_COUNT ; i++ )
			{
				if( SocketArr[i] == *s )
				{
					memset( username[i] , 0, sizeof( username[i]) );
					sprintf(username[i] , "%s" , fromuser );
				}
			}
		
			//�����û��б�
			memset( userlist , 0, sizeof( userlist ) );
			for ( i = 0 ; i < MAX_CONNECTION_COUNT ; i++ )
			{
				if (SocketArr[i] != -1)
				{
					sprintf(userlist , "%s%s\n" , userlist , username[i]);
				}
			}

			//type ==10 Ϊע��ɹ�
			memset( send_buff , 0 , sizeof(send_buff) );
			sprintf(send_buff , "%s\n%s\n%s\n%s%s", "10" ,  "SERVER" , touser , "ע���û��ɹ�����ӭ�� " , fromuser);
			send(client_socket , send_buff, strlen(send_buff)+1 , 0);
			
			//type == 12 Ϊ�����û��б�
			//�����û��б�
			memset( send_buff , 0, sizeof(send_buff) );
			sprintf(send_buff , "%s\n%s\n%s\n%s" , "12" ,  "SERVER" , "0" , userlist);
			serverCount++;
			printf("%d.    �û��б��и��£����û��б�Ϊ��\n%s\n" , serverCount , userlist);
			for(i = 0 ; i < MAX_CONNECTION_COUNT ; i++)
			{
				if (SocketArr[i] != -1)
				{
					send(SocketArr[i] , send_buff , strlen(send_buff)+1, 0);
				}
			}

			//type == 13 ֪ͨ�����û��������û���������뿪
			memset( send_buff , 0, sizeof(send_buff) );
			sprintf(send_buff , "%s\n%s\n%s\n%s%s", "13" ,  "SERVER" , "0"  , fromuser , " ������������");
			serverCount++;
			printf("%d.    %s ������������!\n" , serverCount , fromuser );
			
			for(i = 0 ; i < MAX_CONNECTION_COUNT ; i++)
			{
				if (SocketArr[i] != -1)
				{
					send(SocketArr[i] , send_buff , strlen(send_buff)+1 , 0);
				}
			}
		}

		if(isRegistered == true)
		{
			//type ==11 Ϊע��ʧ��
			memset( send_buff , 0, sizeof(send_buff) );
			sprintf(send_buff , "%s\n%s\n%s\n%s%s", "11" ,  "SERVER" , touser  , fromuser , "   �Ѵ��ڣ���ѡ�������û�����");
			send(client_socket , send_buff, strlen(send_buff)+1,0);
			serverCount++;
			printf("%d.    %s  �û������ڣ��ܾ�����ע�Ტ�ر����ӣ�\n" , serverCount , fromuser);

			closesocket(*s);
			*s = -1;
		}
	}
	
	//�㲥
	 if (type == 1 )
	{
		for(i = 0 ; i < MAX_CONNECTION_COUNT ; i++)
		{
			if (SocketArr[i] != -1)
			{
				memset( send_buff , 0, sizeof(send_buff) );
				sprintf(send_buff , "%s\n%s\n%s\n%s", "1" ,  fromuser , touser , data);
				send(SocketArr[i] , send_buff , strlen(receive_buff)+1 , 0);
			}
		}
		serverCount++;
		printf("%d.    %s ��������˵ �� %s \n" , serverCount ,fromuser  , data);
	}

	//˽�ģ�����
	if (type == 2 )
	{
		//�û����Լ�����˽����Ϣ
		if (strcmp(fromuser , touser) == 0)
		{
			memset( send_buff , 0, sizeof(send_buff) );
			sprintf(send_buff , "%s\n%s\n%s\n%s%s", "14" ,  "SERVER" , fromuser  ,"�����Լ�������һ��˽����Ϣ��",data);
			send(*s , send_buff , strlen(send_buff)+1, 0);
			serverCount++;
			printf("%d.    %s ���Լ�������һ��˽����Ϣ �� %s \n" , serverCount , fromuser  , data );
			return Ret;
		}
		bool isExist = false;
		//�ж�˽�Ķ����Ƿ����
		for(i = 0 ; i < MAX_CONNECTION_COUNT ; i++)
		{
			if (SocketArr[i] != -1 && strcmp(username[i] , touser) == 0)
			{
				//����˽����Ϣ��˽�Ķ���
				memset( send_buff , 0, sizeof(send_buff) );
				sprintf(send_buff , "%s\n%s\n%s\n%s", "2" ,  fromuser , touser , data);
				send(SocketArr[i] , receive_buff , strlen(send_buff)+1 , 0);
				isExist = true;
				break;
			}
		}

		//˽�Ķ������
		if (isExist)
		{
			//���ظ�������
			memset( send_buff , 0, sizeof(send_buff) );
			sprintf(send_buff , "%s\n%s\n%s\n%s", "2" ,  fromuser , touser , data);
			send(*s , send_buff , strlen(send_buff)+1 , 0);
			serverCount++;
			printf("%d.    %s �� %s ˵ �� %s \n" , serverCount , fromuser , touser , data );
		}

		//˽�Ķ��󲻴���
		else
		{
			//���ظ������߳�����Ϣ
			memset( send_buff , 0, sizeof(send_buff) );
			sprintf(send_buff , "%s\n%s\n%s\n%s%s", "14" ,  "SERVER" , fromuser  , touser , "�����ڣ���˶����ߵ��û��б��ٷ���˽����Ϣ��");
			send(*s , send_buff , strlen(send_buff)+1 , 0);
			serverCount++;
			printf("%d.    %s �Բ����ߵ� %s ����һ������Ϊ ��˽����Ϣ :  %s\n" , serverCount , fromuser , touser , data );
		}
	}
	
    return Ret;
}