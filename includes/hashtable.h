//
// Created by arida01 on 18/04/24.
//

#ifndef SGBD_TRABALHO1_HASHINDEX_HASHTABLE_H
#define SGBD_TRABALHO1_HASHINDEX_HASHTABLE_H

#include "bplustree.h"

struct PonteiroParaRaiz{
    std::string chave;
    std::string valor;
    Noh* prox;
};

class HashTable{
private:
    int tamanho;
    PonteiroParaRaiz** dataMap;
    int funcaoHash(std::string chave) const;

public:
    HashTable(int tamanho=7);
    void printHashTable();
};

#endif //SGBD_TRABALHO1_HASHINDEX_HASHTABLE_H