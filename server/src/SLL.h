typedef struct Node {
	void *data;
	char type;
	struct Node *next;
} Node;

typedef struct SLL {
	Node *head;
//	int totalNodes;
//	int maxNodes;
}SLL;

SLL* Init_List();
void InsertAtFirst(SLL *list, const char type, void *data, unsigned int n);
void InsertAtLast(SLL *list, const char type, void *data, unsigned int n);
void RemoveFromFirst(SLL *list);
void RemoveFromLast(SLL *list);
void Traverse(SLL *list);
void Search(SLL *list, int data);
void getNode(SLL *list, unsigned int index);

