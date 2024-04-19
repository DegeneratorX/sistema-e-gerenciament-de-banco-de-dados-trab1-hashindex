//
// Created by arida01 on 18/04/24.
//

#ifndef TRABALHO_1_HASHING_HASH_H
#define TRABALHO_1_HASHING_HASH_H

#endif //TRABALHO_1_HASHING_HASH_H

#include <vector>
#include <tuple>
#include <string>

class Noh{

private:
    std::string chave;
    std::vector<std::string> valores;
    std::vector<Noh*> filhos;
    int cont_valores = static_cast<int>(valores.size());
    Noh* pai = nullptr; // Se é nullptr, é um nó raíz.
    bool eh_folha;

public:
    Noh(std::string& chave, std::vector<std::string> valores, Noh* prox=nullptr);

    std::string getChave();

    std::string getValor();

};


class HashTable{
private:
    int tamanho;
    Noh** dataMap;
    int hashFunction(std::string chave);

public:
    HashTable(int tamanho=7);
    void printHashTable();
};