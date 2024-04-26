//
// Created by arida01 on 23/04/24.
//

#include "HashTable.h"


/**
 * @param profundidadeGlobal é a profundidade dada pelo monitor da disciplina
 *
 * Construtor da Hashtable.
 * - Recebe a profundade globa - PG (dado pelo problema).
 * - A quantidade de buckets é dado pelo 2^PG, pois o PG olha os bits menos significativos.
 * - O vetor de buckets guarda ponteiros para buckets. Inicialmente é zero, mas dado o PG, aloco espaço para a quantidade
 * de buckets. TODO: Eliminar esse vetor e criar um arquivo de índices
 *
 * Em seguida eu faço um laço 'for', que itera pelo vetor de buckets e vai preenchendo com ponteiros para objetos buckets,
 * Cada bucket contém seu id, tamanho inicial zerado, profundidade local igual a global inicialmente, e o
 * caminho de onde esse arquivo vai ser criado em seguida (../data/buckets/id.txt). Se der erro na criação, ele dá um
 * rollback e apaga os arquivos inicialmente criados.
 */
HashTable::HashTable(int profundidadeGlobal){
    this->profundidadeGlobal = profundidadeGlobal;
    this->qtdDeBuckets = static_cast<int>(std::pow(2, profundidadeGlobal));
    this->vetorDeBuckets.resize(this->qtdDeBuckets);
    this->pathIndice = pathIndice;

    for (int i = 0; i < this->qtdDeBuckets; i++){
        const std::string pathDoBucket = "../data/buckets/" + std::to_string(i) + ".txt";
        this->vetorDeBuckets[i] = new Bucket(i, 0, profundidadeGlobal, pathDoBucket);

        std::ofstream arquivoDoBucket(this->vetorDeBuckets[i]->pathDoBucket);
        if (!arquivoDoBucket){
            std::cerr << "Erro no construtor da HashTable. Nao foi possivel criar o arquivo do bucket: " << i << ".txt" << std::endl;

            // Rollback de criação de arquivos de buckets
            for (int j = 0; j < this->qtdDeBuckets; j++){
                std::filesystem::remove("../data/buckets/" + std::to_string(i) + ".txt");
            }
            exit(1);
        }
    }
}

/**
 * Essa função basicamente captura os bits menos significativos da chave.
 *
 * @param chave geralmente é a primary key da tabela.
 * @return Retorna os bits menos significativos dessa chave baseado na profundidade global.
 *
 * Basicamente se PG = 3 e a chave for 53 (110101), ele vai retornar os 3 últimos números (bits menos significativos),
 * 101 = 5. Ou seja, de 000 a 111, tem 8 possibilidades, de 0 a 7. Como deu 5, então esse índice apontará pro bucket de
 * id =
 *
 * A função em si usa uma máscara que desloca o bit menos significativo pra esquerda. Ou seja, 2^3 = 001000. Descobrindo
 * o resto da chave com esse valor, eu descubro os 3 bits menos significativos em forma de resto.
 */
int HashTable::funcaoHash(int chave){
    int mascara = static_cast<int>(pow(2, this->profundidadeGlobal));
    return chave % (mascara);
}


void HashTable::carregarTabela(HashTable* ht) {
    const std::string pathDoCSV = "../data/tabelas/compras.csv";
    std::ifstream arquivoDoCSV(pathDoCSV);
    if (!arquivoDoCSV.is_open()) {
        std::cerr << "Erro ao abrir o arquivo CSV: " << "../data/tabelas/compras.csv" << std::endl;
        return;
    }

    std::string linha;
    while (getline(arquivoDoCSV, linha)) {
        std::istringstream iss(linha);
        std::string id, valor, ano;
        getline(iss, id, ',');
        getline(iss, valor, ',');
        getline(iss, ano, ',');

        // Monta a string para ser armazenada como valor na tabela hash
        std::string valorHash = id + "," + valor + "," + ano;

        // Insere na tabela hash
        if (!ano.empty()) {
            ht->inserir(std::stoi(ano), valorHash);
        }
    }

    arquivoDoCSV.close();
}


