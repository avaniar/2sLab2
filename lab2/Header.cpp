#include "Header.h"
#include <iostream>
using namespace std;
void List::reset_list()
{
	head = nullptr;
	tail = nullptr;
}

List::List()
{
	reset_list();
	size = 0;
}
List::~List()
{
	clear();
}
void List::push_back(string code,char newelement)
{
	if (size == 0)//We add the new element first.
	{
		head = new cipher(code,newelement);
		tail = head;
	}
	else//We add the new element last.
	{
		cipher* current = new cipher(code,newelement);
		tail->next = current;
		tail = current;
	}
	size++;
}
void List::clear()
{
	while (size)
	{
		pop_front();
	}
}
void List::pop_front()
{
	if (size == 0) return;//Exit the function.
	if (size == 1)//We remove the first element and reset the list.
	{
		delete head;
		reset_list();
	}
	else//We remove the first element
	{
		cipher* current = head->next;
		head->next = nullptr;
		delete head;
		head = current;
	}
	size--;
}
void List::insert(string input)
{
	int* massiv = new int[0];
	int currentsize = 0;
	for (int i = 0;i < input.size();i++)
	{
		bool flag=true;
		for(int j=0;j<currentsize;j+=2)
		{
			if (massiv[j] == input[i])
			{
				massiv[j+1]++;
				flag=false;
				break;
			}
		}
		if (flag)
		{
			currentsize += 2;
			massiv= (int*)realloc(massiv, currentsize * sizeof(int));
			massiv[currentsize - 2] = input[i];
			massiv[currentsize - 1] = 1;
		}
	}
	sort(massiv,currentsize);
	string code;
	separation(massiv,currentsize,code);
	print_to_console(massiv, currentsize,input);
}

void List::sort(int*massiv,int size)
{
	int counter;
	do
	{
		counter = 0;
		for (int j = size-1;j >2;j -= 2)
		{
			if (massiv[j] > massiv[j-2])
			{
				int help1 = massiv[j];
				int help2 = massiv[j - 1];
				massiv[j] = massiv[j-2];
				massiv[j-1] = massiv[j - 3];
				massiv[j - 2] =help1;
				massiv[j - 3] = help2;
				counter++;
			}
		}
	} while (counter);
}
void List::print_to_console(int* massiv, int size,string input)
{
	cipher* current;string output;
	for(int i=0;i<size-1;i+=2)
	{
		current = head;
		char symbol = massiv[i];
		while (current->symbol != symbol) current = current->next;
		cout << "'" << symbol << "'|" << " " << massiv[i+1] << " |" << " " << current->code <<endl;
	}
	cout << endl;
	for (int i = 0;i < input.size();i++)
	{
		current = head;
		while (current->symbol != input[i]) current = current->next;
		output.append(current->code);
	}
	cout << "Size before encoding: " << input.size() * 8 << endl;
	cout << "Line after encoding: " << output << endl;
	cout << "Size after encoding: " << output.size() << endl;
	cout << "Compression Ratio: " << 100-(100*output.size())/(input.size() * 8) <<"%"<< endl<<endl;
}

void List::separation(int *massiv,int size,string code)
{
	if (size > 2)
	{
		int left = 0;int sizeleft = 0;int* leftstr = new int[sizeleft];
		int right = 0;int sizeright = 0;int* rightstr = new int[sizeright];
		for (int i = 1;i < size;i += 2)
		{
			if (left > right)
			{
				right += massiv[i];
				sizeright += 2;
				rightstr = (int*)realloc(rightstr, sizeright * sizeof(int));
				rightstr[sizeright - 2] = massiv[i - 1];
				rightstr[sizeright - 1] = massiv[i];
			}
			else
			{
				left += massiv[i];
				sizeleft += 2;
				leftstr = (int*)realloc(leftstr, sizeleft * sizeof(int));
				leftstr[sizeleft - 2] = massiv[i - 1];
				leftstr[sizeleft - 1] = massiv[i];
			}
		}
		string leftcode = code;leftcode.append("1");
		string rightcode = code;rightcode.append("0");
		separation(leftstr, sizeleft, leftcode);
		separation(rightstr, sizeright, rightcode);
	}
	else
	{
		push_back(code, massiv[0]);
	}
}

string List::decryption(string input)
{
	try
	{
		cipher* current;string code;string decryption;
		for (int i = 0;i < input.size();i++)
		{
			code += input[i];
			current = head;
			while (current)
			{
				if (current->code == code)
				{
					decryption += current->symbol;
					code.clear();
					break;
				}
				current = current->next;
			}
		}
		if (code != "") throw "This line cannot be decoded!";
		else cout << "Line after decoding: " << decryption << endl;
		return decryption;
	}
	catch(const char*excep)
	{
		cout << "Error: " << excep << endl;
		return "";
	}
}

