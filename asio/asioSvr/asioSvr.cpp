//#define ASIO_STANDALONE
//#define _WIN32_WINNT 0x0A00
//#define _CRT_SECURE_NO_WARNINGS

#include <asio.hpp>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUF     8192

using asio::ip::tcp;

char sPt[32] = "60000";

struct RemoteHost
{
	std::shared_ptr<tcp::socket> scH;       // socket

	RemoteHost() = default;

	explicit RemoteHost(std::shared_ptr<tcp::socket> s)
		: scH(std::move(s))
	{
	}

	void Close()
	{
		if(!scH)
			return;

		asio::error_code ec;
		scH->shutdown(tcp::socket::shutdown_both, ec);
		scH->close(ec);
		scH.reset();
	}
};

std::vector<std::shared_ptr<RemoteHost>> g_vHost;   // host list
std::mutex g_CS;                                    // 임계 구역

void EchoMsg(const std::string& msg);
void WorkClient(std::shared_ptr<RemoteHost> host);
void DeleteHost(std::shared_ptr<RemoteHost> host);

int main()
{
	try
	{
		asio::io_context ioContext;

		printf("Starting Server.\nPort: %s\n", sPt);

		tcp::acceptor acceptor(
			ioContext,
			tcp::endpoint(tcp::v4(), static_cast<unsigned short>(atoi(sPt)))
		);

		while(true)
		{
			auto socket = std::make_shared<tcp::socket>(ioContext);

			acceptor.accept(*socket);

			// Nagle off
			socket->set_option(tcp::no_delay(true));

			auto host = std::make_shared<RemoteHost>(socket);

			{
				std::lock_guard<std::mutex> lock(g_CS);
				g_vHost.push_back(host);
			}

			auto ep = socket->remote_endpoint();
			printf("Accept Client: %s:%u\n",
				ep.address().to_string().c_str(),
				ep.port());

			std::thread(WorkClient, host).detach();
		}
	}
	catch(const std::exception& e)
	{
		printf("Server Error: %s\n", e.what());
	}

	return 0;
}

void WorkClient(std::shared_ptr<RemoteHost> host)
{
	try
	{
		asio::streambuf rcvBuf;

		while(host && host->scH && host->scH->is_open())
		{
			asio::read_until(*host->scH, rcvBuf, '\n');

			std::istream is(&rcvBuf);
			std::string rcvMsg;
			std::getline(is, rcvMsg);

			if(rcvMsg.empty())
				continue;

			auto ep = host->scH->remote_endpoint();

			char sBuf[MAX_BUF] = {};
			snprintf(sBuf, MAX_BUF, "%5u : %s\n",
				ep.port(),
				rcvMsg.c_str());

			printf("Recv from Client : %s", sBuf);

			EchoMsg(sBuf);
		}
	}
	catch(const std::exception& e)
	{
		printf("Disconnect Client: %s\n", e.what());
	}

	DeleteHost(host);
}

void EchoMsg(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(g_CS);

	for(auto it = g_vHost.begin(); it != g_vHost.end(); )
	{
		auto host = *it;

		if(!host || !host->scH || !host->scH->is_open())
		{
			it = g_vHost.erase(it);
			continue;
		}

		try
		{
			asio::write(*host->scH, asio::buffer(msg));
			++it;
		}
		catch(...)
		{
			host->Close();
			it = g_vHost.erase(it);
		}
	}
}

void DeleteHost(std::shared_ptr<RemoteHost> host)
{
	if(!host)
		return;

	host->Close();

	std::lock_guard<std::mutex> lock(g_CS);

	auto it = std::find(g_vHost.begin(), g_vHost.end(), host);
	if(it != g_vHost.end())
		g_vHost.erase(it);
}