/**
 * @param chave Insere a chave original em um bucket. Essa chave tambem passa pela função hash aqui.
 * @param valor Insere o valor correspondente a essa chave no mesmo bucket.
 *
 * Aqui eu insiro a chave que chega na função hash, que retorna a chave hasheada, que são os bits menos significativos
 * em formato de inteiro, ou seja, o índice que eu preciso para achar o bucket que vai guardar a chave:valor.
 *
 * Após isso, eu faço a leitura e escrita do <id_bucket>.txt com esse índice/id (a leitura é graças ao modo
 * std::ios::app, caso contrário truncaria do zero e apagaria o conteúdo. Esse modo permite abrir e escrever na última
 * linha do arquivo).
 *
 * Se o bucket (limitado a 3 registros) tiver vaga pra por dados, ele simplesmente põe o registro chave:valor lá.
 *
 * Se não tiver vaga, overflow.
 *
 * Dois casos: PG = PL
 *      - Se PG = PL, duplica o arquivo de índices (2^3 para 2^4 por exemplo) através do incremento da PG em ++1.
 *      - Atualizo o número de buckets de 2^3 para 2^4 buckets e faço um resize no vetor que armazena esses ponteiros
 *      para 2^4. Nesse momento o arquivo de índices terá índices que leem 4 bits menos significativos de chaves.
 *      - Coloco novos ponteiros no arquivo de indices para novos buckets que irão preencher esse espaço vazio novo.
 *      - Os buckets novos se manterão com a PL igual a antiga PG, mas o que será armazenado em disco para comportar
 *      os novos dados terão a PL = nova PG.
 *
 */
void HashTable::inserir(int chave, const std::string& valor){

    int indiceDoBucket = this->funcaoHash(chave);

    // Verificação que faço pra ver se o bucket que quero inserir está vazio e já foi um bucket previamente usado com PL
    // incrementado, mas que depois de esvaziar foi decrementado
    if (this->vetorDeBuckets[indiceDoBucket] == nullptr || !std::filesystem::exists(this->vetorDeBuckets[indiceDoBucket]->pathDoBucket)) {
        this->vetorDeBuckets[indiceDoBucket] = new Bucket(indiceDoBucket, 0, this->profundidadeGlobal, "../data/buckets/" + std::to_string(indiceDoBucket) + ".txt");
        int indiceDoBucketPai = indiceDoBucket & (~(1 << (this->vetorDeBuckets[indiceDoBucket]->profundidadeLocal - 1)));

        // Incremento o PL de ambos, bucket e o pai, pra restaurar estado anterior da exclusão
        this->vetorDeBuckets[indiceDoBucket]->profundidadeLocal = this->profundidadeGlobal;
        this->vetorDeBuckets[indiceDoBucketPai]->profundidadeLocal = this->profundidadeGlobal;
    }

    // Leitura do txt do bucket correspondente ao índice (1.txt, 2.txt etc...)
    std::ofstream arquivoDoBucket(this->vetorDeBuckets[indiceDoBucket]->pathDoBucket, std::ios::app);
    if (!arquivoDoBucket) {
        std::cerr << "Erro no método de inserção: não foi posível abrir o pathDoBucket de bucket localizado em " << this->vetorDeBuckets[indiceDoBucket]->pathDoBucket << std::endl; exit(1);
    }

    // Se o tamanho de registros for menor do que 3 dentro do txt do bucket, insere a chave:valor no txt.
    if (contadorDeRegistros(this->vetorDeBuckets[indiceDoBucket]) < 3){
        arquivoDoBucket << chave << "," << valor << std::endl;
        this->vetorDeBuckets[indiceDoBucket]->tamDoBucket += 1;

    } else{ // Se for igual, OVERFLOW.

        /**
         * Esse if verifica se PG = PL com overflow. Se for menor, é porque já tem um ponteiro no arquivo de índices
         * que pode ser usado pra outro bucket. Ou seja, pula tudo isso aqui. Caso seja igual, vou ter que aumentar o
         * PG e criar buckets novos para guardar novos registros.
         */
        if (this->profundidadeGlobal == this->vetorDeBuckets[indiceDoBucket]->profundidadeLocal){
            this->profundidadeGlobal += 1;
            this->qtdDeBuckets = static_cast<int>(std::pow(2, this->profundidadeGlobal));
            this->vetorDeBuckets.resize(this->qtdDeBuckets);

            /**
             * Aqui é um pouco chato de entender, mas eu basicamente preencho os buckets novos com metadados. O laço
             * for começa pela metade do vetor de ponteiros para buckets até o final.
             */
            for (int indiceNovo = (this->qtdDeBuckets) / 2   ;   indiceNovo < (this->qtdDeBuckets)   ;   indiceNovo++){
                std::string pathDoBucket = "../data/buckets/" + std::to_string(indiceNovo - (this->qtdDeBuckets / 2)) + ".txt";
                this->vetorDeBuckets[indiceNovo] = new Bucket(indiceNovo, 0, profundidadeGlobal - 1, pathDoBucket);
            }
        }

        /**
         * Aqui eu finalmente trato o overflow. Capturo o ponteiro que aponta pro bucket cheio, e pego o ponteiro que
         * aponta pro bucket novo que vai guardar as informações em excesso de outro bucket. O bucket novo que guarda
         * as informações será determinado pelo próximo número em binaŕio que termina com o mesmo valor de bits menos
         * significativos do PG antigo. Por exemplo, se o bucket 03 deu overflow e PG = PL do 03 = 2, e 03 = 11, então
         * eu analiso o próximo número em bin que termina em 11. Que é o 07 = 111. Incremento PG++, e o bucket 03 e 07
         * terão PG = PL = 3, o resto terá PL = 2. O novo bucket será o 07 que irá receber dados de 03.
         */
        Bucket* bucketOverflow = this->vetorDeBuckets[indiceDoBucket];
        Bucket* novoBucket;
        if (indiceDoBucket < this->qtdDeBuckets/2) {
            novoBucket = this->vetorDeBuckets[indiceDoBucket + this->qtdDeBuckets / 2];
        }
        else {
            novoBucket = this->vetorDeBuckets[indiceDoBucket - this->qtdDeBuckets / 2];
        }
        novoBucket->pathDoBucket = "../data/buckets/" + std::to_string(novoBucket->idDoBucket) + ".txt";
        std::ofstream novoArquivoBucket(novoBucket->pathDoBucket);

        std::list<std::string> bufferComRegistrosDoBucketComOverflow = this->extrairRegistrosDoBucket(bucketOverflow);
        novoBucket->profundidadeLocal += 1;
        bucketOverflow->profundidadeLocal += 1;

        this->apagarConteudoArquivo(bucketOverflow);

        /**
         * Aqui eu estou pegando os dados do buffer e redistribuindo nos buckets de forma recursiva, incluindo o novo
         * bucket.
         */
        for (const std::string& registro : bufferComRegistrosDoBucketComOverflow){
            std::istringstream iss(registro);
            std::string chaveStr, valorStr;

            // Usamos getline para separar a chave e o valor usando a vírgula como delimitador
            if (std::getline(iss, chaveStr, ',') && std::getline(iss, valorStr)) {
                // Convertendo a chave de string para int
                int chaveInt = std::stoi(chaveStr);
                this->inserir(chaveInt, valorStr);
            } else {
                std::cerr << "Erro no método de inserção: formato inválido de registro: " << registro << std::endl;
            }
        }

        // Depois de redistribuir os registros do bucket com overflow, eu finalmente insiro o último dado que falta, o
        // que iria causar o overflow mas foi impedido de ser colocado. Somente agora pode ser colocado.
        this->inserir(chave, valor);
    }

}


