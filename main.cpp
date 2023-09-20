#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <stdlib.h>
using namespace std;

struct Student {
	int fn,
		age,
		grade1, // BP | offset = 8
		grade2, // Web Design | offset = 12
		grade3, // Matematika | offset = 16
		grade4, // Elektronika | offset = 20
		grade5; // Sport | offset = 24

	char name[50], 
		 status[12], // offset = 78
		 pol;
};//Структурата запазва информацията за всеки студент
const int sizeofstruct = sizeof(Student);

int student_num(string filename);
bool is_fn_entered(string filename, int fn);
void input(string filename);
void output(Student student);
void save_to_binary(Student student, string filename);
void output_all(string filename);
void output_by_fn(string filename, int fn);
void enter_grades(string filename, int fn);
void edit_data(string filename, int num);
void sort_by_name(string filename);
void sort_by_age(string filename);
void sort_by_gender(string filename);
void sort_by_grades(string filename);

int main(){
	SetConsoleOutputCP(65001); // настройва конзолата на кирилица, не работи на всички компютри еднакво

	string filename; // съхранява текущият файл

	cout << "|---------------------------------|\n"
		<< "|      Информационна Система      |\n"
		<< "|      за Студентски Групи        |\n"
		<< "|---------------------------------|\n";
	Sleep(2000);
	system("CLS");
	cout << "!!! Моля въвеждайте имената на латиница за да работи правилно програмата !!!\n";
	Sleep(5000);
	system("CLS");
	cout << "!!! Моля разширете конзолата, ако програмата не извежда ясно и подредено информацията !!!\n";
	Sleep(5000);
	system("CLS");

	int grupa; // съхранява избора за група
	cout << "Моля изберете студентска група\n"
		 << "	1. Група 1\n"
		 << "	2. Група 2\n"
		 << "	3. Група 4\n"
		 << "	4. Група 4\n"
		 << "	5. Група 5\n"
		<< "	6. Група 6\n"
		 << "Въведете вашия избор: ";
	cin >> grupa;
	system("CLS");

	// тук се потребителя избира групата, а тя се определя от името на файла
	switch (grupa) {
	case 1:
		filename = "student_lists/students1.bin";
		break;

	case 2:
		filename = "student_lists/students2.bin";
		break;

	case 3:
		filename = "student_lists/students3.bin";
		break;

	case 4:
		filename = "student_lists/students4.bin";
		break;

	case 5:
		filename = "student_lists/students5.bin";
		break;

	case 6:
		filename = "student_lists/students6.bin";
		break;

	default:
		cout << "Изборът не е валиден\n"
			<< "Изберете отново\n";
		break;
	}

	// главното меню на програмата
	int choice;
	do {
		system("CLS");
		cout << "1. Добавяне на студенти в групата\n"
			 << "2. Извеждане на всички студенти\n"
			 << "3. Въвеждане на оценка\n"
			 << "4. Промяна\n"
			 << "5. Справки\n"
			 << "6. Изход\n"
			 << "Въведете вашия избор: ";
		cin >> choice;

		switch (choice) {

		case 1:
			system("CLS");
			int n;
			cout << "Колко студента желаете да добавите: ";
			cin >> n;
			system("CLS");
			if (n > 0 && n < 31) {
				for (int i = 0; i < n; i++) {
					if (student_num(filename) < 31) {
						cout << "Въвеждане на студент номер: " << i + 1 << "\n\n";
						input(filename);
						system("CLS");
					}
					else {
						cout << "Групата е пълна\n";
						Sleep(2000);
						break;
					}
				}
			}
			else {
				cout << "Изборът не е валиден!\n";
			}
			break;

		case 2:
			system("CLS");
			int num;
			cout << "1. Извеждане на всички студенти\n"
				<< "2. Извеждане на студенти с еднакви първи\n"
				<< "6 цифри във факултетния номер\n\n"
				<< "Въведете вашия избор: ";
			cin >> num;
			if (num == 1) {
				system("CLS");
				// знам, че трябва да се използва setw(), но броенето на символите ме обърка и сметнах този вариант за приемлив
				cout << "    Ф. Номер" << " "
					<< "                                               Име" << " "
					<< " Възраст" << " "
					<< " Пол" << " "
					<< "      Статус" << " "
					<< " Б.П" << " "
					<< " Уеб Диз" << " "
					<< " Мат" << " "
					<< " Елктр" << " "
					<< " ССП" << "\n";

				output_all(filename);
				system("pause");
			}
			else if (num == 2) {
				system("CLS");
				int nomer;
				cout << "Въведете 6-те цифри: ";
				cin >> nomer;
				if ((trunc(log10(nomer) + 1) == 6)) {
					output_by_fn(filename, nomer);
					system("pause");
				}
				else {
					cout << "Невалидно въвеждане\n";
					Sleep(2000);
					break;
				}
			}
			else {
				cout << "Изборът не е валиден\n";
			}
			break;

		case 3:
			system("CLS");
			int fn;
			cout << "Въведете факултетния номер на студента: ";
			cin >> fn;
			if (!is_fn_entered(filename, fn)) {
				cout << "Студентът не съществува\n";
				Sleep(2000);
				break;
			}
			if ((trunc(log10(fn)) + 1) == 8) {
				enter_grades(filename, fn);
			}
			else {
				cout << "Невалидно въвеждане\n";
				Sleep(2000);
			}
			break;

		case 4:
			system("CLS");
			int num1;
			cout << "1. Промяна на статус\n"
				<< "2. Промяна на оценка\n"
				<< "Въведете вашия избор: ";
			cin >> num1;
			if (num1 == 1 || num1 == 2) {
				system("CLS");
				edit_data(filename, num1);
				Sleep(2000);
			}
			else {
				cout << "Невалидно въвеждане\n";
				Sleep(2000);
			}
			break;

		case 5:
			system("CLS");
			int num2;
			cout << "1. Сортиране на студенти\n"
				<< "2. Извеждане на най-младите по пол\n"
				<< "3. Извеждане по най-висок среден успех\n"
				<< "Въведете вашия избор: ";
			cin >> num2;
			if (num2 == 1) {
				int num3;
				system("CLS");
				cout << "1. Сортиране по име\n"
					<< "2. Сортиране по възраст\n"
					<< "Въведете вашия избор: ";
				cin >> num3;
				if (num3 == 1) {
					system("CLS");
					sort_by_name(filename);
					system("pause");
					break;
				}
				else if (num3 == 2) {
					system("CLS");
					sort_by_age(filename);
					system("pause");
					break;
				}
				else {
					cout << "Невалидно въвеждане\n";
					Sleep(2000);
					break;
				}
			}
			else if(num2 == 2) {
				system("CLS");
				sort_by_gender(filename);
				system("pause");
				break;
			}
			else if (num2 == 3) {
				system("CLS");
				sort_by_grades(filename);
				system("pause");
				break;
			}
			else {
				cout << "Невалидно въвеждане\n";
				Sleep(2000);
			}
			break;
			system("pause");
			break;

		case 6:
			cout << "Край\n";
			break;

		default:
			cout << "Изборът не е валиден\n"
				<< "Изберете отново\n";
			break;
		}

	} while (choice != 6);
	return 0;
}

