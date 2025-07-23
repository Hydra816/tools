#include "kafka_service.h"

KafkaConfig g_stKafkaCfg;

KafkaProducerService *g_stKafkaProducerService = NULL;
KafkaConsumerService *g_stKafkaConsumerService = NULL;


std::map<std::string, std::string> load_config(const std::string& filename) {
    std::ifstream file(filename);
    std::map<std::string, std::string> config;

    std::string line;
    while (std::getline(file, line)) {
        // 忽略空行和注释
        if (line.empty() || line[0] == '#') continue;

        size_t pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // 去掉前后空格
        key.erase(0, key.find_first_not_of(" \t\r\n"));
        key.erase(key.find_last_not_of(" \t\r\n") + 1);
        value.erase(0, value.find_first_not_of(" \t\r\n"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);

        config[key] = value;
    }

    return config;
}
KafkaService::KafkaService()
{
	memset(&g_stKafkaCfg, 0, sizeof(g_stKafkaCfg));
}

KafkaService::~KafkaService()
{

}


int KafkaService::Initialize(const string& path)
{
    auto conf_map =  load_config(path);
    g_stKafkaCfg.kafka_broker_list = conf_map["KafkaConnect"];
    g_stKafkaCfg.produce_topic = conf_map["ProduceTopic"];
    g_stKafkaCfg.my_key = conf_map["Key"];
    g_stKafkaCfg.group_id = conf_map["GroupId"];
	g_stKafkaCfg.consume_topic = conf_map["ConsumeTopic"];
	g_stKafkaCfg.auto_commit = atoi(conf_map["AutoCommit"].c_str());
	
}

int KafkaService::Start(void)
{

	// start producer service
	g_stKafkaProducerService = new KafkaProducerService(g_stKafkaCfg.kafka_broker_list.c_str(),
														 g_stKafkaCfg.my_key.c_str());

	if (!g_stKafkaProducerService)
	{
		std::cout << "g_stKafkaProducerService create failed\n";
		return 1;
	}
	
	std::cout << "g_stKafkaProducerService start!\n";
	std::cout 	<< ", kafkaConnet= " << g_stKafkaCfg.kafka_broker_list 
				<< ", my_key= " << g_stKafkaCfg.my_key 
				<< ", producer_topic= " << g_stKafkaCfg.produce_topic 
				<< std::endl;


	// start consumer service
	g_stKafkaConsumerService = new KafkaConsumerService(g_stKafkaCfg.kafka_broker_list.c_str(),
														 g_stKafkaCfg.group_id.c_str(),
														 g_stKafkaCfg.my_key.c_str(),
														 g_stKafkaCfg.consume_topic.c_str(),
														 g_stKafkaCfg.auto_commit);
	// 需要判断返回值
	if (!g_stKafkaConsumerService)
	{
		std::cout << "g_stKafkaConsumerService create failed\n";
		return 1;
	}
	
	std::cout << "g_stKafkaConsumerService start!\n";
	std::cout << "kafkaConnet = " <<g_stKafkaCfg.kafka_broker_list
				<<", groupid = " << g_stKafkaCfg.group_id
				<< ", my_key = " << g_stKafkaCfg.my_key
				<< ", consumer_topic = " << g_stKafkaCfg.consume_topic
				<< ", autocommit = " << g_stKafkaCfg.auto_commit
				<< std::endl;

	return 0;
}


int KafkaService::ProduceMsg(char *pMsgBuff, int iMsgLen, char *pTopic)
{
	return g_stKafkaProducerService->ProduceMsg(pMsgBuff, iMsgLen, pTopic);
}

int KafkaService::ConsumerPollMsg(std::vector<string> &vMessage)
{
	return g_stKafkaConsumerService->ConsumerPollMsg(vMessage);
}

KafkaProducerService::KafkaProducerService( const char *kafkaConnect, const char *key)
{
	my_producer = NULL;
	my_kafkaConnect = kafkaConnect;
	my_key = key;
	my_config = {
		{"metadata.broker.list", my_kafkaConnect},
		{"linger.ms", 100},
		//{"batch.num.messages", 1024 * 1024},
		{ "retries", 3 },//重试次数
		{ "retry.backoff.ms", 200 },//重试间隔
		{"queue.buffering.max.kbytes", 2000000},
		{"queue.buffering.max.messages", 1000000}
	};
	
	my_config.set_delivery_report_callback(
    [](cppkafka::Producer& producer, const cppkafka::Message& message) {
        if (message.get_error()) {
            std::cerr << "Message delivery failed: " << message.get_error() << std::endl;
        }
        else {
            std::cout << "Message delivered to topic " << message.get_topic()
                      << " [" << message.get_partition() << "] at offset "
                      << message.get_offset() << std::endl;
        }
    });

	// my_config.set_delivery_report_callback(
    // [](cppkafka::Producer& producer, const cppkafka::Message& message) {
    //     if (message.get_error()) {
    //         std::cerr << "Message delivery failed: " << message.get_error() << std::endl;
    //     }
    //     else {
    //         std::cout << "Message delivered to topic " << message.get_topic()
    //                   << " [" << message.get_partition() << "] at offset "
    //                   << message.get_offset() << std::endl;
			
    //     }
    // });

	my_producer = new Producer(my_config);
	my_producer->set_timeout((std::chrono::milliseconds)1000); // 1s
}

KafkaProducerService::~KafkaProducerService()
{
	if (my_producer)
	{
		delete my_producer;
		my_producer = NULL;
	}
}

int KafkaProducerService::ProduceMsg(char *msgbuff, int msglen, char *pTopic)
{
	if (!my_producer)
		return -1;
	
	string sendmsg = string((char *)msgbuff, msglen);

	//std::cout << "Sendmsg : " << sendmsg << std::endl;

	my_producer->produce(MessageBuilder(pTopic).key(my_key).payload(sendmsg));
	my_producer->poll((std::chrono::milliseconds)5);
	
	return 0;
}

KafkaConsumerService::KafkaConsumerService(const char *kafkaConnect, const char *groupid, const char *key, const char *consumer_topic, int autocommit)
{
	my_consumer = NULL;
	infomsg = 1;
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
		{"enable.auto.commit", 1}
		//{"auto.commit.interval.ms",5000},
		//{"fetch.max.bytes",200}
	};
	my_consumer = new Consumer(my_config);
	// Set the assignment callback
	my_consumer->set_assignment_callback([&](TopicPartitionList &topic_partitions)
										 {
	// Here you could fetch offsets and do something, altering the offsets on the
	// topic_partitions vector if needed
	if(infomsg)
		cout << "Got assigned " << topic_partitions.size() << " partitions!" << endl; });

	// Set the revocation callback
	my_consumer->set_revocation_callback([&](const TopicPartitionList &topic_partitions)
										 {
		if(infomsg)
		cout << topic_partitions.size() << " partitions revoked!" << endl; });

	// Subscribe
	 my_consumer->subscribe(toplist);
}

