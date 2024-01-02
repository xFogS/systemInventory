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
	void _PrintConsole();
	void _FilesPrint();
	void _LoadFile(string File);
	void loadWindow();
public:
	//start create main menu for user
	void _MenuMain();
	void _mainFileItems();
	void _SaveADDItems();
	void _SaveDeleteItems(vector<string>::iterator i);
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
		auto idIterator = itemID.begin();
		for (auto items = item.begin(); items != item.end(); items++)
		{
			out << '[' << indx << ']' << " Item : " << *items << endl;
			out << '[' << indx << ']' << " ID   : " << *idIterator << endl; idIterator++;
			indx++;
		}
		//cout << "File save" << endl;
		out.close();
	}
}

void Inventory::_SaveADDItems()
{
	ofstream out(addItemTXT, ios::app);
	if (out.is_open())
	{
		for (auto addItem = item.begin(); addItem != item.end(); addItem++)
			out << '[' << __DATE__ << '|' << __TIME__ << ']'
			<< " New Item : " << *addItem << endl;
		//cout << "File save" << endl;
		out.close();
	}
}
void Inventory::_SaveDeleteItems(vector<string>::iterator i)
{
	ofstream out(delItemTXT, ios::app);
	if (out.is_open())
	{
		out << '[' << __DATE__ << '|' << __TIME__ << ']' << " Del Item :" << *i << endl;
		cout << "File save" << endl;
		out.close();
	}
}

void Inventory::_AddNewItem()
{
	system("cls");
	cout << "How much Items: "; cin >> size;
	string newItem; size_t newID;
	if (size >= 1 && size <= maxItems && !cin.fail())
	{
		cin.ignore();
		for (size_t i = 0; i < size; i++)
		{
			system("cls");
			cout << '[' << i << "] Item: "; getline(cin, newItem);
			item.push_back(newItem);
		}

		for (size_t i = 0; i < size; i++)
		{
			system("cls");
			cout << '[' << i << "] ID: "; cin >> newID;
			itemID.push_back(newID);
		}
			
		system("cls");
		item.shrink_to_fit(); itemID.shrink_to_fit(); //clear free bufer
		_mainFileItems();
		_LoadFile(mainFile);
		_SaveADDItems();
	}
	else
	{
		SetColor(Red, 0); cout << "Error type or size." << endl;
		cin.clear(); cin.ignore();
		SetColor(LightGray, 0); return;
	}
}

void Inventory::_DeleteItem()
{
	if (item.empty())
	{
		cout << "Inventory is clear ";
		SetColor(Red, 0); cout << "{^|^}" << endl; SetColor(LightGray, 0);
		return;
	}
	system("cls");
	_LoadFile(mainFile);
	cout << "~~~~~~~~~~" << endl;
	size_t input; cout << "Input index to delete: "; cin >> input;
	auto _iDel = item.begin();
	auto _jDel = itemID.begin();
	if (input >= 0 && input <= item.size() && !cin.fail())
	{
		_SaveDeleteItems(_iDel + input);
		item.erase(_iDel + input), itemID.erase(_jDel + input);
		_mainFileItems();
	}
	else {
		SetColor(Red, 0); cout << "Index error or Type" << endl; 
		cin.clear(); cin.ignore();
		SetColor(LightGray, 0); return;
	}
}

void Inventory::_PrintConsole()
{
	//loadWindow();
	system("cls");
	cout << "Max size Items = " << maxItems << endl;
	if (!item.empty())
	{
		auto j = itemID.begin();
		for (auto i = item.begin(); i != item.end(); i++, j++)
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
	case 0: system("cls"); _LoadFile(mainFile); return;
	case 1: system("cls"); _LoadFile(addItemTXT); return;
	case 2: system("cls"); _LoadFile(delItemTXT); return;
	case 3: system("cls"); return;
	}
}

//nice load window
void Inventory::loadWindow()
{
	system("cls");
	for (size_t i = 0; i <= 59; i++)
	{
		SetColor(rand() % 15 + 1, 0); cout << char(221) << " "; 
		Sleep(6);
	}
	SetColor(7, 0); Sleep(1000);
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