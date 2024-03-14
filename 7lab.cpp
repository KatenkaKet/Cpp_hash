# include <iostream>
#include <ctime>

#define minPages 100
#define maxPages 700
#define minYear 2000
#define maxYear 2009

#define TableSize 1024
#define key 5000

using namespace std;

// 8 вариант

struct Book{
	int Year;
	int Pages;
};

struct Item{
	Book book;
	Item * next;
};

void FillRand(Book *book); // заполнение структуры Book рандомными значениями
void PrintBook(struct Book *book);
void CleanHashTable(Item **HashTable);
int HashFunction(Book book);
void InsertItem(Book book);
void PrintHashTable(Item *HashTable[]);
void FillRandHash(Item *HashTable[], int quantity);

int main(){
	srand(time(NULL));
	struct Book *a = new Book;
	
	Item * HashTable[TableSize];
	CleanHashTable(HashTable);
	FillRandHash(HashTable, key);
	PrintHashTable(HashTable);
	
	return 0;
}

void FillRand(Book *book){
	book->Pages = rand() % (maxPages - minPages) + minPages;
	book->Year = rand() % (maxYear - minYear) + minYear;
}

void PrintBook(struct Book *book){
	cout << book->Pages << " " << book->Year << endl;
}

void CleanHashTable(Item *HashTable[]){
	for(int i = 0; i < TableSize; i++){
		HashTable[i] = nullptr;
	}
}

int HashFunction(Book book){
	return (book.Pages * book.Year) % 1024;
//	return (((book.Pages) * 1024) / 500 + ((book.Pages) * 1024) % 500)%TableSize;
//	return (int)((book.Pages - minPages) * (1 + (book.Year%(maxYear - minYear)))) % TableSize; // лучший вариант
}

void InsertItem(Book book, Item *HashTable[]){
	int index = HashFunction(book);
	Item * temp = HashTable[index];
	while(temp != nullptr){
		if(book.Pages == temp->book.Pages && book.Year == temp->book.Year){
			FillRand(&book);
			index = HashFunction(book);
			temp = HashTable[index];
			continue;
		}
		temp = temp->next;
	}
    if (HashTable[index] == nullptr) {
        HashTable[index] = new Item{book, nullptr};
    }
	else{
        Item* currentItem = HashTable[index];
        while (currentItem->next != nullptr) {
            currentItem = currentItem->next;
        }
        currentItem->next = new Item{book, nullptr};
    }
}

void PrintHashTable(Item *HashTable[]){
	for(int i = 0; i < TableSize; i++){
//		cout << i << ": ";
		Item* currentItem = HashTable[i];
		int j = 0;
		while (currentItem != nullptr) {
//			cout << "(1); ";
			j++;
        	currentItem = currentItem->next;
    	}
//    	if (j > 0) cout << j;
		cout << j;
		cout << endl;
	}
}

void FillRandHash(Item *HashTable[], int quantity){
	for(int i = 0; i < quantity; i++){
		struct Book *a = new Book;
		FillRand(a);
		InsertItem(*a, HashTable);
	}
}

