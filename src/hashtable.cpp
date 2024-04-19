//
// Created by arida01 on 18/04/24.
//

#include "../includes/hashtable.h"
#include <iostream>


HashTable::HashTable(int tamanho) {
    this->tamanho = tamanho;
    this->dataMap = new Noh*[tamanho];
}


void HashTable::printHashTable() {
    for(int i = 0; i < this->tamanho; i++){
        std::cout << i << ":" << std::endl;
        if(this->dataMap[i]){
            Noh* aux = dataMap[i];
            while(aux){
                std::cout << "    {" << aux->getChave() << ", " << aux->getValor() << "}" << std::endl;
            }
        }
    }
}


Noh::Noh(std::string& chave, std::vector<std::string> valores, Noh* prox){
    this->chave = chave;
    this->valores = valores;
    this->prox = prox;
}

std::string Noh::getChave() {
    return this->chave;
}

std::vector<std::string> Noh::getValor() {
    return this->valores;
}


