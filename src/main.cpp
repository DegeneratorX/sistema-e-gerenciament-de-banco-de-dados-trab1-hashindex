#include <iostream>
#include "hashtable.h"

int main() {
    //HashTable* hash = new HashTable(5);
    //hash->printHashTable();
    HashTable* ht = new HashTable(5);
    ht->inserir("Ola", "mundo");
    ht->inserir("Teste", "123");
    ht->inserir("Trynda", "mere");
    ht->inserir("Forge", "points");
    ht->inserir("APS", "TC");
    ht->inserir("CANA", "GRAFOS");
    ht->inserir("Discreta", "Runidi");
    ht->inserir("Automatos", "Francicleber");
    ht->inserir("Carro", "Moto");
    ht->inserir("Cachaça", "Pinga");
    ht->inserir("Tequila", "Vinho");

    ht->printHashTable();

}
