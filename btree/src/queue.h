#ifndef _QUEUE_H_
#define _QUEUE_H_

// btree.hの構造体NODEを使っている
#include "btree.h"

// キューのノード
typedef struct queue_node {
    struct queue_node *next;   // 次のノード
    NODE *data;
} qNODE;

void make_queue(qNODE**, qNODE**);
qNODE *make_qnode (void);
int is_empty (qNODE*, qNODE*);
void enqueue (qNODE**, qNODE**, NODE*);
NODE *dequeue (qNODE**, qNODE**);

#endif
