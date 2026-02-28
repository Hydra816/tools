#include "../include/cppkafka/cppkafka.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>

using namespace cppkafka;

static uint64_t send_num = 0;
static inline uint64_t now_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()).count();
}

static inline std::string gen_imsi(uint64_t seq) {
    char buf[32];
    snprintf(buf, sizeof(buf), "51566%010lu", seq%50000);
    return buf;
}

static inline std::string gen_msisdn(uint64_t seq) {
    char buf[32];
    snprintf(buf, sizeof(buf), "+63992%08lu", seq%50000);
    return buf;
}

//0|SIP|timestamp|msg_id|type|user_phone|imsi|eci|tac|plmn
std::string gen_sip(uint64_t seq, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 100000);
    auto imsi = gen_imsi(seq);
    auto msisdn = gen_msisdn(seq);

    char buf[256];
    snprintf(buf, sizeof(buf),
        "0|SIP|%lu|%d|0|%s|%s|%d|%d|51566",
        now_ms(),
        dist(rng),
        msisdn.c_str(),
        imsi.c_str(),
        dist(rng),
        dist(rng) % 65535
    );
    return buf;
}

std::string gen_dia(uint64_t seq, std::mt19937& rng) {
    auto imsi = gen_imsi(seq);
    auto msisdn = gen_msisdn(seq);
// 0|DIA|time|username|origin_host|origin_realm|msisdn|visited_plmn_id|session_id
    char buf[256];
    snprintf(buf, sizeof(buf),
        "0|DIA|%lu|%s|mme%d.dito.com|dito.com|%s|51566|%s-%lu",
        now_ms(),
        imsi.c_str(), rng() % 100,
        msisdn.c_str(),
        imsi.c_str(), now_ms()
    );
    return buf;
}

std::string gen_map(uint64_t seq, std::mt19937& rng) {
    auto imsi = gen_imsi(seq);
    auto msisdn = gen_msisdn(seq);
//0|MAP|time|event_id|msisdn|imsi|srcgt|destgt|vlr_number|msc_number
    char buf[256];
    snprintf(buf, sizeof(buf),
        "0|MAP|%lu|0|%s|%s|28981%d|1068%d|852%d|853%d",
        now_ms(),
        msisdn.c_str(),
        imsi.c_str(),
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
            ++send_num;
            ++seq;
        }

        producer.flush();
        std::this_thread::sleep_until(next_tick);
    }

    producer.flush();
    std::cout << "Done. Sent " << send_num << " messages\n";
    return 0;
}
