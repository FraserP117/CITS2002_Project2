#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/param.h>

// int MAXPATHLEN has a value of 1024 (bytes).




/*
General Notes:

decclerations.h:
  containing all globally visible declerations of types, functions and variables

showdown.c:
  containing main()
  checks cmd line arguments and calls functions

globals.c:
  define all global variables required by all files

readstuff.c:
  perform all reading into te structs here

createsingletar.c:
  perform the writing to a single tar file
*/



// General Questions:
/*
* Is it better to do the checks across the tarfiles or possibly write all the tarfiles
to one big file and apply the checks to the giant file???
  * Probably not; given out idea about the "mega struct" that will hold all the contents of the tarfiles.

* We should check that we don't distinguish between duplicates within tarfiles as opposed to
duplicates across tarfiles.

* How is the modification date displayed? and will the discrepancy between "our" -tvf and "Chris"
*/


// the "Mega Struct":
struct {
  struct {
    char file_path[MAXPATHLEN]; // or perhaps: char *file_path[MAXPATHLEN]; ??
    struct {
      int file_size;
      char[2] mod_time; // check both the: dd/mm/yyyy and xy:wz ??
      // perhaps: char *mod_time[2]; ??
    } file_info[2];
    // boolean to keep track of duplicate ???
  } one_tarfile_contents[MAX_FILES_IN_TARFILE];
} all_input_tarfiles[MAX_TARFILES];


// This will be a "Non-Duplicate" struct; the thing from which the output tarfile is constructed.
struct {
  // A struct to hold all info pertaining to each file inside a tarfile:
  struct {
    char file_path[MAXPATHLEN]; // relative pathname of random file from the current tarfile.
    // make sure this is actually an array and not a string.
    struct {
      int file_size;  // size of a random file inside a particular tarfile
      int mod_time;   // mod time for random file in tarfile
    } file_info[2];
    // boolean to keep track of duplicate ???
  } one_tarfile_contents[MAX_FILES_IN_TARFILE];
} all_Unique_tarfiles[MAX_TARFILES];



