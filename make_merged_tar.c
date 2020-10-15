#include "mergetars.h"


// NOTES FROM 12/10/20 Lab:
// must use the dirent struct and then the stat() struct
// when we make a "directory exploring" function; call it recursively.

// expand a tarfile into: "char *temporary_directory"
void expand_tarfile(char *input_tarfile_name, char *temporary_directory) {
  // Extract one archive into s temporary directory.

  // temporary_directory = make_a_temporary_dir(input_tarfile_name);

  int pid = fork();

  switch (pid) {
    case -1 :
      printf("fork() failed\n");
      exit(EXIT_FAILURE);
      break;

    case 0: {
      if (temporary_directory == NULL) {
        printf("\t\ttemporary_directory is NULL \n");
      } else {
        printf("\t\ttemporary_directory is NOT NULL \n");
        // strcpy(temporary_directory, make_a_temporary_dir(tarfile_names[0]));
        printf("\t\ttemporary_directory: %s \n", temporary_directory);

        printf("\n");
        printf("\t\tFIRST CHILD commencing... \n");
        printf("\t\texecl() for the extraction of the first tarfile: \n");
        printf("\t\tparent is pid=%i\n", getppid() );
        printf("\t\tchild process for %i is pid=%i\n", getppid(), getpid() );

        // the child will now extract the contents of the
        // first input tar archive into the temporary directory.

        printf("\t\tFIRST CHILD execl() call\n");
        fflush(stdout);
        execl("/usr/bin/tar",
              "tar",
               "-xf",
               input_tarfile_name,
               "-C",
               temporary_directory,
               NULL
        );
      }

      break;
    }

    default: { // original parent process
      printf("\n");
      printf("\tSINGLE TAR ARCHIVE EXTRACTION: \n");
      printf("\n");

      int child;
      int status; // the parent's status
      printf("\t\tparent %i waiting\n", getpid() );
      child = wait( &status ); // is it the case the the parent is doing the "waiting"?
      // exit(child); // ??
      printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
      // exit(EXIT_SUCCESS); //exit the parent pid

      if (WEXITSTATUS(status) != 0) {
        perror("\t\tchild for could not be created\n");
      }

      if (temporary_directory == NULL) {
        printf("\t\toutput_dir is NULL for FIRST default case branch \n");
      } else {
        printf("\t\toutput_dir is NOT NULL for FIRST default case branch \n");
      }
    }
  }
}


