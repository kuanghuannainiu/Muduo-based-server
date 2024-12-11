#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <functional>
#include <iostream>
#include<string>
using namespace muduo;
using namespace std;
using namespace::muduo::net;
using namespace placeholders;

/*
    基于vmuduo库开发的服务器程序
        1.组合TcpServer对象
        2.创建EventLoop事件循环对象的指针
        3.明確TcpServer構造函數需要什麼參數
            TcpServer(
                EventLoop* loop,                事件循環
                const InetAddress& listenAddr,  IP地址 + 端口
                const string& nameArg,          TcpServer的名稱
                Option option = kNoReusePort);  Tcp協議的選項，不需要關注
        4.在當前服務器類的構造函數中，註冊處理連接的回調函數以及處理讀寫的回調函數
        5.設置合適的服務端線程數量，Muduo會自動分配IO線程和Work線程
        6.開啓事件循環
*/

class CharServer{
public:
    CharServer(EventLoop* loop, const InetAddress& listenAddr, const string& name)
            : m_server(loop, listenAddr, name), m_loop(loop)
        {
            //給服務器註冊用戶鏈接的創建和斷開函數回調，
                //因爲事件發生和事件處理不是同一時間，也就是不知道事件是在什麼時候發生
                //所以需要註冊回調函數，讓網絡庫去幫我們監聽，當事件發生時，調用對應的註冊函數
            m_server.setConnectionCallback(std::bind(&CharServer::onConnection, this, _1));
                /*
                    函數解析：setConnectionCallback需要一個可調用對象，所以這裏採取bind來綁定
                            爲什麼需要this指針作爲參數：這是因爲調用非靜態成員函數，需要使用this指針來區分是調用該類的那一個對象
                            爲什麼需要一個佔位符，因爲onConnection需要傳入一個參數
                */
            //給服務器註冊用戶讀寫事件回調
            m_server.setMessageCallback(std::bind(&CharServer::onMessage, this, _1, _2, _3));
            //設置服務器端的線程數量
            m_server.setThreadNum(4);
                /*
                    1.如果不設置，那麼就是只有一個線程，這個線程既要負責MainReactor的連接，又要負責WorkReactor的功能（讀寫處理之類的）
                    2.這裏設置爲4,那麼就是一個MainReactor，3個WorkReactor
                */
        }
        //開啓事件循環
        void start(){
            m_server.start();
        }
private:
    //用戶鏈接(listen、accept)、斷開（close）
    void onConnection(const TcpConnectionPtr& conn){
        if(conn->connected()){
            std::cout << conn->peerAddress().toIpPort() << "->" <<
                conn->localAddress().toIpPort() << "state::online" <<"\n";
        }
        else{
            std::cout << conn->peerAddress().toIpPort() << "->" <<
                conn->localAddress().toIpPort() << "state::offline" <<"\n";
            conn->shutdown();       //close(fd)
            //loop->quit();         //不再提供服務
        }
    }
    //專門處理用戶的讀寫事件
    void onMessage(
        const TcpConnectionPtr& conn,    //連接
        Buffer* buff,                    //緩衝區
        Timestamp time)                  //返回接受到數據的時間信息
    {
        string buf = buff->retrieveAllAsString();   //將接受的數據轉換爲字符串
        std::cout << buf << "time:" << time.toString() << "\n";
        conn->send(buf);     //服務器接受到什麼，直接原路返回給客戶端，方便顯示        
    }
    TcpServer m_server; 
    EventLoop *m_loop;
};

int main(void){
    EventLoop loop;                       //epoll
    InetAddress addr("127.0.0.1", 5000);   //網絡地址
    CharServer server(&loop, addr, "ChatServer");
    server.start();                       //啓動服務，listen、epoll_ctl添加到epoll上
    loop.loop();                           //epoll_wait以阻塞方式等待新用戶連接或用戶的讀寫事件
    return 0;
}
