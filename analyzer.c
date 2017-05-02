/*
Text File Analyzer 
Namila Bandara
E/14/084
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ "r"
#define SIZE 1000
#define verticlebar "│"
#define horizontalbar "─"
#define FILLDOTS "░"
#define MAX_WIDTH 80
#define NORMAL_WIDTH 10

#define SPACEREDUCE 3



typedef struct node{
	//creating a linked list for store data
	char* string;
	int count;
	struct node *next;
}	linklist;  //linked list name


char* removeNonAlphaNum(char *str);
linklist* find(char* string);
void insertdata(char* string);
void readfile(char *filepath,int printmode);
int nodelength();
void sortnodes();
void reversenodes();
int maxlenword(int printlength);
void printchart(int printlength,int scale);


linklist *head=NULL;   //making head and current null for words
linklist *current=NULL;

linklist *filehead=NULL;
linklist *filecurrent=NULL;

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

int maxlenword(int printlength){
	linklist *ptr = head;
   int i=0;
   int maxlen=0;
	
   //start from the beginning
 	  while(i<printlength) {
 	  	
 	  	if(strlen(ptr->string)>maxlen)
        	maxlen=strlen(ptr->string);
        
        ptr = ptr->next;

        i++;
        if(ptr== NULL  )break;
     	
 		}
 		return maxlen;
}




void printchart(int printlength,int scale){
	linklist *ptr = head;
	int graph_area;
	int maxlen=maxlenword(printlength);
	
	int i=0,k,wordspace,barsize;

	int PERCENTAGE_WIDTH ;
	double average,scalesize;

	average=((double)(ptr->count)/(double)totalcount)*100;
	if(scale){
		scalesize=(100/average);
	}else{
		scalesize=1;
	}

	if(average>0 && average<10) PERCENTAGE_WIDTH=5;
	else if(average>=10 && average<100) PERCENTAGE_WIDTH=6;
	else PERCENTAGE_WIDTH=7;


	graph_area=MAX_WIDTH-(SPACEREDUCE+ maxlen+PERCENTAGE_WIDTH);
	printf("%*s\n",MAX_WIDTH,"");
	while(i<printlength){
		
		average=((double)(ptr->count)/(double)totalcount)*100*scalesize;

		char *string=ptr->string;
		wordspace=(maxlen+1)-strlen(string);
		barsize=(int)((graph_area*average)/100);
		//printf("%s %d \n",ptr->string,wordspace);
		
		//printf("%d\n",barsize );
		//first bar
		
		
		printf("%*s%s",(maxlen+2)," ",verticlebar);
		for(k=0;k<barsize;k++){
			printf("%s",FILLDOTS );
		}
		printf("\n");	

		//second bar	
		
		printf("%s%s%*s%s"," ",string,wordspace," ",verticlebar );
		for(k=0;k<barsize;k++){
			printf("%s",FILLDOTS );
		}
			printf("%.2lf%s\n",average/scalesize,"%");



		printf("%*s%s",(maxlen+2)," ",verticlebar);
		for(k=0;k<barsize;k++){
			printf("%s",FILLDOTS );
		}
			printf("\n");

		printf("%*s%s%*s\n",maxlen+2," ",verticlebar,MAX_WIDTH-(maxlen+2)," " );

		

		
		ptr = ptr->next;

		i++;
        if(ptr== NULL  )break;


		}
		printf("%*s%s",maxlen+2," ","└" );
		//printf("%*s\n",maxlen+2,"└");
		//printf("%*s%*s\n",maxlen+2," ",MAX_WIDTH-maxlen-2,"-");
		for(k=1;k<graph_area+PERCENTAGE_WIDTH+1;k++){
			printf("%s",horizontalbar );
		}
			printf("\n");




}

void printList(int printlength) {
   linklist *ptr = filehead;
   int i=0;
	
   //start from the beginning
 	  while(i<printlength) {

        printf("%s  ",ptr->string);
      // double t=ptr->count;
     
       // printf("average:%.02lf\n",(double)(t/totalcount)*100);
        ptr = ptr->next;

        i++;
        if(ptr== NULL  )break;
     
 		}
	
  
}

void reversenodes(){
linklist *nextnode,*current,*prevnode;
	current=head;
	prevnode=NULL;

	while(current!=NULL){
		nextnode=current->next;
		current->next=prevnode;
		prevnode=current;
		current=nextnode;
	}
	
	head=prevnode;

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

				nextnode->string=realloc(nextnode->string,(strlen(current->string)+1));
				strcpy(nextnode->string,current->string);
				nextnode->count=current->count;

				current->string=realloc(current->string,(strlen(tempstring)+1));
				strcpy(current->string,tempstring);
				current->count=count;
				free(tempstring);
			}

			current = current->next;
         	nextnode = nextnode->next;

		}
	}


}
char* removesign(char *string){


}


char* removeNonAlphaNum(char *str)
{
    int i = 0, j = 0;
    int arraysize=strlen(str)+1;
    char c;
    char *temp=malloc(arraysize+1);
    	//printf("%s %d\n",str,arraysize-1 );
    if(!temp){
    	printf("%s\n","Error allocating memory");
    	exit(1);
    }
    
    for(i=0;str[i]!='\0';i++){
        c=str[i];
      	
        if(isalnum(c) && !isspace(c) && !iscntrl(c) && c!=45){
        	
        	if(c>='A' && c<='Z'){
        	c=tolower(c);
        	}
            temp[j]=c;
            // printf("%c%d %d ",c,i,j );
            j++;
            
        }
        
        
    }
    temp[j++]='\0';
   // printf("%c%d %d ",c,i,j );
     char* tempreturn=malloc((strlen(temp)+1));
    i=0,j=0;

    for(i=0;i<=strlen(temp);i++,j++){
    	tempreturn[j]=temp[i];
    }
    tempreturn[j+1]='\0';
    //printf(" temp :%sreturn%d\n",temp,(int)strlen(tempreturn) );
    
   
    	//free(temp);
	
   
   
//    return str;
    return tempreturn;
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
	//printf("%s\n",string );
	char *temp=removeNonAlphaNum(string);
	
	if(strlen(temp) > 0)
	{
		//printf("%d new len\n",(int)strlen(temp) );
		
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



	




}




void readfile(char *filepath,int printmode){
	char string[SIZE];
	
	FILE *fp;
	char c;
	
	
		
		if(!filepath){
			exit(EXIT_FAILURE);
		}
		fp=fopen(filepath,READ);

		
		if(printmode==1){
			while(fscanf(fp,"%s",string)!=EOF){

			char *data=malloc(strlen(string)+1);
			strcpy(data,string);

			insertdata(data);
			
			}


			
		}else if(printmode==2){
			while(fscanf(fp,"%c",&c)!=EOF){
					char *data=malloc(3*sizeof(char));
							data[0]=c;data[2]='\0';
							//printf("%s\n",data );
							insertdata(data);
							
						}
			

		}
		
	


}

void insertfilename(char *filepath){
	linklist *file=(linklist*)malloc (sizeof(file));

		file->string=filepath;
		
		file->next=filehead;
		filehead=file;

}




int main(int argc, char **argv){
	int printlength=10,i,printmode=1,scale=0,j=0,lenplace,flaguse1=0,flaguse2=1;       //printmode; word=1; char=2;
	char *filepath;
	FILE *fp;
	for(i=0;i<argc;i++){
		char *argvv=argv[i];
		char *files;
		if(strcmp(argvv,"-l")==0){
			 lenplace=i+1;
			if(lenplace<argc){
				printlength=atoi(argv[lenplace]);
				if(printlength<=0){
					fprintf(stdout, "Invalid option for [-l]\n" );
					printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
				
					exit(0);
				}
				/*else{
				fprintf(stdout, "Invalid options for [-l]\n" );
				printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
				
				exit(0);
				}
				*/
			}else{
				fprintf(stdout, "Not enough options for [-l]\n" );
				printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
				exit(0);
			}
		}
		else if(strcmp(argvv,"-w")==0){
			printmode=1;
			flaguse1=5;
		}
		else if(strcmp(argvv,"-c")==0){
			printmode=2;
			flaguse2=5;
		}
		else if(strcmp(argvv,"--scaled")==0){
			scale=1;
		}else if( i != 0 && i!=lenplace){
			filepath=argv[i];
			insertfilename(filepath);
			
		}
		
		
		//printf("%d %d  %d\n",printlength,i ,printmode );
	}
	if(flaguse2==flaguse1){
		printf("[-c] and [-w] cannot use together\n");
		printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		exit(0);
	}
	
	linklist *file=filehead;
	while(file!=NULL)
	{
		readfile(file->string,printmode);
		file = file->next;
		if(file== NULL  )break;
	}


	
	
	reversenodes();
	
	sortnodes();
	 
	//printList(printlength);

	printchart(printlength,scale);
	


}