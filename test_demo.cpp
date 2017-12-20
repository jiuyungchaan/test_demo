// test_demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SpiImp.h"
#include "COXSpi.h"
#include "COXServer.h"
#include "TraderManager.h"

#include <iostream>
#include <memory>
#include <windows.h>
using std::cout;
using std::cin;
using std::endl;


#include <objbase.h>
#include <stdio.h>



/// there is a big difference between main and _tmain
int main(int argc, char** argv)
{
	int port = 5555;
	for (int i = 0; i < argc;) {
		if (strcmp(argv[i], "-p") == 0) {
			port = atoi(argv[++i]);
		}else if (strcmp(argv[i], "-a") == 0) {
			TraderManager::GetInstance()->GetTrader(argv[++i]);
		}
		++i;
	}
	COXServer::Instance().RegisterServer(port);
	cout << "Register server successfully" << endl;
	while (true) {
		Sleep(1);
	}

	return 0;
}