// was: void merge_tar_archives(char **tarfile_names) { // must eventually take: "ntarfiles"
void merge_output_and_tmp(char **tarfile_names) { // must eventually take: "ntarfiles"

  // THIS IS WHERE THE THE FIRST TEMP DIR SHOULD GO:
  // char *output_dir = make_a_temporary_dir(tarfile_names[0]);
  // char *output_dir;

  printf("Loc 0 \n");

  // use strdup()
  // have a struct that keeps track of the name of a tarfile and its contents.
  output_dir = make_a_temporary_dir(tarfile_names[0]);

  printf("\n");
  printf("the contents of output_dir: \n");

  store_dir(output_dir);
  printf("\n");

  if (output_dir == NULL) {
    printf("output_dir is NULL \n");
  } else {
    printf("%s \n", output_dir);
  }

  // Extract one archive into the output directory.
  expand_tarfile(tarfile_names[0], output_dir);

  // Extract the rest of the tarfiles into their own temporary dir:
  for (int i = 0; i < ntarfiles - 1; ++i) {

    tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);

    printf("\n");
    printf("the contents of tmp_dir: \n");

    store_dir(tmp_dir);
    printf("\n");

    if (tmp_dir == NULL) {
      printf("output_dir is NULL \n");
    } else {
      printf("%s \n", tmp_dir);
    }

    // expand a remaining tarfile into its own tmp dir:
    expand_tarfile(tarfile_names[i + 1], tmp_dir);

    // do the comparisons/merging with the utput_dir and tmp_dir:

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\tALL OTHER TAR ARCHIVE EXTRACTIONS: \n");
    printf("\n");

    int child;
    int status;
    printf("\t\tparent %i waiting\n", getpid() );

    child = wait( &status );
    // exit(child);
    printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
    // exit(EXIT_SUCCESS); //exit the parent pid

    if (WEXITSTATUS(status) != 0) {
      perror("\t\tchild process could not be created\n");
    }

    if (tmp_dir == NULL) {
      printf("\t\ttmp_dir is NULL for SECOND default case branch\n");
    } else {
      printf("\t\ttmp_dir is NOT NULL for SECOND default case branch\n");
    }

    // ALL COMPARISONS HAPPEN HERE:

    /*
    init the output_dir and tmp_dir variables form their respective dirent and stat() structs
    we need:
      - path_name
      - mod_time
      - file_size
    for each entry in the output_dir and the tmp_dir
    */

    /*
    use DIR *opendir(const char *dirname);
    to return a pointer for the output_dir and temp_dir (respectively)

    use these pointers to compare the contents of output_dir and temp_dir with
    te readdir() - struct dirent *readdir(DIR *dirp); - function.
    */

    // this is a pointer to a "dirent" structure representing the next directory
    // entry in the directory stream pointed to by out_dir:
    // this will point to the call to readdir() for out_dir
    if(output_dir == NULL) {
      perror("\t\toutput_dir is NULL. \n"); // what is this "progname"?
      exit(EXIT_FAILURE);
    }

    if (tmp_dir == NULL) {
      printf("\t\ttmp_dir is NULL \n");
    }

    struct dirent *out_dir_dirent_pointer;
    // this is the pointer to the contents of the output dir:
    DIR *out_dir = opendir(output_dir); // Segmentation fault (core dumped)

    if(out_dir == NULL) {
      perror("\t\tout_dir was NULL. \n"); // what is this "progname"?
      exit(EXIT_FAILURE);
    }
    // it appears that output_dir is null...

    // this is a pointer to a "dirent" structure representing the next directory
    // entry in the directory stream pointed to by tp_dir:
    // this will point to the call to readdir() for otp_dir
    printf("\tL 4\n");
    fflush(stdout);
    struct dirent *tmp_dir_dirent_pointer;
    // this is the pointer to the contents of the tmporary dir:
    printf("\tL 5\n");
    fflush(stdout);
    DIR *tp_dir = opendir(tmp_dir);

    printf("\tL 6\n");
    fflush(stdout);
    out_dir_dirent_pointer = readdir(out_dir);
    printf("\tL 7\n");
    fflush(stdout);
    tmp_dir_dirent_pointer = readdir(tp_dir);
    printf("\tL 8\n");
    fflush(stdout);

    while(out_dir_dirent_pointer != NULL) {
      printf("\tL 9\n");
      fflush(stdout);
      while(tmp_dir_dirent_pointer != NULL) {
        printf("\tL 10\n");
        fflush(stdout);
        // to check if two versions of the same file:
        // check if out_dir_dirent_pointer.d_name == tmp_dir_dirent_pointer.d_name
        // may need:
        // out_dir_dirent_pointer->d_name == tmp_dir_dirent_pointer->d_name
        if (is_same_file(out_dir_dirent_pointer->d_name, tmp_dir_dirent_pointer->d_name)) {
          printf("\tL 11\n");
          fflush(stdout);
          printf("\tthese files do have the same file path. \n");
        } else {
          printf("\tL 12\n");
          fflush(stdout);
          printf("\tthese files DO NOT have the same file path. \n");
        }

        break;
      }

      break;
    }

    printf("\tL 13\n");
    fflush(stdout);
    closedir(out_dir);
    printf("\tL 14\n");
    fflush(stdout);
    closedir(tp_dir);


    break;

    // do the merging here

    // tmp_dir = realloc(tmp_dir, sizeof make_a_temporary_dir(tarfile_names[i + 1]));
    // char *tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);

    // printf("Loc A \n");
    // tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);
    // if (output_dir == NULL) {
    //   printf("tmp_dir is NULL \n");
    // } else {
    //   printf("%s \n", tmp_dir);
    // }



    // // ALL COMPARISONS HAPPEN HERE:
    //
    // /*
    // init the output_dir and tmp_dir variables form their respective dirent and stat() structs
    // we need:
    //   - path_name
    //   - mod_time
    //   - file_size
    // for each entry in the output_dir and the tmp_dir
    // */
    //
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
    // if(output_dir == NULL) {
    //   perror("\t\toutput_dir is NULL. \n"); // what is this "progname"?
    //   exit(EXIT_FAILURE);
    // }
    //
    // if (tmp_dir == NULL) {
    //   printf("\t\ttmp_dir is NULL \n");
    // }
    //
    // struct dirent *out_dir_dirent_pointer;
    // // this is the pointer to the contents of the output dir:
    // DIR *out_dir = opendir(output_dir); // Segmentation fault (core dumped)
    //
    // if(out_dir == NULL) {
    //   perror("\t\tout_dir was NULL. \n"); // what is this "progname"?
    //   exit(EXIT_FAILURE);
    // }
    //
    // // this is a pointer to a "dirent" structure representing the next directory
    // // entry in the directory stream pointed to by tp_dir:
    // // this will point to the call to readdir() for otp_dir
    // struct dirent *tmp_dir_dirent_pointer;
    // // this is the pointer to the contents of the tmporary dir:
    // DIR *tp_dir = opendir(tmp_dir);
    //
    //
    // while((out_dir_dirent_pointer = readdir(out_dir)) != NULL) {
    //   while((tmp_dir_dirent_pointer = readdir(tp_dir)) != NULL) {
    //     // to check if two versions of the same file:
    //     // check if out_dir_dirent_pointer.d_name == tmp_dir_dirent_pointer.d_name
    //     // may need:
    //     // out_dir_dirent_pointer->d_name == tmp_dir_dirent_pointer->d_name
    //     if (strcmp(out_dir_dirent_pointer->d_name, tmp_dir_dirent_pointer->d_name) == 0) {
    //       printf("\tthese files do have the same file path. \n");
    //       // strcpy(output_dir_struct -> name, out_dir_dirent_pointer -> d_name);
    //
    //       // the stat struct for the output_dir:
    //       struct stat output_dir_stat_struct;
    //       output_dir_stat_struct = malloc(sizeof(struct stat)); // must then free this later
    //
    //       // the stat struct for the tmp_dir:
    //       struct stat tmp_dir_stat_struct;
    //       tmp_dir_stat_struct = malloc(sizeof(struct stat)); // must then free this later
    //
    //       for (int i = 0; i < ) {}
    //
    //       if (stat(output_dir_stat_struct -> st_smtime, &output_dir_stat_struct) == 0) {
    //         if (stat(tmp_dir_stat_struct -> st_smtime, &tmp_dir_stat_struct) == 0) {}
    //         // now we can read the stat() struct elems into our own struct
    //         // find their modification times now
    //
    //       } else {
    //         perror("could not stat \n");
    //       }
    //       continue;
    //
    //     } else { // they are different files
    //       printf("\tthese files DO NOT have the same file path. \n");
    //     }
    //
    //     if (strcmp(input_dir_name, "tmp_dir") == 0) {
    //       // init this struct LINUX_DIR tmp_dir;
    //       strcpy(tmp_dir -> name, tmp_dir_dirent_pointer -> d_name);
    //     }
    //
    //     break;
    //   }
    //
    //   break;
    // }
    //
    // closedir(out_dir);
    // closedir(tp_dir);
    // break;
    //
    // // do the merging here
    //
    // // tmp_dir = realloc(tmp_dir, sizeof make_a_temporary_dir(tarfile_names[i + 1]));
    // // char *tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);
    //
    // // printf("Loc A \n");
    // // tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);
    // // if (output_dir == NULL) {
    // //   printf("tmp_dir is NULL \n");
    // // } else {
    // //   printf("%s \n", tmp_dir);
    // // }
  }
}




