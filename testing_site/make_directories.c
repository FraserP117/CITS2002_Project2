/*
General Notes:


Order of operations version 1:
1. extract from a tarfile
2. store this away in the mega struct
3. "expand" and make the equivalent directory by filling out with data from the mega struct.

Order of operations version 2:
1. For each tarfile make an equivalent directory.
2. extract the contents of this tarfile into this directory - this is the "expansion".
3. tar -xvf public_html-14-09-12.tar -C mkdirtmp("the equivalent directory for the tar archive").
    * probably using: mkdirtmp().




All commands are exec with fork(), ececl() and wait():
  - we need to implement the systemcalls?

we can get the size in bytes and mod time from stat() e.g:
>>> stat sample_1.tar:
>>> File: sample_1.tar
>>> Size: 10240           Blocks: 24         IO Block: 4096   regular file
>>> Device: eh/14d  Inode: 13510798882194159  Links: 1
>>> Access: (0777/-rwxrwxrwx)  Uid: ( 1000/fraser_p)   Gid: ( 1000/fraser_p)
>>> Access: 2020-09-28 13:26:57.692909200 +0800
>>> Modify: 2020-09-28 13:26:46.969176800 +0800
>>> Change: 2020-09-28 13:26:46.969176800 +0800

    * can we "parse" this like an eventfile???



probably will need:
perror(),  exit(),
mkdtemp(),  mkdir(),  opendir(),  readdir(),  stat(),  closedir(),
fork(),  execl(),  wait(),
open(),  read(),  write(),  close(), utimes(),
strcpy(),  strcmp(),  strdup(),
malloc(),  calloc(),  realloc(), and  free()

this whole thing is actually creating the equivalent "directory version" of the tar archive.

this is where we "expand" the tar archives'.

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

* why are open/readdir() suggested?
*/

// since we will be dealing with "cloned" files; we may not ned this - probably can go with it though:
// A structure to hold all data in all tarfiles:
typedef struct tarfiles {
  typedef struct tarfile {
    char file_path[MAXPATHLEN]; // or perhaps: char *file_path[MAXPATHLEN]; ??
    typedef struct subfile {
      int file_size;
      char[2] mod_time; // check both the: dd/mm/yyyy and xy:wz ??
      // perhaps: char *mod_time[2]; ??
    } file_info[2];
    // boolean to keep track of duplicate ???
  } one_tarfile_contents[MAX_FILES_IN_TARFILE];
} all_input_tarfiles[MAX_TARFILES];


/*
want to read in the output from tar -tvf tarfile.tar into the array of structs.
how to "read" the output of -tvf into variables??
it is possible to re-direct cmd-line output:
mabey read this into a file and then read that file??
*/
void parse_tarfiles(char tarfile[]) {

//  ATTEMPT TO OPEN OUR EVENTFILE, REPORTING AN ERROR IF WE CAN'T
// attempting to open a tarfile in this manner will not work:
    FILE *fp    = fopen(tarfile, "r");

    char* tarfile_name = all_input_tarfiles[t];
    char* tar_content_opperator = "tar -tvf ";
    char* tarfile_contents = tar_content_opperator + tarfile_name;
    system(tarfile_contents);

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
}

/*
This will create a bunch of empty directories - the "clone" of all the tar archives:
*/
void expand_archive() {
  //
}

/*
This will create the various files inside each directory and wite the the pathname, mod time and size to each file.
The info to write is stored in the struct.
*/
void fill_archive() {
  //
}
