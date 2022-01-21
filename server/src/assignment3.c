#include<stdio.h>
#include<stdlib.h>
#include"DLL.h"

int main() {
	int choice;
	DLL *list = Init_List();
	while(choice != 8) {
		printf("\n1. Insert At First");
		printf("\n2. Insert At Last");
		printf("\n3. Insert At Middle");	
		printf("\n4. Remove From First");	
		printf("\n5. Remove From Last");	
		printf("\n6. Traverse");	
		printf("\n7. Search");
		printf("\n8. Exit");
		printf("\nSelect Choice :  ");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				InsertAtFirst(list);
				break;
			case 2:
				InsertAtLast(list);
				break;
			case 3:
				InsertAtMiddel(list);
				break;
			case 4:
				RemoveFromFirst(list);
				break;
			case 5:
				RemoveFromLast(list);
				break;
			case 6:
				Traverse(list);
				break;
			case 7:
				Search(list);
				break;
			case 8:
				break;
			default:
				printf("\n Invalid Choice ..!!");
		}
	}
	return 0;
}
