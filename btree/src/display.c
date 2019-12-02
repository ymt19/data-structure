#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "btree.h"
#include "queue.h"

// 木全体を幅優先で表示する
// 高さごとに改行する
void display_tree (NODE *root) {
    qNODE *head, *tail;
    make_queue(&head, &tail);
    bfs(root, 1, 0, head, tail);
}

// 幅優先探索
// 表示するノードを決める
// 着目している高さの残りのノードの個数now
// 着目している層より1つ深いノードの個数next
void bfs (NODE *node, int now, int next, qNODE *head, qNODE *tail) {
    if (node->nodekind == INTERNAL) {
    // 内部節の時
        // 持つ子をキューに入れる
        for (int i = 0; i < node->count_keys+1; i++) {
            printf("%d\n", node->childs[i]->keys[0]);
            enqueue(&head, &tail, node->childs[i]);
        }
        display_node(node);
        next += node->count_keys+1;
        now--;

        // 次に見るノードをキューから取り出す
        if ((node = dequeue(&head, &tail)) == NULL) {
            printf("queue error.\n");
            exit(EXIT_FAILURE);
        }

        // nowが0なら高さを変える
        if (now == 0) {
            printf("\n");
            bfs(node, next, 0, head, tail);
        } else {
            bfs(node, now, next, head, tail);
        }
    } else {
    // 葉の時
    // キューに入れる子が無い
        display_node(node);
        if ((node = dequeue(&head, &tail)) == NULL) {
            printf("\n");
            return;
        }
        now--;
        bfs(node, now, next, head, tail);
    }
}

// ノードを受け取り
// そのノードが持つキーを出力する
void display_node (NODE *node) {
    printf("|");
    for (int i = 0; i < node->count_keys; i++) {
        if (i == (node->count_keys-1)) {
            printf(" %d ", node->keys[i]);
        } else {
            printf(" %d", node->keys[i]);
        }
    }
    printf("|");
}