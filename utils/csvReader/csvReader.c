#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int countCols(FILE *fp){
    char character = ' ';
    int count = 0;
    while(character != '\n' && character != EOF && character != '\0'){
        character = (char)fgetc(fp);
        if(character == ',') ++count;
    }
    fclose(fp);
    return count;
}
int countRows(FILE *fp){
    char character = ' ';
    int count = 1;
    while(character != EOF && character != '\0'){
        character = (char)fgetc(fp);
        if(character == '\n') ++count;
    }
    fclose(fp);
    return count;
}

/* Reads a line of csv file that is passed as fp */
char **csvReader(FILE *fp) {
    char line[MAX];
    char *token;
    char **csv_data;
    int col = 0;

    csv_data = (char**)malloc(MAX * sizeof(char*));

    if (fp == NULL) {
        printf("The file cannot be opened!.\n");
        exit(1);
    }

    for(int i = 0; i < MAX; i++){
        csv_data[i] = NULL;
    }

    if (fgets(line, MAX, fp) != NULL) {
        col = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            csv_data[col] = malloc(strlen(token) + 1);
            strcpy(csv_data[col], token);
            col++;
            token = strtok(NULL, ",");
        }
    }

    return csv_data;
}

int main(){
    FILE *fp;
    int col = 0;
    fp = fopen("grammar.csv", "r");
    char** csv_data = csvReader(fp);
    while(csv_data[col] != NULL){
        printf(" %s -", csv_data[col++]);
    }
    fclose(fp);
}