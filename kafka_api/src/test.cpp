#include "vlr_kafka_service.h"
#include <thread>

using std::thread;

int main()
{
    //读取配置文件  
    KafkaService::GetInstance()->Initialize("../cfg/kafka.cfg");

    //初始化生产者和消费者
    KafkaService::GetInstance()->Start();
    vector<string> vMsgs;

    thread t1([&](){
        while(1)
        {
            static int num = 0;
            string msg = "10.20.11.13{hellokafka -- " + std::to_string(num) + " }";
            num++;
            ProducerKafkaMulticCallback(const_cast<char*>(msg.c_str()), msg.size());
            sleep(5);
        }
    });

    thread t2([&](){
        while(1)
        {
            ConsumerPollKafkaMulticCallback(vMsgs);
            for(auto &msg : vMsgs)
            {
                cout << msg << endl;
                sleep(5);
            }
        }
    });


    t1.join();
    t2.join();

    return 0;
}