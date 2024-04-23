//
// Created by Diassis2023 on 20/04/2024.
//

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

#ifndef SGBD_TRABALHO1_HASHINDEX_BPLUSTREE_H
#define SGBD_TRABALHO1_HASHINDEX_BPLUSTREE_H

struct NohB{

    std::vector<std::string> vetorChaves;
    std::vector<std::string> vetorValores;
    std::vector<NohB*> vetorFilhos;
    bool ehFolha;
    NohB* prox;

    NohB(bool ehFolha = true);
    void inserirChaveValorEmNohFolha(const std::string& chave, const std::string& valor);
    void inserirChavePonteiroEmNohInterno(const std::string& chave, NohB* filho);
    bool temOverflow(int maximoChaves);
private:
    int buscaBinaria(const std::vector<std::string>& vetorChaves, const std::string chave);
};

class ArvoreBPlus {
private:
    NohB* raiz;
    int maximoChaves;

    void separarNohFolhaComOverflow(NohB* folha);
    void separarNohInternoComOverflow(NohB* interno);
    void inserirNohPai(NohB* esq, const std::string& chave, NohB* dir);
    NohB* acharPai(NohB* atual, NohB* filho);

public:
    ArvoreBPlus(int grau);

    NohB* acharFolha(const std::string& chave);
    void inserir(const std::string& chave, const std::string& valor);
    void mostrarArvore();
    void mostrarFolhas();
};


#endif //SGBD_TRABALHO1_HASHINDEX_BPLUSTREE_H
