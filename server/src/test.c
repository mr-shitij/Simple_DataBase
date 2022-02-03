#include<stdio.h>
int main(){
	FILE *fp;  
	unsigned int a, b;  
	char str[10];
	fp = fopen("storage", "r");  
	fscanf(fp, "%u %u", &a, &b);  
	printf("%u : %u", a, b);  

	fscanf(fp, "%s", str);  
	printf("%s : ", str);  
	fclose(fp);
	return 0;
}

/*

insert table table_name v1,v2,v3



*/

