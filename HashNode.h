//
// Created by waterfall on 25-3-26.
//

#pragma once
#ifndef HASH_TABLE_HASHNODE_H
#define HASH_TABLE_HASHNODE_H


#include <cstdint>
#include <string>

class HashNode {
public:
    int64_t keyValue;
    std::string str;
    HashNode *next;

    HashNode():keyValue(0),next(nullptr){}

    HashNode(int64_t key,std::string &data,HashNode *nextNode = nullptr):
    keyValue(key),str(data),next(nextNode){}

};


#endif //HASH_TABLE_HASHNODE_H
