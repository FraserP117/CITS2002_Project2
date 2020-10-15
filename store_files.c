#include "mergetars.h"
// functions to read the contents of a directory into the "dir" struct; using the stat() and dirent structures.
// these functions will read the contents of "output_dir" and "tmp_dir" into their respective LINUX_FILE structs.

void store_dir(char *input_dir_name) {

  // this is a pointer to a "dirent" structure representing a file in the input_dir directory
  // this will point to the call to readdir() for input_dir
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
      // strcpy(*output_dir_struct->name, input_dir_dirent_pointer->d_name);
      output_dir_struct->name = strdup((char*)(input_dir_dirent_pointer->d_name));

      // sthe stat struct for the output_dir:
      struct stat *output_dir_stat_struct; // OG was not pointer
      output_dir_stat_struct = malloc(sizeof(struct stat)); // must then free this later

      // int stat(const char *path, struct stat *buf);
      if (stat(input_dir_dirent_pointer->d_name, output_dir_stat_struct) == 0) {
        // now we can read the stat() struct elems into our own struct
        // strcpy(input_dir->array_sub_files, output_dir_stat_struct->st_size);
        input_dir->array_sub_files = strdup((char*)(output_dir_stat_struct->st_size));
      } else {
        perror("could not stat \n");
      }

    if (strcmp(input_dir_name, "tmp_dir") == 0) {
      // init this struct LINUX_DIR tmp_dir;
      strcpy(tmp_dir_struct->name, input_dir_dirent_pointer->d_name);
    }

  }

  void process_dir(char *input_dir_name) {
    ...
    DIR *dirp = opendir(input_dir_name);
    ...
    struct stat *output_dir_stat_struct;
    output_dir_stat_struct = malloc(sizeof(struct stat));
    ...
    dirp->member_for_input_dir = strdup((char*)(output_dir_stat_struct->st_size)); // I get the error here
    ...
  }

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

  closedir(input_dir);
  }

}
