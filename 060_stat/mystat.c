#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

//This fuction takes in st_mode and a permission string, and fills it with filetype infomation
void getpermission(long st_mode, char * permission) {
  //first character
  switch (st_mode & S_IFMT) {
    case S_IFBLK:
      permission[0] = 'b';
      break;
    case S_IFCHR:
      permission[0] = 'c';
      break;
    case S_IFDIR:
      permission[0] = 'd';
      break;
    case S_IFIFO:
      permission[0] = 'p';
      break;
    case S_IFLNK:
      permission[0] = 'l';
      break;
    case S_IFREG:
      permission[0] = '-';
      break;
    case S_IFSOCK:
      permission[0] = 's';
      break;
    default:
      permission[0] = '?';
      fprintf(stderr, "filetype unknown\n");
      break;
  }
  //second character
  permission[1] = ((st_mode & S_IRUSR) != 0) ? 'r' : '-';
  //third character
  permission[2] = ((st_mode & S_IWUSR) != 0) ? 'w' : '-';
  //forth character
  permission[3] = ((st_mode & S_IXUSR) != 0) ? 'x' : '-';
  //fifth character
  permission[4] = ((st_mode & S_IRGRP) != 0) ? 'r' : '-';
  //sixth character
  permission[5] = ((st_mode & S_IWGRP) != 0) ? 'w' : '-';
  //seventh character
  permission[6] = ((st_mode & S_IXGRP) != 0) ? 'x' : '-';
  //eighth character
  permission[7] = ((st_mode & S_IROTH) != 0) ? 'r' : '-';
  //ninth character
  permission[8] = ((st_mode & S_IWOTH) != 0) ? 'w' : '-';
  //tenth character
  permission[9] = ((st_mode & S_IXOTH) != 0) ? 'x' : '-';
  //last character
  permission[10] = '\0';  //last character should be null terminator
}

//this function takes in a filename and prints the stat message
int printfstat(char * filename) {
  struct stat sb;
  if (lstat(filename, &sb) == -1) {  //lstat return -1 when error
    fprintf(stderr, "Failure in reading filename into a struct\n");
    return EXIT_FAILURE;
  }

  //first line
  if (S_ISLNK(sb.st_mode)) {  //if the file is a link
    char linktarget[256];
    ssize_t len = readlink(filename, linktarget, 256);
    if (len >= 0) {  //readlink return -1 when error
      if (len > 255) {
        linktarget[255] = '\0';  //add null terminator
      }
      else {
        linktarget[len] = '\0';  //add null terminator
      }
      printf("  File: %s -> %s\n", filename, linktarget);
    }
    else {
      fprintf(stderr, "Failure in putting targetname in linktarget\n");
      return EXIT_FAILURE;
    }
  }
  else {
    printf("  File: %s\n", filename);
  }

  //second line
  char * filetype = NULL;
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      filetype = "block special file";
      break;
    case S_IFCHR:
      filetype = "character special file";
      break;
    case S_IFDIR:
      filetype = "directory";
      break;
    case S_IFIFO:
      filetype = "fifo";
      break;
    case S_IFLNK:
      filetype = "symbolic link";
      break;
    case S_IFREG:
      filetype = "regular file";
      break;
    case S_IFSOCK:
      filetype = "socket";
      break;
    default:
      filetype = "unknown?";
      break;
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         sb.st_size,
         sb.st_blocks,
         sb.st_blksize,
         filetype);

  //third line
  if ((S_ISCHR(sb.st_mode)) || (S_ISBLK(sb.st_mode))) {  //if the file is a device
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink,
           major(sb.st_rdev),
           minor(sb.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink);
  }

  //forth line
  char permission[11] = "";  //10 character permission plus a null terminator
  getpermission(sb.st_mode, permission);
  printf("Access: (%04o/%s)", sb.st_mode & ~S_IFMT, permission);

  struct passwd * pw;
  pw = getpwuid(sb.st_uid);
  printf("  Uid: (%5d/%8s)", sb.st_uid, pw->pw_name);

  struct group * gr;
  gr = getgrgid(sb.st_gid);
  printf("   Gid: (%5d/%8s)\n", sb.st_gid, gr->gr_name);

  //fifth line
  char * atimestr = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  printf("Access: %s\n", atimestr);
  free(atimestr);

  //sixth line
  char * mtimestr = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  printf("Modify: %s\n", mtimestr);
  free(mtimestr);

  //seventh line
  char * ctimestr = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
  printf("Change: %s\n", ctimestr);
  free(ctimestr);

  //eighth line
  printf(" Birth: -\n");

  return 0;  //return 0 when success
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "Missing input operand\n");
    return EXIT_FAILURE;
  }

  for (int i = 1; i < argc; i++) {
    if (printfstat(argv[i]) != 0) {  //printstat return 0 when success
      fprintf(stderr, "Failure in printfstat\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
