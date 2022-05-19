#include <iostream>
#include <string>
#include <sstream>
//Put a space after each number, action, or parenthesis.
using namespace std;
struct Node
{
	string value;
	Node* next;
};
Node* front{ nullptr };
void push_back(string value)
{
	Node* last = new Node;
	last = front;
	Node* current = new Node;
	current->value = value;
	current->next = nullptr;
	if (front != nullptr)
	{
		while (last->next != nullptr)
		{
			last = last->next;
		}
		last->next = current;
	}
	else {
		front = current;
	}
}
void push_front(string value)
{
	Node* current = new Node;
	current->value = value;
	current->next = front;
	front = current;
}
void pop_front()
{
	Node* current = new Node;
	current = front;
	if (front->next != nullptr)
	{
		front = front->next;
		delete current;
	}
	else
	{
		front = nullptr;
	}
}
void print()
{
	for (Node* current{ front }; current != nullptr; current = current->next)
		cout << current->value;
	cout << endl;
}
int getter(string check) {
	if ((check == "0") || (check == "1") || (check == "2") || (check == "3") || (check == "4") || (check == "5") || (check == "6") || (check == "7") || (check == "8") || (check == "9"))
		return 5;
	if (check == "*" || check == "/")
		return 4;
	if (check == "+" || check == "-")
		return 3;
	if (check == "(")
		return 2;
}
string return_post(string s) {
	string h = "";
	string c = "";
	Node* current = new Node;
	for (int i = 0; i < s.length(); ++i) {
		c = s[i];
		if (getter(c) == 5) {
			while (s[i] != ' ' && i < s.length())
			{
				c = s[i];
				h = h + c;
				i++;
			}
			h += " ";

		}
		else if (getter(c) == 2) {
			push_front(c);
		}
		else if ((s[i] == ')') && (front != nullptr)) {
			while ((front->value != "(") && (front != nullptr)) {
				h = h + front->value + " ";
				pop_front();
			}
			pop_front();
		}
		else if ((front != nullptr && s[i] != ' ' && (getter(c) == 3) && (getter(front->value) == 4))) {
			h = h + front->value + " ";
			pop_front();
			push_front(c);
		}
		else if ((front != nullptr) && s[i] != ' ' && (getter(c) > getter(front->value))) {
			push_front(c);
		}
		else if (s[i] != ' ' && (front != nullptr) && (getter(c) == getter(front->value))) {
			h = h + front->value + " ";
			pop_front();
			push_front(c);
		}
		else if (front == nullptr && (getter(c) == 3 || getter(c) == 4))
			push_front(c);
	}
	while (front != nullptr)
	{
		h = h + front->value + " ";
		pop_front();
	}
	return h;
}
void calculate(string postfix)
{
	string out = "";
	int x = 0;
	int y = 0;
	string b;
	for (int i = 0; i < postfix.length(); ++i)
	{
		b = postfix[i];
		if (getter(b) == 5) {
			while (postfix[i] != ' ' && i < postfix.length())
			{
				b = postfix[i];
				out = out + b;
				i++;
			}
			push_front(out);
			out = "";
		}
		else if ((front != nullptr) && ((getter(b) == 3) || (getter(b) == 4)) && (b != " "))
		{
			x = stoi(front->value);
			pop_front();
			y = stoi(front->value);
			pop_front();
			if (b == "+")
			{
				int s = y + x;
				stringstream ss;
				ss << s;
				ss >> out;
				push_front(out);
				out = "";
			}
			else if (b == "-")
			{
				int s = y - x;
				stringstream ss;
				ss << s;
				ss >> out;
				push_front(out);
				out = "";
			}
			else if (b == "*")
			{
				int s = y * x;
				stringstream ss;
				ss << s;
				ss >> out;
				push_front(out);
				out = "";
			}
			else if (b == "/")
			{
				int s = y / x;
				stringstream ss;
				ss << s;
				ss >> out;
				push_front(out);
				out = "";
			}
		}
	}
	cout << front->value;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	string s = "";
	cout << "input\n";
	getline(cin, s);
	string h = "";
	h = return_post(s);
	cout << h << endl;
	cout << "Solve this example? Press: 1\n";
	int a;
	cin >> a;
	if (a == 1)
	{
		calculate(h);
	}
	else
	{
		cout << "n/a";
	}
}
// 12 + 5 - 7 - ( 2 * 10 )