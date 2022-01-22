#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include<stdarg.h>
#include<string.h>

typedef struct TableRow {
	SLL *row;
	struct TableRow *next;
}TableRow;

typedef struct Table {
	TableRow *tableRow;
	char *columsDataTypes;
}Table;

TableRow* tableRowInit() {
	TableRow *tableRow = (TableRow*) malloc(sizeof(TableRow *));
	tableRow->row = initList();
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
		insertAtLast(table->tableRow->row, *dataType, val, strlen(val));

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
			insertAtLast(iterator->next->row, *dataType, &val, 1);
		}
		else if(*dataType == 'f') {
			float val = va_arg(valist, float);
			insertAtLast(iterator->next->row, *dataType, &val, 1);
		}
		else if(*dataType == 'c') {
			char *val = va_arg(valist, char*);
			insertAtLast(iterator->next->row, *dataType, val, 1);
		}
		else if(*dataType == 'd') {
			double val = va_arg(valist, double);
			insertAtLast(iterator->next->row, *dataType, &val, 1);
		}
		else if(*dataType == 's') {
			char *val = va_arg(valist, char *);
			insertAtLast(iterator->next->row, *dataType, val, strlen(val));
		}
		dataType++;
	}
	va_end(valist);
}

void showColum(Table *table, int index) {
	TableRow *tableRow = table->tableRow->next;
	while(tableRow != NULL){
		Node *temp = getNodeFromRow(tableRow->row, index);
		printBasedOnData(temp->type, temp->data);
		tableRow = tableRow->next;
		printf("\n");
	}
}

void printColums(Table *table) {
	Node *temp = table->tableRow->row->head;
	while(temp != NULL) {
		printString(temp->data);
		printf("\t");
		temp = temp->next;
	}	
}


int main() {
	Table *table = tableInit("sii", "Name", "Age", "Phone No");
	printColums(table);

	printf("\n\n");
	insertRow(table, "sii", "Sanskar", 19, 1234567890);

	printf("\n\n");
	insertRow(table, "sii", "Shitij", 19, 987654321);

	showColum(table, 0);
	showColum(table, 1);
	return 0;
}

