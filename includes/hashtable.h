//
// Created by arida01 on 18/04/24.
//

#ifndef TRABALHO_1_HASHING_HASH_H
#define TRABALHO_1_HASHING_HASH_H

#endif //TRABALHO_1_HASHING_HASH_H

#include <vector>
#include <tuple>
#include <string>

class HashTable{
private:
    int tamanho;

    int hashFunction(std::string chave);

public:
    HashTable(int tamanho=7);
};

class Noh{
private:
    std::string chave;
    int valor;
    Noh* prox;
public:
    Noh(std::string& chave, int valor, Noh* prox);
};