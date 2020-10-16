#include "mergetars.h"
// functions to read the contents of a directory into the "dir" struct; using the stat() and dirent structures.
// these functions will read the contents of "output_dir" and "tmp_dir" into their respective LINUX_FILE structs.

void store_dir_contents(struct LINUX_FILE *input_file_struct, char *input_dir_name) { // call this function on each of the char **tarfile_names

  // this is a pointer to a "dirent" structure representing a file in the input_dir directory
  struct dirent *input_dir_dirent_pointer;
  // this is the pointer to the contents of the output dir:
  DIR *input_dir = opendir(input_dir_name);
  printf("P 1 \n");

  if (input_dir == NULL) {
    perror("could not open the input directory! \n");
    exit(EXIT_FAILURE);
  }

  while ((input_dir_dirent_pointer = readdir(input_dir)) != NULL) {

    num_sub_files++;
    // realloc the subfile struct here ??

    printf("P 2 \n");

    // read the name of all the files from input_dir into the struct for input_dir
    //  Do this with the d_name field from the dirent struct for input_dir
    printf("P 3 \n");
    // init this struct LINUX_DIR output_dir;
    input_file_struct->file_path_name = strdup(input_dir_dirent_pointer->d_name);
    printf("P 4 \n");

    // sthe stat struct for the output_dir:
    struct stat *output_dir_stat_struct; // OG was not pointer
    printf("P 5 \n");
    output_dir_stat_struct = malloc(sizeof(struct stat)); // must then free this later
    printf("P 6 \n");

    // int stat(const char *path, struct stat *buf);
    if (stat(input_dir_dirent_pointer->d_name, output_dir_stat_struct) == 0) {
      printf("P 7 \n");
      // now we can read the stat() struct elems into our own struct
      input_file_struct->file_size = output_dir_stat_struct->st_size;
      printf("P 8 \n");
      input_file_struct->file_mod_time = output_dir_stat_struct->st_mtime;
      printf("P 9 \n");

      if (S_ISREG(output_dir_stat_struct->st_mode) != 0) {
        printf("P 10 \n");
        input_file_struct->isdir = false;
        printf("P 11 \n");
      }
      if (S_ISDIR(output_dir_stat_struct->st_mode) != 0) {
        printf("P 12 \n");
        input_file_struct->isdir = true;
        printf("P 13 \n");
        // we need to change the input file struct to one of the dirs that were found in the first call to store_dir_contents()
        store_dir_contents(input_file_struct, input_dir_dirent_pointer->d_name);
      }

    } else {
      perror("could not stat \n");
    }
  }
  // free(output_dir_stat_struct); do this here ??
  // free(tmp_dir_stat_struct); do this here ??
  closedir(input_dir);
}



// void store_dir_contents(char *input_dir_name) { // call this function on each of the char **tarfile_names
//   printf("hello world! \n");
//
//   // this is a pointer to a "dirent" structure representing a file in the input_dir directory
//   struct dirent *input_dir_dirent_pointer;
//   // this is the pointer to the contents of the output dir:
//   DIR *input_dir = opendir(input_dir_name);
//   printf("P 1 \n");
//
//   if (input_dir == NULL) {
//     perror("could not open the input directory! \n");
//     exit(EXIT_FAILURE);
//   }
//
//   while ((input_dir_dirent_pointer = readdir(input_dir)) != NULL) {
//
//     printf("P 2 \n");
//
//     // read the name of all the files from input_dir into the struct for input_dir
//     //  Do this with the d_name field from the dirent struct for input_dir
//     if (strcmp(input_dir_name, "output_dir") == 0) {
//
//       printf("P 3 \n");
//       // init this struct LINUX_DIR output_dir;
//       output_file_struct->file_path_name = strdup(input_dir_dirent_pointer->d_name);
//       printf("P 4 \n");
//
//       // sthe stat struct for the output_dir:
//       struct stat *output_dir_stat_struct; // OG was not pointer
//       printf("P 5 \n");
//       output_dir_stat_struct = malloc(sizeof(struct stat)); // must then free this later
//       printf("P 6 \n");
//
//       // int stat(const char *path, struct stat *buf);
//       if (stat(input_dir_dirent_pointer->d_name, output_dir_stat_struct) == 0) {
//         printf("P 7 \n");
//         // now we can read the stat() struct elems into our own struct
//         output_file_struct->file_size = output_dir_stat_struct->st_size;
//         printf("P 8 \n");
//         output_file_struct->file_mod_time = output_dir_stat_struct->st_mtime;
//         printf("P 9 \n");
//
//         if (S_ISREG(output_dir_stat_struct->st_mode) != 0) {
//           printf("P 10 \n");
//           output_file_struct->isdir = false;
//           printf("P 11 \n");
//         }
//         if (S_ISDIR(output_dir_stat_struct->st_mode) != 0) {
//           printf("P 12 \n");
//           output_file_struct->isdir = true;
//           printf("P 13 \n");
//           store_dir_contents(input_dir_dirent_pointer->d_name);
//         }
//
//       } else {
//         perror("could not stat \n");
//       }
//     }
//
//     if (strcmp(input_dir_name, "tmp_dir") == 0) {
//       printf("P 14 \n");
//       // init this struct LINUX_DIR tmp_dir;
//       tmp_file_struct->file_path_name = strdup(input_dir_dirent_pointer->d_name);
//       printf("P 15 \n");
//
//       // the stat struct for the tmp_dir:
//       struct stat *tmp_dir_stat_struct; // OG was not pointer
//       printf("P 16 \n");
//       tmp_dir_stat_struct = malloc(sizeof(struct stat)); // must then free this later
//       printf("P 17 \n");
//
//       // int stat(const char *path, struct stat *buf);
//       if (stat(input_dir_dirent_pointer->d_name, tmp_dir_stat_struct) == 0) {
//         printf("P 18 \n");
//         // now we can read the stat() struct elems into our own struct
//         tmp_file_struct->file_size = tmp_dir_stat_struct->st_size;
//         printf("P 19 \n");
//         tmp_file_struct->file_mod_time = tmp_dir_stat_struct->st_mtime;
//         printf("P 20 \n");
//
//         if (S_ISREG(tmp_dir_stat_struct->st_mode) != 0) {
//           printf("P 21 \n");
//           tmp_file_struct->isdir = false;
//         }
//         if (S_ISDIR(tmp_dir_stat_struct->st_mode) != 0) {
//           printf("P 22 \n");
//           tmp_file_struct->isdir = true;
//           printf("P 23 \n");
//           store_dir_contents(input_dir_dirent_pointer->d_name);
//         }
//
//       } else {
//         perror("could not stat \n");
//       }
//     }
//   }
//   // free(output_dir_stat_struct); do this here ??
//   // free(tmp_dir_stat_struct); do this here ??
//   closedir(input_dir);
// }
