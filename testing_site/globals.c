#include "mergetars.h"

char **tarfile_names = NULL;
int ntarfiles = 0;
int nsubfiles = 0;



// the struct for the input tarfiles:
// TAR_FILE *tar_files = NULL;
// INPUT_FILE *tar_files = NULL;
INPUT_FILE tar_files;
INPUT_FILE *tar_file_ptr = &tar_files;


// INPUT_FILE *subfile  = NULL;
// INPUT_FILE *sub_file  = tar_files->sub_file;
// INPUT_FILE *subfile->sub_file;




// INPUT_FILE tar_files;
// INPUT_FILE *tar_files_ptr = &tar_files;
//
// GENERIC_FILE sub_file;
// GENERIC_FILE *subfile_ptr = &sub_file;





// INPUT_FILE file;
// INPUT_FILE next_file;
//
// INPUT_FILE *file_ptr = &file;
// INPUT_FILE *next_file_ptr = &next_file;
