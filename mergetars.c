#include "mergetars.h"

struct LINUX_FILE {
  char *file_path_name; // first name is always the tmp dir for the tarfile
  int file_size;
  int file_mod_time; // type time_t ??
  int num_subfiles; // need this if using *next_file ???
  bool isdir; // need this if using *next_file ?????

  LINUX_FILE *next_file;
};


void init_structs(void) {                                                        // 1

  // struct LINUX_FILE *output_file_struct = NULL;
  output_file_struct = malloc(sizeof(struct LINUX_FILE));
  output_file_struct->file_path_name = malloc(sizeof(char*) * MAXPATHLEN);
  output_file_struct->file_size = 0;
  output_file_struct->file_mod_time = 0;
  output_file_struct->num_subfiles = 0;
  output_file_struct->isdir = true;

  // struct LINUX_FILE *tmp_file_struct = NULL;
  tmp_file_struct = malloc(sizeof(struct LINUX_FILE));
  tmp_file_struct->file_path_name = malloc(sizeof(char*) * MAXPATHLEN);
  tmp_file_struct->file_size = 0;
  tmp_file_struct->file_mod_time = 0;
  tmp_file_struct->num_subfiles = 0;
  tmp_file_struct->isdir = true;

  // next file in curr dir for output
  next_file_struct_for_output = malloc(sizeof(struct LINUX_FILE));
  next_file_struct_for_output->file_path_name = malloc(sizeof(char*) * MAXPATHLEN);
  next_file_struct_for_output->file_size = 0;
  next_file_struct_for_output->file_mod_time = 0;
  next_file_struct->num_subfiles = 0;
  next_file_struct_for_output->isdir = true;

  // next file in curr dir for tmp
  next_file_struct_for_tmp = malloc(sizeof(struct LINUX_FILE));
  next_file_struct_for_tmp->file_path_name = malloc(sizeof(char*) * MAXPATHLEN);
  next_file_struct_for_tmp->file_size = 0;
  next_file_struct_for_tmp->file_mod_time = 0;
  tmp_file_struct->num_subfiles = 0;
  next_file_struct_for_tmp->isdir = true;
}



// void init_structs(struct LINUX_FILE *output_file_struct, struct LINUX_FILE *tmp_file_struct) {
//
//   // struct LINUX_FILE *output_file_struct = NULL;
//   output_file_struct = malloc(sizeof(struct LINUX_FILE));
//   output_file_struct->file_path_name = malloc(sizeof(char*) * MAXPATHLEN);
//   output_file_struct->file_size = 0;
//   output_file_struct->file_mod_time = 0;
//   output_file_struct->isdir = true;
//
//   // struct LINUX_FILE *tmp_file_struct = NULL;
//   tmp_file_struct = malloc(sizeof(struct LINUX_FILE));
//   tmp_file_struct->file_path_name = malloc(sizeof(char*) * MAXPATHLEN);
//   tmp_file_struct->file_size = 0;
//   tmp_file_struct->file_mod_time = 0;
//   tmp_file_struct->isdir = true;
// }












