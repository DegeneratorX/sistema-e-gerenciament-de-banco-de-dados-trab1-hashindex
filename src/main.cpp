#include <iostream>
#include "HashTable.h"

int main(){
    HashTable* ht = new HashTable(2);
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
    ht->remover(2);
}
/*
int main() {
    try {
        // Arquivo de entrada
        std::ifstream arqEntrada("../data/io/in.txt");
        if (!arqEntrada) {
            throw std::runtime_error("Erro: não foi possível abrir o arquivo in.txt");
        }

        // Arquivo de saída
        std::ofstream arqSaida("../data/io/out.txt");
        if (!arqSaida) {
            throw std::runtime_error("Erro: não foi possível abrir o arquivo out.txt");
        }

        // Ler a profundidade global inicial do diretório de hash
        int profundidadeInicial;
        std::string linha;
        std::getline(arqEntrada, linha);
        std::istringstream iss(linha.substr(3));
        iss >> profundidadeInicial;
        std::cout << "PG inicial: " << profundidadeInicial << std::endl;

        HashTable* ht = new HashTable(profundidadeInicial);

        // Carrego o CSV
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
                ht->inserir(chave, valor); // Suponha que a entrada de dados seja uma string genérica
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

    return EXIT_SUCCESS;
}
 */