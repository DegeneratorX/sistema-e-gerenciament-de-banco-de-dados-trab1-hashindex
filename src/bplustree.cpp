//
// Created by Diassis2023 on 20/04/2024.
//

#include "../includes/bplustree.h"

/////////////////////
// MÉTODOS DOS NÓS //
/////////////////////

Noh::Noh(bool ehFolha) {
    this->ehFolha = ehFolha;
    this->prox = nullptr;
}

void Noh::inserirChaveValorEmNohFolha(const std::string &chave, const std::string &valor) {
    auto menorValor = this->buscaBinaria(this->vetorChaves, chave);
    this->vetorChaves.insert(this->vetorChaves.begin() + menorValor, chave);
    this->vetorValores.insert(this->vetorValores.begin() + menorValor, valor);
}

void Noh::inserirChavePonteiroEmNohInterno(const std::string &chave, Noh *filho) {
    //auto menorValor = std::lower_bound(vetorChaves.begin(), vetorChaves.end(), chave);
    auto menorValor = this->buscaBinaria(this->vetorChaves, chave);
    this->vetorChaves.insert(this->vetorChaves.begin(), + menorValor, chave);
    this->vetorFilhos.insert(this->vetorFilhos.begin() + menorValor + 1, filho);
}

bool Noh::temOverflow(int maximoChaves) {
    return vetorChaves.size() > maximoChaves;
}

int Noh::buscaBinaria(const std::vector<std::string> &vetorChaves, const std::string chave) {
    int low = 0, high = this->vetorChaves.size() - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (this->vetorChaves[mid] < chave)
            low = mid + 1;
        else if (this->vetorChaves[mid] > chave)
            high = mid - 1;
        else
            return mid; // Retorna mid se a chave já existir (o comportamento pode ser ajustado)
    }
    return low; // Retorna a posição onde a chave deveria ser inserida se não encontrada
}

///////////////////////
// MÉTODOS DA ÁRVORE //
///////////////////////

ArvoreBPlus::ArvoreBPlus(int grau) {
    this->raiz = nullptr;
    this->maximoChaves = grau-1;
}

void ArvoreBPlus::separarNohFolhaComOverflow(Noh* folha) {
    int splitIndex = this->maximoChaves / 2;
    Noh* novaFolha = new Noh();
    novaFolha->vetorChaves.assign(folha->vetorChaves.begin() + splitIndex, folha->vetorChaves.end());
    novaFolha->vetorValores.assign(folha->vetorValores.begin() + splitIndex, folha->vetorValores.end());
    folha->vetorChaves.resize(splitIndex);
    folha->vetorValores.resize(splitIndex);

    novaFolha->prox = folha->prox;
    folha->prox = novaFolha;

    if (folha == this->raiz) {
        Noh* novaRaiz = new Noh(false);
        novaRaiz->vetorChaves.push_back(novaFolha->vetorChaves.front());
        novaRaiz->vetorFilhos.push_back(folha);
        novaRaiz->vetorFilhos.push_back(novaFolha);
        this->raiz = novaRaiz;
    } else {
        this->inserirNohPai(folha, novaFolha->vetorChaves.front(), novaFolha);
    }
}

void ArvoreBPlus::separarNohInternoComOverflow(Noh* interno) {
    int indiceDivisao = interno->vetorChaves.size() / 2;
    std::string promoverChave = interno->vetorChaves[indiceDivisao];

    Noh* novoInterno = new Noh(false);
    novoInterno->vetorChaves.assign(interno->vetorChaves.begin() + indiceDivisao + 1, interno->vetorChaves.end());
    novoInterno->vetorFilhos.assign(interno->vetorFilhos.begin() + indiceDivisao + 1, interno->vetorFilhos.end());

    interno->vetorChaves.resize(indiceDivisao);
    interno->vetorFilhos.resize(indiceDivisao + 1);

    this->inserirNohPai(interno, promoverChave, novoInterno);
}

