//Jack Edwards
//CSCI 3000
//4-20-18
//ls -l

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

//#define USE_CAN_R(m) 

struct fstats{
	char type;
	char* permissions;
	int numberLinks;
	char* userName;
	char* groupName;
	int size;
	char* time;
	char* fname;
};

char* removeNewLineFromCtimeStr(char* ctstr){
	int len = strlen(ctstr);
	
	char* newstr = (char *)malloc(sizeof(char)*len);
	
	int i = 0;
	while(i < (len - 1)){
		newstr[i] = ctstr[i];
		i++;
	}
	newstr[len - 1] = '\0';
	return newstr;
}

struct fstats getStats(struct stat s, char* fname){
	
	struct fstats fileStats; 
	
	//directory or not
	char type;
	
	if(S_ISDIR(s.st_mode)){
		type = 'd';
	}else{
		type = '-';
	}
	
	fileStats.type = type;
	
	
	//permissions
	char* perms = (char*)malloc(sizeof(char)*10);
	perms[9] = '\0';
	
	//build permissions string
	if(s.st_mode & S_IRUSR){ perms[0] = 'r';}
	else {perms[0] = '-';}
	if(s.st_mode & S_IWUSR){ perms[1] = 'w';}
	else {perms[1] = '-';}
	if(s.st_mode & S_IXUSR){ perms[2] = 'x';}
	else {perms[2] = '-';}
	
	if(s.st_mode & S_IRGRP){ perms[3] = 'r';}
	else {perms[3] = '-';}
	if(s.st_mode & S_IWGRP){ perms[4] = 'w';}
	else {perms[4] = '-';}
	if(s.st_mode & S_IXGRP){ perms[5] = 'x';}
	else {perms[5] = '-';}
	
	if(s.st_mode & S_IROTH){ perms[6] = 'r';}
	else {perms[6] = '-';}
	if(s.st_mode & S_IWOTH){ perms[7] = 'w';}
	else {perms[7] = '-';}
	if(s.st_mode & S_IXOTH){ perms[8] = 'x';}
	else {perms[8] = '-';}
	
	fileStats.permissions = perms;
	
	//links to file
	int numLinks = s.st_nlink;
	
	fileStats.numberLinks = numLinks;
	
	//name of user who creaed file
	struct passwd* user = getpwuid(s.st_uid);
	char* name = user->pw_name;
	
	fileStats.userName = name;
	
	//name of useres group
	struct group* gr = getgrgid(s.st_gid);
	char* g = gr->gr_name;
	
	fileStats.groupName = g;
	
	//num characters
	fileStats.size = s.st_size;
	
	//time
	char* time = removeNewLineFromCtimeStr(ctime(&s.st_mtime));
	fileStats.time = time;
	
	//file/directory name
	fileStats.fname = fname;
		
	return fileStats;
}

void printStats(struct fstats* fileContents, int size){
	int i = 0;
	struct fstats fs;
	while(i < size){
		fs = fileContents[i];
		
		if(fs.fname[0] == '.'){
			
		}else{
			printf("%c", fs.type);
			printf("%s", fs.permissions);
			printf("\t%d", fs.numberLinks);
			printf("\t%s", fs.userName);
			printf("\t%s", fs.groupName);
			printf(" %zu", fs.size);
			printf(" %s", fs.time);
			printf(" %s", fs.fname);
			printf("\n");
		}
		
		i++;
	}
}

int main(int argc, const char** argv){
	
	if(argc >= 2){
		//change to argv[1]
		DIR* directoryP = opendir(argv[1]);
		
		if(directoryP == NULL){
			printf("Error: Could not find directory");
			return 1;
		}else{
			struct dirent* d;
			struct stat s;
			char fPathBuffer[512];
			
			struct fstats* fileContents;
			
			//count items in directory to create array
			int numItemsInDir = 0;
			while(d = readdir(directoryP)){
				numItemsInDir++;
			}
			closedir(directoryP);
			
			
			directoryP = opendir(argv[1]);
			fileContents = malloc(sizeof(struct fstats) * numItemsInDir);
			
			int i = 0;
			while(d = readdir(directoryP)){
				sprintf(fPathBuffer, "%s/%s", argv[1], d->d_name);
				stat(fPathBuffer, &s);
				
				fileContents[i] = getStats(s, d->d_name);
				i++;
			}
			closedir(directoryP);
			
			printStats(fileContents, numItemsInDir);
		}
		
		
		
		printf("didnt crash\n");
	}else{
		printf("No path to dirctory given");
	}
    printf("sup\n");


    return 0;
}
