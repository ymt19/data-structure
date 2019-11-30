#ifndef _BTREE_H_
#define _BTREE_H_

// 1つの節のキー数を決める最小次数
// MIN_DIGREE >= 2 が条件
// MIN_DEGREE-1 <= (キーの個数) <= MIN_DEGREE*2-1
// 根の場合のみ、キーの個数は少なくとも1つ
// MIN_DEGREE <= (子の個数) <= MINDEGREE*2
#define MIN_DEGREE 5

typedef int KEY;

// ノードの種類
typedef enum {
    INTERNAL,       // 内部節
    LEAF,           // 葉
} NodeKind;

typedef struct node {
    NodeKind nodekind;                  // nodeの種類
    int count_keys;                // キーの数
    struct node *childs[MIN_DEGREE*2];     // 子へのポインタ
    KEY keys[MIN_DEGREE*2-1];                // キーの値
} NODE;

NODE *search (NODE*, KEY);
NODE *new_node (void);
NODE *new_tree (void);
void split_tree (NODE*, int, NODE*);
void insert (NODE**, KEY);
void recursion_insert (NODE*, KEY);

#endif
