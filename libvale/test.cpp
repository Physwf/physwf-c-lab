#include "Server.h"
#include "Connection.h"

class Main: public Object
{
public:
    Main()
    {
        printf("Main\n");
        EventLoop *pLoop = new EventLoop();
        printf("1\n");
        Server* server = new Server(pLoop);
        server->createTcpServer(3456);
        
        server->setConnectionHandler(EV_IO_CB(this, Main::onConnect));
        server->start();
        pLoop->run();
        printf("2\n");
    }
public:
    void onConnect(int fd, int event,void* data)
    {
        printf("connected!\n");
    }
    
};

Main *m;
int main(int argc,char** argv)
{
    m = new Main();
}
