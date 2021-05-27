//
// Created by liuchang01_dxm on 2021/5/25.
//
#include <string.h>
#include "dict.h"

static char file_exist;

// 单词的个数即是链表的长度
uint32_t ListCount(FILE *fp){
    uint32_t count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp)){
        if ('#' == buffer[0]){
            ++count;
        }
    }

    rewind(fp); // 这一步一定要做，使文件指针指向文件头
    return count;
}

// 创建链表，返回头结点
dict_t CreateList(dict_t head, FILE *fp, uint32_t count){
    dict_t new, pointer;
    char *a;
    char buf[TARGET_WORD_BUFFER],*word;
    uint8_t word_size, trans_size, mean_count = 1;
    int length = strlen(SEMANTIC_SEPARATOR);
    char *str;
    uint32_t i, j = 0;

    head = (dict_t)malloc(sizeof(word_t)); //分配节点空间
    if (NULL == head){
        fprintf(stderr, "malloc failure!\n");
        exit(1);
    }

    printf("head sccess\n");

    if (count > 0){
        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), fp);
        word_size = strlen(buf);
        buf[word_size - 1] = '\0';
        word = strtok(buf, "#");
        strcpy(head->word, word);

        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), fp);
        trans_size = strlen(buf);
        buf[trans_size - 1] = '\0';

        str = strtok(buf, "@");
        strcpy(head->trans[j++], str + length);
        //printf("str:%s str+6:%s\n", str, str+length);

        while (str){
            strcpy(head->trans[j++], str);
            ++mean_count;
            str = strtok(NULL, "@");
        }

        head->mean_count = mean_count;
/*
        printf("head->word:%s head->mean_count:%d\n", head->word, head->mean_count);
        for(i=0;i<=j;i++){
            printf("head->trans[%d]:%s \n", i, head->trans[i]);
        }*/

        head->next = NULL; // 到这里为止填充了首节点，并将首节点的下一个节点指向空
        pointer = head;

        for (i = 0; i<count-1; ++i){ // 将后面（count-1）个依次链接到首节点后面
            mean_count = 1;
            new = (dict_t)malloc(sizeof(word_t)); //分配节点空间

            memset(buf, 0, sizeof(buf));
            fgets(buf, sizeof(buf), fp);

            word_size = strlen(buf);
            buf[word_size - 1] = '\0';
            word = strtok(buf, "#");
            strcpy(new->word, word);

            //printf("new->word:%s \n", new->word);

            memset(buf, 0, sizeof(buf));
            fgets(buf, sizeof(buf), fp);
            trans_size = strlen(buf);
            buf[trans_size - 1] = '\0';
            for (int j = 0; j < count;) {
                str = strtok(buf, "@");
                strcpy(new->trans[j++], str + length);

                while(str){
                    strcpy(new->trans[j++], str);

                    ++mean_count;
                    str = strtok(NULL, "@");
                }
            }

            new->mean_count = mean_count;
            new->next = NULL;

            pointer->next = new;
            pointer = new;
        }
    }

    rewind(fp);
    return head;
}

// 打印链表
void PrintList(dict_t head){
    dict_t pointer;
    pointer = head;

    while(pointer != NULL){
        printf("pointer->word = %s, pointer->mean_count = %d \n", pointer->word, pointer->mean_count);
        pointer = pointer->next;
    }
}

// 从链表中查找单词
void SearchList(dict_t head, uint32_t count){
    dict_t pointer;
    char str[TARGET_WORD_MAX_SIZE];
    uint32_t i;

    while (1){
        file_exist = 0;
        pointer = head;
        printf("Please input a word:");
        fgets(str, TARGET_WORD_MAX_SIZE, stdin);
        str[strlen(str) - 1] = '\0';

        if (strcmp(str, "exit") == 0){
            exit(1);
        }

        while (pointer != NULL){
            //printf("========pointer->word:%s \n", pointer->word);
            if((strcmp(pointer->word, str)) == 0){
                for(i = 0; i < pointer->mean_count; ++i){
                    file_exist = 1;
                    fprintf(stdout, "Trans%d: %s\n", i+1, pointer->trans[i]);
                }
                break;
            }

            pointer = pointer->next;
        }

        if (file_exist == 0){
            exit(1);
        }
    }
}

// 释放内存
void DestroyList(dict_t head){
    dict_t pointer;

    while(head){
        pointer = head;
        head = head->next;
        free(pointer);
    }
}