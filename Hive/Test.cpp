// Test.cpp: 定义应用程序的入口点。
//

#include "Test.h"
#include "CPrint.h"
#include "spdlog/spdlog.h"
using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	spdlog::info("Welcome to spdlog!");
	G::print();
	return 0;
}
