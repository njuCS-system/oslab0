#ifndef OUR_UTIL_H
#define OUR_UTIL_H

#define TRUE 1
#define FALSE 0
#ifndef NULL
#define NULL 0
#endif 

#define bool char 

typedef struct Info{
    volatile char type;//record the type of an object
    volatile bool valid;

}Info;





#endif