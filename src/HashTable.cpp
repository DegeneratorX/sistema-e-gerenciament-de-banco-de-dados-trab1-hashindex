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
        this->vetorBuckets[i]->id = i;
        this->vetorBuckets[i]->profundidadeLocal = profundidadeGlobal;
        this->vetorBuckets[i]->arquivo = "../data/buckets/" + std::to_string(i) + ".txt";

        std::ofstream criarArquivo(this->vetorBuckets[i]->arquivo);

        if (!criarArquivo){
            std::cout << "Erro! Nao foi possivel criar o bucket " << i << std::endl; exit(1);
        }
    }
}


int HashTable::funcaoHash(int chave){
    int mascara = static_cast<int>(pow(2, this->profundidadeGlobal));  // Usando pow pro deslocamento de bits
    return chave % (mascara);       // Resto q simula a máscara de bits
}


void HashTable::carregarTabela(const std::string& arquivo) {
    std::ifstream csvfile(arquivo);
    if (!csvfile) {
        std::cout << "Erro: n foi possivel abrir o csv " << arquivo << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(csvfile, linha)) {
        std::istringstream linhaStream(linha);
        int pedido;
        std::string valor;

        char delimitador;
        if (linhaStream >> pedido >> delimitador && delimitador == ',' && std::getline(linhaStream, valor)) {
            this->inserir(pedido, valor);   // Supõe que insert_entry agora aceite std::string como dado
        }
    }
}