void ArvoreBPlus::inserirNohPai(Noh *esq, const std::string& chave, Noh *dir) {
    if (esq == this->raiz) {
        Noh* novaRaiz = new Noh(false);
        novaRaiz->vetorChaves.push_back(chave);
        novaRaiz->vetorFilhos.push_back(esq);
        novaRaiz->vetorFilhos.push_back(dir);
        this->raiz = novaRaiz;
        return;
    }

    Noh* pai = this->acharPai(this->raiz, esq);
    pai->inserirChavePonteiroEmNohInterno(chave, dir);
    if (pai->temOverflow(this->maximoChaves)) {
        this->separarNohInternoComOverflow(pai);
    }
}

Noh* ArvoreBPlus::acharPai(Noh* atual, Noh* filho) {
    if (atual->ehFolha || atual->vetorFilhos[0]->ehFolha) return nullptr;

    for (int i = 0; i < atual->vetorFilhos.size(); i++) {
        if (atual->vetorFilhos[i] == filho) return atual;
        Noh* possivelPai = acharPai(atual->vetorFilhos[i], filho);
        if (possivelPai) return possivelPai;
    }
    return nullptr;
}

Noh* ArvoreBPlus::acharFolha(const std::string &chave) {
    Noh* atual = this->raiz;
    while (atual && !atual->ehFolha) {
        for (int i = 0; i < atual->vetorChaves.size(); i++) {
            if (chave < atual->vetorChaves[i]) {
                atual = atual->vetorFilhos[i];
                break;
            }
            if (i == atual->vetorChaves.size() - 1) {
                atual = atual->vetorFilhos[i + 1];
                break;
            }
        }
    }
    return atual;
}

void ArvoreBPlus::inserir(const std::string &chave, const std::string &valor) {
    if (!this->raiz) {
        this->raiz = new Noh();
        this->raiz->vetorChaves.push_back(chave);
        this->raiz->vetorValores.push_back(valor);
        return;
    }

    Noh* folha = this->acharFolha(chave);
    std::cout << folha->vetorChaves.size() << std::endl;
    folha->inserirChaveValorEmNohFolha(chave, valor);
    if (folha->temOverflow(this->maximoChaves)) {
        this->separarNohFolhaComOverflow(folha);
    }
}

void ArvoreBPlus::mostrarArvore() {
    if (!this->raiz) {
        std::cout << "A árvore está vazia." << std::endl;
        return;
    }

    std::queue<Noh*> filaNohs;
    filaNohs.push(this->raiz);
    int level = 0;

    // Percorre os nós da árvore nível por nível
    while (!filaNohs.empty()) {
        int tamanhoFila = filaNohs.size();
        std::cout << "Nível " << level << ": ";
        while (tamanhoFila > 0) {
            Noh* atual = filaNohs.front();
            filaNohs.pop();

            // Exibe as chaves do nó
            std::cout << "[";
            for (int i = 0; i < atual->vetorChaves.size(); i++) {
                std::cout << atual->vetorChaves[i];
                if (i < atual->vetorChaves.size() - 1) std::cout << ", ";
            }
            std::cout << "] ";

            // Se não for folha, adiciona os filhos na fila
            if (!atual->ehFolha) {
                for (Noh* child : atual->vetorFilhos) {
                    filaNohs.push(child);
                }
            }
            tamanhoFila--;
        }
        std::cout << std::endl;
        level++;
    }
}

void ArvoreBPlus::mostrarFolhas() {
    if (!this->raiz) {
        std::cout << "A árvore está vazia." << std::endl;
        return;
    }

    Noh* current = this->raiz;
    // Encontra o primeiro nó folha
    while (current && !current->ehFolha) {
        current = current->vetorFilhos[0];
    }

    // Percorre os nós folha
    std::cout << "Folhas: ";
    while (current) {
        std::cout << "[";
        for (int i = 0; i < current->vetorChaves.size(); i++) {
            std::cout << "(" << current->vetorChaves[i] << ", " << current->vetorValores[i] << ")";
            if (i < current->vetorChaves.size() - 1) std::cout << ", ";
        }
        std::cout << "] ";
        current = current->prox;
    }
    std::cout << std::endl;
}

