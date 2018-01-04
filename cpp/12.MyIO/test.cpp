#include "virtIO_t.h"
#include "asciiIO_t.h"
#include "binIO_t.h"

#include <cstdio>


int main()
{   
    int cont = 1;                   // trigger to stop loop
    int option; 
    
    virtIO_t* io;
    char buf[4];
    char ch;
    int i;
    float f;

    while (cont)
    {
        printf("                                               \n");
        printf("Choose option:                                 \n");
        printf("1: create ascii using default constructor      \n");
        printf("2: create ascii using path + mode constructor  \n");
        printf("3: create binary using default constructor     \n");
        printf("4: create binary using path + mode constructor \n");

        printf("5: open                                 \n");
        printf("6: length                               \n");
        printf("7: << char                              \n");
        printf("8: << int                               \n");
        printf("9: << float                             \n");
        printf("10: >> char                             \n");
        printf("11: >> int                              \n");
        printf("12: >> float                            \n");

        printf("Any another number - stop               \n");


        scanf("%d", &option);
        switch (option)
        {
            case 1:
                io = new asciiIO_t();
            break;
            case 2:
                printf("Please enter mode\n");
                scanf("%s", buf);
                io = new asciiIO_t("OutFile", buf);
            break;
            case 3:
                io = new binIO_t();
            break;
            case 4:
                printf("Please enter mode\n");
                scanf("%s", buf);
                io = new binIO_t("OutFile", buf);
            break;
            case 5:
                printf("Please ener mode\n");
                scanf("%s", buf);
                io->Open("OutFile", buf);
            break;
            case 6:
                printf("%ld", io->GetLength());
            break;
            case 7:
                printf("Please ener input\n");
                scanf("%c", &ch);
                *io << ch;
            break;
            case 8:
                printf("Please ener input\n");
                scanf("%d", &i);
                *io << i;
            break;
            case 9:
                printf("Please ener input\n");
                scanf("%f", &f);
                *io << f;
            break;
            case 10:
                *io >> ch;
                printf("%c", ch);
            break;
            case 11:
                *io >> i;
                printf("%d", i);
            break;
            case 12:
                *io >> f;
                printf("%f", f);
            break;
            default:
                delete io;
                cont = 0;
            break;
        }
    }

    return 0;
}












