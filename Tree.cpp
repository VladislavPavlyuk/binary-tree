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

// ����������� ����� ������
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
	// ���� ���� ���� � ����� �� ���������
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
	// ����� ������ "������" ����
	if(Node != 0)
		while(Node->left != 0)
			Node = Node->left;

	return Node;
}

Elem * Tree::Max(Elem * Node)
{
	// ����� ������ "�������" ����
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
		// ���� ���� ������ �������
		if(Node->right != 0)
			// ��������� ���� - ����� "����� ����" � ������ ���������
			return Min(Node->right);

		// �������� ����
		y = Node->parent;
		// ���� Node �� ������ � Node ������
		while(y != 0 && Node == y->right)
		{
			// �������� �����
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
		// ���� ���� ����� �������
		if(Node->left != 0)
			// ���������� ���� - ����� "������" ���� � ����� ���������
			return Max(Node->left);

		// �������� ����
		y = Node->parent;
		// ���� Node �� ������ � Node �����
		while(y != 0 && Node == y->left)
		{
			// �������� �����
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
	// �������� ���
	z->left = NULL;
	z->right = NULL;

	Elem * y = NULL; // �������� ������������ ��������
	Elem * Node = root;

	// ����� �����
	while(Node != 0)
	{
		// ������� ��������
		y = Node;
		if(strcmp(z->eng, Node->eng) < 0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	// ��������� ��������
	z->parent = y;

	if(y == 0) // ������� ������ (������������)
		root = z;
	// ��� ���� ������?
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
		Elem * Node = NULL; // �������� ���� ��� ���������� ����
		Elem * y = NULL; // ��������� ����
		// �� 2 �������
		if(z->left == 0 || z->right == 0)
			y = z;
		else
			y = Next(z);

		if(y->left != 0)
			Node = y->left;
		else
			Node = y->right;
		// ���� ��������� �� ����
		if(Node != 0)
			Node->parent = y->parent;
		// ��������� �������� ����?
		if(y->parent == 0)
			root = Node;
		else if(y == y->parent->left) // ����� �� ��������?
			y->parent->left = Node;
		else
			y->parent->right = Node;  // ������ �� ��������?

		if(y != z)
		{
			// ����������� ������ ����
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

void Tree::�alancing()
{
	Elem * p = new Elem[count];
	int left = 0, right = count - 1;
	CopyToArray(root, p);
	while (root != 0)
		Del(root);
	�alancing(p, left, right);
	delete[] p;
}

void Tree::�alancing(Elem * p, int left, int right)
{
	if (left <= right)
	{
		int middle = (left + right) / 2;
		Elem *temp = new Elem;
		strcpy_s(temp->eng, p[middle].eng);
		strcpy_s(temp->rus, p[middle].rus);
		Insert(temp);
		cout << p[middle].eng << endl;
		�alancing(p, left, middle - 1);
		�alancing(p, middle + 1, right);
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