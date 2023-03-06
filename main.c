#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	char* name;
	char* place;
	int jel;
	int tojas;
} bunny;


int main (int argc, char* argv[] ){
	char* lakhelyek[7] = {"Baratfa","Lovas","Szula","Kigyos-patak","Malom telek","Paskom","Kaposztas kert"};
	char* lakhelyek1[4] = {"Baratfa","Lovas","Kigyos-patak","Kaposztas kert"};
	char* lakhelyek2[3] = {"Szula","Malom telek","Paskom"};
	FILE* fp=fopen(argv[1],"r");
	int lsize=0;
	bunny *list=malloc(10*sizeof(bunny));
	int cap=10;
	if(fp==NULL)
        {
            fprintf(stderr,"Uj lista keszitese.\n");
        }else
        {
			int buffercap=1024;
			char buffer[buffercap];
			char delim[] = ",";
			while(fgets(buffer,buffercap,fp) != NULL)
			{
				
				if(lsize<cap)
				{
					list[lsize].name = malloc(sizeof(char*));
					char *line = strtok(buffer, delim);
					strcpy(list[lsize].name,line);
					
					list[lsize].place = malloc(sizeof(char*));
					line = strtok(NULL, delim);
					strcpy(list[lsize].place,line);
			
					line = strtok(NULL, delim);
					list[lsize].jel=atoi(line);
					lsize++;
				}else
				{
					cap=cap+10;
					bunny* tmp = realloc(list,(cap*sizeof(bunny)));
					if (tmp == NULL)
					{
						fprintf(stderr,"Sikertelen memoriafoglalas");

					}else
					{
						list = tmp;
						list[lsize].name = malloc(sizeof(char*));
						char *line = strtok(buffer, delim);
						strcpy(list[lsize].name,line);
						
						list[lsize].place = malloc(sizeof(char*));
						line = strtok(NULL, delim);
						strcpy(list[lsize].place,line);
				
						line = strtok(NULL, delim);
						list[lsize].jel=atoi(line);
						lsize++;
					}

				}
			}
			fclose(fp);
		}
		int end = 1;
		char input[20];
		while (end){
			printf("parancsok: writeall, writeplace, input, modify, delete, exit, saveexit, race\n");
			scanf("%s",input);
			if(!strcmp(input,"writeall")){
				int i;
				for(i=0;i<lsize;i++){
					printf("%s,%s,%d\n",list[i].name,list[i].place,list[i].jel);
				}
			}else if (!strcmp(input,"writeplace")){
				printf("Adja meg a kiirando teruletet!\n");
				char place[20];
				scanf("%s",place);
				int i;
				for(i=0;i<lsize;i++){
					if (!strcmp(place,list[i].place))
					printf("%s,%s,%d\n",list[i].name,list[i].place,list[i].jel);
				}
			}else if(!strcmp(input,"saveexit")){
				end=0;
				if (argc==1){
					char filename[20];
					printf("Uj fajl neve:");
					scanf("%s",&filename);
					FILE* fp=fopen(filename,"w");
					int i;
					for(i=0;i<lsize;i++){
						fprintf(fp,"%s,%s,%d\n",list[i].name,list[i].place,list[i].jel);
					}
				}else{
					FILE* fp=fopen(argv[1],"w");
					int i;
					for(i=0;i<lsize;i++){
						fprintf(fp,"%s,%s,%d\n",list[i].name,list[i].place,list[i].jel);
					}
				}
			}else if(!strcmp(input,"exit")){
				end=0;
			}else if(!strcmp(input,"input")){
				char name[20];
				char place[30];
				int jel;
				printf("Nev:");
				scanf("%s",&name);
				printf("Lakohely:");
				int c;
				while ((c = getchar()) != '\n' && c != EOF); 
				fgets(place,30,stdin);
				place[strcspn(place, "\n")] = 0;
				int j=0;
				int helyes = 0;
				while (!helyes && j<7){
					if(!strcmp(lakhelyek[j],place)){
						helyes=1;
						}
					j++;
					}
					if (helyes){
				printf("Hanyadik jelentkezes:");
				scanf("%d",&jel);
				if(lsize<cap)
				{
					list[lsize].name = malloc(sizeof(char*));
					strcpy(list[lsize].name,name);
					list[lsize].place = malloc(sizeof(char*));
					strcpy(list[lsize].place,place);
					list[lsize].jel=jel;
					lsize++;
				}else{
					cap=cap+10;
					bunny* tmp = realloc(list,(cap*sizeof(bunny)));
					if (tmp == NULL)
					{
						fprintf(stderr,"Sikertelen memoriafoglalas");

					}else
					{
						list = tmp;
						list[lsize].name = malloc(sizeof(char*));
						strcpy(list[lsize].name,name);
						list[lsize].place = malloc(sizeof(char*));
						strcpy(list[lsize].place,place);
						list[lsize].jel=jel;
						lsize++;
					}
				}
			}else {
				printf("Helytelen lakhely!\n");
			}
			}else if(!strcmp(input,"modify")){
				char name[20];
				char in[20];
				printf("Nev:");
				scanf("%s",&name);
				int i=0;
				while(i<lsize && strcmp(name,list[i].name)){
					i++;
				}
				if(i<lsize){
				printf("Mit? (hely/szam/nev)\n");
				scanf("%s",&in);
				if(!strcmp(in,"hely")){
					char ujh[20];
					printf("Mire:");
					int c;
					while ((c = getchar()) != '\n' && c != EOF); 
					fgets(ujh,30,stdin);
					ujh[strcspn(ujh, "\n")] = 0;
					int j=0;
					int helyes = 0;
					while (!helyes && j<7){
						if(!strcmp(lakhelyek[j],ujh)){
							helyes=1;
						}
						j++;
					}
					if (helyes){
					strcpy(list[i].place,ujh);
					}else{
						printf("Helytelen lakhely!\n");
						}
				}else if(!strcmp(in,"szam")){
					int uj;
					printf("Mire:");
					scanf("%d",&uj);
					int i=0;
					printf("%d",uj);
					while(strcmp(name,list[i].name)){
						i++;
					}
					list[i].jel=uj;
				}else if(!strcmp(in,"nev")){
					char ujn[20];
					printf("Mire:");
					scanf("%s",&ujn);
					int i=0;
					while(strcmp(name,list[i].name)){
						i++;
					}
					strcpy(list[i].name,ujn);
				}else{
					printf("Rossz parancs!\n");
				}
			}
				else{
					printf("Nincs ilyen nevu nyul\n");
				}
			}else if(!strcmp(input,"delete")){
				char name[20];
				printf("Nev:");
				scanf("%s",&name);
				bunny* tmp=malloc(cap*sizeof(bunny));
				int i=0;
				int newsize=0;
				for (i;i<lsize;i++){
					if (strcmp(name,list[i].name)){
						tmp[newsize]=list[i];
						newsize++;
					}
				}		
				lsize = newsize;
				list = tmp;
			}else if (!strcmp(input,"race")){
				end=0;
				
				pid_t pid1;
				int pipe1[2];
				pid_t pid2;
				int pipe2[2];
				int s1;
				int s2;
				
				bunny arr1[lsize];
				bunny arr2[lsize];
				int size1 = 0;
				int size2 = 0;
				int k=0;
				char current[20];
				
				for (k;k<lsize;k++){
					stpcpy(current,list[k].place);
					int j = 0;
					int ben = 0;
					while (!ben && j<3){
					if(!strcmp(lakhelyek2[j],current)){
						ben=1;
						}
					j++;
					}
					if (ben){
						arr1[size1]=list[k];
						size1++;
					}else{
						arr2[size2]=list[k];
						size2++;
					}
				}
				
				if (pipe(pipe1) == -1) 
				{
				perror("Hiba a pipe nyitaskor!");
				exit(EXIT_FAILURE);
				}
				if (pipe(pipe2) == -1) 
				{
				perror("Hiba a pipe nyitaskor!");
				exit(EXIT_FAILURE);
				}
				pid1 = fork();
				if (pid1 == -1) 
				{
				perror("Fork hiba");
				exit(EXIT_FAILURE);
				}
				
				if (pid1 == 0) //child1
				{
					read(pipe1[0],&s1,sizeof(int));
					read(pipe1[0],arr1,sizeof(bunny)*s1);
					close(pipe1[0]);
					srand(getpid());
					int i=0;
					for (i;i<s1;i++){
						arr1[i].tojas=(rand()%100)+1;
					}
					write(pipe1[1],arr1,sizeof(bunny)*s1);
					close(pipe1[1]);
					exit(0);
				}else{
					pid2 = fork();
					if (pid2 == -1) 
					{
					perror("Fork hiba");
					exit(EXIT_FAILURE);
					}
					if (pid2 == 0) //child2
					{
						read(pipe2[0],&s2,sizeof(int));
						read(pipe2[0],arr2,sizeof(bunny)*s2);
						close(pipe2[0]);
						srand(getpid());
						int i=0;
						for (i;i<s1;i++){
							arr2[i].tojas=(rand()%100)+1;
						}
						write(pipe2[1],arr2,sizeof(bunny)*s2);
						close(pipe2[1]);

						exit(0);
						
					}else{// parent
						write(pipe1[1],&size1,sizeof(size1));
						write(pipe2[1],&size2,sizeof(size2));
						write(pipe1[1],arr1,sizeof(bunny)*size1);
						write(pipe2[1],arr2,sizeof(bunny)*size2);
						close(pipe1[1]);
						close(pipe2[1]);
						int status1;
						int status2;
						waitpid(pid1,&status1,0);
						waitpid(pid2,&status2,0);
						read(pipe1[0],arr1,sizeof(bunny)*size1);
						read(pipe2[0],arr2,sizeof(bunny)*size2);
						int max1=arr1[0].tojas;
						char max1nev[30];
						strcpy(max1nev,arr1[0].name);
						int m1=0;
						

						for (m1;m1<size1;m1++){
							if(arr1[m1].tojas>max1){
								max1=arr1[m1].tojas;
								strcpy(max1nev,arr1[m1].name);
							}
						}
						
						
						int max2=arr2[0].tojas;
						char max2nev[30];
						strcpy(max2nev,arr2[0].name);
						int m2=0;
						
						
						for (m2;m2<size2;m2++){
							if(arr2[m2].tojas>max2){
								max2=arr2[m2].tojas;
								strcpy(max2nev,arr2[m2].name);
							}
						}

						if(max1>max2){
							printf("A győztes: %s\n",max1nev);
						}else{
							printf("A győztes: %s\n",max2nev);
						}
					}	
				}
				
			}else{
				printf("Helytelen parancs!\n");
			}
		}
		int i;
		for(i=0;i<lsize;i++){
			free(list[i].name);
			free(list[i].place);
		}
			free(list);
}