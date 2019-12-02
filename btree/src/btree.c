#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

// keyを探索する
// nodeはその木の根
// 成功したらkeyのある節を返す
// 失敗したらNULLを返す
NODE *search(NODE *node, KEY key) {
    // // 線形探索
    // int i = 0;
    // // 節からkeyがどの部分木に入るのか
    // // 調べる
    // while (i < node->count_keys && key > node->keys[i]) {
    //     i++;
    // }

    // 二分探索
    // keyがどの部分木にいるのかを調べる
    int left = -1, right = node->count_keys-1;
    while (left+1 < right) {
        int mid = (left+right)/2;
        if (key <= node->keys[mid]) {
            right = mid;
        } else {
            if (left == mid) {
            // nodeの最後尾のキーよりもkeyが多きとき
                break;
            }
            left = mid;
        }
    }

    // node->count_keysが1個の時
    // node->keysの最後よりkeyが大きい時
    if (key > node->keys[right]) {
        right += 1;
    }

    // 探索成功
    if (right < node->count_keys && key == node->keys[right]) {
        return node;
    }

    if (node->nodekind == LEAF) {
        // 探索失敗
        return NULL;
    } else {
        return search(node->childs[right], key);
    }
}

// Btreeに入る最も最小のキーを返す
// 根を引数にとる
KEY find_minkey (NODE *node) {
    while (node->nodekind == INTERNAL) {
        node = node->childs[0];
    }
    return node->keys[0];
}

// 新しくノードを作る
NODE *make_node (void) {
    NODE *node = (NODE*)malloc(sizeof(NODE));
    if (node == NULL) {
        printf("memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    return node;
}

// 新しく木を作る
NODE *new_tree (void) {
    NODE *root = make_node();
    root->nodekind = LEAF;
    root->count_keys = 0;
    return root;
}

// 飽和したノードを分割する
// 分割するノードの親は不飽和であると仮定する
// oldercがparentの子であり分割されるノードである
// order(zero-based indexing)がparentに入る子のoldercの番号
void split_tree (NODE *parent, int order, NODE *olderc) {
    // oldercが分割された片方を格納する
    NODE *youngerc = make_node();
    youngerc->nodekind = olderc->nodekind;
    youngerc->count_keys = MIN_DEGREE-1;

    // oldercの後半部をyoungercに移す
    // キーを移す
    for (int i = 0; i < MIN_DEGREE-1; i++) {
        youngerc->keys[i] = olderc->keys[i+MIN_DEGREE];
    }
    // 子を移す
    if (olderc->nodekind == LEAF) {
        for (int i = 0; i < MIN_DEGREE; i++) {
            youngerc->childs[i] = olderc->childs[i+MIN_DEGREE];
        }
    }

    // oldercの情報を整理する
    olderc->count_keys = MIN_DEGREE-1;

    // parentにoldercの中央キーを挿入する
    // oldercの中央キーを挿入する場所を空ける
    for (int i = parent->count_keys-1; i >= order; i--) {
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[order] = olderc->keys[MIN_DEGREE-1];

    // parentの子にyoungercを挿入する
    for (int i = parent->count_keys; i > order; i--) {
        parent->childs[i+1] = parent->childs[i];
    }
    parent->childs[order+1] = youngerc;

    // parentのキーの個数を調整する
    parent->count_keys += 1;
}

// B木へキーを挿入する
void insert (NODE  **root, KEY key) {
    if ((*root)->count_keys == (MIN_DEGREE*2-1)) {
    // 根が飽和状態の時に根を分割する
    // この場合のみ高さが増える

        NODE *new_root = make_node();
        new_root->nodekind = INTERNAL;
        new_root->count_keys = 0;
        new_root->childs[0] = *root;
        split_tree(new_root, 0, *root);
        // 根を更新する
        *root = new_root;
        recursion_insert(*root, key);
    } else {
        recursion_insert(*root, key);
    }
}

// nodeにkeyを挿入する
// nodeが非飽和であることが前提
void recursion_insert (NODE *node, KEY key) {
    // node->keysは[0]~[node->count_keys-1]にkeyが入っている
    int i = node->count_keys-1;
    if (node->nodekind == LEAF) {
    // nodeが葉の時
    // keyを挿入する
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i -= 1;
        }
        i += 1;
        node->keys[i] = key;
        node->count_keys += 1;
    } else {
    // nodeが内部節の時
    // 再帰的に木を降りる
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i += 1;

        // 降りる節が飽和状態だったら分割する
        // nodeは飽和状態である
        if (node->childs[i]->count_keys == (MIN_DEGREE*2-1)) {
            split_tree(node, i, node->childs[i]);
            // 子の中央キーがkeyより小さい場合
            if (key > node->keys[i]) {
                i += 1;
            }
        }
        recursion_insert(node->childs[i], key);
    }
}