// void init_structs() {
//
//   struct LINUX_FILE *output_dir_file = NULL;
//   output_dir_file = malloc(sizeof(struct LINUX_FILE));
//
//   // struct LINUX_FILE {
//   //   char *file_path_name;
//   //   int file_size;
//   //   int file_mod_time;
//   //   bool isdir;
//   // };
//
//   output_dir_file->sub_file_path_name = NULL;
//   // for (int i = 0; i < MAXPATHLEN; ++i) {
//   //   output_dir_file->sub_file_path_name[i] = '\0';
//   // }
//   output_dir_file->sub_file_size = 0;
//   output_dir_file->sub_file_mod_time = 0; // error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘->’ token
//
//   // LINUX_FILE *tmp_dir_file_pointer = &tmp_dir_file;
//   // LINUX_FILE tmp_dir_file = malloc(sizeof(struct file));
//   struct LINUX_FILE *tmp_dir_file = NULL;
//   tmp_dir_file = malloc(sizeof(struct LINUX_FILE));
//
//   tmp_dir_file->sub_file_path_name = NULL;
//   // for (int j = 0; j < MAXPATHLEN; ++j) {
//   //   tmp_dir_file->sub_file_path_name[j] = '\0';
//   // }
//   tmp_dir_file->sub_file_size = 0;
//   tmp_dir_file->sub_file_mod_time = 0;
//
//   // LINUX_DIR *output_dir_struct_pointer = &output_dir_struct;
//   // LINUX_DIR output_dir_struct = malloc(sizeof(struct directory));
//   struct LINUX_DIR *output_dir_struct = NULL;
//   output_dir_struct = malloc(sizeof(struct LINUX_DIR));
//   // point to the entire struct or no???
//   output_dir_struct->array_sub_files = (struct file**)&output_dir_file;
//
//   output_dir_struct->name = NULL;
//   output_dir_struct->array_sub_files = NULL;
//   output_dir_struct->array_sub_dirs = NULL;
//
//   // LINUX_DIR *tmp_dir_struct_pointer = &tmp_dir_struct;
//   // LINUX_DIR tmp_dir_struct = malloc(sizeof(struct directory));
//   struct LINUX_DIR *tmp_dir_struct = NULL;
//   tmp_dir_struct = malloc(sizeof(struct LINUX_DIR));
//   tmp_dir_struct->array_sub_files = (struct file**)&tmp_dir_file;
//
//   // LINUX_DIR tmp_dir_struct = NULL;
//   tmp_dir_struct->name = NULL;
//   tmp_dir_struct->array_sub_files = NULL;
//   tmp_dir_struct->array_sub_dirs = NULL;
// }




















// // function to init the tar_file fields:
// void init_structs(void) {
//   for (int i = 0; i < ntarfiles; i++) {
//
//     INPUT_FILE *file_ptr = &file[i];
//
//     file_ptr -> file_size = 0;
//     file_ptr -> file_path_name = malloc(sizeof nsubfiles * sub_file_size);
//     file_ptr -> file_mod_time = 0;
//
//     INPUT_FILE *next_file_ptr = &next_file[i];
//
//     next_file_ptr -> next_file_ptr[i];
//   }
// }






// // function to init the tar_file fields:
// void init_structs(void) {
//   for (int i = 0; i < ntarfiles; i++) {
//
//     INPUT_FILE *tar_files_ptr = &tar_files[i];
//
//     tar_files_ptr -> tar_file_size = 0;
//     tar_files_ptr -> tar_file_path_name = NULL; // from stat() struct
//
//     for (int j = 0; j < nsubfiles; j++) {
//
//       GENERIC_FILE *subfile_ptr = &sub_file[j];
//
//       sub_file -> tar_files_ptr[i];
//       sub_file -> sub_file_path_name = NULL;
//       sub_file -> sub_file_size = 0;
//       sub_file -> sub_file_mod_time = 0; // fron stat() struct
//
//       sub_file -> sub_file_path_name = malloc(sizeof nsubfiles * sub_file_size);
//     }
//   }
// }



// function to init the tar_file fields:
// void init_structs(void) {
//   for (int i = 0; i < ntarfiles; i++) { // ntarfiles = argc-2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//     struct stat stat_buffer_1;
//
//     if( S_ISREG( stat_buffer_1.st_mode ) ) {
//       tar_file_ptr[i].tar_file_size = 0;         // from stat() struct
//       tar_file_ptr[i].tar_file_path_name = tarfile_names[i]; // tarfile_names init via the from the comand line
//     }
//
//     for (int j = 0; j < nsubfiles; j++) {
//       // tar_file_ptr[i].sub_file[j].sub_file_path_name = strcat(tarfile_names[i], SUB_FILE_PATH_NAME); // the concatenation of the tarfile pathname with the pathname of the contents of this tarfile
//       tar_file_ptr[i].sub_file[j].sub_file_size = 0;
//       tar_file_ptr[i].sub_file[j].sub_file_mod_time = 0; // fron stat() struct
//
//       tar_file_ptr[i].sub_file[j].sub_file_path_name = malloc(sizeof nsubfiles * sub_file_size);
//     }
//   }
// }
