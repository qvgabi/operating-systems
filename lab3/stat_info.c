#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb);
static void print_ino(const struct stat *sb);
static void print_perms(const struct stat *sb);
static void print_linkc(const struct stat *sb);
static void print_owner(const struct stat *sb);
static void print_size(const struct stat *sb);
static void print_laststch(const struct stat *sb);
static void print_lastacc(const struct stat *sb);
static void print_lastmod(const struct stat *sb);
static void print_name(const struct stat *sb, char *name);
/* -------------------------------------------------------------------------------- */

int  main(int argc, char *argv[])
{
  struct stat sb;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  if (stat(argv[1], &sb) == -1) {
    perror("stat");
    exit(EXIT_SUCCESS);
  }
  
  print_type(&sb);
  print_name(&sb, argv[1]);
  print_ino(&sb);
  print_perms(&sb);
  print_linkc(&sb);
  print_owner(&sb);
  print_size(&sb);
  print_laststch(&sb);
  print_lastacc(&sb);
  print_lastmod(&sb);
  
  exit(EXIT_SUCCESS);
}
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb){
  printf("File type:                ");
switch (sb->st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFSOCK:  printf("socket\n");        break;
	case S_IFLNK:  printf("symbolic link\n");        break;
	case S_IFREG:  printf("regular file\n");        break;
	case S_IFIFO:  printf("FIFO\n");        break;
    default:       printf("unknown?\n");                break;
  }
}
/* -------------------------------------------------------------------------------- */

static void print_ino(const struct stat *sb){
  printf("I-node number:            %ld\n", (long) sb->st_ino);
}
/* -------------------------------------------------------------------------------- */

static void print_perms(const struct stat *sb){

	int perms=0;
	if (sb->st_mode & S_IRUSR) perms+=400;
	if (sb->st_mode & S_IWUSR) perms+=200;
	if (sb->st_mode & S_IXUSR) perms+=100;
	if (sb->st_mode & S_IRGRP) perms+=40;
	if (sb->st_mode & S_IWGRP) perms+=20;
	if (sb->st_mode & S_IXGRP) perms+=10;
	if (sb->st_mode & S_IROTH) perms+=4;
	if (sb->st_mode & S_IWOTH) perms+=2;
	if (sb->st_mode & S_IXOTH) perms+=1;
  printf("Mode:                     %d\n",perms);

    
// printf("Mode: %lo (octal)\n", (unsigned long) (sb->st_mode & ~S_IFMT)
// ); 



	const char* name=getenv("USER");
	struct passwd* user=getpwnam(name);
	if(user->pw_uid==sb->st_uid){
		printf("you are the owner: \n");
	}else if(user->pw_gid==sb->st_gid){
		printf("you are in the owner's group\n");
	}else{printf("you are others\n");}

	
	printf("USER:                     %s\n", name);
}
/* -------------------------------------------------------------------------------- */

static void print_linkc(const struct stat *sb){
  printf("Link count:               %ld\n", (long) sb->st_nlink);
}
/* -------------------------------------------------------------------------------- */

static void print_owner(const struct stat *sb){
        uid_t UID = sb->st_uid;
        gid_t GID =  sb->st_gid;
    
        struct passwd* user = getpwuid(UID);
        char* username = user -> pw_name;
    
        struct group* group = getgrgid(GID);
        char* groupname = group -> gr_name;
    
        printf("Ownership:                User: %s(%ld)   Group: %s(%ld)\n",username , (long) UID, groupname, (long) GID);
}
/* -------------------------------------------------------------------------------- */

static void print_size(const struct stat *sb){
	long long size =sb->st_size;
	char* unit ="bytes";
	if(size>1048576){
		size=size/1048576;
		unit="MB";
	}else if(size>1024){
		size=size/1024;
		unit="kB";
	}
	
  printf("Preferred I/O block size: %ld bytes\n", (long) sb->st_blksize);
  printf("File size:                %lld %s\n",size, unit);
  printf("Blocks allocated:         %lld\n",(long long) sb->st_blocks);
}
/* -------------------------------------------------------------------------------- */

static void print_laststch(const struct stat *sb){
    time_t curtime;
    time(&curtime);
    

    long long time;
    time=difftime(curtime,sb->st_ctime);



  printf("Last status change:       %s", ctime(&sb->st_ctime));
  printf("Time from last status change:       %d\n", time/60/60);
}
/* -------------------------------------------------------------------------------- */

static void print_lastacc(const struct stat *sb){
    time_t curtime;
    time(&curtime);
    

    long long time;
    time=difftime(curtime,sb->st_atime);

  printf("Last file access:         %s", ctime(&sb->st_atime));
  printf("Time from last file access:       %d\n", time/60/60);
}
/* -------------------------------------------------------------------------------- */

static void print_lastmod(const struct stat *sb){
    time_t curtime;
    time(&curtime);
    

    long long time;
    time=difftime(curtime,sb->st_mtime);
  printf("Last file modification:   %s", ctime(&sb->st_mtime));
  printf("Time from last file modification (hours):       %d\n", time/60/60);
}
/* -------------------------------------------------------------------------------- */

static void print_name(const struct stat *sb, char *name){
  char* bname = basename(name);
  if((sb->st_mode &S_IFMT)==S_IFLNK){
      unlink(name);
      char* filename=NULL;
      symlink(filename,name);
      printf("Name of the file:         %s -> %s\n", bname,filename);
  }else{
    printf("Name of the file:         %s\n", bname);
  }
}
/* -------------------------------------------------------------------------------- */
