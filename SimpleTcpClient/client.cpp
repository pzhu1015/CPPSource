///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/SimpleTcpClient.h"
#include "Logger/CLogger.h"
#include "System/Thread.h"
#include <vector>
#include <unordered_map>

using namespace System::Net;
using namespace System::Logger;
using namespace System::Threading;
class CellClient;
class CellServer;

#define BUFF_SIZE 102400
#define THREAD_COUNT 4
#define CLIENT_COUNT 5000
std::string g_ip = "127.0.0.1";
int g_port = 8888;

std::vector<CellServer*> g_servers;
std::atomic<int> g_client_count = 0;

struct DataHeader
{
	int m_length = 0;
};

struct DataPackage : DataHeader
{
	DataPackage()
	{
		m_length = sizeof(DataPackage);
	}
	char m_data[96];
};

class CellClient
{
public:
	CellClient(SimpleTcpClient* client)
	{
		m_client = client;
		memset(m_buff, 0, sizeof(m_buff));
		m_last_pos = 0;
	}
	~CellClient()
	{
		delete m_client;
	}

	int Recv(char* data, int length)
	{
		return m_client->Receive(data, length);
	}

	bool Send(char* data, int length)
	{
		return m_client->Send(data, length);
	}

	SimpleTcpClient* GetClient()
	{
		return m_client;
	}

	char* Buff()
	{
		return m_buff;
	}

	int GetLastPos()
	{
		return m_last_pos;
	}

	void SetLastPos(int pos)
	{
		m_last_pos = pos;
	}
private:
	SimpleTcpClient* m_client;
	char m_buff[BUFF_SIZE * 10] = { 0 };
	int m_last_pos = 0;
};

//void OnMsg(const std::shared_ptr<CellClient> &client, DataHeader* header)
//{
//	DataPackage* package = (DataPackage*)header;
//}
//
//bool RecvData(const std::shared_ptr<CellClient> &client)
//{
//	int length = client->Recv(g_recv_buff, BUFF_SIZE);
//	if (length <= 0)
//	{
//		CLOG_CONSOLE_ERROR("client<Socket=%d>exited, task finished", client->GetClient()->GetSocket());
//		return false;
//	}
//
//	memcpy(client->Buff() + client->GetLastPos(), g_recv_buff, length);
//	client->SetLastPos(client->GetLastPos() + length);
//	while (client->GetLastPos() >= sizeof(DataHeader))
//	{
//		DataHeader* header = (DataHeader*)client->Buff();
//		if (client->GetLastPos() >= header->m_length)
//		{
//			int last_size = client->GetLastPos() - header->m_length;
//			OnMsg(client, header);
//			memcpy(client->Buff(), client->Buff() + header->m_length, last_size);
//			client->SetLastPos(last_size);
//		}
//		else
//		{
//			break;
//		}
//	}
//	return true;
//}

class CellServer
{
public:
	CellServer(int count)
	{
		m_client_count = count;
		m_thread = new Thread(std::bind(&CellServer::HandleClients, this));
	}
	~CellServer()
	{
		delete m_thread;
	}

	void AddClient(CellClient* client)
	{
		m_clients.push_back(client);
	}

	void Start()
	{
		m_thread->Start();
	}

	void HandleClients()
	{
		for (int i = 0; i < m_client_count; i++)
		{
			SimpleTcpClient* p_client = new SimpleTcpClient();
			bool rslt = p_client->Connect(g_ip, g_port);
			if (!rslt)
			{
				CLOG_CONSOLE_ERROR("connect failed [%s:%d] ", g_ip, g_port);
				return;
			}

			CellClient* client = new CellClient(p_client);
			m_clients.push_back(client);
			g_client_count++;
			//CLOG_CONSOLE_INFO("connect success <%s:%d><threads=%d><clients=%d><thread clients=%d> ", g_ip, g_port, THREAD_COUNT, g_client_count, i + 1);
		}
		Sleep(1);
		DataPackage packages[10];
		for (int i = 0; i < 10; i++)
		{
			strcpy(packages[i].m_data, "i am send data");
		}
		while (true)
		{
			for (size_t i = 0; i < m_clients.size(); i++)
			{
				auto client = m_clients[i];
				//TODO send data
				bool rslt = client->Send((char*)&packages, sizeof(DataPackage));
				if (!rslt)
				{
					m_clients.erase(m_clients.begin() + i);
					g_client_count--;
					CLOG_CONSOLE_ERROR("send failed, exit client<SOCKET=%d><clients=%d><thread clients=%d>", client->GetClient()->GetSocket(), g_client_count, m_clients.size());
					continue;
				}
			}
		}
	}

private:
	std::vector<CellClient*> m_clients;
	Thread* m_thread;
	int m_client_count = 0;
};

int main(int argc, char** argv)
{
	int per_count = CLIENT_COUNT / THREAD_COUNT;
	int last = CLIENT_COUNT % THREAD_COUNT;

	for (int i = 0; i < THREAD_COUNT; i++)
	{
		int count = per_count;
		if (i == THREAD_COUNT)
		{
			count += last;
		}
		CellServer* server = new CellServer(count);
		g_servers.push_back(server);
	}

	for (int i = 0; i < THREAD_COUNT; i++)
	{
		g_servers[i]->Start();
	}

	//DataPackage package;
	//strcpy(package.m_data, "i am send data");
	//while (g_run)
	//{
	//	for (size_t i=0; i < g_clients.size(); i++)
	//	{
	//		auto client = g_clients[i];
	//		//TODO send data
	//		bool rslt = client->Send((char*)&package, sizeof(DataPackage));
	//		if (!rslt)
	//		{
	//			g_clients.erase(g_clients.begin() + i);
	//			CLOG_CONSOLE_ERROR("send failed, exit client<SOCKET=%d><clients=%d>", client->GetClient()->GetSocket(), g_clients.size());
	//			continue;
	//		}

	//		//TODO receive data
	//		SOCKET sock = client->GetClient()->GetSocket();
	//		fd_set fdReads;
	//		FD_ZERO(&fdReads);
	//		FD_SET(sock, &fdReads);
	//		timeval t = { 0,0 };
	//		int ret = select((int)sock + 1, &fdReads, 0, 0, &t);
	//		if (FD_ISSET(sock, &fdReads))
	//		{
	//			FD_CLR(sock, &fdReads);
	//			bool rslt = RecvData(client);
	//			if (!rslt)
	//			{
	//				g_clients.erase(itr++);
	//				CLOG_CONSOLE_ERROR("send failed, exit client<SOCKET=%d><clients=%d>", client->GetClient()->GetSocket(), g_clients.size());
	//				continue;
	//			}
	//		}
	//	}
	//}
	while (true)
	{
		Sleep(1);
	}
	return 1;
}