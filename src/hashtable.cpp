//
// Created by arida01 on 18/04/24.
//

#include "../includes/hashtable.h"

// Criação da Hash
HashTable::HashTable(int tamanho) {
    this->tamanho = tamanho;

    // Essa tabela hash contém nós raíz. Esse nó só pode ter 1 valor, e ele tem esquerdo e direito.
    // Crio com o tamanho que forneço.
    this->dataMap = new PonteiroParaRaiz*[tamanho];
}


int HashTable::funcaoHash(std::string chave) const {
    int hash = 0;
    for (int i = 0; i < chave.length(); i++){
        int ascii = int(chave[i]);
        hash = (hash + ascii * 23) % this->tamanho;
    }
    return hash;
}
