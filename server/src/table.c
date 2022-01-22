#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include"../lib/TABLE.h"
#include<stdarg.h>
#include<string.h>


int main() {
	Table *table = tableInit("sii", "Name", "Age", "Phone No");
	printColums(table);

	printf("\n\n");
	insertRow(table, "sii", "Sanskar", 19, 1234567890);

	printf("\n\n");
	insertRow(table, "sii", "Shitij", 19, 987654321);

	showColum(table, 0);
	showColum(table, 1);

//	getNode(table, 0, 0);
//	getNode(table, 1, 0);

	return 0;
}

