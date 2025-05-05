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
            }
            if ((*num).value[i]>'7' && (*num).type!='x'){
                (*num).type = 'd';
            }
            if ((*num).value[i]>'1' && (*num).type!='d' && (*num).type!='x'){
                (*num).type = 'o';
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


int main(){
    BASENUM num = getValue();
    autoDetect(&num);
    printf("%s\n", num.value);
    return 0;
}
