// header.h

#define NOT_READY -1
#define FILLED 0 //when sender fill data
#define TAKEN 1 //when receiver take data
#define GO 2 // when sender keep sending
#define STOP 3 // when sender stop sending data

struct numbers {
int nums[5];
};

struct Memory {
int status;
int gostop;
struct numbers data;
int count;
};