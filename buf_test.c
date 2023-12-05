#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct ssd{//ssd data
    int age;
    char name[10];
};

struct buf_val{//lpn + ssd data 구조체
    uint64_t lpn;
    struct ssd *ssd;
};

struct buf_val buf[10]; //버퍼

void buf_flush(){//맨 마지막 내용 제거
    int length = sizeof(buf)/sizeof(buf[0]);
    for(int i=1;i<length;i++){
        buf[i]=buf[i-1]; //맨 마지막칸 밀어내기
    }
}

void LRU_move(int i){//i번째 내용을 0번째로 이동
    struct buf_val temp = buf[i];
    for(int j=1;j<=i;j++){
        buf[j]=buf[j-1];
    }
    buf[0] = temp;
}

void buf_write(struct buf_val *buf_v){//버퍼 write 함수
    int length = sizeof(buf)/sizeof(*buf_v);
    buf[0] = (*buf_v);
    
    for(int i=0;i<length;i++){
        if(buf[i].lpn==0){
            buf[i] = (*buf_v);//비어 있으면 write후 return
            return;
        }
    }
    buf_flush();
    buf[0]=(*buf_v);
    /*마지막 버퍼 제거 후 [0]에 insert*/
}

struct buf_val buf_read(uint64_t lpn_t){//버퍼 read 함수
    struct buf_val temp;
    int length = sizeof(buf)/sizeof(temp);
    for(int i=0;i<length;i++){
        if(buf[i].lpn==lpn_t){
            temp = buf[i];
            LRU_move(i); 
            return temp;
    /*
    해당 버퍼 임시 저장후 해당 내용 return 
    LRU_move()로 read 한 것을 맨 위로 올림
    */
        }
    }
}

void main(){
    struct ssd aaa = {3, "차상민"};//ssd data
    struct buf_val bbb = {24, &aaa}; //lpn + ssd data 구조체
    buf_write(&bbb);
    
    struct buf_val ccc = buf_read(24);
    printf("%d\n",ccc.lpn);
}