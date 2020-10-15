#include "mergetars.h"

// the arguments for all the funcions included here are assumed to be a file "pathname" taken
// from a file inside a tarfile and not including the tarfile.
// need to be able to comapare tarfile mod time - find the latest TARFILE !!!!!!!!!!!!!!!!!!!!!!!!


/*
The inputs are merged to form the output according to the following definitions and rules:

  - Two or more files from different archives are considered the same file if they have the same
    relative pathname (including the name of the directory holding the file and the filename itself).

  - If from different archives, the files "project2/src/mergetars.c" and "project2/src/mergetars.c"
    are considered the same file. In contrast, "monday/project2/src/mergetars.c" and
    "wednesday/project2/src/mergetars.c" are considered different files.

  - Two or more files from different archives with the same relative pathname, are considered
    different versions of the same file. The output archive should contain just the latest of all such versions.

  - If two or more files have the same modification time, then the largest of these should be copied.

  - If two or more files have the same modification time and size, the file from the latest tarfile
  (on the command-line) should be copied.

  - All other files with different relative pathnames are considered different files.
    The output archive should contain one copy of each different file.
*/


/*
Return true if the 2 files - from 2 different archives - have the same file
path, else return false.
*/

// char template[] = "/tmp/file-XXXXXX"; // length: 16
bool is_same_file(char first_file_path_from_archive[256], char second_file_path_from_archive[256]) {
  int i = 16;
  while (first_file_path_from_archive[i] != '\0' && second_file_path_from_archive[i] == '\0') {
    if (first_file_path_from_archive[i] == second_file_path_from_archive[i]) {
      return true;
      ++i;
    }
  }
  return false;
}

// bool is_same_file(char *first_file_path_from_archive, char *second_file_path_from_archive) {
//   int i = 16;
//   while (first_file_path_from_archive[i] != '\0' && second_file_path_from_archive[i] == '\0') {
//     if (first_file_path_from_archive[i] == second_file_path_from_archive[i]) {
//       return true;
//       ++i;
//     }
//   }
//   return false;
// }

// bool is_same_file(char first_file_path_from_archive[], char second_file_path_from_archive[]) {
//   int i = 16;
//   while (first_file_path_from_archive[i] != '\0' && second_file_path_from_archive[i] == '\0') {
//     if (first_file_path_from_archive[i] == second_file_path_from_archive[i]) {
//       return true;
//       ++i;
//     }
//   }
//   return false;
// }

/*
Return true if the 2 files are from the same tar archive, false otherwise.
*/
bool is_from_same_archive(char first_file_path_from_archive[], char second_file_path_from_archive[]) {
  for (int i = 0; i <= 16; ++i) {
    if (first_file_path_from_archive[i] == second_file_path_from_archive[i]) {
      return true;
    }
  }

  return false;
}

/*
Return true if the 2 files are simply different versions of the same file,
false otherwise.
*/
bool is_different_version(char first_file_path_from_archive[], char second_file_path_from_archive[]) {
  return false;
  // is this not just is_same_file() ???
  // ask on help fourm
}

/*
Return true if the 2 files have the same modification time, false otherwise.
*/
// do these have to be strictly "filenames" - and not file pathnames - in oder for the stat buff thing to work?
bool is_same_mod_time(char first_file_path_from_archive[], char second_file_path_from_archive[]) {
  // fork() execl() wait using "tar -tvf [name of tarfile]" in order to get the size and mod time?
  // stat() is probably alright

  /*
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>


  struct stat buffer;
  int         status;
  ...
  status = stat("/home/cnd/mod1", &buffer);
  */

  struct stat stat_buffer_1;
  struct stat stat_buffer_2;

  if(stat(first_file_path_from_archive, &stat_buffer_1) != 0) { // can we 'stat' the file's attributes?
    perror( first_file_path_from_archive );
    exit(EXIT_FAILURE);
  }

  if(stat(second_file_path_from_archive, &stat_buffer_2) != 0) { // can we 'stat' the file's attributes?
    perror( second_file_path_from_archive );
    exit(EXIT_FAILURE);
  }

  else if( S_ISREG( stat_buffer_1.st_mode ) ) {
    if( S_ISREG( stat_buffer_2.st_mode ) ) {
      // assume the mod time will be POSIX time:
      if (ctime( &stat_buffer_1.st_mtime) == ctime( &stat_buffer_2.st_mtime)) {
        return true;
      }
    }
  }

  return false;
}

// printf( "%s is a regular file\n", filename );
//
// // this is the size in bytes:
// printf( "is %i bytes long\n", (int)stat_buffer.st_size );
//
// // this is the mod time:
// printf( "and was last modified on %i\n", (int)stat_buffer.st_mtime);
//
// // this is the POSIX mod time - need this??
// printf( "which was %s", ctime( &stat_buffer.st_mtime) );

