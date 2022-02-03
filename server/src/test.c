#include<stdio.h>
int main(){
	FILE *fp;  
	unsigned int a, b;  
	char str[10];
	fp = fopen("storage", "r");  
	fscanf(fp, "%u %u", &a, &b);  
	printf("%u : %u\n\n", a, b);  

	fscanf(fp, "%s", str);
	printf("%s : \n\n", str);

	char type;
	size_t dataSize;

	fscanf(fp, "%s %c %zu", str, type, dataSize);	
	printf("%s : %c : %zu\n\n", str, type, dataSize);

	fscanf(fp, "%s %c %zu", str, type, dataSize);	
	printf("%s : %c : %zu\n\n", str, type, dataSize);

	fscanf(fp, "%s %c %zu", str, type, dataSize);	
	printf("%s : %c : %zu\n\n", str, type, dataSize);


 
	fclose(fp);
	return 0;
}

/*

insert table table_name v1,v2,v3



*/

