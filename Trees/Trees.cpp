#include <iostream>
#include "TreeAVL.h"
#include <conio.h>

void checkAVL()
{
	TreeAVL<int> subject;
	
    system("cls");
	string menuArr = "Press key from the menu\n0) Exit.............\n1) Insert...........\n2) Remove...........\n3) Print tree.......\n4) Print............\n";

	int but = -1;
	while (but != 0)
	{
		system("cls");
		cout << menuArr;
		but = _getch() - '0';

		if (but == 1)
		{
			int key, value;
			cout << "Enter key: ";
			cin >> key;
			cout << "Enter value: ";
			cin >> value;
			subject.Insert(key, value);
		}
		else if (but == 2)
		{
			int key;
			cout << "Enter key: ";
			cin >> key;
			subject.Remove(key);
		}
		else if (but == 3)
		{
			subject.PrintTree();
			cout << "\n\nPress any key...";
			int cont = _getch();
		}
		else if (but == 4)
		{
			subject.Print();
			cout << "\n\nPress any key...";
			int cont = _getch();
		}

	}
}

int main()
{
	checkAVL();
}