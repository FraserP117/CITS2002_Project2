#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/param.h> // int MAXPATHLEN has a value of 1024 (bytes).

#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern int num_sub_files;
extern int ntarfiles;
extern char **tarfile_names; // pointer to an array of strings
extern char *tmp_dir;
extern char *output_dir;
extern char *temporary_directory;

struct LINUX_FILE {
  char *file_path_name; // first name is always the tmp dir for the tarfile
  int file_size;
  int file_mod_time; // type time_t ??
  int num_subfiles; // need this if using *next_file ???
  bool isdir; // need this if using *next_file ?????

  LINUX_FILE *next_file;
};

// the output_dir and tmp_dir struct pointers:
extern struct LINUX_FILE *output_file_struct;
extern struct LINUX_FILE *tmp_file_struct;

extern struct LINUX_FILE *next_file_struct_for_tmp;
extern struct LINUX_FILE *next_file_struct_for_output;

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
extern char* make_a_temporary_dir(char *tarfile);
// extern void make_an_expanded_dir(char *tarfile);

// make_merged_tar functions - merges a set of tarfiles into one.
// extern void merge_tar_archives(char **tarfile_names);
extern void expand_tarfile(char *input_tarfile_name, char *temporary_directory);
extern void merge_output_and_tmp(char **tarfile_names);
extern void store_dir_contents(struct LINUX_FILE *input_file_struct, char *input_dir_name);
