//
// Created by arida01 on 23/04/24.
//

#include "Bucket.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <list>
#include <cstdio>
#include <filesystem>

#ifndef SGBD_TRABALHO1_HASH_HASHTABLE_H
#define SGBD_TRABALHO1_HASH_HASHTABLE_H

int contadorDeRegistros(Bucket* bucket);

class HashTable{
private:

    int qtdDeBuckets;
    int profundidadeGlobal;

    int funcaoHash(int chave);
    std::list<std::string> extrairRegistrosDoBucket(Bucket* bucket);
    void apagarConteudoArquivo(Bucket* bucket);

public:
    std::vector<Bucket*> vetorDeBuckets;
    HashTable(int profundidadeGlobal);
    void carregarTabela(const std::string& arquivo);
    void inserir(int chave, const std::string& valor);
    void remover(int chave);
    std::string consultarValor(int chave);
};


#endif //SGBD_TRABALHO1_HASH_HASHTABLE_H
