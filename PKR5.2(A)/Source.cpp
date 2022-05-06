#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
#include<fstream>
#include <sstream>
#include <iostream>

using namespace std;

enum Spec {
	COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS,
	PHYSICS_INFORMATICS, WORK_TRAINING
};

string specStr[] = { "Комп\'ютерні науки", "Інформатика",
"Математика та економіка", "Фізика та інформатика","Трудове навчання" };

struct Student
{
	char secondname[100];
	short unsigned kurs;
	Spec spec;
	short unsigned physics;
	short unsigned math;
	short unsigned inf;
};

void Create(char* filename);
void Print(char* filename);
int* Num(char* filename);
double LineSearch(char* filename);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int* k = new int[3];

	char filename[100];

	cout << "Введіть ім\'я файлу: "; cin >> filename;

	Create(filename);
	Print(filename);

	k = Num(filename);

	cout << "кількість п\'ятірок з інформатики: " << k[0] << endl;
	cout << "кількість чітвірок з інформатики: " << k[1] << endl;
	cout << "кількість трійок з інформатики: " << k[2] << endl << endl;

	cout << "Процент студентів які отримали і з фізики і з математики 4 або 5: "
		<< LineSearch(filename) << "%" << endl;

	system("pause");
	return 0;
}

void Create(char* filename)
{
	ofstream fout(filename, ios::binary);
	if (!fout)
	{
		cerr << "Error opening file \"" << filename << "\"" << endl;
		exit(1);
	}

	Student s;
	int spec;
	char ch;
	int i = 0;

	do
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		++i;
		cin.sync();

		cout << "\tпрізвище: "; cin >> s.secondname;
		cout << "\tКурс: "; cin >> s.kurs;
		cout << "\tСпеціальність:\n [0]Комп\'ютерні науки\n [1]Інформатика\n"
			<< " [2]Математика та економіка\n [3]Фізика та інформатика\n"
			<< " [4]Трудове навчання\n Твій вибір: "; cin >> spec;

		s.spec = (Spec)spec;

		switch (s.spec)
		{
		case COMPUTER_SCIENCE:
			cout << "\tОцінка з фізики: "; cin >> s.physics;
			cout << "\tОцінка з математики: "; cin >> s.math;
			cout << "\tОцінка з інформатики: "; cin >> s.inf;
			break;
		case INFORMATICS:
			cout << "\tОцінка з фізики: "; cin >> s.physics;
			cout << "\tОцінка з математики: "; cin >> s.math;
			cout << "\tОцінка з інформатики: "; cin >> s.inf;
			break;
		case MATH_ECONOMICS:
		case PHYSICS_INFORMATICS:
		case WORK_TRAINING:
			cout << "\tОцінка з фізики: "; cin >> s.physics;
			cout << "\tОцінка з математики: "; cin >> s.math;
			cout << "\tОцінка з інформатики: "; cin >> s.inf;
			break;
		}
		cout << endl;

		fout.write((char*)&s, sizeof(Student));

		cout << "Continue? (Y/N): "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
}

void Print(char* filename)
{
	ifstream fin(filename, ios::binary);
	if (!fin)
	{
		cerr << "Error opening file \"" << filename << "\"" << endl;
		exit(1);
	}

	Student s;
	int i = 0;

	cout << "========================================================================================="
		<< endl;
	cout << "| № |   Прізвище   | Курс |      Спеціальність      | Фізика | Математика | інформатики |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------"
		<< endl;

	while(fin.read((char*)&s,sizeof(Student)))
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << s.secondname << " "
			<< "|   " << setw(1) << right << s.kurs << "  "
			<< "| " << setw(23) << left << specStr[s.spec] << " "
			<< "|    " << setw(1) << right << s.physics << "   "
			<< "|      " << setw(1) << left << s.math << "     "
			<< "|       " << setw(1) << right << s.inf << "     |" << endl;
		++i;
	}
	cout << "========================================================================================="
		<< endl;
	cout << endl;
}

int* Num(char* filename)
{
	ifstream fin(filename, ios::binary);
	if (!fin)
	{
		cerr << "Error opening file \"" << filename << "\"" << endl;
		exit(1);
	}

	Student s;
	int i = 0;
	int* k = new int[3];

	for (int j = 0; j < 3; j++)
	{
		k[j] = 0;
	}

	while (fin.read((char*)&s, sizeof(Student)))
	{
		if (s.inf == 5)
		{
			k[0]++;
		}

		if (s.inf == 4)
		{
			k[1]++;
		}

		if (s.inf == 3)
		{
			k[2]++;
		}
		i++;
	}

	return k;
}

double LineSearch(char* filename)
{
	ifstream fin(filename, ios::binary);
	if (!fin)
	{
		cerr << "Error opening file \"" << filename << "\"" << endl;
		exit(1);
	}

	Student s;
	int i = 0;
	double k = 0.0, n;

	while (fin.read((char*)&s, sizeof(Student)))
	{
		if (s.math == 4 && s.physics == 4 ||
			s.math == 5 && s.physics == 5)
		{
			k++;
		}
		i++;
	}

	n = i;

	return 100.0 * k / n;
}