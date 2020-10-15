#include "mergetars.h"
// functions to read the contents of a directory into the "dir" struct; using the stat() and dirent structures.
// these functions will read the contents of "output_dir" and "tmp_dir" into their respective LINUX_FILE structs.


void store_dir_contents(char *input_dir_name) { // call this function on each of the char **tarfile_names

  // this is a pointer to a "dirent" structure representing a file in the input_dir directory
  struct dirent *input_dir_dirent_pointer;
  // this is the pointer to the contents of the output dir:
  DIR *input_dir = opendir(input_dir_name);

  if (input_dir == NULL) {
    perror("could not open the input directory! \n");
    exit(EXIT_FAILURE);
  }

  while ((input_dir_dirent_pointer = readdir(input_dir)) != NULL) {

    // read the name of all the files from input_dir into the struct for input_dir
    //  Do this with the d_name field from the dirent struct for input_dir
    if (strcmp(input_dir_name, "output_dir") == 0) {
      // init this struct LINUX_DIR output_dir;
      output_file_struct->file_path_name = strdup(input_dir_dirent_pointer->d_name);

      // sthe stat struct for the output_dir:
      struct stat *output_dir_stat_struct; // OG was not pointer
      output_dir_stat_struct = malloc(sizeof(struct stat)); // must then free this later

      // int stat(const char *path, struct stat *buf);
      if (stat(input_dir_dirent_pointer->d_name, output_dir_stat_struct) == 0) {
        // now we can read the stat() struct elems into our own struct
        output_file_struct->file_size = output_dir_stat_struct->st_size;
        output_file_struct->file_mod_time = output_dir_stat_struct->st_mtime;

        if (S_ISREG(output_dir_stat_struct->st_mode) != 0) {
          output_file_struct->isdir = false;
        }
        if (S_ISDIR(output_dir_stat_struct->st_mode) != 0) {
          output_file_struct->isdir = true;
          store_dir_contents(input_dir_dirent_pointer->d_name);
        }

      } else {
        perror("could not stat \n");
      }

      if (strcmp(input_dir_name, "tmp_dir") == 0) {
        // init this struct LINUX_DIR tmp_dir;
        tmp_file_struct->file_path_name = strdup(input_dir_dirent_pointer->d_name);

        // the stat struct for the tmp_dir:
        struct stat *tmp_dir_stat_struct; // OG was not pointer
        tmp_dir_stat_struct = malloc(sizeof(struct stat)); // must then free this later

        // int stat(const char *path, struct stat *buf);
        if (stat(input_dir_dirent_pointer->d_name, tmp_dir_stat_struct) == 0) {
          // now we can read the stat() struct elems into our own struct
          tmp_file_struct->file_size = tmp_dir_stat_struct->st_size;
          tmp_file_struct->file_mod_time = tmp_dir_stat_struct->st_mtime;

          if (S_ISREG(tmp_dir_stat_struct->st_mode) != 0) {
            tmp_file_struct->isdir = false;
          }
          if (S_ISDIR(tmp_dir_stat_struct->st_mode) != 0) {
            tmp_file_struct->isdir = true;
            store_dir_contents(input_dir_dirent_pointer->d_name);
          }

        } else {
          perror("could not stat \n");
        }
      }
    }
  }
  closedir(input_dir);
}



//   actually, forget the above; this is what I have:
// ```c
// void process_dir(char *input_dir_name) {
//   ...
//    a_dir_struct->dir_struct_member->file_struct_member = strdup(dirent_pointer->d_name);
//    ...
//  }
//
// // in another file:
// struct MY_DIR *a_dir_struct = NULL;
// a_dir_struct = malloc(sizeof(struct MY_DIR));
//
// struct MY_FILE *a_file_struct = NULL;
// a_file_struct = malloc(sizeof(struct MY_FILE));
// ```

  // void process_dir(char *input_dir_name) {
  //   ...
  //   a_dir_struct->dir_struct_member->file_struct_member = strdup(dirent_pointer->d_name);
  //   ...
  // }
  //

  /*
  typedef struct file { // was struct LINUX_FILE
    // int nsub_files;
    char *sub_file_path_name;
    int sub_file_size;
    int sub_file_mod_time;
    bool isdir;
  } LINUX_FILE;

  // the structs:
  typedef struct directory {
    char *name;
    struct file **array_sub_files;
    struct directory **array_sub_dirs; // will need to malloc the size of this for each directroy

  } LINUX_DIR;
  */