/*
want to read in the output from tar -tvf tarfile.tar into the array of structs.
how to "read" the output of -tvf into variables??
it is possible to re-direct cmd-line output:
mabey read this into a file and then read that file??
*/
// parse tarfiles or parse tarfile ??
void parse_tarfiles(char tarfile[]) {
    #define LINELEN                 100 // probably handled with dynamic memory allocation...
    #define CHAR_COMMENT            '#' // need this ??

//  ATTEMPT TO OPEN OUR EVENTFILE, REPORTING AN ERROR IF WE CAN'T
    FILE *fp    = fopen(tarfile, "r");

    if(fp == NULL) {
        printf("%s: unable to open '%s'\n", program, eventfile);
        exit(EXIT_FAILURE);
    }

    char    line[MAXPATHLEN]; // this is not technically corect
    // there appear to be 5 "words" on each line of: >>> tar -tvf sample_tar_file.tar
    char    words[5][MAXPATHLEN];
    int     lc = 0;

//  READ EACH LINE FROM THE TARFILE, UNTIL WE REACH THE END-OF-FILE
    while(fgets(line, sizeof line, fp) != NULL) {
        ++lc;

//  COMMENT LINES ARE SIMPLY SKIPPED
        if(line[0] == CHAR_COMMENT) {
            continue;
        }

//  ATTEMPT TO BREAK EACH LINE INTO A NUMBER OF WORDS, USING sscanf()
// there are 6 now.
        int nwords = sscanf(line, "%19s %19s %19s %19s %19s, %19s",
                                    words[0], words[1], words[2], words[3], words[4], words[5]);

        char sub_file_path_name = words[5];
        char sub_file_mod_time  = {words[3], words[4]}; // is char ok ??
        char sub_file_size      = words[2];

//  WE WILL SIMPLY IGNORE ANY LINE WITHOUT ANY WORDS
        if(nwords <= 0) {
            continue;
        }

//  IDENTIFY LINES RECORDING FILE_PATHS/NAMES AND THEIR OTHER VALUES - MOD TIME AND SIZE, STORING THESE VALUES
        if(nwords == 5) {
          for (int t = 0; t < MAX_TARFILES; ++t) {
            for (int sf = 0; sf < MAX_SUB_FILES; ++sf) {

              // the file path for the given file on the given line:
              all_input_tarfiles[t].one_tarfile_contents[sf].file_path = words[5];

              // this file's modification time:
              all_input_tarfiles[t].one_tarfile_contents[sf].file_info[1].mod_time[0] = words[3];
              all_input_tarfiles[t].one_tarfile_contents[sf].file_info[1].mod_time[1] = words[4];

              // the size of this file:
              all_input_tarfiles[t].one_tarfile_contents[sf].file_info[0] = words[2];
            }
        }

        //  UNRECOGNISED LINE
        else {
            printf("%s: line %i of '%s' is unrecognized\n", lc, tarfile);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);

#undef  LINELEN
#undef  WORDLEN
#undef  CHAR_COMMENT
}


/*
This function initializes the datastructures - pertaining to pathnames - inside the "non-duplicate" structure
*/
char check_tarfile_content_name_duplicates(char[] input_tarfile) {
  // do we need to check for duplicates inside a single tarfile???
    // this probably does not metter since any such duplicate will be skipped anyway.

  // for each pair of structs in the tafile struct:
  for (int j = 0; j < MAX_FILES_IN_TARFILE; ++j) {
    for (int i = 0; i < MAX_FILES_IN_TARFILE; ++i) {

      char[] a_file_in_the_current_tarfile = tarfile[i].file_path[j];

      for (int k = 0; k < MAX_FILES_IN_TARFILE; ++k) {
        char[] another_file_in_the_current_tarfile = tarfile[i].file_path[k];
        // now check for equivalence of the two file paths:
        // perhaps have 2 pointers that "walk down" the 2 pathname arrays and at each indexe
        int *first_file_path_index;
        int *second_file_path_index;

        &first_file_path_index = a_file_in_the_current_tarfile;
        &second_file_path_index = another_file_in_the_current_tarfile;

        // start of pathname check
        for (int i = 0; i < sizeof(a_file_in_the_current_tarfile); ++i) {
          for (int k = 0; k < sizeof(another_file_in_the_current_tarfile); ++k) {
            if (a_file_in_the_current_tarfile[i] == another_file_in_the_current_tarfile[k]) {
              // then the 2 paths are the same.
              // these are 2 versions of the same file so check mod time then size:
              if (check_tarfile_date_duplicate(input_tarfile)) {
                //
              }
            } else {
              // the 2 paths are not the same.
            }
          }
        }
      }
    }
  }
}

/*
The following checks for same-name relative file paths for all files inside all tarfiles.
might just do all three checks in one function??
return true if duplicates and false otherwise.
*/
bool is_tarfile_content_duplicate(char[] input_tarfile) {
    // for each pair of structs in the tafile struct:
    for (int j = 0; j < MAX_TARFILES; ++j) {
      for (int i = 0; i < MAX_FILES_IN_TARFILE; ++i) {

        char[] a_file_in_the_current_tarfile = tarfile[j].file_path[i];

        for (int k = 0; k < MAX_FILES_IN_TARFILE; ++k) {
          char[] another_file_in_the_current_tarfile = tarfile[j].file_path[k];
          // now check for equivalence of the two file paths:
          // perhaps have 2 pointers that "walk down" the 2 pathname arrays and at each indexe
          int *first_file_path_index = a_file_in_the_current_tarfile[0];
          int *second_file_path_index = another_file_in_the_current_tarfile[0];

          // start of pathname check
          for (int i = 0; i < sizeof(a_file_in_the_current_tarfile); ++i) {
            for (int k = 0; k < sizeof(another_file_in_the_current_tarfile); ++k) {
              if (a_file_in_the_current_tarfile[i] == another_file_in_the_current_tarfile[k]) {
                // then the 2 paths are the same.
                // these are 2 versions of the same file so check mod time then size:
                return true;
            } else {
              // the 2 files are not the same:
              return false;
            }
          }
        }
      }
    }
  }
}

bool check_tarfile_size_duplicate(char[] input_tarfile) {
  //
}

bool check_tarfile_date_duplicate(char[] input_tarfile) {
  //
}