void HashTable::inserir(int chave, const std::string& valor){

    // Insiro a chave. Retorno o índice de bocket que o dado vai ser colocado
    int indiceDoBucket = this->funcaoHash(chave);

    // Leitura do arquivo do bucket correspondente ao índice (1.txt, 2.txt etc...)
    std::ofstream arquivoDiretorioBucket(this->vetorBuckets[indiceDoBucket]->arquivo, std::ios::app);
    if (!arquivoDiretorioBucket) {
        std::cout << "Erro: não foi posível abrir o arquivo de bucket localizado em " << this->vetorBuckets[indiceDoBucket]->arquivo << std::endl; exit(1);
    }

    // Se o tamanho de registros for menor do que 3, insere a chave:valor.
    if (countLinesInFile(this->vetorBuckets[indiceDoBucket]->arquivo) < 3){
        arquivoDiretorioBucket << chave << "," << valor << std::endl;
        this->vetorBuckets[indiceDoBucket]->tam += 1;

    } else{
        // if PG = PL -> duplica o arquivo de indiceDoBucket, trata o overflow (cria um buffer que captura os dados do bucket
        // com overflow, e redistribui com um novo PG += 1, verificando os bits menos significativos a mais que foi ganho
        // para hashing no diretório de ponteiros, e ai os novos buckets na redistribuição vão ter PL = PG.

        // Duplicar o diretório (PG++)
        if (this->profundidadeGlobal == this->vetorBuckets[indiceDoBucket]->profundidadeLocal){
            this->profundidadeGlobal += 1;
            this->qtdBuckets = static_cast<int>(std::pow(2, profundidadeGlobal));
            this->vetorBuckets.resize(this->qtdBuckets);
            for (int s = this->qtdBuckets/2; s < this->qtdBuckets; s++){
                this->vetorBuckets[s] = new Bucket();
                this->vetorBuckets[s]->tam = 0;
                this->vetorBuckets[s]->id = s;
                this->vetorBuckets[s]->profundidadeLocal = profundidadeGlobal-1;
                this->vetorBuckets[s]->arquivo = "../data/buckets/" + std::to_string(s-(this->qtdBuckets/2)) + ".txt";
            }
        }

        // Tratar o overflow
        Bucket* bucketOverflow = this->vetorBuckets[indiceDoBucket];
        Bucket* novoBucket = this->vetorBuckets[indiceDoBucket+this->qtdBuckets/2];
        novoBucket->arquivo = "../data/buckets/" + std::to_string(novoBucket->id) + ".txt";
        std::ofstream criarNovoArquivoBucket(novoBucket->arquivo);

        std::list<std::string> bufferComDadosDoBucketComOverflow = this->bufferBucket(bucketOverflow->id);
        bucketOverflow->profundidadeLocal += 1;
        bucketOverflow->tam = 0;
        novoBucket->profundidadeLocal += 1;
        this->apagarConteudoArquivo(bucketOverflow->arquivo);

        for (const std::string& registro : bufferComDadosDoBucketComOverflow){
            std::istringstream iss(registro);
            std::string chaveStr, valorStr;

            // Usamos getline para separar a chave e o valor usando a vírgula como delimitador
            if (std::getline(iss, chaveStr, ',') && std::getline(iss, valorStr)) {
                // Convertendo a chave de string para int
                int chaveInt = std::stoi(chaveStr);
                this->inserir(chaveInt, valorStr);
            } else {
                std::cerr << "Formato inválido de registro: " << registro << std::endl;
            }
        }
        this->inserir(chave, valor);

        std::cout << "Bucket numero " << indiceDoBucket << " cheio." << std::endl;
        //split_bucket(dir, indiceDoBucket);
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

void HashTable::remover(int chave){
    int indice = this->funcaoHash(chave);
    bool achou = false;
    // Abre o arquivo do balde pra leitura
    std::ifstream arquivoDiretorioBucket(this->vetorBuckets[indice]->arquivo);
    if (!arquivoDiretorioBucket) {
        std::cout << "Erro ao abrir o arquivo do bucket: " << this->vetorBuckets[indice]->arquivo << std::endl;
        return;  // Remove nada caso n encontre
    }

    std::list<std::string> bufferComDadosDoBucket = this->bufferBucket(indice);
    this->apagarConteudoArquivo(this->vetorBuckets[indice]->arquivo);

    for (const std::string& registro : bufferComDadosDoBucket){
        std::istringstream iss(registro);
        std::string chaveStr, valorStr;

        // Usamos getline para separar a chave e o valor usando a vírgula como delimitador
        if (std::getline(iss, chaveStr, ',') && std::getline(iss, valorStr)) {
            // Convertendo a chave de string para int
            int chaveInt = std::stoi(chaveStr);
            if (chaveInt != chave){
                this->inserir(chaveInt, valorStr);
            }
        } else {
            std::cerr << "Formato inválido de registro: " << registro << std::endl;
        }
    }
    /*
    if (countLinesInFile(this->vetorBuckets[indice]->arquivo) == 0){
        int proxBucket = this->vetorBuckets[indice]->id + (this->qtdBuckets/2);
        if (proxBucket > this->qtdBuckets){
            proxBucket = this->vetorBuckets[indice]->id - (this->qtdBuckets/2);
        }
        std::string diretorioBucketASerApagado = "../data/buckets/" + std::to_string(indice) + ".txt";
        this->vetorBuckets[indice]->arquivo = "../data/buckets/" + std::to_string(proxBucket) + ".txt";;
        // A função remove retorna 0 em caso de sucesso e um valor diferente de zero em caso de falha
        if (remove(diretorioBucketASerApagado.c_str()) == 0) {
            std::cout << "Arquivo apagado com sucesso." << std::endl;
        } else {
            std::cerr << "Erro ao tentar apagar o arquivo." << std::endl;
        }
        this->vetorBuckets[proxBucket]->profundidadeLocal -= 1;
    }
    */
}


std::list<std::string> HashTable::bufferBucket(int id) {
    std::string caminho = "../data/buckets/" + std::to_string(id) + ".txt";
    // Função que lê um arquivo de texto e retorna uma lista encadeada com as linhas
    std::ifstream arquivo(caminho);
    std::list<std::string> linhas;

    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            linhas.push_back(linha);
        }
        arquivo.close();
    } else {
        std::cerr << "Erro: não foi possível abrir o arquivo: " << caminho << std::endl;
        // Retorna uma lista vazia em caso de falha ao abrir o arquivo
        return std::list<std::string>();
    }
    return linhas;
}

void HashTable::apagarConteudoArquivo(const std::string& diretorioArquivo) {
    // Abro o arquivo em modo de escrita. Isso trunca o arquivo pra zero.
    std::ofstream arquivo(diretorioArquivo, std::ofstream::trunc);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para truncar." << std::endl;
    } else {
        std::cout << "Conteúdo do arquivo apagado com sucesso." << std::endl;
    }

    arquivo.close(); // Fechando o arquivo
}

int countLinesInFile(const std::string& filePath) {
    std::ifstream file(filePath);
    int lineCount = 0;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << filePath << std::endl;
        return -1;  // Retorna -1 para indicar falha ao abrir o arquivo
    }

    while (std::getline(file, line)) {
        ++lineCount;  // Incrementa o contador para cada linha lida
    }

    file.close();  // Fechando o arquivo após o uso
    return lineCount;
}