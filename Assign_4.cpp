//============================================================================
// Name        : Assignment_4.cpp
// Author      : Harsh Gaggar
// Version     :
// Copyright   : Your copyright notice
// Description : Consider telephone book database of N clients. Make use of a hash table implementation
//				 to quickly look up client‘s telephone number. Make use of two collision handling
//				 techniques and compare them using number of comparisons required to find a set of
//				 telephone numbers (Note: Use linear probing with replacement and without replacement)
//============================================================================
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int tableSize = 10;

struct Client{
    string cname;
    string phoneNo;
};

class DataBase {
private:
    vector<Client> linearProbing;
    vector<Client> linearProbingWithReplacement;
    int compProb;
    int compWithRepl;

    int hash(int key) {
        return (key % tableSize);
    }

public:
    DataBase() {
        linearProbing.resize(tableSize);
        linearProbingWithReplacement.resize(tableSize);
        compProb = 0;
        compWithRepl = 0;
    }

    // without replacement
    void insertProbing(string cname, string no) {
    	int sum = 0;
    	for(int i = 0;i<cname.size();i++){
    		sum += cname[i];
    	}
        int idx = hash(sum);
        int i = idx;
        compProb++;

        while (linearProbing[i].cname != "") {
            i = (i + 1) % tableSize;
            compProb++;
        }

        linearProbing[i] = {cname, no};
    }

    // with replacement
    void insertProbingWithRepl(string cname, string no) {
    	int sum = 0;
		for(int i = 0;i<cname.size();i++){
			sum += cname[i];
		}
		int idx = hash(sum);
        int i = idx;
        compWithRepl++;

        while (linearProbingWithReplacement[i].cname != "" && linearProbingWithReplacement[i].cname != cname) {
            i = (i + 1) % tableSize;
            compWithRepl++;
        }

        linearProbingWithReplacement[i] = {cname, no};
    }

    string getDataProbing(string cname) {
    	int cmp = 0;
    	int sum = 0;
		for(int i = 0;i<cname.size();i++){
			sum += cname[i];
		}
		int idx = hash(sum);
        int i = idx;
        cmp++;

        while (linearProbing[i].cname != "") {
            if (linearProbing[i].cname == cname)
            	cout << "Found in " << cmp << "comparisons" << endl;
                return linearProbing[i].phoneNo;
            i = (i + 1) % tableSize;
            cmp++;
        }

        return "Not Found";
    }

    string getDataWithRepl(string cname) {
    	int cmp = 0;
    	int sum = 0;
		for(int i = 0;i<cname.size();i++){
			sum += cname[i];
		}
		int idx = hash(sum);
        int i = idx;
        cmp++;
        while (linearProbingWithReplacement[i].cname != "") {
            if (linearProbingWithReplacement[i].cname == cname)
            	cout << "Found in " << cmp << "comparisons" << endl;
                return linearProbingWithReplacement[i].phoneNo;
            i = (i + 1) % tableSize;
            cmp++;
        }

        return "Not Found";
    }

    void compRequired() {
        cout << "Comparison For inserting without replacement: " << compProb << endl;
        cout << "Comparison For inserting with Replacement: " << compWithRepl << endl;
    }

    void displayData() {
        cout << "With replacement" << endl;
        for (int i = 0; i < tableSize; i++) {
            if (linearProbingWithReplacement[i].cname != "")
                cout << linearProbingWithReplacement[i].cname << "  " << linearProbingWithReplacement[i].phoneNo << endl;
        }

        cout << "Without replacement" << endl;
        for (int i = 0; i < tableSize; i++) {
            if (linearProbing[i].cname != "")
                cout << linearProbing[i].cname << "  " << linearProbing[i].phoneNo << endl;
        }
    }
};

void display() {
    cout << "1. Insert without replacement\n";
    cout << "2. Insert with replacement\n";
    cout << "3. Get without replacement\n";
    cout << "4. Get with replacement\n";
    cout << "5. Replacement count\n";
    cout << "6. Display data\n";
    cout << "7. END\n";
}

int main() {
    DataBase b;

    int choice;
    while (true) {
        display();
        cin >> choice;
        string cname;
        string no;
        switch (choice) {
            case 1:
                cout << "Enter clientName: " << endl;
                cin >> cname;
                cout << "Enter contact no: " << endl;
                cin >> no;
                b.insertProbing(cname, no);
                cout << "Done\n";
                break;
            case 2:
                cout << "Enter clientName: " << endl;
                cin >> cname;
                cout << "Enter contact no: " << endl;
                cin >> no;
                b.insertProbingWithRepl(cname, no);
                cout << "DONE" << endl;
                break;
            case 3:
                cout << "Enter clientName: " << endl;
                cin >> cname;
                cout << b.getDataProbing(cname) << endl;
                break;
            case 4:
                cout << "Enter clientName: " << endl;
                cin >> cname;
                cout << b.getDataWithRepl(cname)<<endl;
                break;
            case 5:
                b.compRequired();
                break;
            case 6:
                b.displayData();
                break;
            case 7:
                cout << "ENDING..." << endl;
                return 0;
            default:
            	cout << "Enter correct choice.." << endl;
            	break;
        }
    }
}











