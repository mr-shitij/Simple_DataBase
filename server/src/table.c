#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include<stdarg.h>
#include<string.h>

typedef struct TableRow {
	SLL *row;
	struct TableRow *next;
}TableRow;

typedef struct Table{
	TableRow *tableRow;
	char *columsDataTypes;
}Table;

TableRow* tableRowInit() {
	TableRow *tableRow = (TableRow*) malloc(sizeof(TableRow *));
	tableRow->row = Init_List();
	return tableRow;
}

Table* tableInit(const char *dataType, ...) {
	Table *table = (Table *) malloc(sizeof(Table *));
	table->tableRow = tableRowInit();
	table->columsDataTypes = (char *) malloc(sizeof(char *) * strlen(dataType));
	strcpy(table->columsDataTypes, dataType);

	va_list valist;
	va_start(valist, dataType);

	while(*dataType != '\0') {
		char *val = va_arg(valist, char *);
		InsertAtLast(table->tableRow->row, *dataType, val, strlen(val));

		dataType++;
	}

	va_end(valist);
	return table;
}

void insertRow(Table *table, const char *dataType, ...) {
	if(table == NULL || table->tableRow == NULL) {
		printf("\n Table is not Initialized ..!!");
		return;
	}
	else if(strcmp(dataType, table->columsDataTypes)) {
		printf("\n No Of Colums are not matching ..!!\n");
		return;
	}

	va_list valist;
	va_start(valist, dataType);

	TableRow *iterator = table->tableRow;
	while(iterator->next != NULL){
		iterator = iterator->next;
	}

	iterator->next = tableRowInit();

	while(*dataType != '\0') {
		if(*dataType == 'i') {
			int val = va_arg(valist, int);
			InsertAtLast(iterator->next->row, *dataType, &val, 1);	
		}
		else if(*dataType == 'f') {
			float val = va_arg(valist, float);
			InsertAtLast(iterator->next->row, *dataType, &val, 1);	
		}
		else if(*dataType == 'c') {
			char *val = va_arg(valist, char*);
			InsertAtLast(iterator->next->row, *dataType, val, 1);	
		}
		else if(*dataType == 'd') {
			double val = va_arg(valist, double);
			InsertAtLast(iterator->next->row, *dataType, &val, 1);	
		}
		else if(*dataType == 's') {
			char *val = va_arg(valist, char *);
			InsertAtLast(iterator->next->row, *dataType, val, strlen(val));
		}
		dataType++;
	}

	va_end(valist);	
}

int main() {

	Table *table = tableInit("sii", "Name", "Age", "Phone NO");
	PrintColums(table->tableRow->row);

	printf("\n\n");

	insertRow(table, "sii", "Sanskar", 19, 1234567890);
	insertRow(table, "sii", "Shitij", 19, 987654321);
	Traverse(table->tableRow->next->row);
	printf("\n\n");
	Traverse(table->tableRow->next->next->row);
	printf("\n\n");

/*
	getNode(table->tableRow->row, 0);
	getNode(table->tableRow->row, 1);
	getNode(table->tableRow->row, 2);
*/
	return 0;
}








