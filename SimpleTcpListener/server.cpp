///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////

#define FD_SETSIZE      4096
#include "System/SimpleTcpListener.h"
#include "Logger/CLogger.h"
#include "System/Thread.h"
#include "System/SimpleDateTime.h"
#include <unordered_map>
#include <mutex>
#include <deque>
#include <vector>

using namespace System::Net;
using namespace System::Threading;
using namespace System::Logger;
using namespace System::DateTime;
class CellClient;
class CellServer;
struct DataHeader;

#define THREAD_COUNT 4
#define BUFF_SIZE 10240

std::vector<CellServer*> g_servers;
std::shared_ptr<SimpleTcpListener> g_server = std::make_shared<SimpleTcpListener>(8888);

std::atomic<int> g_client_count = 0;
int g_recv_count = 0;
int64_t g_time = 0;

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
	char m_data[996];
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
	char* m_buff = new char[BUFF_SIZE * 5];
	int m_last_pos = 0;
};


class CellServer
{
public:
	CellServer()
	{
		m_thread = new Thread(std::bind(&CellServer::HandleClients, this));
	}
	~CellServer()
	{
		delete m_thread;
	}

	void AddTcpClient(SimpleTcpClient* client)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_tcp_clients.push_back(client);
	}

	void SwapClients()
	{
		if (!m_tcp_clients.empty())
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (!m_tcp_clients.empty())
			{
				for (auto p_client : m_tcp_clients)
				{
					CellClient* client = new CellClient(p_client);
					m_clients[p_client->GetSocket()] = client;
				}
				m_tcp_clients.clear();
			}
		}
	}

	size_t Size()
	{
		return m_clients.size();
	}

	void RecveAllClient()
	{
		if (m_clients.empty())
		{
			SleepMs(0);
			return;
		}
		timeval t = { 1, 10 };
		fd_set fdRead;
		FD_ZERO(&fdRead);
		int max_fd = -1;
		for (auto itr = m_clients.begin(); itr != m_clients.end(); itr++)
		{
			FD_SET(itr->first, &fdRead);
			if (max_fd < (itr->first))
			{
				max_fd = (int)itr->first;
			}
		}
		int ret = select(max_fd + 1, &fdRead, nullptr, nullptr, &t);
		if (0 >= ret)
		{
			return;
		}
		for (size_t i = 0; i < fdRead.fd_count; i++)
		{
			SOCKET sock = fdRead.fd_array[i];
			auto itr = m_clients.find(sock);
			bool rslt = RecvData(itr->second);
			if (!rslt)
			{
				m_clients.erase(itr);
				delete itr->second;
				g_client_count--;
				//CLOG_CONSOLE_ERROR("client exit <SOCKET=%d><clients=%d>", (int)sock, g_client_count);
			}
		}
	}

	bool RecvData(CellClient* client)
	{
		char* szRecv = client->Buff() + client->GetLastPos();
		int length = client->Recv(szRecv, BUFF_SIZE * 5);
		if (length <= 0)
		{
			//CLOG_CONSOLE_ERROR("client<Socket=%d>exited, task finished", client->GetClient()->GetSocket());
			return false;
		}

		client->SetLastPos(client->GetLastPos() + length);
		while (client->GetLastPos() >= sizeof(DataHeader))
		{
			DataHeader* header = (DataHeader*)client->Buff();
			if (client->GetLastPos() >= header->m_length)
			{
				int last_size = client->GetLastPos() - header->m_length;
				OnMsg(client, header);
				memcpy(client->Buff(), client->Buff() + header->m_length, last_size);
				client->SetLastPos(last_size);
			}
			else
			{
				break;
			}
		}
		return true;
	}

	void OnMsg(CellClient* client, DataHeader* header)
	{
		g_recv_count++;
		//DataPackage* package = (DataPackage*)header;
		//client->Send((char*)header, header->m_length);
	}

	void Start()
	{
		m_thread->Start();
	}

	void HandleClients()
	{
		while (true)
		{
			SwapClients();
			RecveAllClient();
		}
	}

private:
	std::mutex m_mutex;
	Thread* m_thread;
	std::vector<SimpleTcpClient*> m_tcp_clients;//need lock shared resource
	std::unordered_map<SOCKET, CellClient*> m_clients;
};


int main(int argc, char** argv)
{
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		auto cell_server = new CellServer();
		g_servers.push_back(cell_server);
		cell_server->Start();
	}
	Sleep(1);
	g_server->Start();
	CLOG_CONSOLE_INFO("server start listen [port=%d]", g_server->GetEndPoint()->GetPort());
	int idx = 0;
	while (true)
	{
		if (g_time == 0)
		{
			g_time = GetTimestamp();
		}
		int64_t crt_t = GetTimestamp();
		double t = (crt_t - g_time)*0.000001;
		if (t > 1.0)
		{
			CLOG_CONSOLE_INFO("<threads=%d><time=%lf><clients=%d><packages=%d>", THREAD_COUNT, t, g_client_count, (int)(g_recv_count / t));
			g_time = crt_t;
			g_recv_count = 0;
		}

		timeval tv = { 0,10 };
		fd_set fdRead;
		FD_ZERO(&fdRead);
		FD_SET(g_server->GetSocket(), &fdRead);

		int ret = select((int)g_server->GetSocket() + 1, &fdRead, nullptr, nullptr, &tv);
		if (0 >= ret)
		{
			continue;
		}

		if (FD_ISSET(g_server->GetSocket(), &fdRead))
		{
			FD_CLR(g_server->GetSocket(), &fdRead);
			SimpleTcpClient* client = g_server->AcceptTcpClient();
			if (client == nullptr)
			{
				CLOG_CONSOLE_ERROR("accept invalid client<error: %s>", strerror(errno));
				break;
			}
			SOCKET sock = client->GetSocket();
			std::string ip = client->GetIPAddress()->GetIPAddress();
			if (INVALID_SOCKET != sock)
			{
				g_servers[idx]->AddTcpClient(client);
				g_client_count++;
				idx++;
				if (idx == THREAD_COUNT)
				{
					idx = 0;
				}
				//CLOG_CONSOLE_INFO("new client join <SOCKET=%d><%d>", (int)sock, g_client_count);
			}
		}
	}
	return 1;
}