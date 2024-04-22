#include <iostream>
#include "hashtable.h"

int main() {
    //HashTable* hash = new HashTable(5);
    //hash->printHashTable();
    ArvoreBPlus* bPlus = new ArvoreBPlus(4);

    bPlus->inserir("Ola", "mundo");
    bPlus->inserir("Teste", "123");
    bPlus->inserir("PAU", "TORA");
    bPlus->inserir("Mae", "n Ve");
    bPlus->inserir("bestera", "naninha");

    //bPlus->mostrarFolhas();
    bPlus->mostrarArvore();

    delete bPlus;
}