// code for recursing a directory structure
// #include <unistd.h>
// #include <sys/types.h>
// #include <dirent.h>
// #include <stdio.h>
// #include <string.h>
//
// void listdir(const char *name, int indent)
// {
//     DIR *dir;
//     struct dirent *entry;
//
//     if (!(dir = opendir(name))) {
//       return;
//     }
//
//     while ((entry = readdir(dir)) != NULL) {
//         if (entry->d_type == DT_DIR) {
//             char path[1024];
//             if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
//                 continue;
//             snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
//             printf("%*s[%s]\n", indent, "", entry->d_name);
//             listdir(path, indent + 2);
//         } else {
//             printf("%*s- %s\n", indent, "", entry->d_name);
//         }
//     }
//     closedir(dir);
// }
//
// int main(void) {
//     listdir(".", 0);
//     return 0;
// }







int main(int argc, char* argv[]) {

  printf("\n");
  printf("\n");
  printf("init_structs(): \n");
  printf("\n");

  init_structs();
  // printf("malloc() output_dir_file: \n");
  // output_dir_file = malloc(sizeof(struct LINUX_FILE));
  // printf("malloc() tmp_dir_file: \n");
  // tmp_dir_file = malloc(sizeof(struct LINUX_FILE));
  // printf("malloc() output_dir_struct: \n");
  // output_dir_struct = malloc(sizeof(struct LINUX_DIR));
  // printf("malloc() tmp_dir_struct: \n");
  // tmp_dir_struct = malloc(sizeof(struct LINUX_DIR));
  printf("\n");

  if (argc < 3) {
    printf("\n");
    printf("need 3 cmdline args \n");
    exit(EXIT_FAILURE);
  } else {
    printf("\n");
    printf("DO YOU SEE ME ? \n");
    ntarfiles = argc - 1;
    // char **tarfile_names = NULL; // this is in globals.c
    tarfile_names = realloc(tarfile_names, ntarfiles * sizeof(tarfile_names[0]));

    printf("\n");
    if (tarfile_names == NULL) {
      printf("\n");
      printf("\ttarfile_names DID NOT get allocated! \n");
      printf("\n");
    } else {
      printf("\n");
      printf("\ttarfile_names were allocated. \n");
      printf("\n");
    }

    for (int i = 0; i < ntarfiles; ++i) {

      tarfile_names[i] = argv[i + 1];

    }

    // merge_tar_archives(tarfile_names);
    merge_output_and_tmp(tarfile_names);
    printf("\n");
    printf("\n");
    printf("\n");

  }
}














