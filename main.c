#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main(){
    char c;

    while(1){
        c = _getch();
        system("cls");
        printf("you've pressd: %c\n", c);
        if (c == 'q') break;
    }

    return 0;
}
