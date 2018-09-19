#include <stdio.h>
#include <stdlib.h>

FILE* get_asphalt_images(int random);
FILE* get_grass_images(int random);
 
int main(){
	FILE asphalt_images[25], grass_images[25];
	
	for(int i=0; i<25; i++)
	{
		asphalt_images[i] = get_asphalt_images(rand() % 50);
		grass_images[i] = get_grass_images(rand() % 50);
	}
	
	return 0;
}

FILE* get_asphalt_images(int random){
	FILE *fp;
	
	if(random <= 10)
		char asphalt[] = ("C:\Users\73041416115\Desktop\2018.2-EDA\projetos\02\asphalt\asphalt_0%d",random);
	else
		char asphalt[] = ("C:\Users\73041416115\Desktop\2018.2-EDA\projetos\02\asphalt\asphalt_%d",random);
	
	fp = fopen(asphalt ,"r")
	
	if(fp==NULL){
		printf("Falha.\n");
		exit(1);
	}
	
	return &fp;
}

FILE* get_grass_images(int random){
	FILE *fp;
	
	if(random <= 10)
		char grass[] = ("C:\Users\73041416115\Desktop\2018.2-EDA\projetos\02\grass\grass_0%d",random);
	else
		char grass[] = ("C:\Users\73041416115\Desktop\2018.2-EDA\projetos\02\grass\grass_%d",random);
	
	fp = fopen(grass ,"r")
	
	if(fp==NULL){
		printf("Falha.\n");
		exit(1);
	}
	
	return &fp;
}