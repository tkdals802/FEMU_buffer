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

struct buf_val buf[10];

void buf_flush(){
    int length = sizeof(buf)/sizeof(buf[0]);
    for(int i=1;i<length;i++){
        buf[i]=buf[i-1]; //맨 마지막칸 밀어내기
    }
}

void LRU_move(int i){
    struct buf_val temp = buf[i];
    for(int j=1;j<=i;j++){
        buf[j]=buf[j-1];//한칸씩 밀어주기
    }
    buf[0] = temp;
}

void buf_write(struct buf_val *buf_v){
    int length = sizeof(buf)/sizeof(*buf_v);
    buf[0] = (*buf_v);

    for(int i=0;i<length;i++){
        if(buf[i].lpn==0){
            buf[i] = (*buf_v);//비어 있으면 write후 return
            return;
        }
    }
    /*빈 공간이 없으면 밀어내고 [0]에 insert*/
    buf_flush();
    buf[0]=(*buf_v);
}

struct buf_val buf_read(uint64_t lpn_t){
    struct buf_val temp;
    int length = sizeof(buf)/sizeof(temp);
    for(int i=0;i<length;i++){
        if(buf[i].lpn==lpn_t){
            temp = buf[i];
            LRU_move(i);
            return temp;//lpn이 있으면 버퍼 구조체 return
        }
    }
    

}

void main(){
    struct ssd aaa = {3, "차상민"};
    struct buf_val bbb;
    buf_write(&bbb);

    
}