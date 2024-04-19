//
// Created by arida01 on 18/04/24.
//

#include "../includes/hashtable.h"


HashTable::HashTable(int tamanho) {
    this->tamanho = tamanho;
    Noh* dataMap[this->tamanho];
}

Noh::Noh(std::string& chave, int valor, Noh* prox=nullptr){
    this->chave = chave;
    this->valor = valor;
    this->prox = prox;
}