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
    num.length = 0;
    num.value = NULL;
    char c;
    printf("You may now enter a number you want to convert.\nPreferably without any prefix.\n");
    while((c = getchar())!='\n'){
        num.length++;
        num.value = realloc(num.value, sizeof(char)*num.length);
        num.value[num.length-1] = c;
    }
    num.value[num.length] = '\0';
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

int power(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return result;
}

//int to str
char* iota(long num, int length){
    char* result = NULL;
    result = realloc(result, length);
    for(int i=0;i<length;i++){
        result[i] = '0'+((num/power(10, length-1-i))%10);
    }
    result[length] = '\0';
    return result;
}

BASENUM convertBD(BASENUM num){
    BASENUM result;
    result.type = 'd';
    result.length = 0;
    long temp = 0;

    for(long i=num.length-1; i>(-1); i--){
       if((num.value[i])=='1'){
           temp+=power(2, result.length);
           printf("%ld. %c = %ld\n", i, num.value[i], temp);

       }
       result.length++;
    }
    result.value = iota(temp, result.length);

    return result;
}

BASENUM convertBX(BASENUM num){
    BASENUM result;
    BASENUM dec_num = convertBD(num);
    result.type = 'x';
    result.length = 0;
    result.value = NULL;
    char* temp = NULL;
    char* endptr;
    long dec = strtol(num.value, &endptr, 10);
    while(dec > 0){
        result.length++;
        temp = realloc(temp, result.length);
        int digit = dec % 16;
        if (digit<10){
            digit = '0'+digit;
            temp[result.length-1] = digit;
            dec = dec/16;
            continue;
        }
        digit = 55+digit;
        temp[result.length-1] = digit;
        dec = dec/16;
    }
    result.value = realloc(result.value, result.length);
    for (int i = 0; i < result.length; i++) {
        result.value[i] = temp[result.length - i - 1];
    }
    result.value[result.length] = '\0';
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
    result.length = 0;
    result.value = NULL;
    char* temp = NULL;
    char* endptr;
    long dec = strtol(num.value, &endptr, 10);
    while(dec>0){
        result.length++;
        temp = realloc(temp, result.length);
        char digit = dec%2;
        dec = dec/2;
        temp[result.length-1] = digit + '0';
    }
    result.value = realloc(result.value, result.length);
    for (int i = 0; i < result.length; i++) {
        result.value[i] = temp[result.length - i - 1];
    }
    result.value[result.length] = '\0';
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
                    printf("BD\n");
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
char convertto() {
    char c;

    while (getchar() != '\n');
    while (1) {
        printf("What to convert to? (x, b, d, o): ");
        c = getchar();

        while (getchar() != '\n');

        if (c == 'x' || c == 'b' || c == 'd' || c == 'o') {
            return c;
        }
        printf("Invalid input. Please enter one of: x, b, d, o.\n");
    }
}

int main(){
    BASENUM num = getValue();
    autoDetect(&num);
    BASENUM result = convert(num, convertto());
    printf("RESULT: %s\n", (result.value));
    return 0;
}
