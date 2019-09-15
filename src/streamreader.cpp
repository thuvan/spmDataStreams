#include "streamreader.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

StreamReader::StreamReader()
{
  //ctor
  streamDataSize = 50;
  currentLength = 0;
  //init random
  srand((unsigned)time(0));
  maxRandomValue = 100;
}

StreamReader::~StreamReader()
{
  //dtor
}

bool StreamReader::hasNext(){
  return currentLength<streamDataSize;
}

uint64_t StreamReader::readNext(){
  return (rand()%maxRandomValue)+1;
}
