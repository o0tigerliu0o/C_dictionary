//
// Created by liuchang01_dxm on 2021/5/25.
//

#include "dict.h"

static char file_exist;

// 单词的个数即是链表的长度
uint32_t ListCount(File *fp){
    uint32_t count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp)){
        if ('#' == buffer[0]){
            ++count;
        }
    }

    rewind(fp); // 这一步一定要做，使文件指针指向文件头
    return count
}

// 创建链表，返回头结点
dict_t CreateList(dict_t head, FILE *fp, uint32_t count){
    dict_t new, pointer;
    char buf[TARGET_WORD_BUFFER];
    uint8_t word_size, trans_size, mean_count = 1, *str;
    uint32_t i, j = 0;

    head = (dict_t)malloc(sizeof(word_t)); //分配节点空间
    if (NULL == head){
        fprintf(stderr, "malloc failure!\n");
        exit(1);
    }

    printf("head sccess");

    if (count > 0){
        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), fp);
        word_size = strlen(buf);
        buf[word_size - 1] = '\0';
        strcpy(head->word, buf);

        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), fp);
        trans_size = strlen(buf);
        buf[trans_size - 1] = '\0';

        str = strtok(buf, "@");
        strcpy(head->trans[j++], str + 6);

        while (str = strtok[NULL, "@"]){
            strcpy(head->trans[j++], str);
            ++mean_count;
        }

        head->mean_count = mean_count;

        head->next = NULL; // 到这里为止填充了首节点，并将首节点的下一个节点指向空
        pointer = head;

        for (i = 0; i<count-1; ++i){ // 将后面（count-1）个依次链接到首节点后面
            mean_count = 1;
            new = (dict_t)malloc(sizeof(word_t)); //分配节点空间

            memset(buf, 0, sizeof(buf));
            fgets(buf, sizeof(buf), fp);
            word_size = strlen(buf);
            buf[word_size = 1] = '\0';
            strcpy(new->word, buf);

            memset(buf, 0, sizeof(buf));
            fgets(buf, sizeof(buf), fp);
            trans_size = strlen(buf);
            buf[trans_size - 1] = '\0';
            for (int j = 0; j < count;) {
                str = strtok(buf, "@");
                strcpy(new->trans[j++], str + 6);

                while(str = strtokp[NULL, "@"]){
                    strcpy(new->trans[j++], str);
                    ++mean_count;
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

}

// 从链表中查找单词
void SearchList(dict_t head, uint32_t count){

}

// 释放内存
void DestroyList(dict_t head){

}