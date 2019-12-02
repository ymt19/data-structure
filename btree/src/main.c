#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "btree.h"
#include "queue.h"
#include "display.h"

typedef struct {
    char *buffer;
    size_t buffer_len;  // 符号なし整数
    ssize_t input_len;  // 符号付き整数 
} InputBuffer;

// プロンプトの表示
void print_prompt () {
    printf("->");
}

// 受け取ったコマンドを格納する領域の確保
InputBuffer *make_inputbuffer () {
    InputBuffer *inputbuffer = (InputBuffer*) malloc (sizeof(InputBuffer));
    inputbuffer->buffer = NULL;
    inputbuffer->buffer_len = 0;
    inputbuffer->input_len = 0;
    return inputbuffer;
}

// 入力されたコマンドを読み込む
void read_buffer (InputBuffer *inputbuffer) {
    ssize_t bytes_read;
    bytes_read = getline(&(inputbuffer->buffer), &(inputbuffer->buffer_len), stdin);

    // 読み込みに失敗
    if (bytes_read <= 0) {
        printf("command read error.\n");
        exit(EXIT_FAILURE);
    }

    // 改行文字を取り除く
    inputbuffer->input_len = bytes_read-1;
    inputbuffer->buffer[bytes_read-1] = '\0';
}

// メモリ解放
void free_inputbuffer (InputBuffer *inputbuffer) {
    free(inputbuffer->buffer);
    free(inputbuffer);
}

int main (int argc, char *argv[]) {
    NODE *root = new_tree();
    InputBuffer *inputbuffer = make_inputbuffer();

    printf("Add a key to Btree: add [num]\n");
    printf("Display Btree data: print\n");
    printf("End the operation : quit\n");
    while (1) {
        print_prompt();
        read_buffer(inputbuffer);

        // addコマンドを受け取る
        // 木に値を挿入する
        if (!strncmp(inputbuffer->buffer, "add", 3)) {
            inputbuffer->buffer += 3;
            char *end;
            int key = (int)strtol(inputbuffer->buffer, &end, 10);
            if (*end == '\0') {
                insert(&root, key);
                printf("success add tree %d\n", key);
                display_tree(root);
            } else {
                printf("there may be an error in the argument of add\n");
            }
            continue;
        }

        // printコマンド
        // 木の全体を表示する
        if (!strncmp(inputbuffer->buffer, "print", 5)) {
            inputbuffer->buffer += 5;
            printf("display tree.\n");
            display_tree(root);
            continue;
        }

        // quitコマンド
        // 木の操作を終了する
        // ループを抜ける
        if (!strncmp(inputbuffer->buffer, "quit", 4)) {
            break;
        }

        // 指定するコマンドが見つからない場合
        printf("not find command %s\n", inputbuffer->buffer);
    }

    return 0;
}