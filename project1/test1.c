#include <syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buff_size 700000
void func1 (char *result);

int main(int argc, char** argv) {
        //char result[buff_size];
        int i=0, pid;
	char *result;
	printf("Enter pid: ");
	scanf("%d", &pid);	
	//printf("PID is : %d\n", pid);	
	//-----
	result = malloc(buff_size * sizeof(char));
	//-----
	printf("\nIn systemcall\n");
        syscall(351,pid,result);

	printf("systemcall finish\n");
       //for(i=0;result[i]!='\0';i++)
        while(*(result+i) != '\0')
	{ 
           printf("%c",*(result+i));
	   i++;
	}
	//func1(result);

	printf("\nend\n");
        fgetc(stdin);
	return 0;
}

void func1 (char *result)
{		
	char *test2;
	unsigned long *imemoryAddr2;
	//--------	
	test2 = result;
	//Variable Defined----------------------
	char memoryAddress[20];
	unsigned long imemoryAddr1;
	
	//unsigned long imemoryAddr2[700000];
		
	const char *delim = ":";
	const char *tag = "-" ;
	const char *rol = "|";
	char *pch,*copy ,*pch1,*code;
	int i,j=0,count=0,y=0;	
	int position_delim = -1;
	int position_rol = -1;
	//----------------------
	
	imemoryAddr2 = malloc(buff_size*sizeof(unsigned long));

	//----------------------
	position_delim = strcspn(test2, delim);
	position_rol = strcspn(test2, rol);
	
	//printf("delim=%d, rol=%d\n", position_delim, position_rol);
	//printf("%s \n",test2);
	//-------
	while(position_delim !=0 && position_rol !=0) { 
		if(position_delim < position_rol) {
			memcpy(memoryAddress, test2, position_delim);
			memoryAddress[position_delim] = '\0';
			test2 = test2 + position_delim + 1;
			//printf("%s\n", test2);
		} else {
			memcpy(memoryAddress, test2, position_rol);
			memoryAddress[position_rol] = '\0';
			test2 = test2 + position_rol + 1;
			//printf("%s\n", test2);
		}
	//-----	
	pch = test2;	 // point to test2
    	pch = strtok(memoryAddress, "-"); 
	sscanf(pch,"%lx",&imemoryAddr1);
	*(imemoryAddr2+j) = imemoryAddr1;
	//printf("[1]imemoryAddr2:%08lX\n",imemoryAddr2[j]);
     	pch = strtok(NULL, "-");
	j++;
	sscanf(pch,"%lx",&imemoryAddr1);
	*(imemoryAddr2+j) = imemoryAddr1;	
	//printf("[2]imemoryAddr2:%08lX\n",imemoryAddr2[j]);
	j++;
	position_delim = strcspn(test2, delim);
	position_rol = strcspn(test2, rol);
	//printf("delim=%d, rol=%d\n", position_delim, position_rol);
	count++;
	
	}
	
	printf("count:%d j:%d\n",count,j);

	for(i=0;i<count-1;i++){    
	    if(i == 0){
	    printf("Code: start:%08lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
		y = y+2;}
	    else if(i == 1){
	     printf("Code: end:%08lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
		y = y+2;}
	    else if(i == 2){
            printf("Data: start:%08lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
		y = y+2;}
	    else if(i == 3){
            printf("Data: end:%08lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
		y = y+2;}
	    else if(i == 4){
            printf("Heap: start:%08lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
		y = y+2;}
	    else if(i == 5){
            printf("Heap: end:%08lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
		y = y+2;}
	    else if(i == 6){
	    printf("Stack: start:%8lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
	    	y = y+4;}
	    else if(i%2 == 1)
	    {
	     printf("Vm: start:%08lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
	      y = y+2;}
	    else{
	     printf("Vm: end:%08lX phy:%08lX\n",*(imemoryAddr2+y),*(imemoryAddr2+y+1));
	       y = y+2;
	     }
	//printf("Y:%d\n",y);
	//printf("[3]imemoryAddr2:%08lX\n",imemoryAddr2[i]);	
	}
}
