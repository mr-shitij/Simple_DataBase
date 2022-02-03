#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include"../lib/TABLE.h"
#include<stdarg.h>
#include<string.h>

int main() {
	Table *table = tableInit("sii", "Name", "Age", "Phone_No");
	printColums(table);

	printf("\n\n p1");


	printf("\n\n p2");
	insertRow(table, "sii", "Sanskar", 19, 1234567890);

	printf("\n\n p3");
	insertRow(table, "sii", "Shitij", 19, 987654321);

	save(table);
	showColum(table, 0);
	showColum(table, 1);

	printf("\n\n p4");
	
	Node *n1 = getNode(table, 0, 2);
	printf("\n N1 : ");
	printBasedOnData(n1->type, n1->data);

	n1 = getNode(table, 1, 1);
	printf("\t N1 : ");
	printBasedOnData(n1->type, n1->data);

	Node *n2 = getNode(table, 0, 0);
	printf("\n N2 : ");
	printBasedOnData(n2->type, n2->data);

	n2 = getNode(table, 0, 1);
	printf("\t N2 : ");
	printBasedOnData(n2->type, n2->data);

//	getNode(table, 0, 0);
//	getNode(table, 1, 0);
	return 0;
}

