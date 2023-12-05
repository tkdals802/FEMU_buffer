#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct ssd{
    int age;
    char name[10];
};

struct buf_val{
    uint64_t lpn;
    struct ssd *ssd;
};

struct buf_val ccc[10];

void buf_write(struct buf_val *buf){
    int length = sizeof(ccc)/sizeof(buf);
    for(int i=0;i<length;i++){
        
    }
}

void main(){
    struct ssd aaa = {3, "차상민"};
    struct buf_val bbb = {10, &aaa};


    printf("%d\n",ccc[0]);

}