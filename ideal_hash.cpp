#include<iostream>
#include<list>
#include<Windows.h>
using namespace std;

class HashTable {
private:
	static const int hashGroups = 11;//Кількість двозвьязних списків які ми будемо використовувати.
	//
	list<pair<int, double>> table[hashGroups]; // list 1 , index 0 , list 2 index 1...
	//цей запис утворюе масив Table розмірністю hashGroups , який будет мати у собі списки які у свою чергу матимуть у собі два значення (int, string)

public:
	bool isEmpty() const;//перевіряє наявність елементів у хеш-таблиці
	int hashFunc(int key);//хеш-функція
	void insertItem(int key, double value);//вставка елементів у хеш-таблицю
	void removeItem(int key);//видалення елементів
	double searchTable(int key);//пошук елементу у таблиці
	void printTable();//виведення усієї таблиці
}; 

bool HashTable::isEmpty() const {
	int sum{};// фігурні дужки автоматично присвоють змінній sum нульове значення
	for (int i{}; i < hashGroups; i++) {
		sum += table[i].size();//table[i].size() повертае розмір контейнеру з індексом і (кількість данних у ньому)
	}

	return !sum;
}

int HashTable::hashFunc(int key) {
	return key % hashGroups; //key: 905, in return , this function will spit out 5.
}

void HashTable::insertItem(int key, double value) {
	int hashValue = hashFunc(key);//присвоемо змінній hashValue значення ключа який пройшов через нашу хеш функцію
	auto& cell = table[hashValue];//оператор auto& визначае тип змінної cell , як ПОСИЛАННЯ на об'єкт що зберігвється у ячейці table[hashValue]
	auto bItr = begin(cell);// Утворює ітератор , який ми перекидаемо на початок списку , котрий лежить у контейнеру масива , функцією begin(cell)
	bool keyExists = false;
	for (; bItr != end(cell); bItr++) {//циклом пробігаємо по списку
		if (bItr->first == key) {//якщо перший елемент списку дорівнює ключу який ми додаємо 
			keyExists = true;
			cell.push_back(make_pair(key, value));//присвоюємо нашему другому елементу списку нове значення value
			cout << "[WARNING] Key exists. Value replaced." << endl;
			break;
		}
		if (!keyExists) {
			//створюємо нову пару ключ-значення та додайте її до списку
			cell.push_back(make_pair(key, value));
		}
	}

	if (!keyExists) {
		cell.emplace_back(key, value);//доде нове значення до контейнера 
	}
	return;
} 

void HashTable::removeItem(int key) {
	int hashValue = hashFunc(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;
	for (; bItr != end(cell); bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr = cell.erase(bItr);
			cout << "[INFO] Item removed." << endl;
			break;
		}
	}

	if (!keyExists) {
		cout << "[WARNING] KEy not found.Pair not remove." << endl;
	}
	return;

}

void HashTable::printTable() {
	for (int i = 0; i < hashGroups; i++) {
		if (table[i].size() == 0) continue;

		cout << "Hash Group " << i << ":" << endl;

		for (const auto& pair : table[i]) {
			cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
		}
	}
}

double HashTable::searchTable(int key) {
	for (int i{}; i < hashGroups; i++) {
		auto bItr = table[i].begin();
		for (; bItr != table[i].end(); bItr++) {
			if (bItr->first == key)
				return bItr->second;
		}
	}
	return -1;
}

int main() {
	HashTable ht;

	int choice, key;
	double value;

	while (true) {
		cout << "Enter your choice: " << endl;
		cout << "1. Check if Hash-table is empty." << endl;
		cout << "2. Insert item in hash table." << endl;
		cout << "3. Remove item from hash-table." << endl;
		cout << "4. Print all hash-table." << endl;
		cout << "5. Serch-table." << endl;
		cout << "0. Exit." << endl;
		cin >> choice;

		switch (choice) {
		case 0:
			return 0;
		case 1:
			system("cls");
			if (ht.isEmpty()) {
				cout << "Hash-table is empty." << endl;
			}
			else {
				cout << "Hash-table is not empty." << endl;
			}
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			cout << "Enter key and value to insert: " << endl;
			cin >> key >> value;
			ht.insertItem(key, value);
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			cout << "Enter key to remove: " << endl;
			cin >> key;
			ht.removeItem(key);
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			ht.printTable();
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");
			cout << "Enter the key that you want to find: " << endl;
			cin >> key;
			cout << ht.searchTable(key) << endl;
			system("pause");
			system("cls");
			break;
		default:
			cout << "Invalid choice. Try again." << endl;
			break;
		}
	}
}