#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){

  int pipefd[2]; // パイプ用ファイルディスクリプタ

  if (pipe(pipefd) < 0) {
    perror("pipe");
    exit(-1);
  }

  pid_t pid = fork(); // int(typedef int pid_t)

  if (pid < 0) { //エラー処理

    perror("fork");
    exit(-1);

  } else if (pid == 0) { // ( == 子プロセス )

    close(pipefd[1]); // 書き込みを閉じる
    int buf;
    read(pipefd[0], buf, sizeof buf);
    printf("parent=[%d]\n", buf);

    close(pipefd[0]);
    return 0;

  } else {

    close(pipefd[0]); // 読み込みを閉じる
    int *buf = 1;
    write(pipefd[1], buf, strlen(buf));

    close(pipefd[1]);
    return 0;

  }
}