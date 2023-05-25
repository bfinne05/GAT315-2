#include "Test.h"
#include "ForceTest.h"

int main(int argc, char* argv[])
{
	Test* test = new (ForceTest);
	test->Initialize();
	while (!test->IsQuit()) { test->Run(); }
	delete test;

	return 0;
}