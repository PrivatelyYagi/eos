int pipefd[2];
if (pipe(pipefd) < 0) {
  perror("pipe");
  exit(-1);
}
pid_t pid = fork();
if (pid < 0) {
  perror("fork");
  exit(-1);
} else if (pid == 0) {
  // 子プロセス
  close(pipefd[0]); //読み込みをクローズ

  char *s = "send from child";
  write(pipefd[1], s, strlen(s));


  close(pipefd[1]);
  return 0;
} else {
  // 親プロセス
  close(pipefd[1]); //書き込みをクローズ

  char buf[128];
  read(pipefd[0], buf, sizeof buf);
  printf("parent=[%s]\n", buf);

  close(pipefd[0]);
  return 0;
}