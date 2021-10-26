#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


int main(void) {
    /* open directory 'tmp' */
    DIR* dir_ptr = opendir("tmp");
    char file_names[16][16];
    ino_t inodes[16];
    int file_index = 0;

    /* traverse all files inside tmp */
    struct dirent* dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        if(strcmp(dirent_ptr->d_name, ".") == 0 || strcmp(dirent_ptr->d_name, "..") == 0) {
            continue;
        }
        /* get current file name */
        char str[80];
        strcpy(str,"tmp/");
        strcat(str, dirent_ptr->d_name);
        /* get number of file's hard links */
        struct stat file_stat;
        stat(str, &file_stat);
        nlink_t links_number = file_stat.st_nlink;
        if(links_number > 1) {
            char* file_name = dirent_ptr->d_name;
            ino_t inode = file_stat.st_ino;
            strcpy(file_names[file_index], file_name);
            inodes[file_index] = inode;
            file_index += 1;
        }
    }

    /* print output */
    for(int i = 0; i < file_index; i++) {
        int inode = inodes[i];
        char* file_name = file_names[i];
        char output[350];
        strcpy(output, file_name);
        strcat(output, " - ");
        for(int k = 0; k < file_index; k++) {
            if(inodes[k] == inode) {
                strcat(output, file_names[k]);
                strcat(output, ", ");
            }
        }
        printf("%s\n", output);
    }

    return 0;
}
