#include"hugeReal.h"
#include<fstream>

void PrintAll(hugeReal**& Is, const int& NOI)
{
	system("cls");
	for (int i = 0; i < NOI; i++)
	{
		cout << "I" << i + 1 << ": ";
		cout << *Is[i] << endl << endl;
	}
}
void SaveInFile(hugeReal**& Is, const int& NOI)
{
	string file;
	cout << "Enter filename with(.txt): ";
	cin >> file;
	ofstream wtr(file);
	wtr << NOI << endl;
	wtr << hugeReal::getBase() << endl;
	for (int i = 0; i < NOI; i++)
	{
		wtr << (*Is[i]) << endl;
	}
	wtr.close();
}
void LoadFromFile(hugeReal**& Is, int& NOI)
{
	string file;
	int base = 0;
	cout << "Enter filename with(.txt): ";
	cin >> file;
	ifstream rdr(file);
	rdr >> NOI;
	rdr >> base;
	hugeReal::setBase(base);
	Is = new hugeReal * [NOI];
	rdr.ignore();
	for (int i = 0; i < NOI; i++)
	{
		Is[i] = new hugeReal[1]{ {rdr} };
	}
	rdr.close();
}
void LoadFromUser(hugeReal**& Is, int& NOI)
{
	int base = 0;
	cout << "Enter amount of Numbers: ";
	cin >> NOI;
	cout << "Enter Base of your numbers: ";
	cin >> base;
	hugeReal::setBase(base);
	Is = new hugeReal * [NOI];
	cin.ignore();
	for (int i = 0; i < NOI; i++)
	{
		try {
			cout << "Enter Number " << i + 1 << ": ";
			Is[i] = new hugeReal[1]{};
			cin >> *Is[i];
		}
		catch (const char* msg)
		{
			cout << msg;
			i--;
		}
		
	}

}
int main()
{
	int NOI = 0;
	hugeReal** Is;
	char option = 'f';
	cout << "Input from file or Console(f/c)";
	cin >> option;
		if (tolower(option) == 'f')
			LoadFromFile(Is, NOI);
		else
			LoadFromUser(Is, NOI);

	
	PrintAll(Is, NOI);
	char o = 'b'; char d = '.', opr = '+'; int r1 = 0, r2 = 0, lv = 0; char c = 'y';
	do
	{
		try
		{
			opr = '.';
			cout << "\nUnary operation (u) or binary operation (b) or assignemnt operations(a) or save on a file(s): ";
			cin >> o;
			if (o == 'b')
			{
				cout << "\nIi=Ij opr Ik\n";
				cin >> d >> lv >> d >> d >> r1 >> opr >> d >> r2;
				lv--; r1--; r2--;
			}
			else if (o == 'u')
			{
				char p;
				cout << "\nPrefix operation or PostFix: (1 / 2)";
				cin >> p;
				if (p == '1')
				{
					cout << "\nIi= opr Ij\n";
					cin >> d >> lv >> d >> opr >> opr >> d >> r1;
					lv--; r1--;
				}
				else
				{
					cout << "\nIi=Ij opr\n";
					cin >> d >> lv >> d >> d >> r1 >> opr >> opr;
					lv--; r1--;
				}
				switch (opr)
				{
				case '+':
					if (p == '1')
						*Is[lv] = ++(*Is[r1]);
					else
						*Is[lv] = (*Is[r1])++;
					break;
				case '-':
					if (p == '1')
						*Is[lv] = --(*Is[r1]);
					else
						*Is[lv] = (*Is[r1])--;
					break;
				default:
					cout << "Invalid operator\n";
					system("pause");
				}

			}
			else if (o == 'a')
			{
				cout << "\nIi opr=Ij\n";
				cin >> d >> lv >> opr >> d >> d >> r1;
				lv--, r1--;
			}
			else if (o == 's')
			{
				opr = 's';
			}
			switch (opr)
			{
			case '+':
				if (o == 'b')
					*Is[lv] = (*Is[r1] + *Is[r2]);
				else if (o == 'a')
					*Is[lv] += *Is[r1];
				break;

			case '*':
				if (o == 'b')
					*Is[lv] = (*Is[r1] * *Is[r2]);
				else if (o == 'a')
					*Is[lv] *= *Is[r1];
				break;
			case '-':
				if (o == 'b')
					*Is[lv] = (*Is[r1] - *Is[r2]);
				else if (o == 'a')
					*Is[lv] -= *Is[r1];
				break;
			case '/':
				if (o == 'b')
					*Is[lv] = (*Is[r1] / *Is[r2]);
				else if (o == 'a')
					*Is[lv] /= *Is[r1];
				break;
			
			case 's':
				SaveInFile(Is, NOI);
				break;
			default:
				cout << "Invalid operator\n";
				system("pause");
			}
		}
		catch (const char* msg)
		{
			cout << msg;
			system("pause>0");
		}
		PrintAll(Is, NOI);
		cout << "\nDo you want to continue?";
		cin >> c;
	} while (c == 'Y' || c == 'y');
	return 0;

}

int main1()
{
	/*for (int i = 0; i < 26; i++)
	{
		cout << i + 10<<char('A'+i)<<" ";
	}*/
	hugeReal R1 ("Z.z"), R2("Z.z");
	cout << R1 << endl << R2 << endl;
	cout << R1 * R2;
	/*try
	{
		cout << (R1 / -R2);
	}
	catch (const char* msg)
	{
		cout << msg;
	}*/
	
	return 0;
}