#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/param.h> // int MAXPATHLEN;

#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int MAXPATHLEN has a value of 1024 (bytes).

// tarfile stuff:
extern char **tarfile_names; // pointer to an array of strings
extern int ntarfiles;
extern int nsubfiles;
extern int nfiles_in_tar_archive;   //do we still need this?

// a structure to hold the elements of a tarfile:
// do we even need this at all???
typedef struct tarfile {
  int tar_file_size;         // this is from the stat struct.
  char *tar_file_path_name;  // this is the "last" tarfile input on the command line (argv[-1]).

  struct subfile {
    char *sub_file_path_name; // from the stat struct.
    int sub_file_size;
    int sub_file_mod_time; // this is from the another stat struct.
  } *sub_file;
} INPUT_FILE;

// extern INPUT_FILE *tar_files;
extern INPUT_FILE tar_files;
extern INPUT_FILE *tar_file_ptr;

extern int SUB_FILE_PATH_NAME;





// input tarfile info:
extern int tar_file_size;
extern char tar_file_mod_time;

// subfile info:
extern char *sub_file_path;
extern int sub_file_size;
extern char sub_file_mod_time;

// the tarfile parser:
extern void parse_tarfiles(char[]);

// function to init the tar_file fields: mergetars.c
extern void init_structs(void);

// the checker functions:
// extern bool is_same_file(char first_file_path_from_archive[], char second_file_path_from_archive[]);
extern bool is_same_file(char *first_file_path_from_archive, char *second_file_path_from_archive);
extern bool is_from_same_archive(char first_file_path_from_archive[], char second_file_path_from_archive[]);
extern bool is_different_version(char first_file_path_from_archive[], char second_file_path_from_archive[]);
extern bool is_same_mod_time(char first_file_path_from_archive[], char second_file_path_from_archive[]);
extern bool is_same_file_size(char first_file_path_from_archive[], char second_file_path_from_archive[]);

// make_dirs functions:
extern char* make_an_expanded_dir(char *tarfile);
// extern void make_an_expanded_dir(char *tarfile);

// make_merged_tar functions - merges a set of tarfiles into one.
extern void merge_tar_archives(char **tarfile_names);















// // initial structure contents:
// extern struct all_tarfiles;
// extern struct one_tarfile;
// extern struct subfile;
//
// extern char file_path[MAXPATHLEN];
// extern int file_size;
// extern char mod_time[2];
//
// // final structure contents:
// // add to list of questions
// extern struct all_unique_tarfiles;
// extern struct Unique_subfile;
// extern struct Unique_subfile_file_info;
//
// extern char u_file_path[MAXPATHLEN];
// extern int u_file_size;
// extern char u_mod_time[2];
