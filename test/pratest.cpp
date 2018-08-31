#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fstream>
#include <sys/time.h>
#include "../src/test.pb.h"
using namespace std;
#define BUFFSIZE 1024
int main()
{
  clock_t start,end;
  start = clock();
  for(int i=0;i<1000000;i++)
  {
   // 写buf, protobuf序列化
   lm::helloworld msg1;
   msg1.set_id(2);
   msg1.set_str("test2");
   char buf[BUFFSIZE];
   memset(buf,0,BUFFSIZE);
   msg1.SerializeToArray(buf,BUFFSIZE);
   //读buf,protobuf反序列化
   lm::helloworld msg2;
   msg2.ParseFromArray(buf, BUFFSIZE);
   google::protobuf::ShutdownProtobufLibrary();
  }
  end = clock();
  double seconds = (double)(end - start)/CLOCKS_PER_SEC;
  fprintf(stderr, "Use time is: %.8f\n", seconds);
  return 0;
}
