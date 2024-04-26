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
    std::string pathIndice; // Caminho para o arquivo de índices

    int funcaoHash(int chave);
    std::list<std::string> extrairRegistrosDoBucket(Bucket* bucket);
    void apagarConteudoArquivo(Bucket* bucket);
    void atualizarIndice();
    std::string getBucketPath(int indice);

public:
    std::vector<Bucket*> vetorDeBuckets;
    HashTable(int profundidadeGlobal, const std::string& pathIndice);
    void carregarTabela(HashTable* ht);
    void inserir(int chave, const std::string& valor);
    bool remover(int chave);
    std::string consultarValor(int chave);
    int getProfundidadeGlobal();
    int getProfundidadeLocal(int chave);
    int incidenciasDeChave(int chave);
};

void leituraInTxt(const std::string& inTxt, const std::string& outTxt, HashTable* ht);

#endif //SGBD_TRABALHO1_HASH_HASHTABLE_H
