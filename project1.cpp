#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int uniqueKey = 0;
string names[] = {"Igor", "João", "Victor", "Iago", "Eric", "Isadora", "Nicole", "Gabriel"};
char sexs[] = "MF";

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
    list.last->next = new TCell;
    list.last = list.last->next;
    list.last->item = item;
    list.last->next = NULL;
}

void showList(TList list)
{
    if (isEmpty(list))
    {
        cout << "The list is empty." << endl;
        return;
    }
    TCell cell = *list.first->next;
    cout << " ===== showList ===== " << endl;
    while (&cell != NULL)
    {
        cout << "  id: " << cell.item.id << endl;
        cout << "  name: " << cell.item.name << endl;
        cout << "  sex: " << cell.item.sex << endl;
        cout << "  age: " << cell.item.age << endl;
        if (cell.next != NULL) { cout << " -------------------- " << endl; }
        cell = *cell.next;
    }
    cout << " ==================== " << endl;
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

    showList(myList);

    return 0;
}