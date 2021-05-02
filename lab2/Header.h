#pragma once
#include<string>
using namespace std;

class List
{
public:
	class cipher
	{
	public:
		cipher(string code, char symbol,cipher* next = nullptr) {
			this->code = code;
			this->symbol = symbol;
			this->next = next;
		};
		~cipher() {};
		string code;
		char symbol;
		cipher* next;
	};
	cipher* head;
	cipher* tail;
	size_t size;
	List();
	~List();
	void reset_list();
	void push_back(string code,char element); // добавление в конец списка
	void clear(); // удаление всех элементов списка
	void pop_front(); // удаление первого элемента
	void insert(string input);
	void sort(int* massiv, int size);
	void print_to_console(int* massiv, int size,string input);
	void separation(int* massiv, int size, string code);
	string decryption(string input);
};