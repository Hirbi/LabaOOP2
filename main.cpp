#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;


class Letter {
	friend void table_output(vector <Letter>& list_of_letters);
	friend vector <Letter> find_by_index(vector <Letter>& list_of_letters);
	friend bool cmp_for_sort(Letter first, Letter second);
	friend vector <Letter> open_db(string db_name);
	friend void close_db(vector <Letter>& list_of_letters, string db_name);
public:
	// конструктор вызывается разу после создания объекта класса
	Letter(int index = 0, string addressee_adress = "", string addressee_name = "", string sender_adress = "", string sender_name = "", double letter_cost = 0) {
		id = count++;
		ind1 = index;
		adr1 = addressee_adress;
		name1 = addressee_name;
		adr2 = sender_adress;
		name2 = sender_name;
		cost = letter_cost;
	}

	// ввод значений объекта класса с клавиатуры
	void enter_info() {

		cout << "Введите индекс получателя\n";
		cin >> ind1;
		cin.ignore();
		cout << "Введите адрес получателя\n";
		getline(cin, adr1);
		cout << "Введите имя получателя\n";
		getline(cin, name1);
		cout << "Введите адрес отправителя\n";
		getline(cin, adr2);
		cout << "Введите имя отправителя\n";
		getline(cin, name2);
		cout << "Введите стоимость письма\n";
		cin >> cost;
		cin.ignore();
	}

	// вывод в консоль значений объекта класса
	void get_info() {
		cout << "Индекс получателя: " << ind1;
		cout << "\nАдрес получателя:  " << adr1;
		cout << "\nИмя получателя:    " << name1;
		cout << "\nАдрес отправителя: " << adr2;
		cout << "\nИндекс получаеля:  " << name2;
		cout << "\nСтоимость письма:  " << cost;
		cout << "\n";
	}

	// проверка имени
	bool check_name(string name_for_find) {
		return (name2 == name_for_find);
	}

private:
	int id;
	int ind1; // индекс получателя
	string adr1;		// адрес получателя
	string name1;		// имя получателя
	string adr2;		// адрес отправителя
	string name2;		// имя отправителя
	double cost;		// стоимость письма
	int count = 0;
};

// обработка БД
vector <Letter> open_db(string db_name) {
	fstream f(db_name);
	vector <Letter> list_of_letters;
	int size;
	f >> size;
	for (int i = 0; i < int(size); i++) {
		Letter x;
		f >> x.ind1;
		f >> x.adr1;
		f >> x.name1;
		f >> x.adr2;
		f >> x.name2;
		f >> x.cost;
		list_of_letters.push_back(x);
	}
	f.close();
	return(list_of_letters);
}

//закрытие БД
void close_db(vector <Letter> &list_of_letters, string db_name) {
	fstream f(db_name, ios::out);
	f << list_of_letters.size() << "\n";
	for (int i = 0; i < list_of_letters.size(); i++) {
		f << list_of_letters[i].ind1 << "\n";
		f << list_of_letters[i].adr1 << "\n";
		f << list_of_letters[i].name1 << "\n";
		f << list_of_letters[i].adr2 << "\n";
		f << list_of_letters[i].name2 << "\n";
		f << list_of_letters[i].cost << "\n";
	}
	f.close();
}

// вывод в табличном виде
void table_output(vector <Letter> &list_of_letters) {
	cout << "      Индекс      | Адрес получателя |  Имя получателя  | Адрес отправителя| Имя отправителя  | Стоимость письма\n";
	for (int i = 0; i < list_of_letters.size(); i++) //цикл по всем студентам
	{
		cout << setw(18) << list_of_letters[i].ind1 << "|";
		cout << setw(18) << list_of_letters[i].adr1 << "|";
		cout << setw(18) << list_of_letters[i].name1 << "|";
		cout << setw(18) << list_of_letters[i].adr2 << "|";
		cout << setw(18) << list_of_letters[i].name2 << "|";
		cout << setw(18) << list_of_letters[i].cost << "|";
		cout << "\n";
		//сетв определяет минимальное количество символов, которые выведутся следующей операцией вывода
	}
	return;
}

// поиск по индексу
vector <Letter> find_by_index(vector <Letter> &list_of_letters) {
	int index;
	cout << "Введите индекс для поиска\n";
	cin >> index;
	cin.ignore(99999, '\n');
	vector <Letter> letters(0);
	for (int i = 0; i < list_of_letters.size(); i++) {
		if (list_of_letters[i].ind1 == index) {
			letters.push_back(list_of_letters[i]);
		}
	}
	if (letters.size() == 0) {
		cout << "Письма с индексом " << index << " не найдено\n";
	}
	else {
		cout << "Письма с индексом " << index << ":\n";
		for (int i = 0; i < letters.size(); i++) {
			letters[i].get_info();
			cout << "\n";
		}
	}
	return letters;
}

// вывод меню в консоль
void menu() {
	cout << "\nМеню:\n";
	cout << "1 - для вывода данных по всем письмам\n";
	cout << "2 - для добавления данных письма\n";
	cout << "3 - для поиска по имени отправителя\n";
	cout << "4 - поиск письма по индексу\n";
	cout << "5 - сортировка по цене\n";
	cout << "0 - выход\n";
}

// компаратор для сортировки по элементу объекта класса
bool cmp_for_sort(Letter first, Letter second) {
	return first.cost < second.cost;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Letter letter;
	string name, db_name = "db.txt";
	bool not_found = true;
	vector <Letter> list_of_letters = open_db(db_name);
	int is_stop;
	do {
		menu();
		cin >> is_stop;
		cin.ignore();
		switch (is_stop) {
			case 1:
				if (list_of_letters.size())
					table_output(list_of_letters);
				else
					cout << "В базе данных ничего нет :(\n";
				break;
			case 2:
				letter.enter_info();
				list_of_letters.push_back(letter);
				break;
			case 3:
				cout << "ВВедите имя отправителя для поиска:\n";
				getline(cin, name);
				not_found = true;
				for (int i = 0; i < list_of_letters.size(); i++) {
					if (list_of_letters[i].check_name(name)) {
						cout << "Письмо отправленное " << name << ":\n";
						letter.get_info();
						not_found = false;
					}
				}
				if (not_found)
					cout << name << " не отправлял писем :(";
				break;
			case 4:
				find_by_index(list_of_letters);
				break;
			case 5:
				sort(list_of_letters.begin(), list_of_letters.end(), cmp_for_sort);
				cout << "Сортировка выполнена.\n";
				break;
			case 0:
				close_db(list_of_letters, db_name);;
				break;
			default:
				cout << "Что-то не так, юзернейм";
				break;
		}
	} while (is_stop);
	cout << "До встречи, юзернейм";
}