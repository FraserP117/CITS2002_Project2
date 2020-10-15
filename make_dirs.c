#include "mergetars.h"

// tarfile[] is an index into: extern char **tarfiles;
char* make_a_temporary_dir(char *tarfile) { 

  // tarfile_names = realloc(tarfile_names, ntarfiles * sizeof(tarfile_names[0]));

  // the template for the temporary directory:
  char template[] = "/tmp/file-XXXXXX";
  // the temporary directory:
  char *temp_dir = mkdtemp(template);

  // this needs to be beefed up
  if(temp_dir == NULL) {
    perror("mkdtemp failed: ");
    return NULL;
    // correct perror code
  }

  return strdup(temp_dir);
}



























// void make_an_expanded_dir(char *tarfile) { // test version
//
//   // tarfile_names = realloc(tarfile_names, ntarfiles * sizeof(tarfile_names[0]));
//
//   // the template for the temporary directory:
//   char template[] = "/tmp/file-XXXXXX";
//   // the temporary directory:
//   char *temp_dir = mkdtemp(template);
//
//   // this needs to be beefed up
//   if(temp_dir == NULL) {
//     perror("mkdtemp failed: ");
//     printf("NULL \n");
//     // correct perror code
//   }
//
//   printf("temp_dir is: %s \n", temp_dir);
//   printf("\n");
// }

// int main(int argc, char* argv[]) {
//
//   if (argc < 2) {
//     printf("need 3 cmdline args \n");
//     exit(EXIT_FAILURE);
//   } else {
//     ntarfiles = argc - 1;
//     tarfile_names = realloc(tarfile_names, ntarfiles * sizeof(tarfile_names[0]));
//
//     for (int i = 0; i < ntarfiles; ++i) {
//       tarfile_names[i] = argv[i + 1];
//     }
//
//     make_an_expanded_dir(tarfile_names[0]);
//     exit(EXIT_SUCCESS);
//   }
// }






















// // tarfile[] is an index into: extern char **tarfiles;
// int make_an_expanded_dir(char tarfile[]) {
//
//   tarfile_names = realloc(tarfile_names, ntarfiles * sizeof(tarfile_names[0]));
//
//   // the template for the temporary directory:
//   char template[] = "/tmp/file-XXXXXX";
//   // the temporary directory:
//   char *temp_dir = mkdtemp(template);
//
//   // this needs to be beefed up
//   if(temp_dir == NULL) {
//     perror("mkdtemp failed: ");
//     return 0;
//   }
//
//   // does this reffer to the child pid ??
//   int pid = fork();
//   printf("child pid: %i\n", getpid());
//   printf("parent pid: %i\n", getppid());
//   switch (pid) {
//     case -1 :
//       printf("fork() failed\n"); // process creation failed
//       exit(EXIT_FAILURE);
//       break;
//
//     case 0: // new child process
//       printf("child is pid=%i\n", getpid() );
//
//       printf("prior to the execl()\n");
//
//       // this currently makes a temporary directory that holds the contents of the
//       // input tar archive.
//       execl("/usr/bin/tar",
//             "tar",
//              "-xvf",
//              tarfile,
//              "-C",
//              temp_dir,
//              NULL
//       );
//
//       exit(0); // exit(pid) instead of "EXIT_SUCCESS"??
//       break;
//
//     default: { // original parent process
//       int child;
//       int status;
//       printf("parent waiting\n");
//       child = wait( &status ); // is it the case the the parent is doing the "waiting"?
//       printf("process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//       exit(EXIT_SUCCESS); //exit the parent pid
//       break;
//     }
//
//     int status;
//     int pid = (int) make_an_expanded_dir(tarfile_names[i]);
//
//     // tarfile_names[i] = (char*)tarfile_names[i];
//
//     if (pid < 0) {
//       break;
//     }
//
//     wait(&status);
//     printf("pid = %i has terminated\n", pid);
//   }
//
//   return pid;
// }




/*
void make_expanded_dirs(int ntarfiles, char **tarfile_names) {
  // how to get the number of tarfiles for the loop
  for (int i = 0; i < ntarfiles; ++i) {
    int status;
    int pid = (int) make_an_expanded_dir(tarfile_names[i]);

    // tarfile_names[i] = (char*)tarfile_names[i];

    if (pid < 0) {
      break;
    }

    wait(&status);
    printf("pid = %i has terminated\n", pid);
  }
}
*/
