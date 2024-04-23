//
// Created by arida01 on 22/04/24.
//

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

#ifndef SGBD_TRABALHO1_HASHINDEX_LINKEDINLIST_H
#define SGBD_TRABALHO1_HASHINDEX_LINKEDINLIST_H

struct NohL{
    std::string chave;
    std::string valor;
    NohL* prox;

    NohL(const std::string& chave, const std::string& valor, NohL* prox = nullptr);
};

class LinkedinList {
public:
    int tam;
    NohL* head;
    NohL* tail;

public:
    LinkedinList();
    LinkedinList(const std::string& chave, const std::string& valor);
    void inserir(const std::string& chave, const std::string& valor);
    void remover(const std::string& chave);
    bool estaVazia();
    void printarLista();
    std::string consultarValor(const std::string& chave);
};


#endif //SGBD_TRABALHO1_HASHINDEX_LINKEDINLIST_H
