#include "kafka_service.h"

#include "utility.h"
#include "vlr_config.h"

KafkaProducer* gKafkaProducer = NULL;
KafkaConsumer* gKafkaConsumer = NULL;

KafkaService::KafkaService() { /*memset(&m_kafka_conf_, 0, sizeof(m_kafka_conf_));*/ }

KafkaService::~KafkaService() {}

int KafkaService::ReadKafkaConf(char* pcFileName) {
  char szValue[256];

  init_readGroupOne(pcFileName, (char*)"SYNC", (char*)"STARTUPMODE", szValue,
                    sizeof(szValue) - 1, (char*)"0");
  if (0 == atoi(szValue) ) {
    return -1;
  }

  init_readGroupOne(pcFileName, (char*)"SYNC", (char*)"KAFKAENABLE", szValue,
                    sizeof(szValue) - 1, (char*)"0");
	m_kafka_conf_.kafka_enable = atoi(szValue);
  if (0 == m_kafka_conf_.kafka_enable) {
    return -1;
  } 
  init_readGroupOne(pcFileName, (char*)"KAFKA", (char*)"KafkaConnet", szValue,
                    sizeof(szValue) - 1, (char*)"nn1.hadoop:9092");
  m_kafka_conf_.kafka_broker_list = szValue;

  init_readGroupOne(pcFileName, (char*)"KAFKA", (char*)"sync_topic",
                    szValue, sizeof(szValue) - 1, (char*)"topicTest1");
  m_kafka_conf_.produce_topic = szValue;

  init_readGroupOne(pcFileName, (char*)"KAFKA", (char*)"my_key", szValue,
                    sizeof(szValue) - 1, (char*)"0.0.0.0");
  m_kafka_conf_.my_key = szValue;

  init_readGroupOne(pcFileName, (char*)"KAFKA", (char*)"sync_consumer_groupid",
                    szValue, sizeof(szValue) - 1, (char*)"vlr1");
  m_kafka_conf_.group_id = szValue;

  init_readGroupOne(pcFileName, (char*)"KAFKA", (char*)"sync_topic",
                    szValue, sizeof(szValue) - 1, (char*)"topicTest1");
  m_kafka_conf_.consume_topic = szValue;

  init_readGroupOne(pcFileName, (char*)"KAFKA", (char*)"consumer_autocommit",
                    szValue, sizeof(szValue) - 1, (char*)"0");
  m_kafka_conf_.auto_commit = atoi(szValue);

  return RTN_SUCCESS;
}

const KafkaConfig & KafkaService::GetKafkaConf() {
  return m_kafka_conf_;
}

int KafkaService::Start(void) {
  // start producer service
  gKafkaProducer = new KafkaProducer(m_kafka_conf_.kafka_broker_list.c_str(),
                                     m_kafka_conf_.my_key.c_str());

  if (!gKafkaProducer) {
    std::cout << "gKafkaProducer create failed\n";
    return 1;
  }

  // std::cout << "gKafkaProducer start!\n";
  // std::cout 	<< ", kafkaConnet= " << m_kafka_conf_.kafka_broker_list
  // 			<< ", my_key= " << m_kafka_conf_.my_key
  // 			<< ", producer_topic= " << m_kafka_conf_.produce_topic
  // 			<< std::endl;

  // start consumer service
  gKafkaConsumer = new KafkaConsumer(
      m_kafka_conf_.kafka_broker_list.c_str(), m_kafka_conf_.group_id.c_str(),
      m_kafka_conf_.my_key.c_str(), m_kafka_conf_.consume_topic.c_str(),
      m_kafka_conf_.auto_commit);

  if (!gKafkaConsumer) {
    std::cout << "gKafkaConsumer create failed\n";
    return 1;
  }

  // std::cout << "gKafkaConsumer start!\n";
  // std::cout << "kafkaConnet = " <<m_kafka_conf_.kafka_broker_list
  // 			<<", groupid = " << m_kafka_conf_.group_id
  // 			<< ", my_key = " << m_kafka_conf_.my_key
  // 			<< ", consumer_topic = " << m_kafka_conf_.consume_topic
  // 			<< ", autocommit = " << m_kafka_conf_.auto_commit
  // 			<< std::endl;

  return 0;
}

int KafkaService::ProduceMsg(char* pMsgBuff, int iMsgLen) {
  return gKafkaProducer->ProduceMsg(pMsgBuff, iMsgLen, const_cast<char*>(m_kafka_conf_.produce_topic.c_str()));
}

int KafkaService::ConsumerPollMsg(std::vector<string>& vMessage) {
  return gKafkaConsumer->ConsumerPollMsg(vMessage);
}

