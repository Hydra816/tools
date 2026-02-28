#include "../include/cppkafka/cppkafka.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanup>
#include<sstream>
using namespace cppkafka;

std::string timestamp_to_string(uint64_t ms_timestamp) {
    // 转换为秒
    time_t seconds = static_cast<time_t>(ms_timestamp / 1000);
    
    // 获取本地时间
    std::tm* local_time = std::localtime(&seconds);
    
    // 格式化为 YYYYMMDDHH
    std::ostringstream oss;
    oss << std::setfill('0')
        << (local_time->tm_year + 1900)  // 年 (从1900开始)
        << std::setw(2) << (local_time->tm_mon + 1)   // 月 (0-11)
        << std::setw(2) << local_time->tm_mday        // 日
        << std::setw(2) << local_time->tm_hour;       // 小时
    
    return oss.str();
}

static inline uint64_t now_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()).count();
}

static inline std::string gen_imsi(uint64_t seq) {
    char buf[32];
    snprintf(buf, sizeof(buf), "4601%011lu", seq);
    return buf;
}

static inline std::string gen_msisdn(uint64_t seq) {
    char buf[32];
    snprintf(buf, sizeof(buf), "+63992%011lu", seq);
    return buf;
}

static std::vector<int> plmn_conf = {20416,27411,22288,23471};

std::string gen_sip(uint64_t seq, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 100000);
    auto imsi = gen_imsi(seq);
    auto msisdn = gen_msisdn(seq);

    int suffix = plmn_conf[seq % 4];
    char buf[256];
    snprintf(buf, sizeof(buf),
        "0|SIP|%s|%d|%d|%s|%s|%d|%d|%d",
        timestamp_to_string(now_ms()).c_str(),
        dist(rng),
        dist(rng) % 5,
        msisdn.c_str(),
        imsi.c_str(),
        dist(rng),
        dist(rng) % 65535,
        suffix
    );
    return buf;
}
//PLMN：20416，27411、22288、23471
std::string gen_dia(uint64_t seq, std::mt19937& rng) {
    auto imsi = gen_imsi(seq);
    auto msisdn = gen_msisdn(seq);

    char buf[256];
    int suffix = plmn_conf[seq % 4];
    snprintf(buf, sizeof(buf),
        "0|DIA|%s|%s|mme%d.dito.com|dito.com|%s|%d|12345-%lu",
        timestamp_to_string(now_ms()).c_str(),
        imsi.c_str(), rng() % 100,
        msisdn.c_str(),
        suffix,
        now_ms()
    );
    return buf;
}

std::string gen_map(uint64_t seq, std::mt19937& rng) {
    auto imsi = gen_imsi(seq);
    auto msisdn = gen_msisdn(seq);
    static std::vector<int> cc_conf = {81,82,63,92};
    int suffix = cc_conf[seq % 4];  
    char buf[256];
    snprintf(buf, sizeof(buf),
        "0|MAP|%s|0|%s|%s|289%d%d|1068%d|852%d|853%d",
        timestamp_to_string(now_ms()).c_str(),
        msisdn.c_str(),
        imsi.c_str(),
        suffix,
        rng() % 1000000,
        rng() % 1000000,
        rng() % 1000000,
        rng() % 1000000
    );
    return buf;
}

int main(int argc, char* argv[]) {
     std::string brokers = "localhost:9092";
     std::string topic   = "DITO_SIG";
     uint32_t QPS        = 2000;   // <<< 可调
     uint32_t DURATION   = 60;     // <<< 秒

    for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--brokers" && i+1 < argc) brokers = argv[++i];
    else if (arg == "--topic" && i+1 < argc) topic = argv[++i];
    else if (arg == "--qps" && i+1 < argc) QPS = std::stoul(argv[++i]);
    else if (arg == "--duration" && i+1 < argc) DURATION = std::stoul(argv[++i]);
}

    Configuration config = {
        { "bootstrap.servers", brokers },
        { "acks", "1" },
        { "linger.ms", 5 },
        { "batch.num.messages", 1000 },
        { "queue.buffering.max.messages", 1000000 },
        { "compression.type", "lz4" }
    };

    Producer producer(config);
    std::mt19937 rng(std::random_device{}());

    uint64_t seq = 1;
    auto start_time = std::chrono::steady_clock::now();

    for (uint32_t sec = 0; sec < DURATION; ++sec) {
        auto next_tick = start_time + std::chrono::seconds(sec + 1);

        for (uint32_t i = 0; i < QPS; ++i) {
            int r = rng() % 100;
            std::string msg;

            if (r < 40) msg = gen_sip(seq, rng);
            else if (r < 70) msg = gen_dia(seq, rng);
            else msg = gen_map(seq, rng);

            producer.produce(
                MessageBuilder(topic).payload(msg)
            );
            ++seq;
        }

        producer.flush();
        std::this_thread::sleep_until(next_tick);
    }

    producer.flush();
    std::cout << "Done. Sent " << seq - 1 << " messages\n";
    return 0;
}
