#include <windows.h>
#include <iostream>
#include <conio.h>
#include <io.h>
#include "tree.h"

using namespace std;

void PrintMenu()
{
	char Menu[] = "1.Insert node\n2.Delete node\n3.Print node\n4.Search node\n5.Balance\n6.Save\n7.Load\n8.Exit\n";
	system("cls");
	cout << Menu;
}

void Insert(Tree &obj)
{
	system("cls");
	cout << "Enter a quantity of elements to add: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		Elem *temp = new Elem;
		cout << "\nEnter an english word " << i + 1 << endl;
		cin >> temp->eng;
		cout << "\nEnter a russian word " << i + 1 << endl;
		cin >> temp->rus;
		obj.Insert(temp);
	}
}

void Print(Tree &obj)
{
	system("cls");
	obj.Print(obj.GetRoot());
	_getch();
}

void Search(Tree &obj)
{
	system("cls");
	cout << "Enter an english word for search:\n";
	char buf[15];
	cin >> buf;
	Elem *elem = obj.Search(obj.GetRoot(), buf);
	if (elem)
		cout << elem->rus;
	else
		cout << "\nWord not found\n";
	_getch();

}

void Delete(Tree &obj)
{
	system("cls");
	cout << "Enter an english word for delete:\n";
	char buf[15];
	cin >> buf;
	Elem*p = obj.Search(obj.GetRoot(), buf);
	obj.Del(p);
}

void Âalancing(Tree &obj)
{
	system("cls");
	obj.Âalancing();
	cout << "\nTree is balanced\n";
	_getch();
}

void Save(Tree &obj)
{
	FILE* f = nullptr;
	fopen_s(&f, "tree.dat", "wb");
	obj.Save(obj.GetRoot(), f);
	fclose(f);
}

void Load(Tree &obj)
{
	FILE* f = nullptr;
	fopen_s(&f, "tree.dat", "rb");
	if (f == nullptr)
		return;
	int n = _filelength(_fileno(f)) / 30;
	Elem* temp = new Elem[n];
	for (int i = 0; i < n; i++)
	{
		obj.Load(&temp[i], f);
	}
	obj.Âalancing(temp, 0, n - 1);
	delete[] temp;
	fclose(f);
}

void main()
{
	Tree obj;
	Load(obj);
	while (true)
	{
		PrintMenu();
		char res = _getch();
		switch (res)
		{
		case '1': Insert(obj);
			break;
		case '2': Delete(obj);
			break;
		case '3': Print(obj);
			break;
		case '4': Search(obj);
			break;
		case '5': Âalancing(obj);
			break;
		case '6': Save(obj);
			break;
		case '7': Load(obj);
			break;
		case '8':
			return;
		}
	}
}