KafkaProducer::KafkaProducer(const char* kafkaConnect, const char* key) {
  my_producer = NULL;
  my_kafkaConnect = kafkaConnect;
  my_key = key;
  my_config = {{"metadata.broker.list", my_kafkaConnect},
               {"linger.ms", 100},
               //{"batch.num.messages", 1024 * 1024},
               {"retries", 3},             // 重试次数
               {"retry.backoff.ms", 200},  // 重试间隔
               {"queue.buffering.max.kbytes", 2000000},
               {"queue.buffering.max.messages", 1000000}};

  // my_config.set_delivery_report_callback(
  // [](cppkafka::Producer& producer, const cppkafka::Message& message) {
  //     if (message.get_error()) {
  //         std::cerr << "Message delivery failed: " << message.get_error() <<
  //         std::endl;
  //     }
  //     else {
  //         std::cout << "Message delivered to topic " << message.get_topic()
  //                   << " [" << message.get_partition() << "] at offset "
  //                   << message.get_offset() << std::endl;

  //     }
  // });

  my_producer = new Producer(my_config);
  my_producer->set_timeout((std::chrono::milliseconds)1000);  // 1s
}

KafkaProducer::~KafkaProducer() {
  if (my_producer) {
    delete my_producer;
    my_producer = NULL;
  }
}

int KafkaProducer::ProduceMsg(char* msgbuff, int msglen, char* pTopic) {
  if (!my_producer) return -1;

  string sendmsg = string((char*)msgbuff, msglen);

  // std::cout << "Sendmsg : " << sendmsg << std::endl;

  my_producer->produce(MessageBuilder(pTopic).key(my_key).payload(sendmsg));
  my_producer->poll(std::chrono::milliseconds(5));

  return 0;
}

KafkaConsumer::KafkaConsumer(const char* kafkaConnect, const char* groupid,
                             const char* key, const char* consumer_topic,
                             int autocommit) {
  my_consumer = NULL;
  infomsg = 0;
  my_kafkaConnect = kafkaConnect;
  my_groupid = groupid;
  my_key = key;
  my_autocommit = autocommit;
  my_consumer_topic = consumer_topic;
  vector<string> toplist;

  toplist.push_back(my_consumer_topic);
  my_config = {
      {"metadata.broker.list", my_kafkaConnect},
      {"group.id", my_groupid},
      {"enable.auto.commit", 1},
      {"auto.offset.reset", "earliest"},  // 没有 offset 时，从最早开始
      {"fetch.wait.max.ms", "100"},       // 控制 broker 等待时间，默认 500ms
      {"fetch.min.bytes", "1"},           // 拉取最小数据量
      {"fetch.max.bytes", "1048576"}      // 单次最大拉取 1MB
                                          //{"auto.commit.interval.ms",5000},
  };

  my_consumer = new Consumer(my_config);
  // Set the assignment callback
  my_consumer->set_assignment_callback(
      [&](TopicPartitionList& topic_partitions) {
        // Here you could fetch offsets and do something, altering the offsets
        // on the topic_partitions vector if needed
        if (infomsg)
          std::cout << "Got assigned " << topic_partitions.size()
                    << " partitions!" << std::endl;
      });

  // Set the revocation callback
  my_consumer->set_revocation_callback(
      [&](const TopicPartitionList& topic_partitions) {
        if (infomsg)
          std::cout << topic_partitions.size() << " partitions revoked!"
                    << std::endl;
      });

  // Subscribe
  my_consumer->subscribe(toplist);
}

KafkaConsumer::~KafkaConsumer() {
  if (my_consumer) {
    delete my_consumer;
    my_consumer = NULL;
  }
}

int KafkaConsumer::ConsumerPollMsg(std::vector<string>& vMessage) {
  std::vector<Message> vRecvMessage;
  string sMsgBuf;

	//auto t1 = std::chrono::steady_clock::now();
  vRecvMessage =
      my_consumer->poll_batch((size_t)1000, (std::chrono::milliseconds)1000);
  // auto t2 = std::chrono::steady_clock::now();
  // std::cout << "Poll used time: "
  //       << std::chrono::duration_cast<std::chrono::milliseconds>(t2 -
  //       t1).count()
  //       << " ms" << std::endl;

  if (vRecvMessage.empty()) return 1;
  // std::cout << "vRecvMessage.size = " << vRecvMessage.size() << std::endl;

  std::string key;
  for (std::vector<Message>::iterator iter = vRecvMessage.begin();
       iter != vRecvMessage.end(); iter++) {
    if (!(*iter).get_error()) {
      key = (*iter).get_key();
      if (my_key == key) continue; //this message is send by myself

      sMsgBuf = string((char*)(*iter).get_payload().get_data(),
                       (*iter).get_payload().get_size());

      // std::cout << "Recvmsg : " << sMsgBuf << std::endl;

      vMessage.push_back(sMsgBuf);
    } else if (!(*iter).is_eof()) {
      if (infomsg)
        std::cout << "[+] Received error notification: " << (*iter).get_error()
                  << std::endl;
    } else {
      if (infomsg) std::cout << "get key: " << (*iter).get_key() << std::endl;
    }
  }

  if (vMessage.size() == 0) return 1;

  return 0;
}

int ProducerKafkaMulticCallback(char* pMsgbuff, int iMsglen) {
  return KafkaService::GetInstance()->ProduceMsg(pMsgbuff, iMsglen);
}

int ConsumerPollKafkaMulticCallback(std::vector<string>& vMessage) {
  return KafkaService::GetInstance()->ConsumerPollMsg(vMessage);
}
