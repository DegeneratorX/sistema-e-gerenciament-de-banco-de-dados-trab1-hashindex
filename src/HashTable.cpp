//
// Created by arida01 on 23/04/24.
//

#include "HashTable.h"

HashTable::HashTable(int profundidadeGlobal){
    this->profundidadeGlobal = profundidadeGlobal;
    this->qtdBuckets = static_cast<int>(std::pow(2, profundidadeGlobal));
    this->vetorBuckets.resize(this->qtdBuckets);
    this->alocarBuckets();
}


void HashTable::alocarBuckets(){
    for (int i = 0; i < this->qtdBuckets; i++){

        this->vetorBuckets[i] = new Bucket();
        this->vetorBuckets[i]->tam = 0;
        this->vetorBuckets[i]->profundidadeLocal = profundidadeGlobal;
        this->vetorBuckets[i]->arquivo = "data/buckets/" + std::to_string(i) + ".txt";

        std::ofstream criarArquivo(this->vetorBuckets[i]->arquivo);

        if (!criarArquivo){
            std::cout << "Erro! Nao foi possivel criar o bucket " << i << std::endl; exit(1);
        }
    }
}


int HashTable::funcaoHash(int chave){
    int mascara = static_cast<int>(pow(2, this->profundidadeGlobal)) - 1;  // Usando pow pro deslocamento de bits
    return chave % (mascara + 1);       // Resto q simula a máscara de bits
}


void HashTable::inserir(int chave, const std::string& valor){
    int indice = this->funcaoHash(chave);

    std::ofstream arquivoDiretorioBucket(this->vetorBuckets[indice]->arquivo, std::ios::app);
    if (!arquivoDiretorioBucket) {
        std::cout << "Erro: não foi posível abrir o arquivo de bucket localizado em " << this->vetorBuckets[indice]->arquivo << std::endl; exit(1);
    }

    if (this->vetorBuckets[indice]->tam < 3){
        arquivoDiretorioBucket << chave << "," << valor << std::endl;
        this->vetorBuckets[indice]->tam += 1;

    } else{
        std::cout << "Bucket numero " << indice << " cheio." << std::endl;
        //split_bucket(dir, indice);
        //insert_entry(dir, key, data); // Tentar novamente após a divisão
    }
}


std::string HashTable::consultarValor(int chave) {
    int indice = this->funcaoHash(chave);

    // Abre o arquivo do balde pra leitura
    std::ifstream arquivoDiretorioBucket(this->vetorBuckets[indice]->arquivo);
    if (!arquivoDiretorioBucket) {
        std::cout << "Erro ao abrir o arquivo do bucket: " << this->vetorBuckets[indice]->arquivo << std::endl;
        return "";  // Retorna string vazia caso n encontre
    }

    std::string linha;
    while (getline(arquivoDiretorioBucket, linha)) {
        std::stringstream ss(linha);
        int chaveAtual;
        std::string valor;

        getline(ss, linha, ',');  // Lê até a vírgula, pegando a chave
        chaveAtual = std::stoi(linha);  // Converte a chave de string para int

        if (chaveAtual == chave) {
            getline(ss, valor);  // Obtém o restante da linha, q são os dados
            return valor;  // Retorna os dados da chave encontrada.
        }
    }

    return "";  // Retorna string vazia se a chave n for encontrada no arquivo
}
