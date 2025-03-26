//
// Created by waterfall on 25-3-26.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTable.h"
#include "Hash.h"

HashTable::HashTable(int len) {
    this->size = 0;
    this->tableLength = len;
    this->list = new HashNode * [len];
    for(int pos = 0;pos< len;++pos){
        list[pos] = nullptr;
    }
}

HashTable::~HashTable() {
    clearTable();
}

void HashTable::clearTable() {
    if(!list){
        return;
    }
    for(int pos = 0;pos < this->tableLength;++pos){
        if(list[pos] == nullptr){
            continue;
        }
        HashNode* current = list[pos];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            removeNode(temp);
        }
        list[pos] = nullptr;
    }
    size = 0;
}

bool HashTable::removeNode(HashNode *&target) {
    if (!target)
        return false;
    HashNode* temp = target;
    target = target->next;
    delete temp;
    return true;
}

int HashTable::getSize() const {
    return size;
}

void HashTable::insert(int64_t key, std::string &newString) {
    uint64_t hash[2] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, hash);
    uint64_t position = hash[1]%this->tableLength;

    if (list[position] == nullptr){
        list[position] = new HashNode(key,newString, nullptr);
        size ++;
        return;
    }

    HashNode *current = list[position];
    while(current->next != nullptr){
        if(current->keyValue == key){
            current->str = newString;
            return;
        }
        current = current->next;
    }
    current->next = new HashNode(key,newString, nullptr);
    size ++;
}

bool HashTable::remove(int64_t key) {
    if(size == 0){
        return false;
    }

    uint64_t hash[2] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, hash);
    uint64_t position = hash[1]%this->tableLength;

    if(list[position] == nullptr){
        return false;
    }
    HashNode* current = list[position];
    HashNode* previous = nullptr;  // 用来记录当前节点的前一个节点

    // 遍历链表，查找要删除的节点
    while (current != nullptr) {
        if (current->keyValue == key) {  // 找到要删除的节点
            if (previous == nullptr) {  // 如果删除的是链表的头节点
                // 更新哈希表槽位的头指针
                list[position] = current->next;
            } else {
                // 如果删除的是中间的节点，更新前一个节点的 `next` 指针
                previous->next = current->next;
            }
            // 删除节点
            removeNode(current);
            size--;  // 删除成功，更新哈希表的大小
            return true;
        }
        // 更新 `previous` 和 `current` 指针，继续遍历链表
        previous = current;
        current = current->next;
    }
}

bool HashTable::search(int64_t key) const {
    if(size == 0){
        return false;
    }
    uint64_t hash[2] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, hash);
    uint64_t position = hash[1]%this->tableLength;

    if(list[position] == nullptr){
        return false;
    }
    HashNode *current = list[position];
    while(current!= nullptr){
        if(current->keyValue == key){
            return true;
        }
        current = current->next;
    }
    return false;
}

std::string HashTable::getString(int64_t key) {
    if(size == 0){
        return std::string();
    }
    uint64_t hash[2] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, hash);
    uint64_t position = hash[1]%this->tableLength;

    if(list[position] == nullptr){
        return std::string();
    }
    HashNode *current = list[position];
    while(current!= nullptr){
        if(current->keyValue == key){
            return current->str;
        }
        current = current->next;
    }
    return std::string();
}

bool HashTable::isEmpty() const {
    return (this->size == 0);
}

void HashTable::readFromfile(const std::string& filepath) {
    // 打开文件
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // 忽略空行或格式不正确的行
        if (line.empty()) continue;

        // 使用 stringstream 解析 key 和 string
        std::stringstream ss(line);
        int64_t key;
        std::string value;

        // 假设文件格式为 "key,value" 类型
        if (ss >> key && std::getline(ss, value, ',')) {
            if (!value.empty() && value[0] == ' ') {  // 检查 value 是否为空
                value = value.substr(1);  // 去掉多余的空格
            }

            // 插入到哈希表中
            insert(key, value);
        } else {
            std::cerr << "Invalid line format: " << line << std::endl;
        }
    }

    // 关闭文件
    file.close();
}