std::list<std::string> HashTable::extrairRegistrosDoBucket(Bucket* bucket) {
    // Função que lê um pathDoBucket de texto e retorna uma lista encadeada com as linhas
    std::ifstream arquivoDoBucket(bucket->pathDoBucket);
    std::list<std::string> linhas;

    if (arquivoDoBucket.is_open()) {
        std::string linha;
        while (std::getline(arquivoDoBucket, linha)) {
            linhas.push_back(linha);
        }
        arquivoDoBucket.close();
    } else {
        std::cerr << "Erro no método 'extrairRegistrosDoBucket()': não foi possível abrir o arquivo " << bucket->pathDoBucket << " para extrair dados linha a linha. Retornarei uma lista vazia." << std::endl;
        // Retorna uma lista vazia em caso de falha ao abrir o pathDoBucket
        return std::list<std::string>();
    }
    return linhas;
}


std::string HashTable::consultarValor(int chave) {
    int indiceDoBucket = this->funcaoHash(chave);

    // Abre o arquivo do balde pra leitura
    std::ifstream arquivoDoBucket(this->vetorDeBuckets[indiceDoBucket]->pathDoBucket);
    if (!arquivoDoBucket) {
        std::cout << "Erro no método de consultar valor: não foi possível abrir o arquivo de bucket localizado em " << this->vetorDeBuckets[indiceDoBucket]->pathDoBucket << std::endl;
        return "";  // Retorna string vazia caso n encontre
    }

    std::string linha;
    while (getline(arquivoDoBucket, linha)) {
        std::stringstream ss(linha);
        int chaveIterador;
        std::string valor;

        getline(ss, linha, ',');  // Lê até a vírgula, pegando a chave
        chaveIterador = std::stoi(linha);  // Converte a chave de string para int

        if (chaveIterador == chave) {
            getline(ss, valor);  // Obtém o restante da linha, q são os dados
            return valor;  // Retorna os dados da chave encontrada.
        }
    }

    return "";  // Retorna string vazia se a chave n for encontrada no arquivo
}


