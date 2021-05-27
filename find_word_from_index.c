//
// Created by liuchang01_dxm on 2021/5/27.
//
#include <stdio.h>
#include "dict.h"

// 建立索引，按协议格式写入文件
void WriteIndexFile(dict_t head, const char *filename, uint32_t count){
    FILE *stream;
    uint32_t i, word_size, trans_size, mean_count;
    uint8_t j;

    dict_t pointer = head;

    if((stream = fopen(filename, "wb")) == NULL){
        fprintf(stderr, "Cannot open output file.\n");
        exit(1);
    }

    fwrite(&count, 4, 1, stream);

    while(pointer != NULL){

        word_size = strlen(pointer->word);
        mean_count = pointer->mean_count;

        fwrite(&word_size, 4, 1, stream);
        fwrite(pointer->word, 1, word_size, stream);
        fwrite(&mean_count, 4, 1, stream);

        for(j = 0; j < mean_count; ++j){
            trans_size = strlen(pointer->trans[j]);
            fwrite(&trans_size, 4, 1, stream);
            fwrite(pointer->trans[j], 1, trans_size, stream);
        }

        pointer = pointer->next;

    }

    fclose(stream);
}

// 从文件中读出单词内容
void ReadIndexFile(dict_t head, const char *filename, uint32_t *count){
    FILE *stream;
    uint8_t i;
    uint32_t word_size, trans_size, mean_count;
    dict_t pointer = head;

    printf("enter...\n");

    if ((stream = fopen(filename, "rb")) == NULL){
        fprintf(stderr, "Cannot open output file.\n");
        exit(1);
    }

    fread(count, 4, 1, stream);
    printf("count = %d\n", *count);

    while (pointer != NULL){
        fread(&word_size, 4, 1, stream);
        fread(pointer->word, 1, word_size, stream);

        pointer->word[word_size] = '\0';

        fread(&pointer->mean_count, 4, 1, stream);

        for(i = 0; i < pointer->mean_count; i++){
            memset(pointer->trans[i], 0, sizeof(pointer->trans[i]));
            fread(&trans_size, 4, 1, stream);
            fread(pointer->trans[i], 1, trans_size, stream);
            pointer->trans[i][trans_size] = '\0';
            printf("trans_size = %d\n", trans_size);
            printf("pointer->trans = %s\n", pointer->trans[i]);
        }

        pointer = pointer->next;
    }

    printf("read over!\n");
}