// FINAL VERSION OF merge_tar_archives:
// void merge_tar_archives(char **tarfile_names) { // must eventually take: "ntarfiles"
//
//   // THIS IS WHERE THE THE FIRST TEMP DIR SHOULD GO:
//   // char *output_dir = make_a_temporary_dir(tarfile_names[0]);
//   // char *output_dir;
//
//   printf("Loc 0 \n");
//
//   // use strdup()
//   // have a struct that keeps track of the name of a tarfile and its contents.
//   output_dir = make_a_temporary_dir(tarfile_names[0]);
//   if (output_dir == NULL) {
//     printf("output_dir is NULL \n");
//   } else {
//     printf("%s \n", output_dir);
//   }
//
//   // Extract one archive into the output directory.
//   expand_tarfiles(tarfile_names, 0);
//
//   // int pid = fork();
//   //
//   // printf("Loc 2 \n");
//   //
//   // switch (pid) {
//   //   case -1 :
//   //     printf("fork() failed\n");
//   //     exit(EXIT_FAILURE);
//   //     break;
//   //
//   //   case 0: {
//   //     if (output_dir == NULL) {
//   //       printf("\t\toutput_dir is NULL \n");
//   //     } else {
//   //       printf("\t\toutput_dir is NOT NULL \n");
//   //       // strcpy(output_dir, make_a_temporary_dir(tarfile_names[0]));
//   //       printf("\t\toutput_dir: %s \n", output_dir);
//   //
//   //       printf("\n");
//   //       printf("\t\tFIRST CHILD commencing... \n");
//   //       printf("\t\texecl() for the extraction of the first tarfile: \n");
//   //       printf("\t\tparent is pid=%i\n", getppid() );
//   //       printf("\t\tchild process for %i is pid=%i\n", getppid(), getpid() );
//   //
//   //       // the child will now extract the contents of the
//   //       // first input tar archive into the temporary directory.
//   //
//   //       printf("\t\tFIRST CHILD execl() call\n");
//   //       fflush(stdout);
//   //       execl("/usr/bin/tar",
//   //             "tar",
//   //              "-xf",
//   //              tarfile_names[0],
//   //              "-C",
//   //              output_dir,
//   //              NULL
//   //       );
//   //     }
//   //
//   //     break;
//   //   }
//   //
//   //   default: { // original parent process
//   //     printf("\n");
//   //     printf("\tSINGLE TAR ARCHIVE EXTRACTION: \n");
//   //     printf("\n");
//   //
//   //     int child;
//   //     int status; // the parent's status
//   //     printf("\t\tparent %i waiting\n", getpid() );
//   //     child = wait( &status ); // is it the case the the parent is doing the "waiting"?
//   //     // exit(child); // ??
//   //     printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//   //     // exit(EXIT_SUCCESS); //exit the parent pid
//   //
//   //     if (WEXITSTATUS(status) != 0) {
//   //       perror("\t\tchild for could not be created\n");
//   //     }
//   //
//   //     if (output_dir == NULL) {
//   //       printf("\t\toutput_dir is NULL for FIRST default case branch \n");
//   //     } else {
//   //       printf("\t\toutput_dir is NOT NULL for FIRST default case branch \n");
//   //     }
//   //
//   //
//   //     break;
//   //   }
//   // }
//
//   // Extract the rest of the tarfiles into their own temporary dir:
//   for (int i = 0; i < ntarfiles - 1; ++i) {
//     expand_tarfiles(tarfile_names, i);
//
//     // tmp_dir = realloc(tmp_dir, sizeof make_a_temporary_dir(tarfile_names[i + 1]));
//     // char *tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);
//
//     printf("Loc A \n");
//     tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);
//     if (output_dir == NULL) {
//       printf("tmp_dir is NULL \n");
//     } else {
//       printf("%s \n", tmp_dir);
//     }
//
//     // int pid = fork();
//     //
//     // switch (pid) {
//     //   case -1 :
//     //     printf("fork() failed\n");
//     //     exit(EXIT_FAILURE);
//     //     break;
//     //
//     //   case 0: {
//     //     if (tmp_dir == NULL) {
//     //       printf("\t\ttmp_dir is NULL \n");
//     //     } else {
//     //       printf("\t\ttmp_dir is NOT NULL \n");
//     //       // strcpy(tmp_dir, make_a_temporary_dir(tarfile_names[i + 1]));
//     //
//     //       printf("\n");
//     //       printf("\t\tSECOND CHILD commencing... \n");
//     //       printf("\t\tparent is pid=%i\n", getppid() );
//     //       printf("\t\tchild process for %i is pid=%i\n", getppid(), getpid() );
//     //
//     //       // the child will now extract the contents of the
//     //       // remaining input tar archives into the temporary directory.
//     //       printf("\t\tThe susequent execl() for the extraction of the next tarfile: \n");
//     //       fflush(stdout);
//     //       execl("/usr/bin/tar",
//     //             "tar",
//     //              "-xf",
//     //              tarfile_names[i + 1],
//     //              "-C",
//     //              tmp_dir,
//     //              NULL
//     //       );
//     //     }
//     //
//     //     break;
//     //   }
//     //
//     //   default: { // original parent process
//     //     printf("\n");
//     //     printf("\n");
//     //     printf("\n");
//     //     printf("\tALL OTHER TAR ARCHIVE EXTRACTIONS: \n");
//     //     printf("\n");
//     //
//     //     int child;
//     //     int status;
//     //     printf("\t\tparent %i waiting\n", getpid() );
//     //
//     //     child = wait( &status );
//     //     // exit(child);
//     //     printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//     //     // exit(EXIT_SUCCESS); //exit the parent pid
//     //
//     //     if (WEXITSTATUS(status) != 0) {
//     //       perror("\t\tchild process could not be created\n");
//     //     }
//     //
//     //     if (tmp_dir == NULL) {
//     //       printf("\t\ttmp_dir is NULL for SECOND default case branch\n");
//     //     } else {
//     //       printf("\t\ttmp_dir is NOT NULL for SECOND default case branch\n");
//     //     }
//     //
//     //     // ALL COMPARISONS HAPPEN HERE:
//     //
//     //     /*
//     //     use DIR *opendir(const char *dirname);
//     //     to return a pointer for the output_dir and temp_dir (respectively)
//     //
//     //     use these pointers to compare the contents of output_dir and temp_dir with
//     //     te readdir() - struct dirent *readdir(DIR *dirp); - function.
//     //     */
//     //
//     //     // this is a pointer to a "dirent" structure representing the next directory
//     //     // entry in the directory stream pointed to by out_dir:
//     //     // this will point to the call to readdir() for out_dir
//     //     if(output_dir == NULL) {
//     //       perror("\t\toutput_dir is NULL. \n"); // what is this "progname"?
//     //       exit(EXIT_FAILURE);
//     //     }
//     //
//     //     if (tmp_dir == NULL) {
//     //       printf("\t\ttmp_dir is NULL \n");
//     //     }
//     //
//     //     printf("\tL 1\n");
//     //     fflush(stdout);
//     //     struct dirent *out_dir_dirent_pointer;
//     //     // this is the pointer to the contents of the output dir:
//     //     printf("\tL 2\n");
//     //     fflush(stdout);
//     //     DIR *out_dir = opendir(output_dir); // Segmentation fault (core dumped)
//     //
//     //     // use opendir() and readdir() or opendir() and stat()?
//     //     printf("\tL 3\n");
//     //     fflush(stdout);
//     //     if(out_dir == NULL) {
//     //       perror("\t\tout_dir was NULL. \n"); // what is this "progname"?
//     //       exit(EXIT_FAILURE);
//     //     }
//     //     // it appears that output_dir is null...
//     //
//     //     // this is a pointer to a "dirent" structure representing the next directory
//     //     // entry in the directory stream pointed to by tp_dir:
//     //     // this will point to the call to readdir() for otp_dir
//     //     printf("\tL 4\n");
//     //     fflush(stdout);
//     //     struct dirent *tmp_dir_dirent_pointer;
//     //     // this is the pointer to the contents of the tmporary dir:
//     //     printf("\tL 5\n");
//     //     fflush(stdout);
//     //     DIR *tp_dir = opendir(tmp_dir);
//     //
//     //     printf("\tL 6\n");
//     //     fflush(stdout);
//     //     out_dir_dirent_pointer = readdir(out_dir);
//     //     printf("\tL 7\n");
//     //     fflush(stdout);
//     //     tmp_dir_dirent_pointer = readdir(tp_dir);
//     //     printf("\tL 8\n");
//     //     fflush(stdout);
//     //
//     //     while(out_dir_dirent_pointer != NULL) {
//     //       printf("\tL 9\n");
//     //       fflush(stdout);
//     //       while(tmp_dir_dirent_pointer != NULL) {
//     //         printf("\tL 10\n");
//     //         fflush(stdout);
//     //         // to check if two versions of the same file:
//     //         // check if out_dir_dirent_pointer.d_name == tmp_dir_dirent_pointer.d_name
//     //         // may need:
//     //         // out_dir_dirent_pointer->d_name == tmp_dir_dirent_pointer->d_name
//     //         if (is_same_file(out_dir_dirent_pointer->d_name, tmp_dir_dirent_pointer->d_name)) {
//     //           printf("\tL 11\n");
//     //           fflush(stdout);
//     //           printf("\tthese files do have the same file path. \n");
//     //         } else {
//     //           printf("\tL 12\n");
//     //           fflush(stdout);
//     //           printf("\tthese files DO NOT have the same file path. \n");
//     //         }
//     //
//     //         break;
//     //       }
//     //
//     //       break;
//     //     }
//     //
//     //     printf("\tL 13\n");
//     //     fflush(stdout);
//     //     closedir(out_dir);
//     //     printf("\tL 14\n");
//     //     fflush(stdout);
//     //     closedir(tp_dir);
//     //
//     //
//     //     break;
//     //   }
//   }
// }
// //}



