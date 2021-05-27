//
// Created by liuchang01_dxm on 2021/5/24.
//

#ifndef C_DICTIONARY_DICT_H
#define C_DICTIONARY_DICT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

#define TARGET_TEXT_NAME "./dict.txt"
#define TARGET_INDEX_NAME "./dict.dat"
#define SEMANTIC_SEPARATOR "Trans:"
#define TARGET_WORD_MAX_SIZE 60
#define TARGET_WORD_MEANING_COUNT 20
#define TARGET_WORD_MAX_TRANSLATION 100
#define TARGET_WORD_BUFFER 1024

// 单词链表 ---- 单词名称，单词有几种翻译，单词翻译的结果
typedef struct dict{
    char word[TARGET_WORD_MAX_SIZE]; // 要输入的单词，如"#superstar"
    uint8_t mean_count; // 单词解释的个数，如既可以做名词也可以做动词，用@分开
    char trans[TARGET_WORD_MEANING_COUNT][TARGET_WORD_MAX_TRANSLATION];  // 翻译结果
    struct dict *next;
} word_t, *dict_t;

uint32_t ListCount(FILE *fp);  // 词典里面单词的个数，即是要创建链表的长度
dict_t CreateList(dict_t head, FILE *fp, uint32_t count); // 创建单链表，返回首节点。分配内存。
void PrintList(dict_t head); // 打印链表
void SearchList(dict_t head, uint32_t count); // 查找输入的单词
void DestroyList(dict_t head); // 释放内存
void WriteIndexFile(dict_t head, const char *filename, uint32_t count);  // 建立索引，按协议格式写入文件
void ReadIndexFile(dict_t head, const char *filename, uint32_t *count);  // 从文件中读出单词内容

void Process(int argc, char **argv); // 主进程， main函数主要调用接口

#endif //C_DICTIONARY_DICT_H

