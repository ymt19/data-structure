#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "btree.h"

// 新しいキューを作る
void make_queue (qNODE **head, qNODE **tail) {
    *head = NULL;
    *tail = NULL;
}

// 新しいキューのノードを作る
qNODE *make_qnode (void) {
    qNODE *new_qnode = (qNODE*) malloc (sizeof(qNODE));
    if (new_qnode == NULL) {
        printf("memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    return new_qnode;
}

// キューが空かどうか判定する
int is_empty (qNODE *head, qNODE *tail) {
    if (head == NULL && tail == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// キューの最後尾にB木のノードをenqueueする
void enqueue (qNODE **head, qNODE **tail, NODE *data) {
    qNODE *new_qnode = make_qnode();
    new_qnode->data = data;
    new_qnode->next = NULL;

    if (is_empty(*head, *tail)) {
    // キューが空の時
        *head = new_qnode;
        *tail = new_qnode;
    } else {
        (*tail)->next = new_qnode;
        *tail = new_qnode;
    }
}

// キューの先頭のB木のノードをdequeueする
// そのノードを返す
NODE *dequeue (qNODE **head, qNODE **tail) {
    // キューが空の時
    if (is_empty(*head, *tail)) {
        return NULL;
    }

    qNODE *head_data = *head;
    if (*head == *tail) {
    // キューに1つのデータしかない時
        *head = NULL;
        *tail = NULL;
    } else {
        *head = (*head)->next;
    }

    NODE *ret_data = (head_data)->data;
    free(head_data);
    return ret_data;
}
