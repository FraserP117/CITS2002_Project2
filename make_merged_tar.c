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

  store_dir_contents(output_dir);
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

    // recursively calls itself for ever dir it finds inside the currnet tarfile:
    store_dir_contents(tmp_dir);
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
  }
}







int main(int argc, char* argv[]) {

  printf("\n");
  printf("\n");
  printf("init_structs(): \n");
  printf("\n");

  init_structs();

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
