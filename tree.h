#pragma once

struct Elem
{
	char eng[15]; // ключ
	char rus[15]; // значение
	Elem *left/*левый потомок*/, *right/*правый потомок*/, *parent/*родитель*/;
};

class Tree
{
	// корень
	Elem * root;
	// количество узлов
	int count;
public:
	Tree();
	~Tree();
	// печать от указанного узла
	void Print(Elem * Node);
	// поиск от указанного узла
	Elem * Search(Elem * Node, char * key);
	// min от указанного узла
	Elem * Min(Elem * Node);
	// max от указанного узла
	Elem * Max(Elem * Node);
	// следующий для указанного узла
	Elem * Next(Elem * Node);
	// предыдущий для указанного узла
	Elem * Previous(Elem * Node);
	// вставка узла
	void Insert(Elem * z);
	// удаление ветки для указанного узла, 
	void Del(Elem * z);
	// количество узлов дерева
	int GetCount()
	{
		return count;
	}
	// получить корень
	Elem * GetRoot();
	// сохранения данных дерева в файл
	void Save(Elem * Node, FILE*f);
	// загрузка данных из файла
	void Load(Elem * Node, FILE*f);
	// балансировка дерева
	void Вalancing();
	// рекурсивная функция балансировки
	void Вalancing(Elem * p, int left, int right);
	// копирование данных в массив
	void CopyToArray(Elem* node, Elem* p);
};