KafkaConsumerService::~KafkaConsumerService()
{
	if (my_consumer)
	{
		delete my_consumer;
		my_consumer = NULL;
	}
}

int KafkaConsumerService::ConsumerPollMsg(std::vector<string> &vMessage)
{
	std::vector<Message> vRecvMessage;
	string sMsgBuf;
	//for calculate poll time
	//auto t1 = std::chrono::steady_clock::now();
	vRecvMessage = my_consumer->poll_batch((size_t)100, (std::chrono::milliseconds)1000);
	// auto t2 = std::chrono::steady_clock::now();
	// std::cout << "Poll used time: " 
    //       << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() 
    //       << " ms" << std::endl;
	
	if (vRecvMessage.empty())
		return 1;

	std::cout << "< ConsumerPollMsg > vRecvMessage size = " << vRecvMessage.size() << std::endl;
	
	std::string key;

	for (std::vector<Message>::iterator iter = vRecvMessage.begin(); iter != vRecvMessage.end(); iter++)
	{
		if (!(*iter).get_error())
		{
			key = (*iter).get_key();
			if(my_key == key)	continue;
			sMsgBuf = string((char*)(*iter).get_payload().get_data(), (*iter).get_payload().get_size());

			std::cout << "< ConsumerPollMsg > buf = " << sMsgBuf << ", my_key = " << my_key << std::endl;

			vMessage.push_back(sMsgBuf);
		}
		else if (!(*iter).is_eof())
		{
			if (infomsg)
				cout << "[+] Received error notification: " << (*iter).get_error() << endl;
		}
		else
		{
			if (infomsg)
				cout << "get key: " << (*iter).get_key() << endl;
		}
	}
	if (vMessage.size() == 0)
		return 1;

	return 0;
}
