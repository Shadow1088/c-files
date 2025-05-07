#include "stdio.h"
#include <inttypes.h>
#include <stdlib.h>


typedef struct{
    char type;
    char* value;
    int length;
}BASENUM;


BASENUM getValue(){
    BASENUM num;
    num.length=0;
    char c;
    while((c = getchar())!='\n'){
        num.length++;
        num.value = realloc(num.value, sizeof(num)*num.length);
        num.value[num.length-1] = c;
    }
    return num;
}
// 'u' = unknown, 'x' = hexadecimal, 'd' = decimal, 'b' = binary, 'o' = octal
void autoDetect(BASENUM *num){
    (*num).type = 'u';
    if ((*num).value[0] == '0' && (*num).value[1] == 'x'){
        (*num).type = 'x';
    }else{
        for(int i=0; i<(*num).length;i++){
            if ((*num).value[i]<'2' && (*num).type=='u'){
                (*num).type = 'b';
            }

            if ((*num).value[i]>='a' && (*num).value[i]<='f'){
                (*num).type = 'x';
                for(int j=0; j<(*num).length;j++){
                    if ((*num).value[j]>'f'){
                        (*num).type = 'u';
                        break;
                    }
                }
                break;
            }
            if ((*num).value[i]>'7' && (*num).value[i]<'9' && (*num).type!='x'){
                (*num).type = 'd';
                continue;
            }
            if ((*num).value[i]>'1' && (*num).value[i]<'8' && (*num).type!='d' && (*num).type!='x' && (*num).length%3==0){
                printf("%d", (*num).length);
                (*num).type = 'o';
                continue;
            }

            if ((*num).type=='b' && (*num).value[i] >'2'){
                (*num).type = 'd';
                break;
            }
        }
    }
    printf("Program autodetected base of this number, is it correct?\n%s -> %c\nIf yes, press Enter, otherwise write the base yourself, please.\n", (*num).value, (*num).type);
    char answer = getchar();
    if (answer!='\n'&& (answer == 'x' || answer == 'o' || answer == 'd' || answer == 'b')){
        (*num).type=answer;
    }
    printf("selected type: %c\n", (*num).type);
}


BASENUM convertBD(BASENUM num){
    BASENUM result;
    result.type = 'd';

    return result;
}

BASENUM convertBX(BASENUM num){
    BASENUM result;
    result.type = 'x';

    return result;
}

BASENUM convertBO(BASENUM num){
    BASENUM result;
    result.type = 'o';

    return result;
}

BASENUM convertDB(BASENUM num){
    BASENUM result;
    result.type = 'b';

    return result;
}

BASENUM convertDX(BASENUM num){
    BASENUM result;
    result.type = 'x';

    return result;
}

BASENUM convertDO(BASENUM num){
    BASENUM result;
    result.type = 'o';

    return result;
}

BASENUM convertXD(BASENUM num){
    BASENUM result;
    result.type = 'd';

    return result;
}

BASENUM convertXB(BASENUM num){
    BASENUM result;
    result.type = 'b';

    return result;
}

BASENUM convertXO(BASENUM num){
    BASENUM result;
    result.type = 'o';

    return result;
}

BASENUM convertOD(BASENUM num){
    BASENUM result;
    result.type = 'd';

    return result;
}

BASENUM convertOB(BASENUM num){
    BASENUM result;
    result.type = 'b';

    return result;
}

BASENUM convertOX(BASENUM num){
    BASENUM result;
    result.type = 'x';

    return result;
}


BASENUM convert(BASENUM num, char type){
    switch (type) {
        case 'b':
            switch (num.type) {
                case 'b':
                    printf("%s is already binary\n", num.value);
                    break;
                case 'd':
                    return convertDB(num);
                case 'x':
                    return convertXB(num);
                case 'o':
                    return convertOB(num);
            }
            break;

        case 'd':
            switch (num.type) {
                case 'b':
                    return convertBD(num);
                case 'd':
                    printf("%s is already decimal\n", num.value);
                    break;
                case 'x':
                    return convertXD(num);
                case 'o':
                    return convertOD(num);
            }
            break;

        case 'x':
            switch (num.type) {
                case 'b':
                    return convertBX(num);
                case 'd':
                    return convertDX(num);
                case 'x':
                    printf("%s is already hexadecimal\n", num.value);
                    break;
                case 'o':
                    return convertOX(num);
            }
            break;

        case 'o': // Target: octal
            switch (num.type) {
                case 'b':
                    return convertBO(num);
                case 'd':
                    return convertDO(num);
                case 'x':
                    return convertXO(num);
                case 'o':
                    printf("%s is already octal\n", num.value);
                    break;
            }
            break;
    }

    return num;
}

// asks user what base do we convert our string to
char convertto(){
    printf("What to convert to?");
    char c = getchar();
    while (!(c=='\n' || (c == 'x' || c == 'o' || c == 'd' || c == 'b'))){
        printf("Invalid input, (x; b; d; o;)\nWhat to convert to?\n");

        while (getchar() != '\n');
        c = getchar();

    }
    return c;
}

int main(){
    BASENUM num = getValue();
    autoDetect(&num);
    BASENUM result = convert(num, convertto());
    printf("%c\n", num.type);
    return 0;
}
