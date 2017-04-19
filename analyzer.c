/*
Text File Analyzer 
Namila Bandara
E/14/084
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ "r"
#define SIZE 100




typedef struct node{
	//creating a linked list for store data
	char* string;
	int count;
	struct node *next;
}	linklist;  //linked list name


char* removeNonAlphaNum(char *str);
linklist* find(char* string);
void insertdata(char* string);
void readfile(FILE *fp,char *filepath);
int nodelength();
void sortnodes();


linklist *head=NULL;   //making head and current null
linklist *current=NULL;

int totalcount=0;

int nodelength(){
	int length=0;;
	linklist * current;
	current=head;

	for(current=head;current!=NULL;current=current->next){
		length++;
	}

	return length;
}


void printList() {
   linklist *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("%s,%d ",ptr->string,ptr->count);
      double t=ptr->count;
   
      printf("average:%.02lf\n",(double)(t/totalcount)*100);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

void sortnodes(){
	linklist *current, *nextnode;
	int i,j,k,nodesize,count;
	char *tempstring;

	nodesize=nodelength();
	k=nodesize;

	for(i=0;i<nodesize;i++,k--){
		current=head;
		nextnode=head->next;

		for(j=1;j<k;j++){
			if(nextnode->count>current->count){
				int strlength=strlen(nextnode->string);
				tempstring=(char*)malloc((strlength+1)*sizeof(char));
				

				strcpy(tempstring,nextnode->string);
				count=nextnode->count;

				nextnode->string=realloc(nextnode->string,strlen(current->string)+1);
				strcpy(nextnode->string,current->string);
				nextnode->count=current->count;

				current->string=realloc(current->string,strlen(tempstring)+1);
				strcpy(current->string,tempstring);
				current->count=count;
			}
			current = current->next;
         	nextnode = nextnode->next;

		}
	}


}


char* removeNonAlphaNum(char *str)
{
    int i = 0, j = 0;
    int arraysize=strlen(str)+1;
    char c;
    char *temp=malloc(arraysize* sizeof(char));

    for(i=0;i<arraysize;i++){
        c=str[i];
        if(isalnum(c)!= 0){
            temp[j++]=c;
        }
        
    }
    temp[j]='\0';


    
//    return str;
    return temp;
}

linklist* find(char* string){
	 current=head;

	if(head==NULL){
		return NULL;
	}

	while (strcmp(current->string,string)!=0){
		if(current->next==NULL){
			return NULL;
		}	
		else{
			current=current->next;
		}

	}
	return current;
}


void insertdata(char* string){
	char *temp=removeNonAlphaNum(string);
	current=find(temp);
	
	if(current==NULL){
		linklist *link=(linklist*)malloc (sizeof(link));

		link->string=temp;
		link->count=1;
		totalcount=1+totalcount;
		link->next=head;
		head=link;
	}else{
		current->count=(current->count)+1;
		totalcount=1+totalcount;

	}




}




void readfile(FILE *fp,char *filepath){
	char string[SIZE];
	
	
	fp=fopen(filepath ,READ);

	while(fscanf(fp,"%s",string)!=EOF){
		char *data=malloc(sizeof(strlen(string)));
		strcpy(data,string);
		insertdata(data);
	}


}



int main(int argc, char **argv){

	char *filepath=argv[1];
	FILE *fp;

	readfile(fp,filepath);
	//printList();
	sortnodes();
	printList();
	printf("%d\n",totalcount );


}