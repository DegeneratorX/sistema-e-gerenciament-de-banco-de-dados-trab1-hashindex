//
// Created by arida01 on 18/04/24.
//

#ifndef TRABALHO_1_HASHING_HASH_H
#define TRABALHO_1_HASHING_HASH_H

#endif //TRABALHO_1_HASHING_HASH_H

#include <vector>
#include <tuple>
#include <string>

template<typename T>
class Noh{

private:
    T chave;
    int valor;
    Noh* prox;
public:
    Noh(std::string& chave, int valor, Noh* prox=nullptr);

    T getChave();

    T getValor();

};

template<typename T>
class HashTable{
private:
    int tamanho;
    Noh<T>** dataMap;
    int hashFunction(std::string chave);

public:
    HashTable(int tamanho=7);
    void printHashTable();
};