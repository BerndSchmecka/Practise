#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char spielfeld[] = "|---|---|---|\n| 1 | 2 | 3 |\n|---|---|---|\n| 4 | 5 | 6 |\n|---|---|---|\n| 7 | 8 | 9 |\n|---|---|---|\n";


/*
This Funtion is from 'The Paramagnetic Croissant':
https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
(Yeah, I was too lazy to code my own str_replace but the rest is my own code.)
*/
void str_replace(char *target, const char *needle, const char *replacement)
{
    char buffer[1024] = { 0 };
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, needle);

        // walked past last occurrence of needle; copy remaining part
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }

        // copy part before needle
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;

        // copy replacement string
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;

        // adjust pointers, move on
        tmp = p + needle_len;
    }

    // write altered string back to target
    strcpy(target, buffer);
}

char* strarr[9] = {" ", " ", " ", " ", " ", " ", " ", " ", " "};

void printArrMap(){
    char* tst = (char*)malloc(sizeof(spielfeld));
    strcpy(tst, spielfeld);
    
    for (int i = 0; i < 9; i++){
        char strtor[2];
        sprintf(strtor, "%d", i+1);
        str_replace(tst, strtor, strarr[i]);
    }
    printf(tst);
    free(tst);
}

int someoneHasWon(char* pointer){
    for (int i = 0; i <= 6; i=i+3){
        if(strarr[i] == strarr[i+1] && strarr[i+1] == strarr[i+2] && strarr[i] != " "){
            *pointer = *strarr[i];
            return 1;
        }
    }
    
    for (int i = 0; i <= 2; i++){
            if (strarr[i] == strarr[i+3] && strarr[i+3] == strarr[i+6] && strarr[i] != " ") {
                *pointer = *strarr[i];
                return 1;
            } else if (i != 1 && strarr[i] == strarr[4] && strarr[4] == strarr[8-i] && strarr[i] != " ") {
                *pointer = *strarr[i];
                return 1;
            }
    }
    
    for (int i = 0; i<9; i++){
        if(strarr[i] == " "){
            return 0;
        }
    }
    
    *pointer = '?';
    return 1;
}

int main() {
    int input = 0;
    char currChar = 'O';
    while(input != 99){
        printArrMap();
        printf("Spieler %c ist am Zug!\n", currChar);
        printf("Eingabe: ");
        scanf("%d", &input);
        if(input < 1 || input > 9){
            continue;
        }
        if(strarr[input-1] != " "){
            continue;
        }
        
        if(currChar == 'O') {
            strarr[input-1] = "O";
            currChar = 'X';
        } else {
            strarr[input-1] = "X";
            currChar = 'O';
        }
        
        char r = '-';
        if(someoneHasWon(&r)){
            printf("%c hat gewonnen!\n", r);
            printArrMap();
            return 0;
        }
    }
    printf("Exiting! Bye!");
    return 0;
}
