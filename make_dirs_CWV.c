#include "mergetars.h"

// this is a macro
// #define _POSIX_C_SOURCE 200809L

/*
General Notes:

Order of operations version 1:
1. extract from a tarfile
2. store this away in the mega struct
3. "expand" and make the equivalent directory by filling out with data from the mega struct.

Order of operations version 2:
1. For each tarfile make an equivalent directory.
2. extract the contents of this tarfile into this directory - this is the "expansion".
3. tar -xvf public_html-14-09-12.tar -C mkdtemp("the equivalent directory for the tar archive").
    * probably using: mkdtemp().

All commands are exec with fork(), ececl() and wait():
  - we need to implement the systemcalls?

we can get the size in bytes and mod time from stat() e.g:
>>> stat sample_1.tar:
>>> File: sample_1.tar
>>> Size: 10240           Blocks: 24         IO Block: 4096   regular file
>>> Device: eh/14d  Inode: 13510798882194159  Links: 1
>>> Access: (0777/-rwxrwxrwx)  Uid: ( 1000/fraser_p)   Gid: ( 1000/fraser_p)
>>> Access: 2020-09-28 13:26:57.692909200 +0800
>>> Modify: 2020-09-28 13:26:46.969176800 +0800
>>> Change: 2020-09-28 13:26:46.969176800 +0800

* can we "parse" this like an eventfile???
*/


// General Questions:
/*
* How is the modification date displayed? and will the discrepancy between "our" -tvf and "Chris"
  - is it o to use stat() for this??
*/





/*
1. char *mkdtemp(char *template);
  ERRORS
  EINVAL The last six characters of template were not XXXXXX.  Now template is unchanged.
*/
/*
execl(  "./goodchessmove",      // on-disk location of program
                "goodchessmove",        // its argv[0]
                gamestate,              // its argv[1]
                outputfile,             // its argv[2]
                NULL
            );
*/


/*
This function reads in the output from tar -xvf tarfile.tar
into a unique, temporary directory.
*/

// WITHOUT FORK - EXTRAT INTO mkdirtemp():
/*
int make_an_expanded_dir(char tarfile[]) {
  // this function is supposed to extract a tar archive into the result of "mkdtemp(template)"
  // char *temp_dir = mkdtemp(template); // Segmentation fault (core dumped)

  // the template for the temporary directory:
  char template[] = "/tmp/file-XXXXXX";
  // the temporary directory:
  char *temp_dir = mkdtemp(template);
  // the cmd line refference to the tarfile:
  // printf("error 3\n");
  // char *the_tarfile = strcat(tarfile, ".tar");

  // this needs to be beefed up
  if(temp_dir == NULL) {
    perror("mkdtemp failed: ");
    return 0;
  }

  // the location of tar is found by the cmdline thing type tar
  // do we want to frok() an excel()???

  execl("/usr/bin/tar",
        "tar",
        "-xf", // -xvf for testing!
        tarfile, // this is actually tar_2.tar
        "-C",
        temp_dir,
        NULL
  );
}
*/




// WITHOUT FORK - EXTRACT INTO "NORMAL" DIRECTORY:
/*
int make_an_expanded_dir(char tarfile[]) {
  // this function is supposed to extract a tar archive into the result of "mkdtemp(template)"
  // char *temp_dir = mkdtemp(template); // Segmentation fault (core dumped)

  // the template for the temporary directory:
  printf("error 1\n");
  char template[] = "/tmp/file-XXXXXX";
  // the temporary directory:
  printf("error 2\n");
  char *temp_dir = mkdtemp(template);
  // the cmd line refference to the tarfile:
  // printf("error 3\n");
  // char *the_tarfile = strcat(tarfile, ".tar");

  // this needs to be beefed up
  if(temp_dir == NULL) {
    perror("mkdtemp failed: ");
    return 0;
  }

  // the location of tar is found by the cmdline thing type tar
  // do we want to frok() an excel()???

  printf("before the execl()\n");

  execl("/usr/bin/tar",
        "tar",
         "-xvf",
         tarfile, // this is actually tar_2.tar
         "-C",
         "TARGET_DIR/",
         NULL
  );
}
*/





