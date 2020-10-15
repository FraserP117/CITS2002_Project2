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
// extern int nsubfiles;
// extern int nfiles_in_tar_archive;   //do we still need this?

extern int SUB_FILE_PATH_NAME;
extern int ntarfiles;

extern char **tarfile_names; // pointer to an array of strings
extern char *tmp_dir;
extern char *output_dir;
extern char *temporary_directory;

/*
struct for a directory that holds:
  - the size of the Directory
  - the path name of the directory
  - the mod time of the directoy
  - a pointer to a file_pointer contatining the struct for a sub directory in the curent directory.
  - an array of "file" structs that hold:
    - the pathname of the file
    - the file size
    - the mod time of the file
    - a boolean variable that is "True" if the file is a directory
*/

// typedef struct
// 	{
// 		char s1[81];
// 		char s2[81];
// 		char s3[81];
// 	} Rec;
// 	Rec *a[10]; // is this it??
//
// 	a[0] = (Rec *)malloc(sizeof(Rec));
// 	strcpy(a[0]->s1, "hello");
// 	free(a[0]);

// struct car
// {
//     char make[20];
//     char model[30];
//     int year;
// };
//
// struct car arr_car[10];

//
// typedef struct {
//
//   char *sub_file_path_name;
//   int sub_file_size;
//   int sub_file_mod_time;
//   bool isdir;
//
// } LINUX_FILE;
//
// // the structs:
// typedef struct {
//
//   char *name;
//   struct file **array_sub_files; // struct LINUX_FILE** **array_sub_files;
//   struct directory **array_sub_dirs; // struct LINUX_DIR** **array_sub_dirs;
//
// } LINUX_DIR;


struct LINUX_FILE {

  char *sub_file_path_name;
  int sub_file_size;
  int sub_file_mod_time;
  // bool isdir;

};

// the structs:
struct LINUX_DIR {

  char *name;
  struct file **array_sub_files; // struct LINUX_FILE** **array_sub_files;
  struct directory **array_sub_dirs; // struct LINUX_DIR** **array_sub_dirs;

};

// the structs:
// typedef struct {
//
//   char *name;
//   LINUX_FILE file**;
//   LINUX_DIR directory**;
//
// } LINUX_DIR;

// typedef struct my_meme {
//
//   struct MEME_STRUCT **a_good_meme;
//
// } MEME_STRUCT;

// the output_dir and tmp_dir struct pointers:
extern struct LINUX_DIR *output_dir_struct;
extern struct LINUX_DIR *tmp_dir_struct;

// these are LINUX_DIR struct pointers to the files in the current directory
extern struct LINUX_FILE *output_dir_file;
extern struct LINUX_FILE *tmp_dir_file;

// // the output_dir and tmp_dir struct pointers:
// extern struct LINUX_DIR **output_dir_sub_dir_struct;
// extern struct LINUX_DIR **tmp_dir_sub_dir_struct;

// // these are LINUX_DIR struct pointers to the files in the current directory
// extern struct LINUX_FILE **output_dir_sub_file;
// extern struct LINUX_FILE **tmp_dir_sub_file;





// these are LINUX_DIR struct pointers to the sub directories in the current directory
// extern LINUX_DIR next_dir_in_output_dir_struct;
// extern LINUX_DIR *array_of_output_dir_dir_pointer;
//
// extern LINUX_DIR next_dir_in_tmp_dir_struct;
// extern LINUX_DIR *array_of_tmp_dir_dir_pointers;

// these are LINUX_DIR struct pointers to the files in the current directory
// extern LINUX_FILE *output_dir_file; // only declare a pointer to the struct not the struct itself
// extern LINUX_FILE *tmp_dir_file;











// extern struct LINUX_DIR sub_dir;
// extern struct LINUX_DIR *sub_dir_pointer;

// typedef struct file {
//   char *path_name;
//   int size;
//   int mod_time;
//
//   // struct file *next_file;
//
//   // "sub_file" is a pointer to a list of LINUX_FILE structs
//   // that reccord the info for the files inside the LINUX_FILE for "file".
//   struct sub_file *file_ents;
//
// } LINUX_FILE;

// extern INPUT_FILE *tar_files;
// extern LINUX_FILE output_file;
// extern LINUX_FILE tmp_file;



// extern LINUX_FILE *tar_file_ptr;

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

extern void store_dir(char *input_dir_name);
extern void init_structs();















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
