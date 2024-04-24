//
// Created by arida01 on 23/04/24.
//

#include "Bucket.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

#ifndef SGBD_TRABALHO1_HASH_HASHTABLE_H
#define SGBD_TRABALHO1_HASH_HASHTABLE_H


class HashTable{
private:
    std::vector<Bucket*> vetorBuckets;
    int qtdBuckets;
    int profundidadeGlobal;

    int funcaoHash(int chave);
    void alocarBuckets();

public:
    HashTable(int profundidadeGlobal);
    void inserir(int chave, const std::string& valor);
    void remover(int chave);
    std::string consultarValor(int chave);
};


#endif //SGBD_TRABALHO1_HASH_HASHTABLE_H
