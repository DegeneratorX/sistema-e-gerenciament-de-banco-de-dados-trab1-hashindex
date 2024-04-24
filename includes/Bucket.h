//
// Created by arida01 on 23/04/24.
//

#include <iostream>
#include "string"

#ifndef SGBD_TRABALHO1_HASH_BUCKET_H
#define SGBD_TRABALHO1_HASH_BUCKET_H

class Bucket {
public:
    std::string arquivo;
    int id;
    int tam;
    int profundidadeLocal;

    Bucket();
};


#endif //SGBD_TRABALHO1_HASH_BUCKET_H
