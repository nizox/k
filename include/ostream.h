#ifndef KERNEL_OSTREAM_H_
#define KERNEL_OSTREAM_H_

namespace std
{

struct ostream
{
    virtual ~ostream() {}

    virtual ostream&    operator<<(const char* string) = 0;
    virtual ostream&    operator<<(char c) = 0;
    virtual ostream&    operator<<(int number) = 0;
    virtual ostream&    operator<<(unsigned int number) = 0;
    virtual ostream&    operator<<(const void* ptr) = 0;
    virtual ostream&    operator<<(std::termination) = 0;

};

}

#endif /* end of include guard: KERNEL_OSTREAM_H_ */
