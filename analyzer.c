/*
Text File Analyzer 
Namila Bandara
E/14/084
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>

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
void reversefilename();
int maxlenword(int printlength);
void printchart(int printlength,int scale);


linklist *head=NULL;   //making head and current null for words
linklist *current=NULL;

linklist *filehead=NULL; //making head for file inserts
linklist *filecurrent=NULL;

int totalcount=0; //total amount of words/chars in files


int nodelength(){
	/*finding the node amounts
	*/
	int length=0;;
	linklist * current;
	current=head;

	for(current=head;current!=NULL;current=current->next){
		length++;
	}

	return length;
}

int maxlenword(int printlength){
	/* finding maximum length of the word in the list
	*/
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
	/*function for printing chart
	*/
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
	//^^making sizes for percentage values

	graph_area=MAX_WIDTH-(SPACEREDUCE+ maxlen+PERCENTAGE_WIDTH);
	printf("%*s\n",MAX_WIDTH,"");

	while(i<printlength){
		
		average=((double)(ptr->count)/(double)totalcount)*100*scalesize;

		char *string=ptr->string;
		wordspace=(maxlen+1)-strlen(string);
		barsize=(int)((graph_area*average)/100);
		
		
		//first bar
		printf("%*s%s",(maxlen+2)," ",verticlebar);
		for(k=0;k<barsize;k++)
		{
			printf("%s",FILLDOTS );
		}
		printf("\n");	

			
		//second bar
		printf("%s%s%*s%s"," ",string,wordspace," ",verticlebar );
		for(k=0;k<barsize;k++)
		{
			printf("%s",FILLDOTS );
		}
			printf("%.2lf%s\n",average/scalesize,"%");


		//third bar,same as first bar
		printf("%*s%s",(maxlen+2)," ",verticlebar);
		for(k=0;k<barsize;k++)
		{
			printf("%s",FILLDOTS );
		}
		printf("\n");

		//printing space for next chart
		printf("%*s%s%*s\n",maxlen+2," ",verticlebar,MAX_WIDTH-(maxlen+2)," " );

		

		
		ptr = ptr->next;

		i++;
        if(ptr== NULL  )break;


		}
		//printing ending lines
		printf("%*s%s",maxlen+2," ","└" );
		
		for(k=1;k<graph_area+PERCENTAGE_WIDTH+1;k++)
		{
			printf("%s",horizontalbar );
		}
			printf("\n");

}


void reversenodes(){
	//reversing inserted words/chars
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

void reversefilename(){
	//reversing filename
	linklist *nextnode,*current,*prevnode;
	current=filehead;
	prevnode=NULL;

	while(current!=NULL){
		nextnode=current->next;
		current->next=prevnode;
		prevnode=current;
		current=nextnode;
	}
	
	filehead=prevnode;

}


void sortnodes(){
	//sorting nodes from highest to lowers
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
				tempstring=(char*)malloc((strlength+1));
				

				strcpy(tempstring,nextnode->string);
				count=nextnode->count;

				nextnode->string=realloc(nextnode->string,(strlen(current->string)+1));

				strcpy(nextnode->string,current->string);
				nextnode->count=current->count;

				current->string=realloc(current->string,(strlen(tempstring)+1));
				strcpy(current->string,tempstring);
				current->count=count;
				//free(tempstring);
			}

			current = current->next;
         	nextnode = nextnode->next;

		}
	}


}



char* removeNonAlphaNum(char *str)
{
	//removing non alpha chars and lower capital letters
    int i = 0, j = 0;
    
    char c;
    char *temp=malloc(strlen(str)+1);
    	
    if(!temp){
    	printf("%s\n","Error allocating memory");
    	exit(1);
    }
    
    for(i=0;str[i]!='\0';i++){
        c=str[i];
      	
        if(isalnum(c) && !isspace(c) && !iscntrl(c)){
        	
        	
        	c=tolower(c);
        	
            temp[j++]=c;
            
         }
        
        
    }
    temp[j++]='\0';
   
     char* tempreturn=malloc((strlen(temp)+1));
    i=0,j=0;

    for(i=0;i<=strlen(temp);i++,j++){
    	tempreturn[j]=temp[i];
    }
    tempreturn[j++]='\0';
        
   
    	//free(temp);
	
   
   

    return tempreturn;
}

