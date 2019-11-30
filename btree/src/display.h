#ifndef _DISPLAY_H_
#define _DISPLAY_H_

// ここで定義する関数をbtree.cで定義しようとしたが
// btree.hとqueue.hで相互に循環的に参照しなければならず
// 新しくファイルを作り, それぞれをincludeした
#include "btree.h"
#include "queue.h"

void display_tree (NODE*);
void bfs (NODE*, int, int, qNODE*, qNODE*);
void display_node (NODE*);

#endif