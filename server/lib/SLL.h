typedef struct Node {
	void *data;
	char type;
	size_t size;
	struct Node *next;
} Node;

typedef struct SLL {
	Node *head;
}SLL;

SLL* initList();
void insertAtFirst(SLL *list, const char type, void *data, unsigned int n);
void insertAtLast(SLL *list, const char type, void *data, unsigned int n);
void removeFromFirst(SLL *list);
void removeFromLast(SLL *list);
void traverse(SLL *list);
void search(SLL *list, int data);

size_t getDataTypeSize(const char type);
void assignDataToMemory(const char type, size_t data_size, void *newNode, void *new_data);

void printInt(void *n);
void printChar(void *n);
void printString(void *n);
void printFloat(void *f);
void printDouble(void *n);
void printBasedOnData(const char type, void *data);


