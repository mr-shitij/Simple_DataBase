/*
	Generic Table Structure (Runtime Cache)
*/
#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include"../lib/TABLE.h"
#include<stdarg.h>
#include<string.h>

int main() {

	Table *table = tableInit("sids", "Name", "Age", "Heart Rate", "Blood Group");

	insertRow(table, "sids", "Ganesh", 19, 100.100, "AB");
	insertRow(table, "sids", "Hanuman", 19, 100.100, "+A");
	insertRow(table, "sids", "Ram", 19, 100.100, "O");
	insertRow(table, "sids", "Sham", 19, 100.100, "AB");
	insertRow(table, "sids", "Shitij", 19, 100.100, "+A");
	insertRow(table, "sids", "Sanskar", 19, 100.100, "-O");
	insertRow(table, "sids", "Pratik", 19, 100.100, "-O");

	showTable(table);

	printf("\nDisplaying 3rd Row : \n");
	showRow(table, 3);

	printf("\nDisplaying 3rd Colum : \n");
	showColum(table, 3);

	printf("\nDeleting 5th Row : \n");
	deleteRow(table, 5);

	showTable(table);

	printf("\n\n");
	printf("Now Saving The Data To The File ..!!\n");
	save(table, "data.txt");

	printf("Now Opening The Data File ..!!\n");
	Table *newTable = open("data.txt");
	showTable(newTable);

	printf("\n\n\n\n");

	printf("Matrix-1 : \n");
	Table *m1 = tableInit("iiii", "C1", "C2", "C3", "C4");
	insertRow(m1, "iiii", 1, 0, 0, 0);
	insertRow(m1, "iiii", 0, 1, 0, 0);
	insertRow(m1, "iiii", 0, 0, 1, 0);
	insertRow(m1, "iiii", 0, 0, 0, 1);

	showTable(m1);
	printf("\n\n");

	printf("Matrix-2 : \n");
	Table *m2 = tableInit("iiii", "C1", "C2", "C3", "C4");
	insertRow(m2, "iiii", 1, 0, 0, 0);
	insertRow(m2, "iiii", 0, 1, 0, 0);
	insertRow(m2, "iiii", 0, 0, 1, 0);
	insertRow(m2, "iiii", 0, 0, 0, 1);

	showTable(m2);
	printf("Sum Of Matrices : \n\n");

	for(int i=0; i < m1->rows; i++) {
		for(int j=0; j < m1->colums; j++) {
			Node *n1 = getNode(m1, i, j);
			Node *n2 = getNode(m2, i, j);
		
			int sum = *(int *)(n1->data) + *(int *)(n2->data);
			printf("%d\t", sum);
		}
		printf("\n");
	}
	printf("\n\n");

	return 0;
}

