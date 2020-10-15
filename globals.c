#include "mergetars.h"

char **tarfile_names = NULL; // struct with tarfile name and temp dir name

char *tmp_dir = NULL;
char *output_dir = NULL;

// name of the created temporary directory
char *temporary_directory = NULL;

// From the commandline
int ntarfiles = 0;

// Within a directory
int nsubfiles = 0;

// --------------------------------------------------------------------------------

// void init_structs() {
//   struct LINUX_FILE *output_dir_file = NULL;
//   // output_dir_file = malloc(sizeof(struct LINUX_FILE));
//
//   struct LINUX_FILE output_dir_file->sub_file_path_name = NULL;
//   struct LINUX_FILE output_dir_file->sub_file_size = 0;
//   struct LINUX_FILE output_dir_file->sub_file_mod_time = 0;
//   struct LINUX_FILE output_dir_file->sub_file_mod_time = 0;
//
//   // LINUX_FILE *tmp_dir_file_pointer = &tmp_dir_file;
//   // LINUX_FILE tmp_dir_file = malloc(sizeof(struct file));
//   struct LINUX_FILE *tmp_dir_file = NULL;
//   // tmp_dir_file = malloc(sizeof(struct LINUX_FILE));
//
//   struct LINUX_FILE tmp_dir_file->sub_file_path_name = NULL;
//   struct LINUX_FILE tmp_dir_file->sub_file_size = 0;
//   struct LINUX_FILE tmp_dir_file->sub_file_mod_time = 0;
//   struct LINUX_FILE tmp_dir_file->sub_file_mod_time = 0;
//
//
//   // LINUX_DIR *output_dir_struct_pointer = &output_dir_struct;
//   // LINUX_DIR output_dir_struct = malloc(sizeof(struct directory));
//   struct LINUX_DIR *output_dir_struct = NULL;
//   // output_dir_struct = malloc(sizeof(struct LINUX_DIR));
//
//   struct LINUX_DIR output_dir_struct->name = NULL;
//   struct LINUX_DIR output_dir_struct->array_sub_files = NULL;
//   struct LINUX_DIR output_dir_struct->array_sub_dirs = NULL;
//
//   // LINUX_DIR *tmp_dir_struct_pointer = &tmp_dir_struct;
//   // LINUX_DIR tmp_dir_struct = malloc(sizeof(struct directory));
//   struct LINUX_DIR *tmp_dir_struct = NULL;
//   // tmp_dir_struct = malloc(sizeof(struct LINUX_DIR));
//
//   // LINUX_DIR tmp_dir_struct = NULL;
//   struct LINUX_DIR tmp_dir_struct->name = NULL;
//   struct LINUX_DIR tmp_dir_struct->array_sub_files = NULL;
//   struct LINUX_DIR tmp_dir_struct->array_sub_dirs = NULL;
// }


































// need a function to init all these structs:

// // for the file struct - inside the dir struct:
// LINUX_DIR output_dir_file = {
//   .sub_file_path_name = NULL,
//   .sub_file_size = 0,
//   .sub_file_mod_time = 0
// };
// LINUX_FILE *output_dir_file_pointer = &output_dir_file;
//
//
// // for the file struct - inside the dir struct:
// LINUX_DIR tmp_dir_file = {
//   .sub_file_path_name = NULL,
//   .sub_file_size = 0,
//   .sub_file_mod_time = 0
// };
// LINUX_FILE *tmp_dir_file_pointer = &tmp_dir_file;
//
//
// // for the output_dir struct
// LINUX_DIR output_dir_struct = {
//   .size = 0,
//   .name = NULL,
//   .mod_time = 0,
//   .sub_file = file_pointer,
//   .sub_dir = NULL
// };
// LINUX_DIR *output_dir_pointer = &output_dir;
//
// // for the tmp_dir struct
// LINUX_DIR tmp_dir_struct = {
//   .size = 0,
//   .name = NULL,
//   .mod_time = 0,
//   .sub_file = file_pointer,
//   .sub_dir = NULL
// };
// LINUX_DIR *tmp_dir_pointer = &tmp_dir;






































// // for the sub dirs inside dir:
// LINUX_DIR sub_dir = {
//   .size = 0,
//   .name = NULL,
//   .mod_time = 0,
//   .sub_file = file_pointer,
//   .sub_dir = NULL
// };
// LINUX_DIR *sub_dir_pointer = &sub_dir;



// the struct for the input tarfiles:
// TAR_FILE *tar_files = NULL;
// INPUT_FILE *tar_files = NULL;
// INPUT_FILE tar_files;
// INPUT_FILE *tar_file_ptr = &tar_files;

// typedef struct file {
//   char *path_name;
//   int size;
//   int mod_time;
//
//   // struct file *next_file;
//
//   // "sub_file" is a pointer to a list of LINUX_FILE structs
//   // that reccord the info for the files inside the LINUX_FILE for "file".
//   struct sub_file **next_file;
//
// } LINUX_FILE;


// LINUX_FILE output_file = {.path_name = NULL, .size = 0, .mod_time = 0, .next_file = NULL};
// LINUX_FILE tmp_file = {.path_name = NULL, .size = 0, .mod_time = 0, .next_file = NULL};
