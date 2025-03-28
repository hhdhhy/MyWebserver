#pragma once
#include<sys/epoll.h>
#include<functional>
#include"Loop.h"

//封装fd与其关注事件与发生事件 和回调函数
class Channel
{
    typedef std::function<void()> callback_function;

public:
    Channel(std::shared_ptr<Loop> loop,int fd,int event=NONE_EVENT);
    ~Channel();

    void set_callback_read(const callback_function& callback);
    void set_callback_write(const callback_function& callback);
    void set_callback_close(const callback_function& callback);
    void set_callback_error(const callback_function& callback);

    void set_events(const int &event);
    void set_revents(const int &revent);
    int get_events();
    int get_revents();
    int get_fd();
    std::shared_ptr<Loop> get_loop();
    void  enable_read();
    void  enable_write();
    void  disable_read();
    void  disable_write();

    void  disable_all();

    void update_epoll();//更新loop对应的epoll

    void handle_all();
    bool is_in_epoll();

private:
    /* data */
    static const int READ_EVENT = EPOLLIN;
    static const int WRITE_EVENT = EPOLLOUT;
    static const int NONE_EVENT = 0;
    const int fd_;
    std::atomic<bool> is_calling_;
    std::atomic<bool> is_in_epoll_;
    int events_;
    int revents_;
    std::shared_ptr<Loop> loop_;
    callback_function callback_read_;
    callback_function callback_write_;
    callback_function callback_close_;
    callback_function callback_error_;

};