/**
 *
 * @param chave É a chave que vai dizer qual registro vai ser removido
 *
 * Essa função é muito complexa. Basicamente ela retira tudo do arquivo e redistribui. Não retira apenas um registro/tupla.
 */
bool HashTable::remover(int chave){
    bool removeu = false;
    int indiceDoBucket = this->funcaoHash(chave);

    std::ifstream arquivoDoBucket(this->vetorDeBuckets[indiceDoBucket]->pathDoBucket);
    if (!arquivoDoBucket) {
        std::cerr << "Erro no método de inserção: não foi posível abrir o pathDoBucket de bucket localizado em " << this->vetorDeBuckets[indiceDoBucket]->pathDoBucket << std::endl;
        return removeu;  // Remove nada caso n encontre
    }

    /**
     * Eu removo tudo do arquivo ao invés de um registro só, pois por segurança é bom redistribuir tudo de novo.
     */
    std::list<std::string> bufferComDadosDoBucket = this->extrairRegistrosDoBucket(this->vetorDeBuckets[indiceDoBucket]);
    this->apagarConteudoArquivo(this->vetorDeBuckets[indiceDoBucket]);

    for (const std::string& registro : bufferComDadosDoBucket){
        std::istringstream iss(registro);
        std::string chaveStr, valorStr;

        // Usamos getline para separar a chave e o valor usando a vírgula como delimitador
        if (std::getline(iss, chaveStr, ',') && std::getline(iss, valorStr)) {
            // Convertendo a chave de string para int
            int chaveInt = std::stoi(chaveStr);
            if (chaveInt != chave){
                this->inserir(chaveInt, valorStr);
            } else {removeu = true;}
        } else {
            std::cerr << "Erro no método de inserção: formato inválido de registro: " << registro << std::endl;
        }
    }

    arquivoDoBucket.close();
    // Verifique se o bucket está vazio após a remoção
    if (contadorDeRegistros(this->vetorDeBuckets[indiceDoBucket]) == 0) {
        std::filesystem::remove(this->vetorDeBuckets[indiceDoBucket]->pathDoBucket);
        this->vetorDeBuckets[indiceDoBucket]->tamDoBucket = 0; // Zerar o tamanho do bucket
        this->vetorDeBuckets[indiceDoBucket]->profundidadeLocal--;

        // Identificar o bucket pai e verificar sua situação
        int indiceDoBucketPai = indiceDoBucket & (~(1 << (this->vetorDeBuckets[indiceDoBucket]->profundidadeLocal)));
        if (this->vetorDeBuckets[indiceDoBucketPai]->profundidadeLocal > this->vetorDeBuckets[indiceDoBucket]->profundidadeLocal) {
            this->vetorDeBuckets[indiceDoBucketPai]->profundidadeLocal--;
        }

        // Verificar se é necessário reduzir o PG
        bool reduzirPG = true;
        for (auto& bucket : this->vetorDeBuckets) {
            if (bucket->profundidadeLocal == this->profundidadeGlobal) {
                reduzirPG = false;
                break;
            }
        }

        // Se todos os PLs forem menores que PG, reduza o PG
        if (reduzirPG) {
            this->profundidadeGlobal--;
            this->vetorDeBuckets.resize(std::pow(2, this->profundidadeGlobal));
        }
    }
    return removeu;

    /*
    if (contadorDeRegistros(this->vetorDeBuckets[indiceDoBucket]->pathDoBucket) == 0){
    int proxBucket = this->vetorDeBuckets[indiceDoBucket]->idDoBucket + (this->qtdDeBuckets/2);
    if (proxBucket > this->qtdDeBuckets){
        proxBucket = this->vetorDeBuckets[indiceDoBucket]->idDoBucket - (this->qtdDeBuckets/2);
    }
    std::string diretorioBucketASerApagado = "../data/buckets/" + std::to_string(indiceDoBucket) + ".txt";
    this->vetorDeBuckets[indiceDoBucket]->pathDoBucket = "../data/buckets/" + std::to_string(proxBucket) + ".txt";;
    // A função remove retorna 0 em caso de sucesso e um valor diferente de zero em caso de falha
    if (remove(diretorioBucketASerApagado.c_str()) == 0) {
        std::cout << "Arquivo apagado com sucesso." << std::endl;
    } else {
        std::cerr << "Erro ao tentar apagar o pathDoBucket." << std::endl;
    }
    this->vetorDeBuckets[proxBucket]->profundidadeLocal -= 1;
    }
    */
}




