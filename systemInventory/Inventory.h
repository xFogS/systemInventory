#pragma once
#include "menu.h"
#include <string>
#include <fstream>

using namespace std;

constexpr auto maxItems = 15;

class Inventory
{
	vector<string> item;
	vector<int> itemID;
	size_t size = 0;

	string mainFile = "mainFile.txt";
	string addItemTXT = "addItem.txt";
	string delItemTXT = "delItems.txt";

	void _AddNewItem();
	void _DeleteItem();
	void _PrintConsole() const;
	void _FilesPrint();
	void _LoadFile(string File);
public:
	//start create main menu for user
	void _MenuMain();
	void _mainFileItems();
	void _SaveADDItems();
	void _SaveDeleteItems(size_t numValue);
};

void Inventory::_MenuMain()
{
	while (true)
	{
		system("cls");
		int input = Menu::select_vertical({ "Add new item",
			"Delete item with inventory",
			"Print Console",
			"Work with files",
			"Exit Program" },
			HorizontalAlignment::Left);
		switch (input)
		{
		case 0: system("cls"); _AddNewItem(); system("pause"); break;
		case 1: system("cls"); _DeleteItem(); system("pause"); break;
		case 2:	system("cls"); _PrintConsole(); system("pause"); break;
		case 3:	system("cls"); _FilesPrint(); system("pause"); break;
		case 4: SetColor(6, 0); cout << '\n' << __DATE__ << ' ' << __TIME__ << endl;
			SetColor(7, 0); system("pause"); exit(0);
		}
	}
}

void Inventory::_mainFileItems()
{
	ofstream out(mainFile);
	if (out.is_open())
	{
		size_t indx = 0;
		auto idIterator = itemID.begin() + 1;
		for (auto items = item.begin() + 1; items != item.end(); items++)
		{
			out << '[' << indx << ']' << " Item : " << *items << endl;
			out << '[' << indx << ']' << " ID   : " << *idIterator << endl; idIterator++;
			indx++;
		}
		cout << "File save" << endl;
		out.close();
	}
}

void Inventory::_SaveADDItems()
{
	ofstream out(addItemTXT, ios::app);
	if (out.is_open())
	{
		for (auto addItem = item.begin() + 1; addItem != item.end(); addItem++)
			out << '[' << __DATE__ << '|' << __TIME__ << ']'
			<< " New Item : " << *addItem << endl;
		cout << "File save" << endl;
		out.close();
	}
}
void Inventory::_SaveDeleteItems(size_t numValue)
{
	ofstream out(delItemTXT, ios::app);
	if (out.is_open())
	{
		auto delItem = item.begin() + numValue;
		out << '[' << __DATE__ << '|' << __TIME__ << ']'
			<< " Del Item :" << *delItem << endl;
		cout << "File save" << endl;
		out.close();
	}
}

void Inventory::_AddNewItem()
{
	system("cls");
	cout << "How much Items: "; cin >> size;
	string newItem; size_t newID;
	if (size <= maxItems)
	{
		for (size_t i = 0; i <= size; i++)
		{
			system("cls");
			cout << '[' << i << "] Item: "; getline(cin, newItem);
			item.push_back(newItem);
		}

		for (size_t i = 0; i <= size; i++)
		{
			system("cls");
			cout << '[' << i << "] ID: "; cin >> newID;
			itemID.push_back(newID);
		}

		system("cls");
		//Є один лишній ввід ІД, вона не впливає, це так зміщення з 0 індексу
		/*sort(item.begin(), item.end());*/
		auto j = itemID.begin();
		for (vector<string>::iterator i = item.begin(); i != item.end(); i++)
		{
			cout << "Item: " << *i << endl;
			cout << "ID: " << *j << endl;
			j++;
		}
		item.shrink_to_fit(); itemID.shrink_to_fit(); //clear free bufer
		_mainFileItems();
		_SaveADDItems();
	}
}

void Inventory::_DeleteItem()
{
	if (item.empty())
	{
		cout << "Inventory is clear ";
		SetColor(Red, 0); cout << "{^|^}" << endl; SetColor(LightGray, 0);
		system("pause"); return;
	}
	system("cls");
	_LoadFile(mainFile);
	cout << "~~~~~~~~~~" << endl;
	size_t input; cout << "Input index for delete: "; cin >> input;
	//auto i = item.begin();
	//auto j = itemID.begin();
	auto _iDel = item.begin() + input;
	auto _jDel = itemID.begin() + input;
	if (_iDel != item.begin())
	{
		item.erase(_iDel), itemID.erase(_jDel);
		_mainFileItems();
		_SaveDeleteItems(input);
	}
	else {
		item.erase(_iDel); itemID.erase(_jDel);
		_mainFileItems();
		_SaveDeleteItems(input);
	}
}

void Inventory::_PrintConsole() const
{
	system("cls");
	cout << "Max size Items = " << maxItems << endl;
	if (!item.empty())
	{
		auto j = itemID.begin() + 1;
		for (auto i = item.begin() + 1; i != item.end(); i++)
		{
			cout << "Item: " << *i <<
				"\nID  : " << *j << endl;
		}
	}
	else {
		cout << "Inventory is clear ";
		SetColor(Red, 0); cout << "{^|^}" << endl; SetColor(LightGray, 0);
	}
}
void Inventory::_FilesPrint()
{
	system("cls");
	int input = Menu::select_vertical({ "main file",
		"add items",
		"delete items",
		"return back" },
		HorizontalAlignment::Left);
	switch (input)
	{
	case 0: system("cls"); _LoadFile(mainFile); system("pause"); return;
	case 1: system("cls"); _LoadFile(addItemTXT); system("pause"); return;
	case 2: system("cls"); _LoadFile(delItemTXT); system("pause"); return;
	case 3: system("cls"); return;
	}
}

void Inventory::_LoadFile(string File)
{
	ifstream load;
	load.open(File);
	char temp[1024];
	if (load.is_open())
	{
		while (load.getline(temp, 1024))
		{
			cout << temp << endl;
		}
		load.close();
	}
}