#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include"../lib/TABLE.h"
#include<stdarg.h>
#include<string.h>

Table* open(char *fileName) {
	return 0;
}

void save(Table *table) {
	FILE *filePointer;
	filePointer = fopen("storage", "w") ;
	if ( filePointer == NULL ) {
		printf( "storage file failed to open." ) ;

	}
	else {
		fputs("", filePointer);
		/*
		for(int i=0; i < table->rows; i++) {
			for(int j=0; j < table->colums; j++) {
				Node *node = getNode(table, i, j);

			}

		}
		*/
		fclose(filePointer);

	}

}

TableRow* tableRowInit() {
	TableRow *tableRow = (TableRow*) malloc(sizeof(TableRow *));
	tableRow->row = initList();
	return tableRow;
}

Table* tableInit(const char *dataType, ...) {
	Table *table = (Table *) malloc(sizeof(Table *));
	table->rows = 0;
	table->colums = 0;
	table->tableRow = tableRowInit();
	table->columsDataTypes = (char *) malloc(sizeof(char *) * strlen(dataType));
	strcpy(table->columsDataTypes, dataType);

	va_list valist;
	va_start(valist, dataType);

	while(*dataType != '\0') {
		char *val = va_arg(valist, char *);
		insertAtLast(table->tableRow->row, *dataType, val, strlen(val));

		table->colums = table->colums + 1;
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
	table->rows = table->rows + 1;

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

Node* getNodeFromRow(SLL *list, unsigned int index) {
	Node *temp = list->head;
	while(index != 0) {
		temp = temp->next;
		index --;
	}
	return temp;
}

TableRow* getRowFromColum(Table *table, unsigned int index) {
	TableRow *tableRow = table->tableRow->next;
	while(index != 0){
		tableRow = tableRow->next;
		index--;
	}
	return tableRow;
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

void updateNode(Table *table, const char type, int rowIndex, int colIndex, void *data) {
	if(type != table->columsDataTypes[rowIndex])
		return;

	TableRow *tableRow = getRowFromColum(table, colIndex);
	Node *node = getNodeFromRow(tableRow->row, rowIndex);
	assignDataToMemory(node->type, node->size, node->data, data);
}

Node* getNode(Table *table, int colIndex, int rowIndex) {
	TableRow *tableRow = getRowFromColum(table, colIndex);
	Node *node = getNodeFromRow(tableRow->row, rowIndex);
	return node;
}

void printColums(Table *table) {
	Node *temp = table->tableRow->row->head;
	while(temp != NULL) {
		printString(temp->data);
		printf("\t");
		temp = temp->next;
	}
}

