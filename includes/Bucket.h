//
// Created by arida01 on 23/04/24.
//

#include <iostream>
#include "string"

#ifndef SGBD_TRABALHO1_HASH_BUCKET_H
#define SGBD_TRABALHO1_HASH_BUCKET_H

class Bucket {
public:
    int idDoBucket;
    int tamDoBucket;
    int profundidadeLocal;
    std::string pathDoBucket;

    Bucket(int idDoBucket, int tamDoBucket, int profundidadeLocal, const std::string& pathDoBucket);
};


#endif //SGBD_TRABALHO1_HASH_BUCKET_H
