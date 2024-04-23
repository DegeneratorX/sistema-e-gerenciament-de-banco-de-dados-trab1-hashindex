//
// Created by arida01 on 18/04/24.
//

#ifndef SGBD_TRABALHO1_HASHINDEX_HASHTABLE_H
#define SGBD_TRABALHO1_HASHINDEX_HASHTABLE_H

#include "bplustree.h"
#include "linkedinlist.h"

struct PonteiroParaLinkedinList{
    std::string chave;
    std::string valor;
    LinkedinList* lista;

    PonteiroParaLinkedinList(const std::string& chave = "", const std::string& valor = "", LinkedinList* lista = new LinkedinList());
};

class HashTable{
public:
    int tamanho;
    PonteiroParaLinkedinList** dataMap;
    int funcaoHash(const std::string chave) const;

public:
    HashTable(int tamanho=7);
    void inserir(const std::string& chave, const std::string& valor);
    void remover(const std::string& chave);
    std::string consultarValor(const std::string& chave);
    void printHashTable();
};

#endif //SGBD_TRABALHO1_HASHINDEX_HASHTABLE_H