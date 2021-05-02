#include "pch.h"
#include "CppUnitTest.h"
#include"../lab2/Header.h"
#include"../lab2/Header.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		List* newlist;
		TEST_METHOD_INITIALIZE(TestMethod1)
		{
			newlist = new List;
		}
		TEST_METHOD(correct_incert)
		{
			newlist->insert("hello");
			Assert::AreEqual(newlist->head->symbol,'l');
			Assert::IsTrue(newlist->head->code== "11");
			Assert::AreEqual(newlist->head->next->symbol, 'o');
			Assert::IsTrue(newlist->head->next->code == "10");
			Assert::AreEqual(newlist->head->next->next->symbol, 'h');
			Assert::IsTrue(newlist->head->next->next->code == "01");
			Assert::AreEqual(newlist->head->next->next->next->symbol, 'e');
			Assert::IsTrue(newlist->head->next->next->next->code == "00");
		}
		TEST_METHOD(correct_sort)
		{
			int massiv[8] = { 52,1,28,5,78,8,6,2 };
			newlist->sort(massiv, 8);
			Assert::AreEqual(massiv[1], 8);
			Assert::AreEqual(massiv[3], 5);
			Assert::AreEqual(massiv[5], 2);
			Assert::AreEqual(massiv[7], 1);
		}
		TEST_METHOD(correct_decryption)
		{
			newlist->insert("hello");
			string test = newlist->decryption("1110");
			Assert::IsTrue(test=="lo");
		}
		TEST_METHOD(incorrect_decryption)
		{
			newlist->insert("hello");
			string test = newlist->decryption("11100");
			Assert::IsTrue(test == "");
		}
	};
}