void input(string filename) {
	Student student;

	cout << "Въведете факултетния номер на студента: ";
	cin >> student.fn;
	if ((trunc(log10(student.fn)) + 1) > 8 || (trunc(log10(student.fn)) + 1) < 8) { //trunc(log10(student.fn) == броят на въведените символи в student.fn
		cout << "Невалидно въвеждане!\n";
		Sleep(2000);
		return;
	}
	if (is_fn_entered(filename, student.fn)) {
		cout << "Факултетният номер вече съществува!\n";
		Sleep(2000);
		return;
	}

	cout << "Въведете името на студента: ";
	cin.ignore();
	cin.getline(student.name, 50);

	cout << "Въведете възрастта на студента: ";
	cin >> student.age;
	if (student.age < 0 || student.age > 99) {
		cout << "Невалидно въвеждане!\n";
		Sleep(2000);
		return;
	}

	int pol;
	do {
		cout << "Изберете пола на студента: \n"
			<< "	1. Мъж (M)\n"
			<< "	2. Жена (F)\n"
			<< "Въведете вашия избор: ";
		cin >> pol;

		switch (pol)
		{
		case 1:
			student.pol = 'M';
			break;

		case 2:
			student.pol = 'F';
			break;

		default:
			cout << "Изборът не е валиден. \n"
				<< "Изберете отново.\n";
			break;
		}

	} while (!pol);

	int status;
	do {
		cout << "Изберете статуса на студента: \n"
			<< "	1. Незавършил\n"
			<< "	2. Завършил\n"
			<< "Въведете вашия избор: ";
		cin >> status;

		switch (status)
		{
		case 1:
			strncpy(student.status, "Nezavyrshil", 12);
			break;

		case 2:
			strncpy(student.status, "*Zavyrshil*", 12);
			break;

		default:
			cout << "Изборът не е валиден. \n"
				<< "Изберете отново.\n";
			break;
		}
	} while (!status);

	student.grade1 = 0;
	student.grade2 = 0;
	student.grade3 = 0;
	student.grade4 = 0;
	student.grade5 = 0;

	save_to_binary(student, filename);
}
bool is_fn_entered(string filename, int fn) { // връща true ако фн вече съществува и false ако не съществува
	ifstream file;
	file.open(filename, ios::binary);
	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		for (int i = 0; i < student_num(filename) - 1; i++) {
			int nomer;
			file.seekg(i * sizeofstruct);
			file.read((char*)&nomer, 4);
			if (nomer != fn) {
				continue;
			}
			else {
				file.close();
				return true;
			}
		}
	}
	file.close();
	return false;
}
int student_num(string filename) {
	Student student;
	ifstream file;
	file.open(filename, ios::binary);
	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		file.seekg(0, ios::end);
		int size = (file.tellg() / sizeof(student)) + 1;
		file.close();
		return size;
	}
} // връща (броя на студентите + 1) в даден файл 
void output(Student student) {
	cout << setw(8) << student.fn << " "
		<< setw(50) << student.name << " "
		<< setw(8) << student.age << " "
		<< setw(4) << student.pol << " "
		<< setw(12) << student.status << " "
		<< setw(4) << student.grade1 << " "
		<< setw(8) << student.grade2 << " "
		<< setw(4) << student.grade3 << " "
		<< setw(6) << student.grade4 << " "
		<< setw(4) << student.grade5 << "\n";
}
void save_to_binary(Student student, string filename) {
	ofstream file;
	file.open(filename, ios::binary | ios::app);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		file.write((char*)&student, sizeofstruct);
	}

	file.close();
}
void output_all(string filename) {
	ifstream file;
	file.open(filename, ios::binary);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		for (int i = 0; i < student_num(filename) - 1; i++) {
			Student student;
			file.seekg(i * sizeofstruct);
			file.read((char*)&student, sizeofstruct);
			cout << setw(2) << i + 1 << ". ";
			output(student);
		}
	}

	file.close();
}
void output_by_fn(string filename, int fn) {
	ifstream file;
	file.open(filename, ios::binary);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		for (int i = 0; i < student_num(filename) - 1; i++) {
			Student student;
			file.seekg(i * sizeofstruct);
			file.read((char*)&student, sizeofstruct);
			if ((student.fn / 100) == fn) {
				cout << setw(2) << i + 1 << ". ";
				output(student);
			}
		}
	}

	file.close();
}
void enter_grades(string filename, int fn) {
	fstream file;
	file.open(filename, ios::in | ios::out | ios::binary);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		for (int i = 0; i < student_num(filename) - 1; i++) {
			Student student;
			file.seekg((i * sizeofstruct));
			file.read((char*)&student, sizeofstruct);

			if (student.fn == fn) {
				output(student);
				Sleep(2000);
				system("CLS");
				cout << "Въвеждане на оценки(2-6)\n\n";

				if (student.grade1 == 0) {
					int ocenka;
					cout << "Въведете оценка по Базово Програмиране: ";
					cin >> ocenka;
					if (ocenka >= 2 && ocenka <= 6) {
						file.seekg((i * sizeofstruct) + 8);
						file.put(ocenka);
						cout << "\n";
					}
					else {
						cout << "Грешно въведена оценка\n";
						return;
					}
				}
				else {
					cout << "Оценката вече е въведена\n";
					Sleep(500);
				}

				if (student.grade2 == 0) {
					int ocenka;
					cout << "Въведете оценка по Уеб Дизайн: ";
					cin >> ocenka;
					if (ocenka >= 2 && ocenka <= 6) {
						file.seekg((i * sizeofstruct) + 12);
						file.put(ocenka);
						cout << "\n";
					}
					else {
						cout << "Грешно въведена оценка\n";
						return;
					}
				}
				else {
					cout << "Оценката вече е въведена\n";
					Sleep(500);
				}

				if (student.grade3 == 0) {
					int ocenka;
					cout << "Въведете оценка по Математика: ";
					cin >> ocenka;
					if (ocenka >= 2 && ocenka <= 6) {
						file.seekg((i * sizeofstruct) + 16);
						file.put(ocenka);
						cout << "\n";
					}
					else {
						cout << "Грешно въведена оценка\n";
						return;
					}
				}
				else {
					cout << "Оценката вече е въведена\n";
					Sleep(500);
				}

				if (student.grade4 == 0) {
					int ocenka;
					cout << "Въведете оценка по Електроника: ";
					cin >> ocenka;
					if (ocenka >= 2 && ocenka <= 6) {
						file.seekg((i * sizeofstruct) + 20);
						file.put(ocenka);
						cout << "\n";
					}
					else {
						cout << "Грешно въведена оценка\n";
						return;
					}
				}
				else {
					cout << "Оценката вече е въведена\n";
					Sleep(500);
				}

				if (student.grade5 == 0) {
					int ocenka;
					cout << "Въведете оценка по ССП: ";
					cin >> ocenka;
					if (ocenka >= 2 && ocenka <= 6) {
						file.seekg((i * sizeofstruct) + 24);
						file.put(ocenka);
						cout << "\n";
					}
					else {
						cout << "Грешно въведена оценка\n";
						return;
					}
				}
				else {
					cout << "Оценката вече е въведена\n";
					Sleep(500);
				}
			}
		}
	}

	file.close();
}
void edit_data(string filename, int num) {
	fstream file;
	file.open(filename, ios::in | ios::out | ios::binary);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	switch (num) {
	case 1:
		char ime[50];
		cout << "Въведете името на студента: ";
		cin.ignore();
		cin.getline(ime, 50);

		for (int i = 0; i < student_num(filename) - 1; i++) {
			Student student;
			file.seekg(i * sizeofstruct);
			file.read((char*)&student, sizeofstruct);
			if (student.name == ime) {
				if (student.status == "Nezavyrshil") {
					file.seekg((i * sizeofstruct) + 78);
					file.write((char*)"*Zavyrshil*", 12);
					cout << "\n";
				}
				else {
					cout << "Студентът вече е завършил";
					Sleep(2000);
					return;
				}
			}
		}
		break;

	case 2:
		int fn;
		cout << "Въведете факултетен номер: ";
		cin >> fn;
		if (!is_fn_entered(filename, fn)) {
			cout << "Студентът не съществува\n";
			Sleep(2000);
			return;
		}

		if ((trunc(log10(fn)) + 1) > 8 || (trunc(log10(fn)) + 1) < 8) {
			cout << "Невалидно въвеждане!\n";
			Sleep(2000);
			return;
		}
		else {
			int ocenka_num;
			cout << "1. Базово Програмиране\n"
				<< "2. Уеб Дизайн\n"
				<< "3. Математика\n"
				<< "4. Електроника\n"
				<< "5. Спорт\n"
				<< "Въведете вашия избор: ";
			cin >> ocenka_num;
			if (ocenka_num > 0 && ocenka_num < 6) {
				for (int i = 0; i < student_num(filename) - 1; i++) {
					Student student;
					file.seekg(i * sizeofstruct);
					file.read((char*)&student, sizeofstruct);
					if (student.fn == fn) {
						int ocenka;
						cout << "Въведете оценката: ";
						cin >> ocenka;
						if (ocenka >= 2 && ocenka <= 6) {
							switch (ocenka_num) {
							case 1:
								file.seekg((i * sizeofstruct) + 8);
								file.put(ocenka);
								cout << "\n";
								break;

							case 2:
								file.seekg((i * sizeofstruct) + 12);
								file.put(ocenka);
								cout << "\n";
								break;

							case 3:
								file.seekg((i * sizeofstruct) + 16);
								file.put(ocenka);
								cout << "\n";
								break;

							case 4:
								file.seekg((i * sizeofstruct) + 21);
								file.put(ocenka);
								cout << "\n";
								break;

							case 5:
								file.seekg((i * sizeofstruct) + 24);
								file.put(ocenka);
								cout << "\n";
								break;

							default:
								cout << "Изборът не е валиден. \n";
								break;
							}
						}
						else {
							cout << "Грешно въведена оценка\n";
							return;
						}
					}
				}
			}
		}
		break;

	default:
		cout << "Изборът не е валиден.\n";
		break;
	}

	file.close();
}
void sort_by_name(string filename) {
	ifstream file;
	file.open(filename, ios::binary);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		Student student[30];

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			file.seekg(i * sizeofstruct);
			file.read((char*)&student[i], sizeofstruct);
		}

		for (int j = 0; j < (student_num(filename) - 1); j++)
		{
			for (int i = j + 1; i < student_num(filename); i++)
			{
				if (strcmp(student[j].name, student[i].name) > 0)
				{
					char temp[50];
					strncpy(temp, student[j].name, sizeof(temp));
					strncpy(student[j].name, student[i].name, sizeof(student[j].name));
					strncpy(student[i].name, temp, sizeof(student[i].name));
				}
			}
		}

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			output(student[i]);
		}
	}

	file.close();
}
void sort_by_age(string filename) {
	ifstream file;
	file.open(filename, ios::binary);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		Student student[30];

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			file.seekg(i * sizeofstruct);
			file.read((char*)&student[i], sizeofstruct);	
		}

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			for (int j = 0; j < (student_num(filename) - 2); j++){
				if (student[j].age > student[j + 1].age)
				{
					int temp = student[j].age;
					student[j].age = student[j + 1].age;
					student[j + 1].age = temp;
				}
			}
		}

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			output(student[i]);
		}
	}

	file.close();
}
void sort_by_gender(string filename) {
	ifstream file;
	file.open(filename, ios::binary);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		Student student[30];

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			file.seekg(i * sizeofstruct);
			file.read((char*)&student[i], sizeofstruct);
		}

		Student male{};
		Student female{};
		int min = student[0].age;

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			if (student[i].pol == 'M') {
				male = student[i];
				for (int i = 0; i < (student_num(filename) - 1); i++)
				{
					if (male.age < min)
					{
						min = male.age;
					}
				}
			}
			else {
				female = student[i];
				for (int i = 0; i < (student_num(filename) - 1); i++)
				{
					if (female.age < min)
					{
						min = female.age;
					}
				}
			}
		}
		cout << "Най-младият мъж е\n";
		output(male);
		cout << "\nНай-младата жена е\n";
		output(female);
	}
	file.close();
}
void sort_by_grades(string filename) {
	ifstream file;
	file.open(filename, ios::binary);

	if (!file.is_open()) {
		cout << "Грешка при отварянето на файла\n";
		Sleep(2000);
		exit(1);
	}
	else {
		Student student[30];
		float av_grade[30];
		for (int i = 0; i < (student_num(filename) - 1); i++) {
			file.seekg(i * sizeofstruct);
			file.read((char*)&student[i], sizeofstruct);
			av_grade[i] = (student[i].grade1 + student[i].grade2 + student[i].grade3 + student[i].grade4 + student[i].grade5) / 5;
		}

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			for (int j = 0; j < (student_num(filename) - 2); j++) {
				if (av_grade[j] < av_grade[j + 1])
				{
					float temp = av_grade[j];
					av_grade[j] = av_grade[j + 1];
					av_grade[j + 1] = temp;

					Student temp1 = student[j];
					student[j] = student[j + 1];
					student[j + 1] = temp1;
				}
			}
		}

		for (int i = 0; i < (student_num(filename) - 1); i++) {
			output(student[i]);
			cout << "Със среден успех: " << setw(3) << av_grade[i] << "\n\n";
		}
	}
	file.close();
}