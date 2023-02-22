#include <iostream>
using namespace std;
#include "tree.h"

Tree::Tree()
{
	root = NULL;
	count = 0;
}

Tree::~Tree()
{
	while(root != 0)
		Del(root);
}

// Рекурсивный обход дерева
void Tree::Print(Elem * Node)
{
	if(Node != 0)
	{
		Print(Node->left);
		cout << Node->eng << " \t\t" << Node->rus << endl;
		Print(Node->right);
	}
}

Elem * Tree::Search(Elem * Node, char * k)
{
	// Пока есть узлы и ключи не совпадают
	while(Node != 0 && strcmp(k, Node->eng) != 0)
	{
		if(strcmp(k, Node->eng) < 0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	return Node;
}

Elem * Tree::Min(Elem * Node)
{
	// Поиск самого "левого" узла
	if(Node != 0)
		while(Node->left != 0)
			Node = Node->left;

	return Node;
}

Elem * Tree::Max(Elem * Node)
{
	// Поиск самого "правого" узла
	if(Node != 0)
		while(Node->right != 0)
			Node = Node->right;

	return Node;
}

Elem * Tree::Next(Elem * Node)
{
	Elem * y = 0;
	if(Node != 0)
	{
		// если есть правый потомок
		if(Node->right != 0)
			// Следующий узел - самый "левый узел" в правом поддереве
			return Min(Node->right);

		// родитель узла
		y = Node->parent;
		// если Node не корень и Node справа
		while(y != 0 && Node == y->right)
		{
			// Движемся вверх
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

Elem * Tree::Previous(Elem * Node)
{
	Elem * y = 0;
	if(Node != 0)
	{
		// если есть левый потомок
		if(Node->left != 0)
			// Предыдущий узел - самый "правый" узел в левом поддереве
			return Max(Node->left);

		// родитель узла
		y = Node->parent;
		// если Node не корень и Node слева
		while(y != 0 && Node == y->left)
		{
			// Движемся вверх
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

Elem * Tree::GetRoot()
{
	return root;
}

void Tree::Insert(Elem * z)
{
	// потомков нет
	z->left = NULL;
	z->right = NULL;

	Elem * y = NULL; // родитель вставляемого элемента
	Elem * Node = root;

	// поиск места
	while(Node != 0)
	{
		// будущий родитель
		y = Node;
		if(strcmp(z->eng, Node->eng) < 0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	// заполняем родителя
	z->parent = y;

	if(y == 0) // элемент первый (единственный)
		root = z;
	// чей ключ больше?
	else if(strcmp(z->eng, y->eng) < 0)
		y->left = z;
	else
		y->right = z;
	count++;
}

void Tree::Del(Elem * z)
{
	if(z != 0)
	{
		Elem * Node = NULL; // дочерний узел для удаляемого узла
		Elem * y = NULL; // удаляемый узел
		// не 2 потомка
		if(z->left == 0 || z->right == 0)
			y = z;
		else
			y = Next(z);

		if(y->left != 0)
			Node = y->left;
		else
			Node = y->right;
		// Если удаляется не лист
		if(Node != 0)
			Node->parent = y->parent;
		// Удаляется корневой узел?
		if(y->parent == 0)
			root = Node;
		else if(y == y->parent->left) // слева от родителя?
			y->parent->left = Node;
		else
			y->parent->right = Node;  // справа от родителя?

		if(y != z)
		{
			// Копирование данных узла
			strcpy_s(z->eng, y->eng);
			strcpy_s(z->rus, y->rus);
		}
		delete y;
		count--;
	}
}

void Tree::CopyToArray(Elem* node, Elem* p)
{
	static int i = 0;
	if (node != 0)
	{
		CopyToArray(node->left, p);
		strcpy_s(p[i].eng, node->eng);
		strcpy_s(p[i].rus, node->rus);
		i++;
		CopyToArray(node->right, p);
	}
}

void Tree::Вalancing()
{
	Elem * p = new Elem[count];
	int left = 0, right = count - 1;
	CopyToArray(root, p);
	while (root != 0)
		Del(root);
	Вalancing(p, left, right);
	delete[] p;
}

void Tree::Вalancing(Elem * p, int left, int right)
{
	if (left <= right)
	{
		int middle = (left + right) / 2;
		Elem *temp = new Elem;
		strcpy_s(temp->eng, p[middle].eng);
		strcpy_s(temp->rus, p[middle].rus);
		Insert(temp);
		cout << p[middle].eng << endl;
		Вalancing(p, left, middle - 1);
		Вalancing(p, middle + 1, right);
	}
}

void Tree::Save(Elem * Node, FILE*f)
{
	if (Node != 0)
	{
		Save(Node->left, f);
		fwrite(Node->eng, sizeof(char), 15, f);
		fwrite(Node->rus, sizeof(char), 15, f);
		Save(Node->right, f);
	}
	else
		cout << "\nTREE IS EMPRY!\n";
}

void Tree::Load(Elem * Node, FILE*f)
{
	if (Node != 0)
	{
		fread(Node->eng, sizeof(char), 15, f);
		fread(Node->rus, sizeof(char), 15, f);
	}
}