// void merge_tar_archives(char **tarfile_names) { // must eventually take: "ntarfiles"
//
//   // THIS IS WHERE THE THE FIRST TEMP DIR SHOULD GO:
//   // char *output_dir = make_a_temporary_dir(tarfile_names[0]);
//   // char *output_dir;
//
//   printf("Loc 0 \n");
//
//   // use strdup()
//   // have a struct that keeps track of the name of a tarfile and its contents.
//   output_dir = make_a_temporary_dir(tarfile_names[0]);
//   if (output_dir == NULL) {
//     printf("output_dir is NULL \n");
//   } else {
//     printf("%s \n", output_dir);
//   }
//
//   // Extract one archive into the output directory.
//   int pid = fork();
//
//   printf("Loc 2 \n");
//
//   switch (pid) {
//     case -1 :
//       printf("fork() failed\n");
//       exit(EXIT_FAILURE);
//       break;
//
//     case 0: {
//       if (output_dir == NULL) {
//         printf("\t\toutput_dir is NULL \n");
//       } else {
//         printf("\t\toutput_dir is NOT NULL \n");
//         // strcpy(output_dir, make_a_temporary_dir(tarfile_names[0]));
//         printf("\t\toutput_dir: %s \n", output_dir);
//
//         printf("\n");
//         printf("\t\tFIRST CHILD commencing... \n");
//         printf("\t\texecl() for the extraction of the first tarfile: \n");
//         printf("\t\tparent is pid=%i\n", getppid() );
//         printf("\t\tchild process for %i is pid=%i\n", getppid(), getpid() );
//
//         // the child will now extract the contents of the
//         // first input tar archive into the temporary directory.
//
//         printf("\t\tFIRST CHILD execl() call\n");
//         fflush(stdout);
//         execl("/usr/bin/tar",
//               "tar",
//                "-xf",
//                tarfile_names[0],
//                "-C",
//                output_dir,
//                NULL
//         );
//       }
//
//       break;
//     }
//
//     default: { // original parent process
//       printf("\n");
//       printf("\tSINGLE TAR ARCHIVE EXTRACTION: \n");
//       printf("\n");
//
//       int child;
//       int status; // the parent's status
//       printf("\t\tparent %i waiting\n", getpid() );
//       child = wait( &status ); // is it the case the the parent is doing the "waiting"?
//       // exit(child); // ??
//       printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//       // exit(EXIT_SUCCESS); //exit the parent pid
//
//       if (WEXITSTATUS(status) != 0) {
//         perror("\t\tchild for could not be created\n");
//       }
//
//       if (output_dir == NULL) {
//         printf("\t\toutput_dir is NULL for FIRST default case branch \n");
//       } else {
//         printf("\t\toutput_dir is NOT NULL for FIRST default case branch \n");
//       }
//
//
//       break;
//     }
//   }
//
//   for (int i = 0; i < ntarfiles - 1; ++i) {
//
//     // tmp_dir = realloc(tmp_dir, sizeof make_a_temporary_dir(tarfile_names[i + 1]));
//     // char *tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);
//
//     printf("Loc A \n");
//     tmp_dir = make_a_temporary_dir(tarfile_names[i + 1]);
//     if (output_dir == NULL) {
//       printf("tmp_dir is NULL \n");
//     } else {
//       printf("%s \n", tmp_dir);
//     }
//
//     int pid = fork();
//
//     switch (pid) {
//       case -1 :
//         printf("fork() failed\n");
//         exit(EXIT_FAILURE);
//         break;
//
//       case 0: {
//         if (tmp_dir == NULL) {
//           printf("\t\ttmp_dir is NULL \n");
//         } else {
//           printf("\t\ttmp_dir is NOT NULL \n");
//           // strcpy(tmp_dir, make_a_temporary_dir(tarfile_names[i + 1]));
//
//           printf("\n");
//           printf("\t\tSECOND CHILD commencing... \n");
//           printf("\t\tparent is pid=%i\n", getppid() );
//           printf("\t\tchild process for %i is pid=%i\n", getppid(), getpid() );
//
//           // the child will now extract the contents of the
//           // remaining input tar archives into the temporary directory.
//           printf("\t\tThe susequent execl() for the extraction of the next tarfile: \n");
//           fflush(stdout);
//           execl("/usr/bin/tar",
//                 "tar",
//                  "-xf",
//                  tarfile_names[i + 1],
//                  "-C",
//                  tmp_dir,
//                  NULL
//           );
//         }
//
//         break;
//       }
//
//       default: { // original parent process
//         printf("\n");
//         printf("\n");
//         printf("\n");
//         printf("\tALL OTHER TAR ARCHIVE EXTRACTIONS: \n");
//         printf("\n");
//
//         int child;
//         int status;
//         printf("\t\tparent %i waiting\n", getpid() );
//
//         child = wait( &status );
//         // exit(child);
//         printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//         // exit(EXIT_SUCCESS); //exit the parent pid
//
//         if (WEXITSTATUS(status) != 0) {
//           perror("\t\tchild process could not be created\n");
//         }
//
//         if (tmp_dir == NULL) {
//           printf("\t\ttmp_dir is NULL for SECOND default case branch\n");
//         } else {
//           printf("\t\ttmp_dir is NOT NULL for SECOND default case branch\n");
//         }
//
//         // ALL COMPARISONS HAPPEN HERE:
//
//         /*
//         use DIR *opendir(const char *dirname);
//         to return a pointer for the output_dir and temp_dir (respectively)
//
//         use these pointers to compare the contents of output_dir and temp_dir with
//         te readdir() - struct dirent *readdir(DIR *dirp); - function.
//         */
//
//         // this is a pointer to a "dirent" structure representing the next directory
//         // entry in the directory stream pointed to by out_dir:
//         // this will point to the call to readdir() for out_dir
//         if(output_dir == NULL) {
//           perror("\t\toutput_dir is NULL. \n"); // what is this "progname"?
//           exit(EXIT_FAILURE);
//         }
//
//         if (tmp_dir == NULL) {
//           printf("\t\ttmp_dir is NULL \n");
//         }
//
//         printf("\tL 1\n");
//         fflush(stdout);
//         struct dirent *out_dir_dirent_pointer;
//         // this is the pointer to the contents of the output dir:
//         printf("\tL 2\n");
//         fflush(stdout);
//         DIR *out_dir = opendir(output_dir); // Segmentation fault (core dumped)
//
//         // use opendir() and readdir() or opendir() and stat()?
//         printf("\tL 3\n");
//         fflush(stdout);
//         if(out_dir == NULL) {
//           perror("\t\tout_dir was NULL. \n"); // what is this "progname"?
//           exit(EXIT_FAILURE);
//         }
//         // it appears that output_dir is null...
//
//         // this is a pointer to a "dirent" structure representing the next directory
//         // entry in the directory stream pointed to by tp_dir:
//         // this will point to the call to readdir() for otp_dir
//         printf("\tL 4\n");
//         fflush(stdout);
//         struct dirent *tmp_dir_dirent_pointer;
//         // this is the pointer to the contents of the tmporary dir:
//         printf("\tL 5\n");
//         fflush(stdout);
//         DIR *tp_dir = opendir(tmp_dir);
//
//         printf("\tL 6\n");
//         fflush(stdout);
//         out_dir_dirent_pointer = readdir(out_dir);
//         printf("\tL 7\n");
//         fflush(stdout);
//         tmp_dir_dirent_pointer = readdir(tp_dir);
//         printf("\tL 8\n");
//         fflush(stdout);
//
//         while(out_dir_dirent_pointer != NULL) {
//           printf("\tL 9\n");
//           fflush(stdout);
//           while(tmp_dir_dirent_pointer != NULL) {
//             printf("\tL 10\n");
//             fflush(stdout);
//             // to check if two versions of the same file:
//             // check if out_dir_dirent_pointer.d_name == tmp_dir_dirent_pointer.d_name
//             // may need:
//             // out_dir_dirent_pointer->d_name == tmp_dir_dirent_pointer->d_name
//             if (is_same_file(out_dir_dirent_pointer->d_name, tmp_dir_dirent_pointer->d_name)) {
//               printf("\tL 11\n");
//               fflush(stdout);
//               printf("\tthese files do have the same file path. \n");
//             } else {
//               printf("\tL 12\n");
//               fflush(stdout);
//               printf("\tthese files DO NOT have the same file path. \n");
//             }
//
//             break;
//           }
//
//           break;
//         }
//
//         printf("\tL 13\n");
//         fflush(stdout);
//         closedir(out_dir);
//         printf("\tL 14\n");
//         fflush(stdout);
//         closedir(tp_dir);
//
//
//         break;
//       }
//     }
//   }
// }























