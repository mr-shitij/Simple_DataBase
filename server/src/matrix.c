#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include"../lib/TABLE.h"
#include<string.h>

int main(int argc, char *args[]){
        if(argc < 2) {
                printf("Enter the string ..!!");
                return 0;
        }

        Table *table = tableInit("ii", "row", "col");
        char *ptr = NULL;
        while(*ptr != '\0') {
                int first = *ptr;
			printf("%s\n", args[1]);
                ptr++;
                if(*ptr == '\0') {
                        insertRow(table, "ii", *ptr, 0);
                } else {
  	                int second = *ptr;
			ptr++;
                        insertRow(table, "ii", first, second);
                }
        }
        showTable(table);
        return 0;
}

char* encode(char *input) {

}

char* decode(char *input) {

}

