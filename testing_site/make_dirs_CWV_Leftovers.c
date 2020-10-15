/*
General Notes:

Order of operations version 1:
1. extract from a tarfile
2. store this away in the mega struct
3. "expand" and make the equivalent directory by filling out with data from the mega struct.

Order of operations version 2:
1. For each tarfile make an equivalent directory.
2. extract the contents of this tarfile into this directory - this is the "expansion".
3. tar -xvf public_html-14-09-12.tar -C mkdtemp("the equivalent directory for the tar archive").
    * probably using: mkdtemp().

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
*/


// General Questions:
/*
* How is the modification date displayed? and will the discrepancy between "our" -tvf and "Chris"
  - is it o to use stat() for this??
*/





/*
1. char *mkdtemp(char *template);
  ERRORS
  EINVAL The last six characters of template were not XXXXXX.  Now template is unchanged.
*/
/*
execl(  "./goodchessmove",      // on-disk location of program
                "goodchessmove",        // its argv[0]
                gamestate,              // its argv[1]
                outputfile,             // its argv[2]
                NULL
            );
*/


/*
This function reads in the output from tar -xvf tarfile.tar
into a unique, temporary directory.
*/

// WITHOUT FORK - EXTRAT INTO mkdirtemp():
/*
int make_an_expanded_dir(char tarfile[]) {
  // this function is supposed to extract a tar archive into the result of "mkdtemp(template)"
  // char *temp_dir = mkdtemp(template); // Segmentation fault (core dumped)

  // the template for the temporary directory:
  char template[] = "/tmp/file-XXXXXX";
  // the temporary directory:
  char *temp_dir = mkdtemp(template);
  // the cmd line refference to the tarfile:
  // printf("error 3\n");
  // char *the_tarfile = strcat(tarfile, ".tar");

  // this needs to be beefed up
  if(temp_dir == NULL) {
    perror("mkdtemp failed: ");
    return 0;
  }

  // the location of tar is found by the cmdline thing type tar
  // do we want to frok() an excel()???

  execl("/usr/bin/tar",
        "tar",
        "-xf", // -xvf for testing!
        tarfile, // this is actually tar_2.tar
        "-C",
        temp_dir,
        NULL
  );
}
*/




// WITHOUT FORK - EXTRACT INTO "NORMAL" DIRECTORY:
/*
int make_an_expanded_dir(char tarfile[]) {
  // this function is supposed to extract a tar archive into the result of "mkdtemp(template)"
  // char *temp_dir = mkdtemp(template); // Segmentation fault (core dumped)

  // the template for the temporary directory:
  printf("error 1\n");
  char template[] = "/tmp/file-XXXXXX";
  // the temporary directory:
  printf("error 2\n");
  char *temp_dir = mkdtemp(template);
  // the cmd line refference to the tarfile:
  // printf("error 3\n");
  // char *the_tarfile = strcat(tarfile, ".tar");

  // this needs to be beefed up
  if(temp_dir == NULL) {
    perror("mkdtemp failed: ");
    return 0;
  }

  // the location of tar is found by the cmdline thing type tar
  // do we want to frok() an excel()???

  printf("before the execl()\n");

  execl("/usr/bin/tar",
        "tar",
         "-xvf",
         tarfile, // this is actually tar_2.tar
         "-C",
         "TARGET_DIR/",
         NULL
  );
}
*/
