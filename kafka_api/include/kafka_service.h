#ifndef _KAFKA_SERVICE_H_
#define _KAFKA_SERVICE_H_

#include "cppkafka/cppkafka.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
using cppkafka::Configuration;
using cppkafka::Consumer;
using cppkafka::Message;
using cppkafka::MessageBuilder;
using cppkafka::Producer;
using cppkafka::Topic;
using cppkafka::TopicPartitionList;
using std::string;
using std::vector;


typedef struct kafkaConfigs
{
	string kafka_broker_list;
	string produce_topic;
	string my_key;
	string group_id;
	string consume_topic;
	int auto_commit;
	// int			infomsg;
} KafkaConfig;


//produce后的回调
//需要手动poll 或 flush 才会调用


class KafkaService 
{
public:

	KafkaServie(const KafkaService& rhs)  = delete;
	KafkaService& operator=(const KafkaService& rhs) = delete;

	static KafkaService* GetInstance()
    {
        static KafkaService instance;
        return &instance;
    }

	int Initialize(const string& path = ""); //standard initialize interface 
	int Start(void);//standard start service interface 

public:
	int ProduceMsg(char *pMsgBuff, int iMsgLen, char *pTopic);
	int ConsumerPollMsg(std::vector<string> &vMessage);

protected:
	KafkaService();
	virtual ~KafkaService();
};

class KafkaProducerService
{
private:
	string my_kafkaConnect;
	string my_key;
	Configuration my_config;
	Producer *my_producer;

public:
	KafkaProducerService(const char *kafkaConnect, const char *key);

	~KafkaProducerService();

	int ProduceMsg(char *msgbuff, int msglen, char *pTopic);
};

class KafkaConsumerService
{
private:

	string my_kafkaConnect;
	string my_groupid;
	int my_autocommit;
	string my_key;
	string my_consumer_topic;
	Configuration my_config;
	int infomsg;
	Consumer *my_consumer;

public:
	KafkaConsumerService(const char *kafkaConnect, const char *groupid,
	 const char *key, const char *consumer_topic, int autocommit);

	~KafkaConsumerService();

	int ConsumerPollMsg(std::vector<string> &v_Message);
};

#endif
