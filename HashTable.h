//
// Created by waterfall on 25-3-26.
// This is a hash table based upon chain structure
// A node contains a key(int64_t) and a std::string
// Functions includes insert, delete ,search and build
//

#pragma once
#ifndef HASH_TABLE_HASHTABLE_H
#define HASH_TABLE_HASHTABLE_H
#include "HashNode.h"

class HashTable{
private:
    int tableLength;
    HashNode **list;
    int size;

    bool removeNode(HashNode *&target);
public:
    HashTable():list(nullptr),tableLength(0),size(0){}
    HashTable(int len);

    ~HashTable();

    void clearTable();

    int getSize()const;

    void insert(int64_t key,std::string &newString);

    bool remove(int64_t key);

    bool isEmpty()const;

    bool search(int64_t key)const;

    std::string getString(int64_t key);

    void readFromfile(const std::string &file_path);
};

#endif //HASH_TABLE_HASHTABLE_H
