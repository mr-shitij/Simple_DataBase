#include<stdio.h>
#include<stdlib.h>
#include"../lib/SLL.h"
#include"../lib/TABLE.h"
#include<stdarg.h>
#include<string.h>

TableRow* tableRowInit() {
	printf("TR-1 \n\n");
	TableRow *tableRow = (TableRow*) malloc(sizeof(TableRow));
	tableRow->next = NULL;
	printf("TR-2 \n\n");
	tableRow->row = initList();
	printf("TR-3 \n\n");

	return tableRow;
}

// Table{row, col, data_type}
// struct SLL00, struct Node01(Colum_name), struct Node02(Colum_name), struct Node03(Colum_name)
// struct SLL10, struct Node11, struct Node12, struct Node13
// struct SLL20, struct Node21, struct Node22, struct Node23

// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)

Table* open(char *fileName) {
	printf("OP-1\n");
	Table *table = NULL;
	FILE *filePointer;
	filePointer = fopen("storage", "r");
	if (filePointer == NULL) {
		printf("storage file failed to open.");
		printf("OP-ERROR\n");
	}
	else {
		printf("OP-2\n");
		table = (Table *) malloc(sizeof(Table));
		printf("OP-2.5\n");

		char aa[100];
		unsigned int a, b;
		printf("OP-3\n");


		fscanf(filePointer, "%u %u", &a, &b);  
		table->rows = a;
		table->colums = b;

		fscanf(filePointer, "%s", aa);
		printf("OP-4\n");
		table->columsDataTypes = (char *) malloc(sizeof(char) * strlen(aa));
		printf("OP-5\n");
		strcpy(table->columsDataTypes, aa);
		printf("OP-6\n");
		
//		table->tableRow = tableRowInit();
//		table->tableRow->next = NULL;
		
		TableRow *tableRow = table->tableRow;
		int firstColum = 1;
		while(filePointer != NULL) {
			printf("OP-7\n");
			tableRow = tableRowInit();
			Node tempNode;
			printf("OP-8\n");

			int colums = 0;
			while(colums != table->colums) {
				printf("OP-9\n");
				if(aa[colums] == 's' || firstColum == 1) {
					firstColum = 0;
					fscanf(filePointer, "%s %c %zu", tempNode.data, tempNode.type, tempNode.size);
				}
				else if(aa[colums] == 'i') {
					fscanf(filePointer, "%d %c %zu",  tempNode.data, tempNode.type, tempNode.size);
				}
				else if(aa[colums] == 'c') {
					fscanf(filePointer, "%c %c %zu",  tempNode.data, tempNode.type, tempNode.size);
				}
				else if(aa[colums] == 'f') {
					fscanf(filePointer, "%f %c %zu",  tempNode.data, tempNode.type, tempNode.size);
				}
				else if(aa[colums] == 'd') {
					fscanf(filePointer, "%lf %c %zu", tempNode.data, tempNode.type, tempNode.size);
				}

				printf("OP-10\n");				
				printf("OP-DBUG : Type: %c, %s, %zu\n", tempNode.type, tempNode.data, tempNode.size);
				insertAtLast(tableRow->row, tempNode.type, tempNode.data, tempNode.size);	
				printf("OP-11\n");
				colums++;
			}
			tableRow = tableRow->next;
		}
		fclose(filePointer);
	}
	return table;
}

void save(Table *table) {
	FILE *filePointer;
	filePointer = fopen("storage", "w");
	if (filePointer == NULL) {
		printf("storage file failed to open.");
	}
	else {
		/*

		typedef struct Table {
			TableRow *tableRow;
			char *columsDataTypes;
			unsigned int rows;
			unsigned int colums;
			
		}Table;

		typedef struct Node {
			void *data;
			char type;
			size_t size;
			struct Node *next;

		} Node;

		*/

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
//	printf("\n I-P1");
	if(table == NULL || table->tableRow == NULL) {
		printf("\n Table is not Initialized ..!!");
//		printf("\n I-P2");
		return;
	}
	else if(strcmp(dataType, table->columsDataTypes)) {
		printf("\n No Of Colums are not matching ..!!\n");
//		printf("\n I-P3");
		return;
	}

//	printf("\n I-P4");
	va_list valist;
	va_start(valist, dataType);

	TableRow *iterator = table->tableRow;
	while(iterator->next != NULL){
		iterator = iterator->next;
	}

//	printf("\n I-P5");
	iterator->next = tableRowInit();
	iterator->next->next = NULL;
	table->rows = table->rows + 1;

//	printf("\n I-P6");
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
//		printf("\n I-PR");
	}
//	printf("\n I-P7");
	va_end(valist);
//	printf("\n I-P8");
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
//	printf("GN-1 \n\n ");
	Node *temp = list->head;
//	printf("GN-2 \n\n ");
	while(index != 0) {
//		printf("GN-3 \n\n ");
		temp = temp->next;
		index --;
	}
//	printf("GN-4 \n\n ");
	return temp;
}

void showColum(Table *table, int index) {
//	printf("SC-1 \n\n ");
	TableRow *tableRow = table->tableRow->next;
//	printf("SC-2 \n\n ");
	while(tableRow != NULL){
//		printf("SC-3 \n\n ");
		Node *temp = getNodeFromRow(tableRow->row, index);
//		printf("SC-4 \n\n ");
		printBasedOnData(temp->type, temp->data);
//		printf("SC-5 \n\n ");
		tableRow = tableRow->next;
//		printf("SC-6 \n\n ");
	}
//	printf("SC-7 \n\n ");
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

