//#define ASIO_STANDALONE
//#define _WIN32_WINNT 0x0A00
//#define _CRT_SECURE_NO_WARNINGS

#include <asio.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUF     8192

using asio::ip::tcp;

char sPt[32] = "60000";
char sIp[64] = "127.0.0.1";

void WorkRcv(tcp::socket* socket);

int main()
{
	try
	{
		asio::io_context ioContext;
		tcp::socket socket(ioContext);

		printf("Starting Client.\nIP: %s\nPort: %s\n", sIp, sPt);

		tcp::endpoint endpoint(
			asio::ip::make_address(sIp),
			static_cast<unsigned short>(atoi(sPt))
		);

		socket.connect(endpoint);

		// Nagle off
		socket.set_option(tcp::no_delay(true));

		printf("Connection Successed\n");

		std::thread rcvThread(WorkRcv, &socket);

		while(socket.is_open())
		{
			char sSnd[MAX_BUF] = {};

			if(nullptr == fgets(sSnd, MAX_BUF, stdin))
				break;

			int iLen = static_cast<int>(strlen(sSnd));

			if(1 > iLen)
				continue;

			if('\n' == sSnd[iLen - 1])
			{
				sSnd[iLen - 1] = 0;
				--iLen;
			}

			if(0 >= iLen)
				continue;

			std::string msg = sSnd;
			msg += '\n';

			asio::write(socket, asio::buffer(msg));

			if(msg == "/quit\n")
				break;
		}

		asio::error_code ec;
		socket.shutdown(tcp::socket::shutdown_both, ec);
		socket.close(ec);

		if(rcvThread.joinable())
			rcvThread.join();
	}
	catch(const std::exception& e)
	{
		printf("Client Error: %s\n", e.what());
	}

	return 0;
}

void WorkRcv(tcp::socket* socket)
{
	try
	{
		asio::streambuf rcvBuf;

		while(socket && socket->is_open())
		{
			asio::read_until(*socket, rcvBuf, '\n');

			std::istream is(&rcvBuf);
			std::string rcvMsg;
			std::getline(is, rcvMsg);

			printf("Recv from server : %s\n", rcvMsg.c_str());
		}
	}
	catch(const std::exception& e)
	{
		printf("Network Close: %s\n", e.what());
	}
}
