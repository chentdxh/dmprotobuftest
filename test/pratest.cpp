#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fstream>
#include "test.pb.h"
using namespace std;
#define BUFFSIZE 1024
int main()
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  //写文件
  lm::helloworld msg1;
  msg1.set_id(1);
  msg1.set_str("test1");
  fstream output("./log", ios::out | ios::trunc | ios::binary);
  if (!msg1.SerializeToOstream(&output)) {
      cerr << "Failed to write msg." << endl;
      return -1;
  }
  output.close();
  //读文件
  lm::helloworld msg2;
  fstream input("./log", ios::in | ios::binary);
  if (!input)
  {
     cerr << "open file failed!\n";
     return -1;
  }
  if (!msg2.ParseFromIstream(&input)) {
      cerr << "Parse file failed!" << endl;
      return -1;
  }
  input.close();
  for(int i=0;i<100000;i++)
  {
   // 写buf, protobuf序列化
   lm::helloworld msg3;
   msg3.set_id(2);
   msg3.set_str("test2");
   char buf[BUFFSIZE];
   memset(buf,0,BUFFSIZE);
   msg3.SerializeToArray(buf,BUFFSIZE);
   //读buf,protobuf反序列化
   lm::helloworld msg4;
   msg4.ParseFromArray(buf, BUFFSIZE);
   google::protobuf::ShutdownProtobufLibrary();
  }
  return 0;
}
