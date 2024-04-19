//
// Created by arida01 on 18/04/24.
//

#include "../includes/hashtable.h"
#include <iostream>

template<typename T>
HashTable<T>::HashTable(int tamanho) {
    this->tamanho = tamanho;
    this->dataMap = new Noh<T>*[tamanho];
}

template<typename T>
void HashTable<T>::printHashTable() {
    for(int i = 0; i < this->tamanho; i++){
        std::cout << i << ":" << std::endl;
        if(this->dataMap[i]){
            Noh<T>* aux = dataMap[i];
            while(aux){
                std::cout << "    {" << aux->getChave() << ", " << aux->getValor() << "}" << std::endl;
            }
        }
    }
}


template<typename T> Noh<T>::Noh(std::string& chave, int valor, Noh* prox){
    this->chave = chave;
    this->valor = valor;
    this->prox = prox;
}

template<typename T> T Noh<T>::getValor() {
    return this->valor;
}

template<typename T> T Noh<T>::getChave() {
    return this->chave;
}
