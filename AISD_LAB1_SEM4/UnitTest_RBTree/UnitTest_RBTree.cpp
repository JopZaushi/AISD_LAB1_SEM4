#include "pch.h"
#include "CppUnitTest.h"
#include "..\\AISD_LAB1_SEM4\Classes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestforRBtree
{
	TEST_CLASS(UnitTestforRBtree)
	{
	public:

		TEST_METHOD(CONSTRUCTOR_WITHOUT_PARAMETERS)
		{
			map<int, int> a;
			Assert::IsTrue(a.size == 0);
		}

		TEST_METHOD(DESTRUCTOR)
		{
			map<int, int> a;
			a.insert(12, 4);
			a.insert(21, 1);
			a.insert(2, 5);
			Assert::IsTrue(a.size == 3);
			a.clear();
			Assert::IsTrue(a.size == 0);
		}

		TEST_METHOD(INSERT_ELEMENT)
		{
			//lecture example
			map<int, int> a;
			a.insert(5, 33);
			a.insert(3, 13);
			a.insert(2, 53);
			a.insert(1, 41);
			a.insert(10, 61);
			a.insert(6, 11);
			a.insert(8, 21);
			a.insert(4, 15);
			a.insert(14, 31);
			a.insert(44, 20);
			Assert::IsTrue(a.size == 10);
			Assert::IsTrue(a.find(8)->color == BLACK);
			Assert::IsTrue(a.find(3)->color == RED);
			Assert::IsTrue(a.find(5)->color == RED);
			Assert::IsTrue(a.find(6)->color == BLACK);
			Assert::IsTrue(a.find(4)->color == BLACK);
			Assert::IsTrue(a.find(14)->color == BLACK);
			Assert::IsTrue(a.find(2)->color == BLACK);
			Assert::IsTrue(a.find(44)->color == RED);
			Assert::IsTrue(a.find(1)->color == RED);
			Assert::IsTrue(a.find(10)->color == RED);
		}

		TEST_METHOD(REMOVE_ELEMENT)
		{
			//lecture example
			map<int, int> b;
			b.insert(12, 55);
			b.insert(7, 65);
			b.insert(54, 40);
			b.insert(55, 60);
			b.insert(78, 75);
			b.insert(81, 57);
			Assert::IsTrue(b.size == 6);
			b.remove(54);
			Assert::IsTrue(b.size == 5);
			Assert::IsTrue(b.find(7)->color == BLACK);
			Assert::IsTrue(b.find(81)->color == RED);
			Assert::IsTrue(b.find(78)->color == BLACK);
			Assert::IsTrue(b.find(12)->color == BLACK);
			Assert::IsTrue(b.find(55)->color == BLACK);
		}

		TEST_METHOD(SEARCH_FOR_AN_ELEMENT_BY_KEY)
		{
			//lecture example
			map<int, int> a;
			a.insert(5, 33);
			a.insert(3, 13);
			a.insert(2, 53);
			a.insert(1, 41);
			a.insert(10, 61);
			a.insert(6, 11);
			a.insert(8, 21);
			a.insert(4, 15);
			a.insert(14, 31);
			a.insert(44, 20);
			Assert::IsTrue(a.size == 10);
			Assert::IsTrue(a.find(8)->color == BLACK);
			Assert::IsTrue(a.find(3)->color == RED);
			Assert::IsTrue(a.find(5)->color == RED);
			Assert::IsTrue(a.find(6)->color == BLACK);
			Assert::IsTrue(a.find(4)->color == BLACK);
			Assert::IsTrue(a.find(14)->color == BLACK);
			Assert::IsTrue(a.find(2)->color == BLACK);
			Assert::IsTrue(a.find(44)->color == RED);
			Assert::IsTrue(a.find(1)->color == RED);
			Assert::IsTrue(a.find(10)->color == RED);
		}

		TEST_METHOD(REMOVING_SINGLE_ELEMENT)
		{
			map<int, int> a;
			a.insert(5, 33);
			a.insert(3, 13);
			a.insert(2, 53);
			a.insert(1, 41);
			a.insert(10, 61);
			a.insert(6, 11);
			a.insert(8, 21);
			a.insert(4, 15);
			a.insert(14, 31);
			a.insert(44, 20);
			Assert::IsTrue(a.size == 10);
			a.remove_one_elem(20);
			Assert::IsTrue(a.size == 9);
		}

		TEST_METHOD(CLEAR)
		{
			map<int, int> a;
			a.insert(12, 4);
			a.insert(21, 1);
			a.insert(2, 5);
			Assert::IsTrue(a.size == 3);
			a.clear();
			Assert::IsTrue(a.size == 0);
		}

	};
}
