//
// Created by arida01 on 22/04/24.
//

#include "linkedinlist.h"

NohL::NohL(const std::string& chave, const std::string& valor, NohL* prox) {
    this->chave = chave;
    this->valor = valor;
    this->prox = prox;
}

LinkedinList::LinkedinList() {
    this->tam = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

LinkedinList::LinkedinList(const std::string& chave, const std::string& valor){
    this->tam = 1;
    this->head = new NohL(chave, valor);
    this->tail = this->head;
}

void LinkedinList::inserir(const std::string& chave, const std::string& valor) {
    NohL* novoNoh = new NohL(chave, valor);
    if (this->tam == 0){
        this->head = novoNoh;
        this->head->prox = nullptr;
        this->tail = this->head;
        this->tam += 1;
        return;
    }
    if (this->tam == 1){
        if (chave >= this->head->chave){
            this->head->prox = novoNoh;
            this->tail = novoNoh;
            this->tam += 1;
            return;
        }
        novoNoh->prox = this->head;
        this->head = novoNoh;
        this->tam += 1;
        return;
    }
    NohL* atual = this->head;
    for (int i = 0; i < tam; i++){
        if (atual == this->head && chave <= this->head->chave){
            novoNoh->prox = this->head;
            this->head = novoNoh;
            this->tam +=1;
            return;
        }
        if (atual != this->tail && chave <= atual->prox->chave){
            novoNoh->prox = atual->prox;
            atual->prox = novoNoh;
            this->tam += 1;
            return;
        }
        if (atual == this->tail){
            novoNoh->prox = nullptr;
            this->tail->prox = novoNoh;
            this->tail = novoNoh;
            this->tam += 1;
            return;
        }
        atual = atual->prox;
    }

}

void LinkedinList::remover(const std::string& chave) {
    if (this->tam == 0){
        return;
    }
    if (this->tam == 1){
        if (this->head->chave == chave) {
            this->head->prox = this->tail->prox = nullptr;
            delete this->head;
        }
        this->tam -= 1;
        return;
    }
    NohL* atual = this->head;
    NohL* ant = atual;
    for (int i = 0; i < this->tam; i++){
        if (atual == this->head && atual->chave == chave){
            this->head = this->head->prox;
            atual->prox = nullptr;
            delete atual;
            this->tam -= 1;
            return;
        }
        if (atual->prox == this->tail && atual->prox->chave == chave){
            atual->prox = nullptr;
            delete this->tail;
            this->tail = atual;
            this->tam -= 1;
            return;
        }
        if (atual->chave == chave){
            ant->prox = atual->prox;
            atual->prox = nullptr;
            this->tam -= 1;
            delete atual;
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
}


bool LinkedinList::estaVazia() {
    if (this->tam == 0) return true;
    return false;
}

std::string LinkedinList::consultarValor(const std::string& chave) {
    NohL* atual = this->head;
    while (atual != nullptr) {
        if (chave == atual->chave) { return atual->valor; }
        atual = atual->prox;
    }
}

void LinkedinList::printarLista() {
    NohL* atual = this->head;
    int i = 1;
    while (atual != nullptr) {
        std::cout <<"    Lista Colisao "<< i << ": [Chave: " << atual->chave << "  ||  Valor: " << atual->valor << "]"<< std::endl;
        atual = atual->prox;
        i += 1;
    }
}