// WITH FORK - EXTRACTING INTO TEMPORARY DIR:
int make_an_expanded_dir_with_fork(char tarfile[]) {
  // the template for the temporary directory:
  printf("error 1\n");
  char template[] = "/tmp/file-XXXXXX";
  // the temporary directory:
  printf("error 2\n");
  char *temp_dir = mkdtemp(template);

  // this needs to be beefed up
  if(temp_dir == NULL) {
    perror("mkdtemp failed: ");
    return 0;
  }

  // does this reffer to the child pid ??
  int pid = fork();
  printf("child pid: %i\n", getpid());
  printf("parent pid: %i\n", getppid());
  switch (pid) {
    case -1 :
      printf("fork() failed\n"); // process creation failed
      exit(EXIT_FAILURE);
      break;

    case 0: // new child process
      printf("child is pid=%i\n", getpid() );

      printf("prior to the execl()\n");

      // this is the child process:
      execl("/usr/bin/tar",
            "tar",
             "-xvf",
             tarfile,
             "-C",
             temp_dir,
             NULL
      );

      exit(EXIT_SUCCESS);
      break;

    default: { // original parent process
      int child;
      int status;
      printf("parent waiting\n");
      child = wait( &status );
      printf("process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
      exit(EXIT_SUCCESS);
      break;
    }
  }

  return pid;
}

// this will probably need to be a doubble pointer
// dynamic memory allocation for number of tarfiles.
// char **tarfiles = NULL;
int make_all_expanded_dirs(char **tarfiles) {
  for (int i = 0; i < NUM_TARFILES; ++i) {
    int status;

    int pid = (int) make_an_expanded_dir_with_fork(tarfiles[i]);

    if (pid < 0) {
      break;
    }
  }

  wait( &status );
  printf("pid = %i has terminated\n", pid);
}




int main(int argc, char* argv[]) {
  if (argc != 1) {
    printf("need 2 args...\n");
    return 0;
  } else {
    char *tarfile_names = malloc((argc-1) * sizeof(char));
    for (int t = 0; t < argc; ++t) {
      tarfile_names[t] = argv[t];
    }
    // make_an_expanded_dir_with_fork("tar_2.tar");
    // make_an_expanded_dir("tar_2.tar");
    make_all_expanded_dirs(tarfile_names);
    printf("something happened...\n");
  }
}

























































/*

int make_all_expanded_dirs(char tarfile[]) { // this should be a list of all tarfiles:

  for (int t = 0; t < MAX_TARFILES + 1, ++t) {
    int status;
    int pid = make_an_expanded_dir(tarfile);
    if (pid < 0) {
      break;
    }
    wait(&status);
  }


  // the template for the temporary directory:
  printf("error 1\n");
  char template[] = "/tmp/file-XXXXXX";
  // the temporary directory:
  printf("error 2\n");
  char *temp_dir = mkdtemp(template);
  // the cmd line refference to the tarfile:
  // printf("error 3\n");
  // char *the_tarfile = strcat(tarfile, ".tar");

  // this needs to be beefed up
  if(temp_dir == NULL) {
    perror("mkdtemp failed: ");
    return 0;
  }

  int pid = fork();
  switch (pid) {
    case -1 :
      printf("fork() failed\n"); // process creation failed
      exit(EXIT_FAILURE);
      break;

    case 0: // new child process
      printf("child is pid=%i\n", getpid() );
      // this is where we do the ececlp()?
      exit(EXIT_SUCCESS);
      break;

    default: { // original parent process
      int child
      int status;
      printf("parent waiting\n");
      child = wait( &status );
      printf("process pid=%i terminated with exit status=%i\n",
      child, WEXITSTATUS(status) );
      exit(EXIT_SUCCESS);
      break;
    }
  }

  printf("prior to the execl()\n");
  execl("/usr/bin/tar",
  "-xvf",
  // "-xf",
  tarfile,
  "-C",
  temp_dir,
  NULL);

  printf("after the execl()\n");

}
*/
