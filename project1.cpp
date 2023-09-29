#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int uniqueKey = 0;
string names[] = {"Igor", "João", "Victor", "Iago", "Eric", "Isadora", "Nicole", "Gabriel"};
char sexs[] = {'M', 'F'};

struct TItem
{
    int id;
    string name;
    char sex;
    int age;
};

struct TCell
{
    TItem item;
    TCell *next;
    TCell *previous;
};

struct TList
{
    TCell *first;
    TCell *last;
};

TList createEmptyList()
{
    TList list;
    list.first = new TCell;
    list.last = list.first;
    return list;
}

bool isEmpty(TList list)
{
    return list.first == list.last;
}

void appendToList(TList &list, TItem item)
{
    TCell *tempCell = list.last;
    list.last->next = new TCell;
    list.last = list.last->next;
    list.last->item = item;
    list.last->next = NULL;
    list.last->previous = tempCell;
}

void prependToList(TList &list, TItem item)
{
    TCell *tempCell = list.first->next;
    list.first->next = new TCell;
    list.first->next->item = item;
    list.first->next->next = tempCell;
    list.first->next->next->previous = list.first->next;
    list.first->next->previous = list.first;
}

void showList(TList list, bool debug)
{
    if (isEmpty(list))
    {
        cout << "The list is empty." << endl;
        return;
    }
    TCell *cell = list.first->next;
    cout << " ======== showList ======== " << endl;
    while (cell != NULL)
    {
        cout << "  id:   " << cell->item.id << endl;
        cout << "  name: " << cell->item.name << endl;
        cout << "  sex:  " << cell->item.sex << endl;
        cout << "  age:  " << cell->item.age << endl;
        if (debug)
        {
            cout << "  debug true (" << endl;
            cout << "   prev: " << cell->previous << endl;
            cout << "   ref:  " << cell << endl;
            cout << "   next: " << cell->next << " )" << endl;
        }
        if (cell->next != NULL) { cout << " -------------------------- " << endl; }
        cell = cell->next;
    }
    cout << " ========================== " << endl;
}

void showItem(TCell* cell)
{
    cout << " ======== showItem ======== " << endl;
    cout << "  id:   " << cell->item.id << endl;
    cout << "  name: " << cell->item.name << endl;
    cout << "  sex:  " << cell->item.sex << endl;
    cout << "  age:  " << cell->item.age << endl;
    cout << " ========================== " << endl;
}

void showStack(TList list, bool debug)
{
    if (isEmpty(list))
    {
        cout << "The list is empty." << endl;
        return;
    }
    TCell *cell = list.last;
    cout << " ======= showStack ======== " << endl;
    while (cell != list.first)
    {
        cout << "  id:   " << cell->item.id << endl;
        cout << "  name: " << cell->item.name << endl;
        cout << "  sex:  " << cell->item.sex << endl;
        cout << "  age:  " << cell->item.age << endl;
        if (debug)
        {
            cout << "  debug true (" << endl;
            cout << "   prev: " << cell->previous << endl;
            cout << "   ref:  " << cell << endl;
            cout << "   next: " << cell->next << " )" << endl;
        }
        if (cell->previous != list.first) { cout << " -------------------------- " << endl; }
        cell = cell->previous;
    }
    cout << " ========================== " << endl;
}

TCell* findItem(TList &list, int key)
{
    if (isEmpty(list))
    {
        cout << "The list is empty." << endl;
        return NULL;
    }
    TCell *cell = list.first->next;
    while (cell != NULL)
    {
        if (cell->item.id == key)
        {
            return cell;
        }
        
        cell = cell->next;
    }
    return NULL;
}

TCell* popItem(TList &list, int key)
{
    TCell* cell = findItem(list, key);
    cell->next->previous = cell->previous;
    cell->previous->next = cell->next;
    return cell;
}

void removeItem(TList &list, int key)
{
    TCell* cell = findItem(list, key);
    cell->next->previous = cell->previous;
    cell->previous->next = cell->next;
    delete cell;
}

TItem createItem(string name, char sex, int age)
{
    TItem item;
    item.id = uniqueKey++;
    item.name = name;
    item.sex = sex;
    item.age = age;
    return item;
}

TItem createItem()
{
    TItem item;
    item.id = uniqueKey++;
    item.name = names[rand() % 8];
    item.sex = sexs[rand() % 2];
    item.age = rand() % 11 + 18;
    return item;
}

int main()
{
    srand(time(NULL));

    TList myList = createEmptyList();

    appendToList(myList, createItem());
    appendToList(myList, createItem());
    appendToList(myList, createItem());
    appendToList(myList, createItem());
    appendToList(myList, createItem());

    showStack(myList, true);

    TCell* myCell = popItem(myList, 2);

    showStack(myList, true);

    showItem(myCell);

    return 0;
}