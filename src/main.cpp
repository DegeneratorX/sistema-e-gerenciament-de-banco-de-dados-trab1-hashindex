#include <iostream>
#include <string>
#include "hashtable.h"

int main() {
    HashTable<int>* hash = new HashTable<int>(5);
    hash->printHashTable();
}
