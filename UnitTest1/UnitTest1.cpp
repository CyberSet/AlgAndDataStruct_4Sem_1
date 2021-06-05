#include "pch.h"
#include "CppUnitTest.h"
#include "..//map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mapUnitTest
{
	TEST_CLASS(mapUnitTest)
	{
	public:
		map<int, string> test;
		list<int> *keys = new list<int>;
		TEST_METHOD(CreateTest)
		{	
			keys = test.get_keys();
			Assert::IsTrue(keys->getSize() == 0);
		}

		TEST_METHOD(InsertTest)
		{
			test.insert(1, "jan");
			test.insert(2, "feb");
			test.insert(3, "mar");
			keys = test.get_keys();
			Assert::IsTrue(keys->at(0) == 2 && keys->at(1) == 1 && keys->at(2) == 3);
		}

		TEST_METHOD(LeftRotationTest)
		{
			test.insert(1, "jan");
			test.insert(2, "feb");
			test.insert(3, "mar");
			test.leftRotation(test.getRoot());
			keys = test.get_keys();
			Assert::IsTrue(keys->at(0) == 3 && keys->at(1) == 2 && keys->at(2) == 1);
		}

		TEST_METHOD(RightRotationTest)
		{
			test.insert(1, "jan");
			test.insert(2, "feb");
			test.insert(3, "mar");
			test.rightRotation(test.getRoot());
			keys = test.get_keys();
			Assert::IsTrue(keys->at(0) == 1 && keys->at(1) == 2 && keys->at(2) == 3);
		}

		TEST_METHOD(RemoveTest)
		{
			test.insert(1, "jan");
			test.insert(2, "feb");
			test.insert(3, "mar");
			test.remove(2);
			keys = test.get_keys();
			Assert::IsTrue(keys->at(0) == 1 && keys->at(1) == 3);
		}

		TEST_METHOD(FindTest)
		{
			node<int, string>* temp = new node<int, string>;
			test.insert(1, "jan");
			test.insert(2, "feb");
			test.insert(3, "mar");
			temp = test.find(3);
			Assert::IsTrue(temp->getValue() == "mar");
		}

		TEST_METHOD(ClearTest)
		{
			test.insert(1, "jan");
			test.insert(2, "feb");
			test.insert(3, "mar");
			test.clear();
			keys = test.get_keys();
			Assert::IsTrue(keys->getSize() == 0);
		}

	};
}