linklist* find(char* string){
	/*searching the link list ,if the word is already insert,otherwise
	creating a new one*/
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
	/*inserting data for link list*/
	char *temp=removeNonAlphaNum(string);
	
	if(strlen(temp) > 0)
	{
		current=find(temp);
	
	if(current==NULL){
		linklist* link=(linklist*)malloc(sizeof(link));

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
	/* reading files*/
	char string[SIZE];
	FILE *fp;
	char c;
	
	if(!filepath)
	{
		exit(EXIT_FAILURE);
	}
		fp=fopen(filepath,READ);
		
		
	if(printmode==1)
	{
		while(fscanf(fp,"%s",string)!=EOF){

		char *data=malloc(strlen(string)+1);
		strcpy(data,string);

		insertdata(data);
		
		}


			
	}
	else if(printmode==2)
	{
		while(fscanf(fp,"%c",&c)!=EOF){
				char *data=malloc(3*sizeof(char));
				data[0]=c;data[2]='\0';
				insertdata(data);
						
					}
	}

}

void insertfilename(char *filepath){
	/* inserting file names given in args
	*/
	linklist *file=(linklist*)malloc (sizeof(file));

	file->string=filepath;
	
	file->next=filehead;
	filehead=file;
	

}




int main(int argc, char **argv){
	int printlength=10,i,printmode=1,scale=0,lenplace,flaguse1=0,flaguse2=1;       //printmode; word=1; char=2;
	char *filepath;
	
	
	for(i=0;i<argc;i++){
		char *argvv=argv[i];
		
		if(strcmp(argvv,"-l")==0){
			 lenplace=i+1;

			if(lenplace<argc){

				printlength=atoi(argv[lenplace]);
				if(printlength<=0){
					//for non positive numbers
					fprintf(stdout, "Invalid option for [-l]\n" );
					printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
				
					exit(0);
				}
				
			}
			else{
				//if there is no arg for length
				fprintf(stdout, "Not enough options for [-l]\n" );
				printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
				exit(0);
			}
		}
		else if(strcmp(argvv,"-w")==0){
			//flag for word insert mode
			printmode=1;
			flaguse1=5;
		}
		else if(strcmp(argvv,"-c")==0){
			//flag for char insert mode
			printmode=2;
			flaguse2=5;
		}
		else if(strcmp(argvv,"--scaled")==0){
			//scaling maximum print size
			scale=1;
		}else if( i != 0 && i!=lenplace){
			//inserting files
			filepath=argv[i];
			insertfilename(filepath);
			
			
			
		}
		
	
	
		
	}
	if(flaguse2==flaguse1){
		//cant use both -w and -c modes
		printf("[-c] and [-w] cannot use together\n");
		printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		exit(0);
	}

	if(filehead==NULL)
	{
		printf("No input files were given\n");
		printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		exit(0);
	}
	
	reversefilename(); //reversing inserted filenames
	
	struct stat statr;
	
	linklist *file=filehead;
	while(file!=NULL)
	{	
		stat(file->string, &statr);
		
		
		if(stat(file->string, &statr))
		{
			//if file cant be opened
		printf("Cannot open one or more given files\n");
		exit(0);
		}

		else{
			readfile(file->string,printmode);
			file = file->next;

			if(file== NULL  )break;
			}
	}
	
	if(totalcount==0)
	{

        printf("No data to process\n");
    	exit(0);
	}
	
	
	reversenodes(); 
	sortnodes();
	
	

	printchart(printlength,scale);
	

	return 0;

}