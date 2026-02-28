#ifndef _VLR_KAFKA_SERVICE_H_
#define _VLR_KAFKA_SERVICE_H_

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "cppkafka/cppkafka.h"

using cppkafka::Configuration;
using cppkafka::Consumer;
using cppkafka::Message;
using cppkafka::MessageBuilder;
using cppkafka::Producer;
using cppkafka::Topic;
using cppkafka::TopicPartitionList;
using std::string;
using std::vector;

typedef struct kafkaConfigs {
  string kafka_broker_list;
  string produce_topic;
  string my_key;
  string group_id;
  string consume_topic;
  int auto_commit;
  int kafka_enable;
  // int			infomsg;
} KafkaConfig;

// produce后的回调
// 需要手动poll 或 flush 才会调用

class KafkaService {
 public:
  KafkaService(const KafkaService& rhs) = delete;
  KafkaService& operator=(const KafkaService& rhs) = delete;

  static KafkaService* GetInstance() {
    static KafkaService instance;
    return &instance;
  }

  /* **
   * @function：read kafka config file
   * @return value：
   *			-1 ：Do not enable the Kafka service
   *			0 ：use kafka service
   */
  int ReadKafkaConf(char* pcFileName);

  int Start(void);
  
  int ProduceMsg(char* pMsgBuff, int iMsgLen);
  int ConsumerPollMsg(std::vector<string>& vMessage);
  const KafkaConfig &GetKafkaConf();
 protected:
  KafkaService();
  virtual ~KafkaService();
private:
  KafkaConfig m_kafka_conf_;
};

class KafkaProducer {
 private:
  string my_kafkaConnect;
  string my_key;
  Configuration my_config;
  Producer* my_producer;

 public:
  KafkaProducer(const char* kafkaConnect, const char* key);

  ~KafkaProducer();

  int ProduceMsg(char* msgbuff, int msglen, char* pTopic);
};

class KafkaConsumer {
 private:
  string my_kafkaConnect;
  string my_groupid;
  int my_autocommit;
  string my_key;
  string my_consumer_topic;
  Configuration my_config;
  int infomsg;
  Consumer* my_consumer;

 public:
  KafkaConsumer(const char* kafkaConnect, const char* groupid, const char* key,
                const char* consumer_topic, int autocommit);

  ~KafkaConsumer();

  int ConsumerPollMsg(std::vector<string>& v_Message);
};

int ProducerKafkaMulticCallback(char* pMsgbuff, int iMsglen);
int ConsumerPollKafkaMulticCallback(std::vector<string>& vMessage);

#endif