// void expand_tarfiles(char **tarfile_names, int num_tarfiles) {
//   // Extract one archive into s temporary directory.
//   int pid = fork();
//
//   if (num_tarfiles == 1) {
//     switch (pid) {
//       case -1 :
//         printf("fork() failed\n");
//         exit(EXIT_FAILURE);
//         break;
//
//       case 0: {
//         if (temporary_directory == NULL) {
//           printf("\t\ttemporary_directory is NULL \n");
//         } else {
//           printf("\t\ttemporary_directory is NOT NULL \n");
//           // strcpy(temporary_directory, make_a_temporary_dir(tarfile_names[0]));
//           printf("\t\ttemporary_directory: %s \n", temporary_directory);
//
//           printf("\n");
//           printf("\t\tFIRST CHILD commencing... \n");
//           printf("\t\texecl() for the extraction of the first tarfile: \n");
//           printf("\t\tparent is pid=%i\n", getppid() );
//           printf("\t\tchild process for %i is pid=%i\n", getppid(), getpid() );
//
//           // the child will now extract the contents of the
//           // first input tar archive into the temporary directory.
//
//           printf("\t\tFIRST CHILD execl() call\n");
//           fflush(stdout);
//           execl("/usr/bin/tar",
//                 "tar",
//                  "-xf",
//                  tarfile_names[0],
//                  "-C",
//                  temporary_directory,
//                  NULL
//           );
//         }
//
//         break;
//       }
//
//       default: { // original parent process
//         printf("\n");
//         printf("\tSINGLE TAR ARCHIVE EXTRACTION: \n");
//         printf("\n");
//
//         int child;
//         int status; // the parent's status
//         printf("\t\tparent %i waiting\n", getpid() );
//         child = wait( &status ); // is it the case the the parent is doing the "waiting"?
//         // exit(child); // ??
//         printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//         // exit(EXIT_SUCCESS); //exit the parent pid
//
//         if (WEXITSTATUS(status) != 0) {
//           perror("\t\tchild for could not be created\n");
//         }
//
//         if (temporary_directory == NULL) {
//           printf("\t\toutput_dir is NULL for FIRST default case branch \n");
//         } else {
//           printf("\t\toutput_dir is NOT NULL for FIRST default case branch \n");
//         }
//
//         // if (num_tarfiles != 0) {
//         //   printf("\n");
//         //   printf("\n");
//         //   printf("\n");
//         //   printf("\tALL OTHER TAR ARCHIVE EXTRACTIONS: \n");
//         //   printf("\n");
//         //
//         //   int child;
//         //   int status;
//         //   printf("\t\tparent %i waiting\n", getpid() );
//         //
//         //   child = wait( &status );
//         //   // exit(child);
//         //   printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//         //   // exit(EXIT_SUCCESS); //exit the parent pid
//         //
//         //   if (WEXITSTATUS(status) != 0) {
//         //     perror("\t\tchild process could not be created\n");
//         //   }
//         //
//         //   if (tmp_dir == NULL) {
//         //     printf("\t\ttmp_dir is NULL for SECOND default case branch\n");
//         //   } else {
//         //     printf("\t\ttmp_dir is NOT NULL for SECOND default case branch\n");
//         //   }
//         //
//         //   // ALL COMPARISONS HAPPEN HERE:
//         //
//         //   /*
//         //   use DIR *opendir(const char *dirname);
//         //   to return a pointer for the output_dir and temp_dir (respectively)
//         //
//         //   use these pointers to compare the contents of output_dir and temp_dir with
//         //   te readdir() - struct dirent *readdir(DIR *dirp); - function.
//         //   */
//         //
//         //   // this is a pointer to a "dirent" structure representing the next directory
//         //   // entry in the directory stream pointed to by out_dir:
//         //   // this will point to the call to readdir() for out_dir
//         //   if(output_dir == NULL) {
//         //     perror("\t\toutput_dir is NULL. \n"); // what is this "progname"?
//         //     exit(EXIT_FAILURE);
//         //   }
//         //
//         //   if (tmp_dir == NULL) {
//         //     printf("\t\ttmp_dir is NULL \n");
//         //   }
//         //
//         //   printf("\tL 1\n");
//         //   fflush(stdout);
//         //   struct dirent *out_dir_dirent_pointer;
//         //   // this is the pointer to the contents of the output dir:
//         //   printf("\tL 2\n");
//         //   fflush(stdout);
//         //   DIR *out_dir = opendir(output_dir); // Segmentation fault (core dumped)
//         //
//         //   // use opendir() and readdir() or opendir() and stat()?
//         //   printf("\tL 3\n");
//         //   fflush(stdout);
//         //   if(out_dir == NULL) {
//         //     perror("\t\tout_dir was NULL. \n"); // what is this "progname"?
//         //     exit(EXIT_FAILURE);
//         //   }
//         //   // it appears that output_dir is null...
//         //
//         //   // this is a pointer to a "dirent" structure representing the next directory
//         //   // entry in the directory stream pointed to by tp_dir:
//         //   // this will point to the call to readdir() for otp_dir
//         //   printf("\tL 4\n");
//         //   fflush(stdout);
//         //   struct dirent *tmp_dir_dirent_pointer;
//         //   // this is the pointer to the contents of the tmporary dir:
//         //   printf("\tL 5\n");
//         //   fflush(stdout);
//         //   DIR *tp_dir = opendir(tmp_dir);
//         //
//         //   printf("\tL 6\n");
//         //   fflush(stdout);
//         //   out_dir_dirent_pointer = readdir(out_dir);
//         //   printf("\tL 7\n");
//         //   fflush(stdout);
//         //   tmp_dir_dirent_pointer = readdir(tp_dir);
//         //   printf("\tL 8\n");
//         //   fflush(stdout);
//         //
//         //   while(out_dir_dirent_pointer != NULL) {
//         //     printf("\tL 9\n");
//         //     fflush(stdout);
//         //     while(tmp_dir_dirent_pointer != NULL) {
//         //       printf("\tL 10\n");
//         //       fflush(stdout);
//         //       // to check if two versions of the same file:
//         //       // check if out_dir_dirent_pointer.d_name == tmp_dir_dirent_pointer.d_name
//         //       // may need:
//         //       // out_dir_dirent_pointer->d_name == tmp_dir_dirent_pointer->d_name
//         //       if (is_same_file(out_dir_dirent_pointer->d_name, tmp_dir_dirent_pointer->d_name)) {
//         //         printf("\tL 11\n");
//         //         fflush(stdout);
//         //         printf("\tthese files do have the same file path. \n");
//         //       } else {
//         //         printf("\tL 12\n");
//         //         fflush(stdout);
//         //         printf("\tthese files DO NOT have the same file path. \n");
//         //       }
//         //
//         //       break;
//         //     }
//         //
//         //     break;
//         //   }
//         //
//         //   printf("\tL 13\n");
//         //   fflush(stdout);
//         //   closedir(out_dir);
//         //   printf("\tL 14\n");
//         //   fflush(stdout);
//         //   closedir(tp_dir);
//         //
//         //
//         //   break;
//         // }
//       }
//     }
//   }
//
//   if (num_tarfiles > 1) {
//     switch (pid) {
//       case -1 :
//         printf("fork() failed\n");
//         exit(EXIT_FAILURE);
//         break;
//
//       case 0: {
//         if (temporary_directory == NULL) {
//           printf("\t\ttemporary_directory is NULL \n");
//         } else {
//           printf("\t\ttemporary_directory is NOT NULL \n");
//           // strcpy(temporary_directory, make_a_temporary_dir(tarfile_names[0]));
//           printf("\t\ttemporary_directory: %s \n", temporary_directory);
//
//           printf("\n");
//           printf("\t\tFIRST CHILD commencing... \n");
//           printf("\t\texecl() for the extraction of the first tarfile: \n");
//           printf("\t\tparent is pid=%i\n", getppid() );
//           printf("\t\tchild process for %i is pid=%i\n", getppid(), getpid() );
//
//           // the child will now extract the contents of the
//           // first input tar archive into the temporary directory.
//
//           printf("\t\tFIRST CHILD execl() call\n");
//           fflush(stdout);
//           execl("/usr/bin/tar",
//                 "tar",
//                  "-xf",
//                  tarfile_names[1 + num_tarfiles],
//                  "-C",
//                  temporary_directory,
//                  NULL
//           );
//         }
//
//         break;
//       }
//
//       default: { // original parent process
//         printf("\n");
//         printf("\tSINGLE TAR ARCHIVE EXTRACTION: \n");
//         printf("\n");
//
//         int child;
//         int status; // the parent's status
//         printf("\t\tparent %i waiting\n", getpid() );
//         child = wait( &status ); // is it the case the the parent is doing the "waiting"?
//         // exit(child); // ??
//         printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//         // exit(EXIT_SUCCESS); //exit the parent pid
//
//         if (WEXITSTATUS(status) != 0) {
//           perror("\t\tchild for could not be created\n");
//         }
//
//         if (temporary_directory == NULL) {
//           printf("\t\toutput_dir is NULL for FIRST default case branch \n");
//         } else {
//           printf("\t\toutput_dir is NOT NULL for FIRST default case branch \n");
//         }
//
//         // if (num_tarfiles != 0) {
//         //   printf("\n");
//         //   printf("\n");
//         //   printf("\n");
//         //   printf("\tALL OTHER TAR ARCHIVE EXTRACTIONS: \n");
//         //   printf("\n");
//         //
//         //   int child;
//         //   int status;
//         //   printf("\t\tparent %i waiting\n", getpid() );
//         //
//         //   child = wait( &status );
//         //   // exit(child);
//         //   printf("\t\tchild process pid=%i terminated with exit status=%i\n", child, WEXITSTATUS(status) );
//         //   // exit(EXIT_SUCCESS); //exit the parent pid
//         //
//         //   if (WEXITSTATUS(status) != 0) {
//         //     perror("\t\tchild process could not be created\n");
//         //   }
//         //
//         //   if (tmp_dir == NULL) {
//         //     printf("\t\ttmp_dir is NULL for SECOND default case branch\n");
//         //   } else {
//         //     printf("\t\ttmp_dir is NOT NULL for SECOND default case branch\n");
//         //   }
//         //
//         //   // ALL COMPARISONS HAPPEN HERE:
//         //
//         //   /*
//         //   use DIR *opendir(const char *dirname);
//         //   to return a pointer for the output_dir and temp_dir (respectively)
//         //
//         //   use these pointers to compare the contents of output_dir and temp_dir with
//         //   te readdir() - struct dirent *readdir(DIR *dirp); - function.
//         //   */
//         //
//         //   // this is a pointer to a "dirent" structure representing the next directory
//         //   // entry in the directory stream pointed to by out_dir:
//         //   // this will point to the call to readdir() for out_dir
//         //   if(output_dir == NULL) {
//         //     perror("\t\toutput_dir is NULL. \n"); // what is this "progname"?
//         //     exit(EXIT_FAILURE);
//         //   }
//         //
//         //   if (tmp_dir == NULL) {
//         //     printf("\t\ttmp_dir is NULL \n");
//         //   }
//         //
//         //   printf("\tL 1\n");
//         //   fflush(stdout);
//         //   struct dirent *out_dir_dirent_pointer;
//         //   // this is the pointer to the contents of the output dir:
//         //   printf("\tL 2\n");
//         //   fflush(stdout);
//         //   DIR *out_dir = opendir(output_dir); // Segmentation fault (core dumped)
//         //
//         //   // use opendir() and readdir() or opendir() and stat()?
//         //   printf("\tL 3\n");
//         //   fflush(stdout);
//         //   if(out_dir == NULL) {
//         //     perror("\t\tout_dir was NULL. \n"); // what is this "progname"?
//         //     exit(EXIT_FAILURE);
//         //   }
//         //   // it appears that output_dir is null...
//         //
//         //   // this is a pointer to a "dirent" structure representing the next directory
//         //   // entry in the directory stream pointed to by tp_dir:
//         //   // this will point to the call to readdir() for otp_dir
//         //   printf("\tL 4\n");
//         //   fflush(stdout);
//         //   struct dirent *tmp_dir_dirent_pointer;
//         //   // this is the pointer to the contents of the tmporary dir:
//         //   printf("\tL 5\n");
//         //   fflush(stdout);
//         //   DIR *tp_dir = opendir(tmp_dir);
//         //
//         //   printf("\tL 6\n");
//         //   fflush(stdout);
//         //   out_dir_dirent_pointer = readdir(out_dir);
//         //   printf("\tL 7\n");
//         //   fflush(stdout);
//         //   tmp_dir_dirent_pointer = readdir(tp_dir);
//         //   printf("\tL 8\n");
//         //   fflush(stdout);
//         //
//         //   while(out_dir_dirent_pointer != NULL) {
//         //     printf("\tL 9\n");
//         //     fflush(stdout);
//         //     while(tmp_dir_dirent_pointer != NULL) {
//         //       printf("\tL 10\n");
//         //       fflush(stdout);
//         //       // to check if two versions of the same file:
//         //       // check if out_dir_dirent_pointer.d_name == tmp_dir_dirent_pointer.d_name
//         //       // may need:
//         //       // out_dir_dirent_pointer->d_name == tmp_dir_dirent_pointer->d_name
//         //       if (is_same_file(out_dir_dirent_pointer->d_name, tmp_dir_dirent_pointer->d_name)) {
//         //         printf("\tL 11\n");
//         //         fflush(stdout);
//         //         printf("\tthese files do have the same file path. \n");
//         //       } else {
//         //         printf("\tL 12\n");
//         //         fflush(stdout);
//         //         printf("\tthese files DO NOT have the same file path. \n");
//         //       }
//         //
//         //       break;
//         //     }
//         //
//         //     break;
//         //   }
//         //
//         //   printf("\tL 13\n");
//         //   fflush(stdout);
//         //   closedir(out_dir);
//         //   printf("\tL 14\n");
//         //   fflush(stdout);
//         //   closedir(tp_dir);
//         //
//         //
//         //   break;
//         // }
//       }
//     }
//   }
// }
