#include<stdio.h>
#include<stdlib.h>

typedef struct TableRow {
	SLL *row;
	struct TableRow *next;
}TableRow;

typedef struct Table {
	TableRow *tableRow;
	char *columsDataTypes;
	unsigned int rows;
	unsigned int colums;
}Table;

void save(Table *table);
Table* open(char *fileName);

Table* tableInit(const char *dataType, ...);
void insertRow(Table *table, const char *dataType, ...);
Node* getNodeFromRow(SLL *list, unsigned int index);
TableRow* getRowFromColum(Table *table, unsigned int index);
void showColum(Table *table, int index);
void updateNode(Table *table, const char type, int rowIndex, int colIndex, void *data);
Node* getNode(Table *table, int rowIndex, int colIndex);
void printColums(Table *table);


