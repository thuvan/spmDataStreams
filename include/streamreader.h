#ifndef STREAMREADER_H
#define STREAMREADER_H

#include<stdint.h>

class StreamReader
{
  public:
    StreamReader();
    virtual ~StreamReader();

    virtual bool hasNext();
    virtual uint64_t readNext();

  protected:

  private:
    int streamDataSize=-1;
    int currentLength = 0;
    int maxRandomValue=100;
};

#endif // STREAMREADER_H