/*
Return true if the 2 files have the same size (in terms of bytes),
false otherwise.
*/
bool is_same_file_size(char first_file_path_from_archive[], char second_file_path_from_archive[]) {

  struct stat stat_buffer_1;
  struct stat stat_buffer_2;

  if(stat(first_file_path_from_archive, &stat_buffer_1) != 0) { // can we 'stat' the file's attributes?
    perror( first_file_path_from_archive );
    exit(EXIT_FAILURE);
  }

  if(stat(second_file_path_from_archive, &stat_buffer_2) != 0) { // can we 'stat' the file's attributes?
    perror( second_file_path_from_archive );
    exit(EXIT_FAILURE);
  }

  else if( S_ISREG( stat_buffer_1.st_mode ) ) {
    if( S_ISREG( stat_buffer_2.st_mode ) ) {
      if ((int)stat_buffer_1.st_size == (int)stat_buffer_2.st_size) {
        return true;
      }
    }
  }

  return false;
}


























































// /*
// Return true if the 2 files have the same modification time, false otherwise.
// */
// // do these have to be strictly "filenames" - and not file pathnames - in oder for the stat buff thing to work?
// bool is_same_mod_time(char first_file_path_from_archive[], char second_file_path_from_archive[]) {
//   // fork() execl() wait using "tar -tvf [name of tarfile]" in order to get the size and mod time?
//   // stat() is probably alright
//
//   /*
//   #include <sys/types.h>
//   #include <sys/stat.h>
//   #include <fcntl.h>
//
//
//   struct stat buffer;
//   int         status;
//   ...
//   status = stat("/home/cnd/mod1", &buffer);
//   */
//
//   struct stat stat_buffer_1;
//   struct stat stat_buffer_2;
//
//   /*
//   int         first_tarfile_status;
//   int         second_tarfile_status;
//
//   first_tarfile_status = stat(first_file_path_from_archive, &stat_buffer_1);
//   second_tarfile_status = stat(second_file_path_from_archive, &stat_buffer_2);
//   */
//
//   // we need one for each file...
//   // struct stat stat_buffer;
//
//   if(stat(first_file_path_from_archive, &stat_buffer_1) != 0) { // can we 'stat' the file's attributes?
//     perror( first_file_path_from_archive );
//     exit(EXIT_FAILURE);
//   }
//
//   if(stat(second_file_path_from_archive, &stat_buffer_2) != 0) { // can we 'stat' the file's attributes?
//     perror( second_file_path_from_archive );
//     exit(EXIT_FAILURE);
//   }
//
//   else if( S_ISREG( stat_buffer_1.st_mode ) ) {
//     if( S_ISREG( stat_buffer_2.st_mode ) ) {
//       // assume the mod time will be POSIX time:
//       if (ctime( &stat_buffer_1.st_mtime) == ctime( &stat_buffer_2.st_mtime)) {
//         return true;
//       }
//     }
//   }
//
//   return false;
// }
//
// // printf( "%s is a regular file\n", filename );
// //
// // // this is the size in bytes:
// // printf( "is %i bytes long\n", (int)stat_buffer.st_size );
// //
// // // this is the mod time:
// // printf( "and was last modified on %i\n", (int)stat_buffer.st_mtime);
// //
// // // this is the POSIX mod time - need this??
// // printf( "which was %s", ctime( &stat_buffer.st_mtime) );
//
// /*
// Return true if the 2 files have the same size (in terms of bytes),
// false otherwise.
// */
// bool is_same_file_size(char first_file_path_from_archive[], char second_file_path_from_archive[]) {
//
//   struct stat stat_buffer_1;
//   struct stat stat_buffer_2;
//
//   /*
//   int         first_tarfile_status;
//   int         second_tarfile_status;
//
//   first_tarfile_status = stat(first_file_path_from_archive, &stat_buffer_1);
//   second_tarfile_status = stat(second_file_path_from_archive, &stat_buffer_2);
//   */
//
//   if(stat(first_file_path_from_archive, &stat_buffer_1) != 0) { // can we 'stat' the file's attributes?
//     perror( first_file_path_from_archive );
//     exit(EXIT_FAILURE);
//   }
//
//   if(stat(second_file_path_from_archive, &stat_buffer_2) != 0) { // can we 'stat' the file's attributes?
//     perror( second_file_path_from_archive );
//     exit(EXIT_FAILURE);
//   }
//
//   else if( S_ISREG( stat_buffer_1.st_mode ) ) {
//     if( S_ISREG( stat_buffer_2.st_mode ) ) {
//       if ((int)stat_buffer_1.st_size == (int)stat_buffer_2.st_size) {
//         return true;
//       }
//     }
//   }
//
//   return false;
// }
