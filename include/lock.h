#ifndef LOCK_H
#define LOCK_H

class lock
{
  public:
    lock();
    ~lock();

    bool take();
    bool is_locked();
    bool release();

  private:
    bool _locked;
};

#endif