void HashTable::apagarConteudoArquivo(Bucket* bucket) {
    // Abro o pathDoBucket em modo de escrita. Isso trunca o pathDoBucket pra zero.
    std::ofstream arquivo(bucket->pathDoBucket, std::ofstream::trunc);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o pathDoBucket para truncar." << std::endl;
    }
    bucket->tamDoBucket = 0;
    arquivo.close(); // Fechando o pathDoBucket
}


int HashTable::getProfundidadeGlobal() {
    return this->profundidadeGlobal;
}

int HashTable::getProfundidadeLocal(int chave) {
    int indiceDoBucket = this->funcaoHash(chave);
    return this->vetorDeBuckets[indiceDoBucket]->profundidadeLocal;
}


int contadorDeRegistros(Bucket* bucket) {

    std::ifstream file(bucket->pathDoBucket);
    int contadorLinhas = 0;
    std::string linha;

    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o pathDoBucket: " << bucket->pathDoBucket << std::endl;
        return -1;  // Retorna -1 para indicar falha ao abrir o arquivo de bucket
    }

    while (std::getline(file, linha)) {
        ++contadorLinhas;  // Incrementa o contador para cada linha lida
    }

    file.close();  // Fechando o pathDoBucket após o uso
    std::cout << std::endl;
    return contadorLinhas;
}

void leituraInTxt(const std::string& inTxt, const std::string& outTxt, HashTable* ht){
    std::ifstream in(inTxt);
    std::ofstream out(outTxt);

    if (!in.is_open() || !out.is_open()) {
        std::cerr << "Erro ao abrir arquivos." << std::endl;
        return;
    }

    std::string linha;
    getline(in, linha);  // Lê a profundidade global inicial
    int profundidadeGlobalInicial = std::stoi(linha.substr(3));
    HashTable* ht2 = new HashTable(profundidadeGlobalInicial);
    out << linha << std::endl;  // Escreve a profundidade global inicial no arquivo de saída

    while (getline(in, linha)) {
        std::istringstream iss(linha);
        std::string comando, chaveStr;
        getline(iss, comando, ':');
        getline(iss, chaveStr);
        int chave = std::stoi(chaveStr);

        if (comando == "INC") {
            ht->inserir(chave, "Valor");  // Assume que inserir pode manipular valores vazios
            // Pego o o PG e PL após inserção
            out << linha << "/" << ht2->getProfundidadeGlobal() << "," << ht2->getProfundidadeLocal(chave) << std::endl;
        } else if (comando == "BUS") {
            int count = ht2->incidenciasDeChave(chave);
            out << linha << "/" << count << std::endl;
        } else if (comando == "REM") {
            int count = 0;
            while (ht2->remover(chave)){
                count += 1;
            }
            // Pego o PG e PL dps da remoção
            out << linha << "/" << count << "," << ht2->getProfundidadeGlobal() << "," << ht2->getProfundidadeLocal(chave) << std::endl;
        }
    }

    // Escreve o PG final
    out << "P/" << ht2->getProfundidadeGlobal() << std::endl;

    in.close();
    out.close();
}

int HashTable::incidenciasDeChave(int chave) {
    int indiceDoBucket = this->funcaoHash(chave);

    // Abre o arquivo do balde pra leitura
    std::ifstream arquivoDoBucket(this->vetorDeBuckets[indiceDoBucket]->pathDoBucket);
    if (!arquivoDoBucket) {
        std::cout << "Erro no método de consultar valor: não foi possível abrir o arquivo de bucket localizado em " << this->vetorDeBuckets[indiceDoBucket]->pathDoBucket << std::endl;
        return -1;  // Retorna string vazia caso n encontre
    }

    std::string linha;

    int count = 0;
    while (getline(arquivoDoBucket, linha)) {
        std::stringstream ss(linha);
        int chaveIterador;

        getline(ss, linha, ',');  // Lê até a vírgula, pegando a chave
        chaveIterador = std::stoi(linha);  // Converte a chave de string para int

        if (chaveIterador == chave) {
            count += 1;
        }
    }

    return count;  // Retorna string vazia se a chave n for encontrada no arquivo
}


std::string HashTable::getBucketPath(int indice) {
    std::ifstream in(this->pathIndice);
    std::string line;
    // Pular a linha do PG
    std::getline(in, line);
    for (int i = 0; i <= indice; ++i) {
        std::getline(in, line);
    }
    return "../data/buckets/" + line + ".txt";
}

