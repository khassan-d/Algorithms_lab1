#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

class HashTable {
private:
    vector<list<double>> table;
    int currentSize;

    void resizeTable() {
        int oldSize = table.size();
        int newSize = max(2 * oldSize, 10);
        vector<list<double>> newTable(newSize);

        for (int i = 0; i < oldSize; ++i) {
            for (double value : table[i]) {
                int newIndex = hashFunc(value, newSize);
                newTable[newIndex].push_back(value);
            }
        }

        table = move(newTable);
    }

public:
    HashTable() : currentSize(0) {
        table.resize(10);
    }

    int hashFunc(double value, int mod) const {
        double temp = value * 5.5;
        return static_cast<int>(mod * (temp - floor(temp)));
    }

    void insertItem(double value) {
        if (currentSize == table.size() - 1) {
            resizeTable();
        }

        int index = hashFunc(value, table.size());
        while (!table[index].empty()) {
            index = (index + 1) % table.size();
        }

        table[index].push_back(value);
        ++currentSize;
    }

    bool containsItem(double value) {
        int index = hashFunc(value, table.size());
        for (const double& val : table[index]) {
            if (val == value) {
                return true;
            }
        }
        return false;
    }

    void printTable() {
        for (int i = 0; i < table.size(); i++) {
            cout << "Hash Index " << i << ": ";
            for (const double& value : table[i]) {
                cout << value << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    HashTable ht;
    int choice;
    double value;

    while (true) {
        cout << "1. Insert a value into the hash table." << endl;
        cout << "2. Print the hash table." << endl;
        cout << "3. Check if a value exists in the hash table." << endl;
        cout << "0. Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter a real number: ";
            cin >> value;
            ht.insertItem(value);
            break;
        case 2:
            ht.printTable();
            break;
        case 3:
            cout << "Enter a value to check: ";
            cin >> value;
            if (ht.containsItem(value)) {
                cout << "Value found in the hash table." << endl;
            }
            else {
                cout << "Value not found in the hash table." << endl;
            }
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
