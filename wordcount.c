//lines printf(l);
//words printf(w);
//characters printf(c);

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>


    int main(int argc, char *argv[]){
        if(argc != 2) {
            //no file input error
            printf("Error: Expected one argument: file %d.\n", argc -1);
            return -1;
        }

    // open file disciptor
    int fd = open(argv[1], O_RDONLY);
        if(fd == -1){
            //file does not exist error
            printf("Error: Cannot open file: %s\n", argv[1]);
            return -1;
        }
    // initialize count variables
    int charcount = 0;
    int wordcount = 0;
    int linecount = 0;
    char curr;
    char prev = ' '; //check for previous space
    int bytes;
    int inword = 0; //whether youre in a word or not

    while ((bytes = read(fd, &curr, 1)) > 0){
        charcount++;

        if(curr == '\n'){
            linecount++;
            if(inword){
                wordcount++;
                inword = 0;
            }
        }
        //spaces
        else if(isspace(curr)){
            if(inword){
                wordcount++;
                inword = 0;
            }
        }
        else {
            inword = 1;
        }
        }
        //in case we hit EOF with a word in the current line
        if(inword){
            wordcount++;
            linecount++;
        }

        // read and EOF errors
        if(bytes == -1){
            printf("Error reading file: %s\n", argv[1]);
            close(fd);
            return -1;
        }

        // close file discriptor
        close(fd);
        printf("%d %d %d %s\n", linecount, wordcount, charcount, argv[1]);
        return 0;
    }