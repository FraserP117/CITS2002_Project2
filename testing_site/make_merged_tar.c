#include "mergetars.h"
// #include "merge_check.c"

//   /*
//   The inputs are merged to form the output according to the following definitions and rules:
//
//     - Two or more files from different archives are considered the same file if they have the same
//       relative pathname (including the name of the directory holding the file and the filename itself).
//
//     - If from different archives, the files "project2/src/mergetars.c" and "project2/src/mergetars.c"
//       are considered the same file. In contrast, "monday/project2/src/mergetars.c" and
//       "wednesday/project2/src/mergetars.c" are considered different files.
//
//     - Two or more files from different archives with the same relative pathname, are considered
//       different versions of the same file. The output archive should contain just the latest of all such versions.
//
//     - If two or more files have the same modification time, then the largest of these should be copied.
//
//     - If two or more files have the same modification time and size, the file from the latest tarfile
//     (on the command-line) should be copied.
//
//     - All other files with different relative pathnames are considered different files.
//       The output archive should contain one copy of each different file.
//   */
//   // and actually perform the merging.
// }

/*
only make one temp directory.

copy the one extracted archive into this temporary directory.

Now compare all the remaining extracted archives against the current
contents of the temporary directory.
*/

void merge_tar_archives(char **tarfile_names) { // get the size oaf the input as the second arg

  // Extract one archive into the output directory.
  int pid = fork();

  // extract the first tar file on the cmdline into the temporary directory:
  // switch on the return values of fork() for the parent:
  switch (pid) {
    case -1 :
      printf("fork() failed\n"); // process creation failed
      exit(EXIT_FAILURE);
      break;

    case 0: {// new child process
      // char *output_dir = make_an_expanded_dir(tarfile_names[0]); // may need "const char*" dereference tarfile_names[0]?
      char *output_dir = malloc(sizeof make_an_expanded_dir(tarfile_names[0]));
      strcpy(output_dir, make_an_expanded_dir(tarfile_names[0]));

      printf("\n");
      printf("first case: 0 \n");
      printf("\tparent is pid=%i\n", getppid() );
      printf("\tchild process for %i is pid=%i\n", getppid(), getpid() );

      // do we always have to call execl() to get the child to exec another process from that of the parent?
      // e.g if we "sleep(1)" here; the child will sleep for 1 sec while the parent does not and this was done without execl()...

      // the child will now extract the contents of the
      // first input tar archive into the temporary directory.

      printf("\tfirst execl() \n");
      fflush(stdout);
      execl("/usr/bin/tar",
            "tar",
             "-xf",
             tarfile_names[0],
             "-C",
             output_dir,
             NULL
      );
      perror("failed: execl\n");
      fflush(stdout);
      printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
      printf("\tend execl() 1 \n");
      fflush(stdout);

      // exit(pid); // exit(pid) instead of "EXIT_SUCCESS"??

      // int child;
      // int status;
      // printf("parent %i waiting\n", getppid() );
      // child = wait( &status ); // is it the case the the parent is doing the "waiting"?
      // printf("child process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
      // // exit(EXIT_SUCCESS); //exit the parent pid

      break;
    }

    default: { // original parent process
      printf("\n");
      printf("SINGLE TAR ARCHIVE EXTRACTION: \n");
      printf("\n");

      int child;
      int status; // the parent's status
      printf("\tparent %i waiting\n", getpid() );
      child = wait( &status ); // is it the case the the parent is doing the "waiting"?
      // exit(child); // ??
      printf("\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
      // exit(EXIT_SUCCESS); //exit the parent pid
      break;
    }
  }


// Now create a second temporary directory: "tmp_dir" and while there are remaining tarred archives:
// extract one of these remaining archives into "tmp_dir", compare the contents of "tmp_dir" against the contents of "output_dir"
// and copy across the requisite material form "tmp_dir".

  for (int i = 0; i < ntarfiles - 1; ++i) {

    int pid = fork();

    // extract the first tar file on the cmdline into the temporary directory:
    switch (pid) {
      case -1 :
        printf("fork() failed\n"); // process creation failed
        exit(EXIT_FAILURE);
        break;

      case 0: {// new child process
        char *tmp_dir = malloc(sizeof make_an_expanded_dir(tarfile_names[i + 1]));
        strcpy(tmp_dir, make_an_expanded_dir(tarfile_names[i + 1]));

        printf("\n");
        printf("second case: 0 \n");
        printf("\tparent is pid=%i\n", getppid() );
        printf("\tchild process for %i is pid=%i\n", getppid(), getpid() );

        // the child will now extract the contents of the
        // remaining input tar archives into the temporary directory.
        printf("\tsecond execl() \n");
        fflush(stdout);
        execl("/usr/bin/tar",
              "tar",
               "-xf",
               tarfile_names[i + 1],
               "-C",
               tmp_dir,
               NULL
        );
        perror("failed: execl\n");
        fflush(stdout);
        printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
        printf("\tend execl() 2 \n");
        fflush(stdout);

        // does this ever happen???
        // exit(pid);

        // int child;
        // int status;
        // printf("\tparent %i waiting\n", getppid() );
        // child = wait( &status ); // is it the case the the parent is doing the "waiting"?
        // printf("\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
        // exit(EXIT_SUCCESS); //exit the parent pid
        // printf("\n");

        break;
      }

      default: { // original parent process
        printf("\n");
        printf("ALL OTHER TAR ARCHIVE EXTRACTIONS: \n");
        printf("\n");
        int child;
        int status;
        printf("\tparent %i waiting\n", getpid() );
        child = wait( &status ); // is it the case the the parent is doing the "waiting"?
        // exit(child);
        printf("\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
        // exit(EXIT_SUCCESS); //exit the parent pid
        break;
      }

      // /*
      // use DIR *opendir(const char *dirname);
      // to return a pointer for the output_dir and temp_dir (respectively)
      //
      // use these pointers to compare the contents of output_dir and temp_dir with
      // te readdir() - struct dirent *readdir(DIR *dirp); - function.
      // */
      //
      // // this is a pointer to a "dirent" structure representing the next directory
      // // entry in the directory stream pointed to by out_dir:
      // // this will point to the call to readdir() for out_dir
      // struct dirent *out_dir_dirent_pointer;
      // // this is the pointer to the contents of the output dir:
      // DIR *out_dir = opendir(output_dir);
      //
      //
      // // this is a pointer to a "dirent" structure representing the next directory
      // // entry in the directory stream pointed to by tp_dir:
      // // this will point to the call to readdir() for otp_dir
      // struct dirent *tmp_dir_dirent_pointer;
      // // this is the pointer to the contents of the tmporary dir:
      // DIR *tp_dir = opendir(tmp_dir);
      //
      // // use opendir() and readdir() or opendir() and stat()?
      // if(out_dir == NULL) {
      //   perror("out_dir was NULL. \n"); // what is this "progname"?
      //   exit(EXIT_FAILURE);
      // }
      //
      // while((out_dir_dirent_pointer = readdir(out_dir)) != NULL) {
      //   while((tmp_dir_dirent_pointer = readdir(tp_dir)) != NULL) {
      //     // to check if t versions of the same file:
      //     // check if out_dir_dirent_pointer.d_name == tmp_dir_dirent_pointer.d_name
      //     // may need:
      //     // out_dir_dirent_pointer->d_name == tmp_dir_dirent_pointer->d_name
      //     if (is_same_file(out_dir_dirent_pointer->d_name, tmp_dir_dirent_pointer->d_name)) {
      //       printf("these files do have the same file path. \n");
      //     }
      //   }
      // }
    }
  }
}



// void manychessmoves(int N, char gamestate[], char goodmove[]) {
//   for (int i = 0; i < N; ++i) {
//     int status;
//
//     int pid = start_onemove(i, gamestate, goodmove);
//
//     if (pid < 0) {
//       break;
//     }
//
//     wait( &status );
//     printf("pid = %i has terminated\n", pid);
//   }
// }


// FOR TESTING:
// void merge_tar_archives(char **tarfile_names) {
//   make_an_expanded_dir(tarfile_names[0]);
// }


int main(int argc, char* argv[]) {

  if (argc < 3) {
    printf("\n");
    printf("need 3 cmdline args \n");
    exit(EXIT_FAILURE);
  } else {
    ntarfiles = argc - 1;
    // char **tarfile_names = NULL; // this is in globals.c
    tarfile_names = realloc(tarfile_names, ntarfiles * sizeof(tarfile_names[0]));

    printf("vital stats for the program: \n");
    if (tarfile_names == NULL) {
      printf("\n");
      printf("tarfile_names DID NOT get allocated! \n");
      printf("\n");
    } else {
      printf("\n");
      printf("tarfile_names were allocated. \n");
      printf("\n");
    }

    for (int i = 0; i < ntarfiles; ++i) {

      tarfile_names[i] = argv[i + 1];

    }

    merge_tar_archives(tarfile_names);
    printf("/n");
    // int child;
    // int status;
    // printf("parent %i waiting\n", getppid() );
    // child = wait( &status ); // is it the case the the parent is doing the "waiting"?
    // printf("child process pid=%i - of parent: %i - terminated with exit status=%i\n", child, getppid(), WEXITSTATUS(status) );
    // // exit(EXIT_SUCCESS); //exit the parent pid
  }
}















// void merge_tar_archives(char **tarfile_names) {
//
//   // debug stuff:
//   printf("EXEC OF 'merge_tar_archives'\n");
//   printf("ntarfiles: %i\n", ntarfiles);
//   fflush(stdout);
//   for (int j = 0; j < 2; ++j) {
//     printf("%s\n", tarfile_names[j]);
//     fflush(stdout);
//   }
//
//   // Extract one archive into the output directory.
//   char *output_dir = make_an_expanded_dir(tarfile_names[0]); // may need "const char*"
//   int pid = fork();
//
//   // extract the first tar file on the cmdline into the temporary directory:
//   switch (pid) {
//     case -1 :
//       printf("fork() failed\n"); // process creation failed
//       exit(EXIT_FAILURE);
//       break;
//
//     case 0: // new child process
//       printf("child is pid=%i\n", getpid() );
//
//       // the child will now extract the contents of the
//       // first input tar archive into the temporary directory.
//       execl("/usr/bin/tar",
//             "tar",
//              "-xvf",
//              tarfile_names[0],
//              "-C",
//              output_dir,
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
//   }
//
//
// // Now create a second temporary directory: "tmp_dir" and while there are remaining tarred archives:
// // extract one of these remaining archives into "tmp_dir", compare the contents of "tmp_dir" against the contents of "output_dir"
// // and copy across the requisite material form "tmp_dir".
//
//   for (int i = 0; i < ntarfiles - 1; ++i) {
//
//     char *tmp_dir = make_an_expanded_dir(tarfile_names[i + 1]);
//     int pid = fork();
//
//     // extract the first tar file on the cmdline into the temporary directory:
//     switch (pid) {
//       case -1 :
//         printf("fork() failed\n"); // process creation failed
//         exit(EXIT_FAILURE);
//         break;
//
//       case 0: // new child process
//         printf("child is pid=%i\n", getpid() );
//
//         // the child will now extract the contents of the
//         // remaining input tar archives into the temporary directory.
//         execl("/usr/bin/tar",
//               "tar",
//                "-xvf",
//                tarfile_names[i + 1],
//                "-C",
//                tmp_dir,
//                NULL
//         );
//         exit(0); // exit(pid) instead of "EXIT_SUCCESS"??
//         break;
//
//       default: { // original parent process
//         int child;
//         int status;
//         printf("parent waiting\n");
//         child = wait( &status ); // is it the case the the parent is doing the "waiting"?
//         printf("process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//         exit(EXIT_SUCCESS); //exit the parent pid
//         break;
//       }
//
//       /*
//       use DIR *opendir(const char *dirname);
//       to return a pointer for the output_dir and temp_dir (respectively)
//
//       use these pointers to compare the contents of output_dir and temp_dir with
//       te readdir() - struct dirent *readdir(DIR *dirp); - function.
//       */
//
//       // void list_directory(char *dirname) {
//       //   DIR *dirp;
//       //   struct dirent *dp;
//       //   dirp = opendir(dirname);
//       //
//       //   if(dirp == NULL) {
//       //     perror( progname );
//       //     exit(EXIT_FAILURE);
//       //   }
//       //
//       //   while((dp = readdir(dirp)) != NULL) {
//       //     printf( "%s\n", dp->d_name );
//       //     // do stuff...
//       //   }
//       //   closedir(dirp);
//       // }
//
//       // this is a pointer to a "dirent" structure representing the next directory
//       // entry in the directory stream pointed to by out_dir:
//       // this will point to the call to readdir() for out_dir
//       struct dirent *out_dir_dirent_pointer;
//       // this is the pointer to the contents of the output dir:
//       DIR *out_dir = opendir(output_dir);
//
//
//       // this is a pointer to a "dirent" structure representing the next directory
//       // entry in the directory stream pointed to by tp_dir:
//       // this will point to the call to readdir() for otp_dir
//       struct dirent *tmp_dir_dirent_pointer;
//       // this is the pointer to the contents of the tmporary dir:
//       DIR *tp_dir = opendir(tmp_dir);
//
//       // the dirent struct:
//       // struct dirent {
//       //   ino_t          d_ino;       /* Inode number */
//       //   off_t          d_off;       /* Not an offset; see below */
//       //   unsigned short d_reclen;    /* Length of this record */
//       //   unsigned char  d_type;      /* Type of file; not supported
//       //                                         by all filesystem types */
//       //   char           d_name[256]; /* Null-terminated filename */
//       // };
//
//       // use opendir() and readdir() or opendir() and stat()?
//       if(out_dir == NULL) {
//         perror("out_dir was NULL. \n"); // what is this "progname"?
//         exit(EXIT_FAILURE);
//       }
//
//       while((out_dir_dirent_pointer = readdir(out_dir)) != NULL) {
//           while((tmp_dir_dirent_pointer = readdir(tp_dir)) != NULL) {
//             // to check if t versions of the same file:
//             // check if out_dir_dirent_pointer.d_name == tmp_dir_dirent_pointer.d_name
//             // may need:
//             // out_dir_dirent_pointer->d_name == tmp_dir_dirent_pointer->d_name
//             if (is_same_file(out_dir_dirent_pointer->d_name, tmp_dir_dirent_pointer->d_name)) {
//               printf("these files do have the same file path. \n");
//               // these are the same files - different versions of the same file.
//               // The output archive should contain just the latest of all such versions of these "subfiles".
//               // must now check the modification time of each file.
//
//             //   if (is_same_mod_time(first_sub_file_path_name, second_sub_file_path_name)) {
//             //     // only upload the latest one.
//             //     // If two or more files have the same modification time, then the largest of these should be copied.
//             //     if (is_same_file_size(first_sub_file_path_name, second_sub_file_path_name)) {
//             //       // If two or more files have the same modification time and size, the file from the latest tarfile
//             //       // (on the command-line) should be copied.
//             //
//             //       // mod_time_for_parent_of_output_dir =
//             //       printf("the mod time for the tarfile that contains \n first_sub_file_path_name: %s", ???);
//             //       printf("the mod time for the tarfile that contains \n second_sub_file_path_name: %s", ???);
//             //     }
//             //   }
//             //
//             // } else {
//             //   printf("these files do NOT have the same file path!!!!!!!\n");
//             // }
//           }
//       }
//
//
//
//
//
//
//
//
//
//       // // these 2 loops go through the output_dir and tmp_dir:
//       // for (int td = 0; td <= ntarfiles-1; ++td) {
//       //
//       //   // this is where we DFS on the temp dir and the remaining - current - archive.
//       //
//       //
//       //   for (int first_file = 0; first_file < nsubfiles; ++first_file) {
//       //     for (int second_file = 0; second_file < nsubfiles; ++second_file) {
//       //       // these are the path names for 2 "sub files" from inside their respective tar archives:
//       //
//       //       // this is our pointer to the tarfile struct:
//       //         // TAR_FILE *tar_files;
//       //
//       //       char *first_sub_file_path_name = tar_files[output_dir_cont]->sub_file_path[first_file];
//       //       char *second_sub_file_path_name = tar_files[td]->sub_file_path[second_file];
//       //
//       //       // FIRST MERGE CONDITION:
//       //       // Two or more files from different archives are considered the same file if they have the same
//       //       // relative pathname (including the name of the directory holding the file and the filename itself).
//       //
//       //       // We want to do all the following checks on files that exist inside their respective tar archives:
//       //
//       //       if (is_same_file(first_sub_file_path_name, second_sub_file_path_name)) {
//       //         printf("these files do have the same file path. \n");
//       //         // these are the same files - different versions of the same file.
//       //         // The output archive should contain just the latest of all such versions of these "subfiles".
//       //         // must now check the modification time of each file.
//       //         if (is_same_mod_time(first_sub_file_path_name, second_sub_file_path_name)) {
//       //           // only upload the latest one.
//       //           // If two or more files have the same modification time, then the largest of these should be copied.
//       //           if (is_same_file_size(first_sub_file_path_name, second_sub_file_path_name)) {
//       //             // If two or more files have the same modification time and size, the file from the latest tarfile
//       //             // (on the command-line) should be copied.
//       //
//       //             // mod_time_for_parent_of_output_dir =
//       //             printf("the mod time for the tarfile that contains \n first_sub_file_path_name: %s", ???);
//       //             printf("the mod time for the tarfile that contains \n second_sub_file_path_name: %s", ???);
//       //           }
//       //         }
//       //
//       //       } else {
//       //         printf("these files do NOT have the same file path!!!!!!!\n");
//       //       }
//       //     }
//       //   }
//       // }
//
//
//
//     }
//   }
// }




















// OG:
// void merge_tar_archives(char **tarfile_names) {
//
//   // debug stuff:
//   printf("EXEC OF 'merge_tar_archives'\n");
//   printf("ntarfiles: %i\n", ntarfiles);
//   fflush(stdout);
//   for (int j = 0; j < 2; ++j) {
//     printf("%s\n", tarfile_names[j]);
//     fflush(stdout);
//   }
//
//   // copy the one extracted archive into this temporary directory.
//   char *temp_dir = make_an_expanded_dir(tarfile_names[0]);
//   int pid = fork();
//
//   // extract the first tar file on the cmdline into the temporary directory:
//   switch (pid) {
//     case -1 :
//       printf("fork() failed\n"); // process creation failed
//       exit(EXIT_FAILURE);
//       break;
//
//     case 0: // new child process
//       printf("child is pid=%i\n", getpid() );
//
//       // the child will now extract the contents of the
//       // first input tar archive into the temporary directory.
//       execl("/usr/bin/tar",
//             "tar",
//              "-xvf",
//              tarfile_names[0],
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
//   }
//
//
//   // Now extract all the remaining tarfiles into the current working directory:
//   // copy the one extracted archive into this temporary directory.
//   // char *temp_dir = make_an_expanded_dir(tarfile_names[0]);
//   for (int i = 0; i < ntarfiles - 1; ++i) {
//
//     int pid = fork();
//
//     // extract the first tar file on the cmdline into the temporary directory:
//     switch (pid) {
//       case -1 :
//         printf("fork() failed\n"); // process creation failed
//         exit(EXIT_FAILURE);
//         break;
//
//       case 0: // new child process
//         printf("child is pid=%i\n", getpid() );
//
//         // the child will now extract the contents of the
//         // remaining input tar archives into the temporary directory.
//         execl("/usr/bin/tar",
//               "tar",
//                "-xvf",
//                tarfile_names[i + 1],
//                NULL
//         );
//
//         exit(0); // exit(pid) instead of "EXIT_SUCCESS"??
//         break;
//
//       default: { // original parent process
//         int child;
//         int status;
//         printf("parent waiting\n");
//         child = wait( &status ); // is it the case the the parent is doing the "waiting"?
//         printf("process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//         exit(EXIT_SUCCESS); //exit the parent pid
//         break;
//       }
//     }
//   }
//
//   // Now perform all the checks between all the
//   // remaining extracted archives against the current
//   // contents of the temporary directory and copy across the new file if unique
//
//   // these 2 loops go through the temp dir and current archive (td):
//   // for (int td = 0; td <= ntarfiles-1; ++td) {
//   //
//   //   // this is where we DFS on the temp dir and the remaining - current - archive.
//   //
//   //
//   //   for (int first_file = 0; first_file < nsubfiles; ++first_file) {
//   //     for (int second_file = 0; second_file < nsubfiles; ++second_file) {
//   //       // these are the path names for 2 "sub files" from inside their respective tar archives:
//   //
//   //       // this is our pointer to the tarfile struct:
//   //         // TAR_FILE *tar_files;
//   //
//   //       char *first_sub_file_path_name = tar_files[temp_dir_cont]->sub_file_path[first_file];
//   //       char *second_sub_file_path_name = tar_files[td]->sub_file_path[second_file];
//   //
//   //       // FIRST MERGE CONDITION:
//   //       // Two or more files from different archives are considered the same file if they have the same
//   //       // relative pathname (including the name of the directory holding the file and the filename itself).
//   //
//   //       // We want to do all the following checks on files that exist inside their respective tar archives:
//   //
//   //       if (is_same_file(first_sub_file_path_name, second_sub_file_path_name)) {
//   //         printf("these files do have the same file path. \n");
//   //         // these are the same files - different versions of the same file.
//   //         // The output archive should contain just the latest of all such versions of these "subfiles".
//   //         // must now check the modification time of each file.
//   //         if (is_same_mod_time(first_sub_file_path_name, second_sub_file_path_name)) {
//   //           // only upload the latest one.
//   //           // If two or more files have the same modification time, then the largest of these should be copied.
//   //           if (is_same_file_size(first_sub_file_path_name, second_sub_file_path_name)) {
//   //             // If two or more files have the same modification time and size, the file from the latest tarfile
//   //             // (on the command-line) should be copied.
//   //
//   //             // mod_time_for_parent_of_temp_dir =
//   //             printf("the mod time for the tarfile that contains \n first_sub_file_path_name: %s", ???);
//   //             printf("the mod time for the tarfile that contains \n second_sub_file_path_name: %s", ???);
//   //           }
//   //         }
//   //
//   //       } else {
//   //         printf("these files do NOT have the same file path!!!!!!!\n");
//   //       }
//   //     }
//   //   }
//   // }
// }
