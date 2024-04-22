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

struct Noh{

    std::vector<std::string> vetorChaves;
    std::vector<std::string> vetorValores;
    std::vector<Noh*> vetorFilhos;
    bool ehFolha;
    Noh* prox;

    Noh(bool ehFolha = true);
    void inserirChaveValorEmNohFolha(const std::string& chave, const std::string& valor);
    void inserirChavePonteiroEmNohInterno(const std::string& chave, Noh* filho);
    bool temOverflow(int maximoChaves);
private:
    int buscaBinaria(const std::vector<std::string>& vetorChaves, const std::string chave);
};

class ArvoreBPlus {
private:
    Noh* raiz;
    int maximoChaves;

    void separarNohFolhaComOverflow(Noh* folha);
    void separarNohInternoComOverflow(Noh* interno);
    void inserirNohPai(Noh* esq, const std::string& chave, Noh* dir);
    Noh* acharPai(Noh* atual, Noh* filho);

public:
    ArvoreBPlus(int grau);

    Noh* acharFolha(const std::string& chave);
    void inserir(const std::string& chave, const std::string& valor);
    void mostrarArvore();
    void mostrarFolhas();
};


#endif //SGBD_TRABALHO1_HASHINDEX_BPLUSTREE_H
