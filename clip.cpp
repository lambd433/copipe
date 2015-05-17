#include "clip.h"

void setClip(std::string text){
  int fd[2]; //file desc
  int pid;
  pipe(fd);

  if((pid=fork()) == 0){ // child
 
    close(fd[0]);
    write(fd[1], text.c_str(), text.size());
    exit(0);
    
  }else{ //parent(pbcopy)
    close(fd[1]);
    int stat;
    waitpid(pid, &stat, 0);
    dup2(fd[0], STDIN_FILENO);
    execlp("pbcopy", "pbcopy", (char *) NULL);    
  }
}

std::string getClip(){
  int fd[2]; //file desc
  int pid;
  pipe(fd);
  if((pid=fork()) == 0){ // child
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    execlp("pbpaste", "pbpaste",  (char *) NULL);
    exit(0);
  }else{ //parent
    close(fd[1]);
    int stat;
    char buf[1024];
    waitpid(pid, &stat, 0);
    read(fd[0], buf, 1024);
    // std::cout << "buf = " << buf << std::endl;
    return std::string(buf);
  }    
}
