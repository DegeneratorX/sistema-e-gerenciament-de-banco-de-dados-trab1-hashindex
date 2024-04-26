#include <iostream>
#include "HashTable.h"

int main(){
    HashTable* ht = new HashTable(2, "../data/indices/indice.txt");
    ht->carregarTabela(ht);
    leituraInTxt("../data/io/in.txt","../data/io/out.txt", ht);
    /*
    ht->inserir(2, "2");
    ht->inserir(4, "4");
    ht->inserir(5, "5");
    ht->inserir(8, "8");
    ht->inserir(16, "16");
    ht->inserir(32, "32");
    ht->inserir(3, "3");
    ht->inserir(7, "7");
    ht->inserir(15, "15");
    ht->inserir(19, "19");
    ht->remover(4);
    ht->inserir(4, "4");

    std::cout << ht->vetorDeBuckets.size() << std::endl;
    std::cout << ht->vetorDeBuckets[0]->profundidadeLocal << std::endl;
    std::cout << ht->vetorDeBuckets[4]->profundidadeLocal << std::endl;
     */
}

/*
int main() {
    try {
        std::ifstream arqEntrada("../data/io/in.txt");
        if (!arqEntrada) {
            throw std::runtime_error("Erro: não foi possível abrir o pathDoBucket in.txt");
        }
        std::ofstream arqSaida("../data/io/out.txt");
        if (!arqSaida) {
            throw std::runtime_error("Erro: não foi possível abrir o pathDoBucket out.txt");
        }

        int profundidadeInicial;
        std::string linha;
        std::getline(arqEntrada, linha);
        std::istringstream iss(linha.substr(3));
        iss >> profundidadeInicial;
        std::cout << "PG inicial: " << profundidadeInicial << std::endl;

        HashTable* ht = new HashTable(profundidadeInicial);

        ht->carregarTabela("../data/tabelas/compras.csv");

        int chave;
        std::string valor;
        std::string acao;

        while (std::getline(arqEntrada, linha)) {
            std::istringstream lineStream(linha);
            std::getline(lineStream, acao, ':');
            lineStream >> chave;
            std::getline(lineStream, valor, ',');

            std::cout << "Operacao: " << acao << " || Chave: " << chave << "|| Valor: " << valor << std::endl;

            if (acao == "INC") {
                ht->inserir(chave, valor);
                arqSaida << "INC:" << chave;
            }
            else if (acao == "REM") {
                ht->remover(chave);
                arqSaida << "REM:" << chave;
            } else if (acao == "BUS") {
                std::string valorBuscado = ht->consultarValor(chave);
                if (!valorBuscado.empty()) {
                    arqSaida << "BUS:" << chave;
                } else {
                    arqSaida << "BUS:" << chave;
                }
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Exceção capturada: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
*/