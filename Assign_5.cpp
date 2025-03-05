//============================================================================
// Name        : Assignment_5.cpp
// Author      : Harsh Gaggar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<string.h>
using namespace std;

class SLL
{
public:
    int key;
    char val[10];
    SLL *next;
}HT[6];

class OpenHash
{
public:
    SLL *node;
    OpenHash()
    {
        for(int i=0; i<6; i++)
        {
            HT[i].key = 0;
            strcpy(HT[i].val,"---");
            HT[i].next = NULL;
        }
    }
    void insert_KeyVal();
    void show_Table();
    void find_KeyVal(int key);
    void delete_KeyVal(int key);
};

void OpenHash :: insert_KeyVal()
{
    int i, cnt, index;
    SLL *Newnode, *temp;

    cout<<"\n\t How many Key-Value Pairs to Insert: ";
    cin>>cnt;

    for(i=0; i<cnt; i++)
    {
        Newnode = new SLL;

        cout<<"\n\t Enter Key : ";
        cin>>Newnode->key;
        cout<<"\n\t Enter Val : ";
        cin>>Newnode->val;
        Newnode->next = NULL;


        index = Newnode->key % 6;

        if(HT[index].next == NULL)
        {
            HT[index].next = Newnode;
        }
        else
        {
            temp = HT[index].next;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = Newnode;
        }
    }
}

void OpenHash :: show_Table()
{
    int i;
    SLL *temp;

    cout<<"\n\n\t Index Key->Value.....";
    for(i=0; i<6; i++)
    {
        cout<<"\n\n\t"<<i<<"--->";
        temp = HT[i].next;
        while(temp)
        {
            cout<<"("<<temp->key<<","<<temp->val<<")---->";
            temp = temp->next;
        }
        cout<<"Null" << endl;
    }
}

void OpenHash :: find_KeyVal(int key)
{

    SLL *temp;

    int idx = key % 6;
    temp = HT[idx].next;
    bool found = false;
    cout << endl;
    while(temp)
    {
        if(temp->key == key){
        	cout << "found" << endl;
            cout << "\t"<<temp->key<<","<<temp->val<<endl;;
            found = true;
            break;
        }else{
            temp = temp->next;
        }

    }
    if(found == false) cout << "key not found" << endl;
}

void OpenHash :: delete_KeyVal(int key){

    SLL *temp;

    int idx = key % 6;
    temp = HT[idx].next;
    cout << endl;
    if(temp == nullptr){
        cout << "no key to delete" << endl;
        return;
    }else if(temp->key == key){
        HT[idx].next = temp->next;
        show_Table();
    }else{
        while(temp){
        if(temp->next->key == key){
            temp->next = temp->next->next;
            show_Table();
            break;
        }else{
            temp = temp->next;
        }

    }
    }}



void display() {
    cout << "1. Insert\n";
    cout << "2. Search with key\n";
    cout << "3. Delete with key\n";
    cout << "4. Show table\n";

    cout << "5. END\n";
}

int main()
{
    OpenHash H1;
    int key;

    int choice;
        while (true) {
            display();
            cin >> choice;
            switch (choice) {
                case 1:
                	  H1.insert_KeyVal();
                    break;
                case 2:
                	cout << "enter key to search" << endl;
                	cin >> key;
                	H1.find_KeyVal(key);
                    break;
                case 3:
                	cout << "enter key to delete" << endl;
                	cin >> key;
                	H1.delete_KeyVal(key);


                    break;
                case 4:
					H1.show_Table();
					break;

                default:
                	cout << "Enter correct choice.." << endl;
                	break;
            }
        }





    return 0;
}
