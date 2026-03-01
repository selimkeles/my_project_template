#ifndef CIRC_BUFF
#define CIRC_BUFF

void taskOneMain(void);

template <class T> class ringBuffer
{
  private:
    int head = 0, tail = 0;
    static constexpr int BUFF_SIZE = 100;
    T buf_[BUFF_SIZE];

  public:
    ringBuffer() : head(0), tail(0)
    {
    }

    void push(T val)
    {
        if (full())
        {
            head = (head + 1) % BUFF_SIZE;
        }
        buf_[tail] = val;
        tail = (tail + 1) % BUFF_SIZE;
    }

    bool pop(T& out)
    {
        if (empty())
        {
            return false;
        }
        out = buf_[head];
        head = (head + 1) % BUFF_SIZE;
        return true;
    }

    bool peek(T& out)
    {
        if (empty())
        {
            return false;
        }
        out = buf_[head];
        return true;
    }

    int size()
    {
        return (tail - head + BUFF_SIZE) % BUFF_SIZE;
    }

    bool full()
    {
        return (tail + 1) % BUFF_SIZE == head;
    }

    bool empty()
    {
        return head == tail;
    }
};

#endif
