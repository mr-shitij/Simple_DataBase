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
	int rows = table->rows;	
	int i=0;
	while(i <= rows) {
		printf("\n");
		showRow(table, i);
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
		char dataType[100];
		unsigned int r, c;

		table = (Table *) malloc(sizeof(Table));
		table->tableRow = tableRowInit();

		fscanf(filePointer, "%u %u", &r, &c);  
		table->rows = r;
		table->colums = c;

		printf("Row : %d, Col : %d\n\n", table->rows, table->colums);

		fscanf(filePointer, "%s", dataType);
		table->columsDataTypes = (char *) malloc(sizeof(char) * strlen(dataType));
		strcpy(table->columsDataTypes, dataType);
				
		TableRow *tableRow = table->tableRow;

		int firstColum = 1;
		r = 0; 
		while(r <= table->rows) {
			Node tempNode;
			if(tableRow == NULL)
				tableRow = tableRowInit();

			int colums = 0;
			while(colums < table->colums) {
				if(dataType[colums] == 's' || firstColum == 1) {
					fscanf(filePointer, "%s %c %zu\n", tempNode.data, &tempNode.type, &tempNode.size);
				}
				else if(dataType[colums] == 'i') {
					fscanf(filePointer, "%d %c %zu\n", tempNode.data, &tempNode.type, &tempNode.size);
				}
				else if(dataType[colums] == 'c') {
					fscanf(filePointer, "%c %c %zu\n", tempNode.data, &tempNode.type, &tempNode.size);
				}
				else if(dataType[colums] == 'f') {
					fscanf(filePointer, "%f %c %zu\n", tempNode.data, &tempNode.type, &tempNode.size);
				}
				else if(dataType[colums] == 'd') {
					fscanf(filePointer, "%lf %c %zu\n", tempNode.data, &tempNode.type, &tempNode.size);
				}

			//	printf("Type: %c, Size: %zu, Data: %s \n\n", tempNode.type, tempNode.size, tempNode.data);
				insertAtLast(tableRow->row, dataType[colums], tempNode.data, tempNode.size);
				colums++;
			}
			firstColum = 0;
			tableRow = tableRow->next;
			r++;
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
		fprintf(filePointer, "%u %u\n", table->rows, table->colums);
		fprintf(filePointer, "%s\n", table->columsDataTypes);

		TableRow *row = NULL;
		row = table->tableRow;
	
		int first=0;
		while(row != NULL) {
			Node *node = row->row->head;
			while(node != NULL) {
				if(node->type == 's' || first < table->colums) {
					first++;
					fprintf(filePointer, "%s %c %zu\n", node->data, node->type, node->size);
				}
				else if(node->type == 'i') {
					fprintf(filePointer, "%d %c %zu\n",  *(int *)node->data, node->type, node->size);
				}
				else if(node->type == 'c') {
					fprintf(filePointer, "%c %c %zu\n",  *(char *)node->data, node->type, node->size);
				}
				else if(node->type == 'f') {
					fprintf(filePointer, "%f %c %zu\n",  *(float *)node->data, node->type, node->size);
				}
				else if(node->type == 'd') {
					fprintf(filePointer, "%lf %c %zu\n",  *(double *)node->data, node->type, node->size);
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

