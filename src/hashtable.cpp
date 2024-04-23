//
// Created by arida01 on 18/04/24.
//

#include "../includes/hashtable.h"


PonteiroParaLinkedinList::PonteiroParaLinkedinList(const std::string& chave, const std::string& valor, LinkedinList* lista) {
    this->chave = chave;
    this->valor = valor;
    this->lista = lista;
}

// Criação da Hash
HashTable::HashTable(int tamanho) {
    this->tamanho = tamanho;

    // Essa tabela hash contém nós raíz. Esse nó só pode ter 1 valor, e ele tem esquerdo e direito.
    // Crio com o tamanho que forneço.
    this->dataMap = new PonteiroParaLinkedinList*[tamanho];
    for (int i = 0; i < tamanho; i++){
        dataMap[i] = new PonteiroParaLinkedinList();
    }
}


int HashTable::funcaoHash(const std::string chave) const {
    int hash = 0;
    for (int i = 0; i < chave.length(); i++){
        int ascii = int(chave[i]);
        hash = (hash + ascii * 23) % this->tamanho;
    }
    return hash;
}

void HashTable::inserir(const std::string& chave, const std::string& valor) {
    int index = this->funcaoHash(chave);
    if (this->dataMap[index]->chave.empty() && this->dataMap[index]->valor.empty()){
        this->dataMap[index]->chave = chave;
        this->dataMap[index]->valor = valor;
        return;
    }
    dataMap[index]->lista->inserir(chave, valor);
}

void HashTable::remover(const std::string& chave) {
    int index = this->funcaoHash(chave);
    if (this->dataMap[index]->chave == chave){
        this->dataMap[index]->chave = "";
        this->dataMap[index]->valor = "";
    }
    else if (!this->dataMap[index]->lista->estaVazia()) {
        this->dataMap[index]->lista->remover(chave);
    }
}

std::string HashTable::consultarValor(const std::string& chave) {
    int index = this->funcaoHash(chave);
    if (this->dataMap[index]->chave == chave) {
        return this->dataMap[index]->valor;
    }
    return this->dataMap[index]->lista->consultarValor(chave);
}

void HashTable::printHashTable() {
    for (int i = 0; i < this->tamanho ; i++){
        std::cout << "Indice " << i << ": [Chave: " << this->dataMap[i]->chave << "  ||  Valor: " << this->dataMap[i]->valor << "]" << std::endl;
        if (!this->dataMap[i]->lista->estaVazia()){
            this->dataMap[i]->lista->printarLista();
        }
    }
}


