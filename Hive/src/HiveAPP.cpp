#include "Bear.h"


class Hive : public BEngine::Application
{
public:
	Hive(){ std::cout << "cons Hive" << std::endl; }
	~Hive() { std::cout << "Dre Hive" << std::endl; }

};


BEngine::Application* BEngine::CreateApplication()
{
	return new Hive();
}