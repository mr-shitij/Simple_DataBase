#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include"../lib/TABLE.h"
#include<stdarg.h>
#include<string.h>

TableRow* tableRowInit() {
	TableRow *tableRow = (TableRow*) malloc(sizeof(TableRow));
	tableRow->next = NULL;
	tableRow->row = initList();
	return tableRow;
}

void showTable(Table *table) {
	printColums(table);
	printf("\n");
	int rows = table->rows;
	int i=0;
	while(i <= rows) {
		showRow(table, i);
		printf("\n");
		i++;
	}
}

void deleteRow(Table *table, int index) {
	if(table->tableRow->next == NULL) {
		printf("No Rows ..!!\n\n");
		return;

	} else if(index > table->rows) {
		printf("No More Rows ..!!\n\n");
		return;		
	}

	TableRow *prev = table->tableRow;
	TableRow *row = table->tableRow->next;
	while(index != 0) {
		index--;
		prev = row;
		row = row->next;
	}

	prev->next = row->next;
	while(row->row->head != NULL) {
		removeFromFirst(row->row);
	}
	table->rows = table->rows - 1;
	free(row);
}

Table* open(char *fileName) {
	Table *table = NULL;
	FILE *filePointer;
	filePointer = fopen(fileName, "r");
	if (filePointer == NULL) {
		printf("storage file failed to open.");
		printf("OP-ERROR\n");
	}
	else {
		table = (Table *) malloc(sizeof(Table));
		table->tableRow = tableRowInit();

		fscanf(filePointer, "%u", &table->rows);
		fscanf(filePointer, "%u", &table->colums);
		table->columsDataTypes = (char *) malloc(sizeof(char) * table->colums);
		fscanf(filePointer, " %[^\t\n]s", table->columsDataTypes);

//		printf("Row : %d, Col : %d, DataType : %s\n\n", table->rows, table->colums, table->columsDataTypes);

		TableRow *tableRow = table->tableRow;

		int firstColum = 1;
		int r = 0; 
		while(r <= table->rows) {

			int colums = 0;
			while(colums < table->colums) {
				Node tempNode;
				char data[100];

				fscanf(filePointer, "%zu", &tempNode.size);
				fscanf(filePointer, "%zu", &tempNode.size);
				fscanf(filePointer, "%c", &tempNode.type);
//				printf("Type: %c, Size: %zu, Data : ", tempNode.type, tempNode.size, tempNode.data);

				if(*(table->columsDataTypes + colums) == 's' || firstColum == 1) {
					fscanf(filePointer, " %[^\t\n]s", data);
					tempNode.data = malloc(sizeof(char) * strlen(data));
					strcpy(tempNode.data, data);
	
//					printBasedOnData('s', tempNode.data);
//					printf("\n\n");

					insertAtLast(tableRow->row, *(table->columsDataTypes + colums), tempNode.data, tempNode.size);
				}
				else if(*(table->columsDataTypes + colums) == 'i') {
					int integ;
					fscanf(filePointer, "%d", &integ);

//					printBasedOnData(tempNode.type, &integ);
//					printf("\n\n");

					insertAtLast(tableRow->row, *(table->columsDataTypes + colums), &integ, tempNode.size);
				}
				else if(*(table->columsDataTypes + colums) == 'c') {
					char ch;
					fscanf(filePointer, "%c", &ch);

//					printBasedOnData(tempNode.type, &ch);
//					printf("\n\n");

					insertAtLast(tableRow->row, *(table->columsDataTypes + colums), &ch, tempNode.size);
				}
				else if(*(table->columsDataTypes + colums) == 'f') {
					float fl;
					fscanf(filePointer, "%f", &fl);

//					printBasedOnData(tempNode.type, &fl);
//					printf("\n\n");

					insertAtLast(tableRow->row, *(table->columsDataTypes + colums), &fl, tempNode.size);
				}
				else if(*(table->columsDataTypes + colums) == 'd') {
					double dl;
					fscanf(filePointer, "%lf", &dl);

//					printBasedOnData(tempNode.type, &dl);
//					printf("\n\n");

					insertAtLast(tableRow->row, *(table->columsDataTypes + colums), &dl, tempNode.size);
				}

				colums++;
			}
			firstColum = 0;
			r++;
			if(r <= table->rows) {
				tableRow->next = tableRowInit();
				tableRow = tableRow->next;
			}

		}
		fclose(filePointer);
	}
	return table;
}

void save(Table *table, char *fileName) {
	FILE *filePointer;
	filePointer = fopen(fileName, "w");
	if (filePointer == NULL) {
		printf("storage file failed to open.");
	}
	else {
		fprintf(filePointer, "%u\t", table->rows);
		fprintf(filePointer, "%u\t", table->colums);
		fprintf(filePointer, "%s\t", table->columsDataTypes);

		TableRow *row = NULL;
		row = table->tableRow;
	
		int first=0;
		while(row != NULL) {
			Node *node = row->row->head;
			while(node != NULL) {
				fprintf(filePointer, "%zu\t", node->size);
				fprintf(filePointer, "%c\t", node->type);
				if(node->type == 's' || first < table->colums) {
					first++;
					fprintf(filePointer, "%s\t", node->data);
				}
				else if(node->type == 'i') {
					fprintf(filePointer, "%d\t", *(int *)node->data);
				}
				else if(node->type == 'c') {
					fprintf(filePointer, "%c\t", *(char *)node->data);
				}
				else if(node->type == 'f') {
					fprintf(filePointer, "%f\t", *(float *)node->data);
				}
				else if(node->type == 'd') {
					fprintf(filePointer, "%lf\t",  *(double *)node->data);
				}
				node = node->next;
			}
			row = row->next;
		}
		fclose(filePointer);
	}
}

Table* tableInit(const char *dataType, ...) {
	Table *table = (Table *) malloc(sizeof(Table));
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
		printf("\n Table is not Initialized ..!!\n");
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
	iterator->next->next = NULL;
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

TableRow* getRowFromColum(Table *table, unsigned int index) {
	TableRow *tableRow = table->tableRow->next;
	while(index != 0){
		tableRow = tableRow->next;
		index--;
	}
	return tableRow;
}

Node* getNodeFromRow(SLL *list, unsigned int index) {
	Node *temp = list->head;
	while(index != 0) {
		temp = temp->next;
		index --;
	}
	return temp;
}

void showColum(Table *table, int index) {
	TableRow *tableRow = table->tableRow->next;
	while(tableRow != NULL){
		Node *temp = getNodeFromRow(tableRow->row, index);
		printBasedOnData(temp->type, temp->data);
		tableRow = tableRow->next;
	}
}

void showRow(Table *table, int index) {
	TableRow *tableRow = table->tableRow->next;
	while(index != 0){
		index--;
		tableRow = tableRow->next;
	}

	if(tableRow != NULL) {
		Traverse(tableRow->row);
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

