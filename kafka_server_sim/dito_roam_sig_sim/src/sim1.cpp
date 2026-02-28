#include "../include/cppkafka/cppkafka.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>
#include <atomic>
#include <csignal>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <functional>
#include <algorithm>  

using namespace cppkafka;
using namespace std::chrono;

// 全局控制变量
std::atomic<bool> g_running{true};
std::atomic<uint64_t> g_total_sent{0};
std::atomic<uint64_t> g_total_failed{0};

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

void signal_handler(int signal) {
    g_running = false;
    std::cout << "\nShutdown signal received, waiting for graceful shutdown..." << std::endl;
}

class HighPerformanceProducer {
private:
    Producer producer_;
    std::string topic_;
    std::vector<std::mt19937> rngs_;
    std::vector<int> plmn_conf_{20416, 27411, 22288, 23471};
    std::vector<int> cc_conf_{81, 82, 63, 92};
    
    // 统计
    steady_clock::time_point start_time_;
    steady_clock::time_point last_stats_time_;
    uint64_t last_stats_count_;
    
public:
    HighPerformanceProducer(const Configuration& config, 
                          const std::string& topic)
        : producer_(config), topic_(topic) {
        
        // 初始化多个随机数生成器
        unsigned int seed = static_cast<unsigned int>(
            system_clock::now().time_since_epoch().count());
        for (size_t i = 0; i < 4; ++i) {
            rngs_.emplace_back(seed + i);
        }
        
        start_time_ = steady_clock::now();
        last_stats_time_ = start_time_;
        last_stats_count_ = 0;
    }
    
    std::string gen_imsi(uint64_t seq) {
        char buf[32];
        snprintf(buf, sizeof(buf), "4601%011lu", seq);
        return buf;
    }
    
    std::string gen_msisdn(uint64_t seq) {
        char buf[32];
        snprintf(buf, sizeof(buf), "+63992%011lu", seq);
        return buf;
    }
    
    std::string gen_sip(uint64_t seq) {
        auto& rng = rngs_[seq % rngs_.size()];
        thread_local char buf[512];
        auto imsi = gen_imsi(seq);
        auto msisdn = gen_msisdn(seq);
        
        std::uniform_int_distribution<int> dist(0, 100000);
        int suffix = plmn_conf_[seq % plmn_conf_.size()];
        
        // auto now_ms = duration_cast<milliseconds>(
        //     system_clock::now().time_since_epoch()).count();
        
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
    
    std::string gen_dia(uint64_t seq) {
        auto& rng = rngs_[seq % rngs_.size()];
        thread_local char buf[512];
        auto imsi = gen_imsi(seq);
        auto msisdn = gen_msisdn(seq);
        
        int suffix = plmn_conf_[seq % plmn_conf_.size()];
        // auto now_ms = duration_cast<milliseconds>(
        //     system_clock::now().time_since_epoch()).count();
        
        snprintf(buf, sizeof(buf),
            "0|DIA|%s|%s|mme%d.dito.com|dito.com|%s|%d|12345-%lu",
            timestamp_to_string(now_ms()).c_str(),
            imsi.c_str(),
            static_cast<int>(rng() % 100),
            msisdn.c_str(),
            suffix,
            now_ms
        );
        return buf;
    }
    
    std::string gen_map(uint64_t seq) {
        auto& rng = rngs_[seq % rngs_.size()];
        thread_local char buf[512];
        auto imsi = gen_imsi(seq);
        auto msisdn = gen_msisdn(seq);
        
        int suffix = cc_conf_[seq % cc_conf_.size()];
        // auto now_ms = duration_cast<milliseconds>(
        //     system_clock::now().time_since_epoch()).count();
        
        snprintf(buf, sizeof(buf),
            "0|MAP|%s|0|%s|%s|289%d%d|1068%d|852%d|853%d",
            timestamp_to_string(now_ms()).c_str(),
            msisdn.c_str(),
            imsi.c_str(),
            suffix,
            static_cast<int>(rng() % 1000000),
            static_cast<int>(rng() % 1000000),
            static_cast<int>(rng() % 1000000),
            static_cast<int>(rng() % 1000000)
        );
        return buf;
    }
    
    // 批量生产消息
    bool produce_batch(uint64_t start_seq, uint32_t count) {
        try {
            for (uint32_t i = 0; i < count && g_running; ++i) {
                uint64_t seq = start_seq + i;
                auto& rng = rngs_[seq % rngs_.size()];
                
                int r = rng() % 100;
                std::string msg;
                
                if (r < 40) {
                    msg = gen_sip(seq);
                } else if (r < 70) {
                    msg = gen_dia(seq);
                } else {
                    msg = gen_map(seq);
                }
                
                // 直接构造 MessageBuilder，避免拷贝
                producer_.produce(
                    MessageBuilder(topic_).payload(msg)
                );
            }
            return true;
        } catch (const std::exception& e) {
            std::cerr << "\nBatch produce error: " << e.what() << std::endl;
            return false;
        }
    }
    
    // 单消息生产（备用）
    bool produce_single(uint64_t seq) {
        try {
            auto& rng = rngs_[seq % rngs_.size()];
            int r = rng() % 100;
            std::string msg;
            
            if (r < 40) {
                msg = gen_sip(seq);
            } else if (r < 70) {
                msg = gen_dia(seq);
            } else {
                msg = gen_map(seq);
            }
            
            producer_.produce(
                MessageBuilder(topic_).partition(rng() % 4).payload(msg)
            );
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Produce error: " << e.what() << std::endl;
            return false;
        }
    }
    
    void print_stats() {
        auto now = steady_clock::now();
        auto elapsed = duration_cast<seconds>(now - start_time_).count();
        auto recent_elapsed = duration_cast<seconds>(now - last_stats_time_).count();
        
        uint64_t total = g_total_sent.load();
        uint64_t recent = total - last_stats_count_;
        
        double overall_qps = elapsed > 0 ? static_cast<double>(total) / elapsed : 0;
        double recent_qps = recent_elapsed > 0 ? static_cast<double>(recent) / recent_elapsed : 0;
        
        // 获取队列状态
        auto queue_len = producer_.get_out_queue_length();
        
        std::cout << "\r[" << std::setw(8) << elapsed << "s] "
                  << "Total: " << std::setw(10) << total
                  << " | Queue: " << std::setw(5) << queue_len
                  << " | QPS: " << std::setw(8) << std::fixed << std::setprecision(1) << recent_qps
                  << " | Failed: " << g_total_failed.load()
                  << std::flush;
        
        last_stats_time_ = now;
        last_stats_count_ = total;
    }
    
    void flush() {
        try {
            producer_.flush(std::chrono::milliseconds(5000));
        } catch (const std::exception& e) {
            std::cerr << "\nFlush error: " << e.what() << std::endl;
        }
    }
    
    Producer& get_producer() { return producer_; }
};

// 精确速率控制的生产循环
void produce_with_rate_control(HighPerformanceProducer& producer, 
                              uint32_t target_qps, 
                              uint32_t duration_sec) {
    const uint32_t MICRO_BATCH_SIZE = 100;  // 微批次大小
    const auto TARGET_INTERVAL = milliseconds(10);  // 10ms一个控制周期
    
    auto start_time = steady_clock::now();
    auto next_batch_time = start_time;
    uint64_t seq = 1;
    
    // 计算每个周期的目标消息数
    uint32_t messages_per_interval = static_cast<uint32_t>(
        target_qps * TARGET_INTERVAL.count() / 1000.0);
    
    if (messages_per_interval == 0) messages_per_interval = 1;
    
    std::cout << "Target: " << target_qps << " QPS, " 
              << messages_per_interval << " messages per " 
              << TARGET_INTERVAL.count() << "ms" << std::endl;
    
    // 主循环
    while (g_running) {
        auto now = steady_clock::now();
        
        // 检查是否超时
        if (duration_cast<seconds>(now - start_time).count() >= duration_sec) {
            std::cout << "\nDuration reached, stopping..." << std::endl;
            g_running = false;
            break;
        }
        
        // 控制发送速率
        if (now >= next_batch_time) {
            // 生产一批消息
            uint32_t produced = 0;
            while (produced < messages_per_interval && g_running) {
                // 修复这里：确保类型一致
                uint32_t to_produce = std::min<uint32_t>(
                    MICRO_BATCH_SIZE, 
                    messages_per_interval - produced);
                
                if (producer.produce_batch(seq, to_produce)) {
                    g_total_sent += to_produce;
                    seq += to_produce;
                } else {
                    g_total_failed += to_produce;
                }
                
                produced += to_produce;
                
                // 短暂休息，避免CPU占用过高
                if (to_produce < MICRO_BATCH_SIZE) {
                    std::this_thread::sleep_for(microseconds(10));
                }
            }
            
            // 更新下一批次时间
            next_batch_time += TARGET_INTERVAL;
            
            // 如果落后了，跳过一些周期
            if (now > next_batch_time) {
                next_batch_time = now + TARGET_INTERVAL;
            }
            
            // 定期打印统计信息
            static auto last_stats = steady_clock::now();
            if (duration_cast<seconds>(now - last_stats).count() >= 5) {
                producer.print_stats();
                last_stats = now;
            }
        } else {
            // 等待下一批次时间
            auto wait_time = duration_cast<microseconds>(next_batch_time - now);
            if (wait_time.count() > 0) {
                std::this_thread::sleep_for(wait_time);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // 参数配置
    std::string brokers = "localhost:9092";
    std::string topic = "DITO_SIG";
    uint32_t target_qps = 2000;
    uint32_t duration_sec = 5 * 3600; // 5小时
    
    // 解析命令行参数
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--brokers" && i + 1 < argc) brokers = argv[++i];
        else if (arg == "--topic" && i + 1 < argc) topic = argv[++i];
        else if (arg == "--qps" && i + 1 < argc) target_qps = std::stoul(argv[++i]);
        else if (arg == "--duration" && i + 1 < argc) duration_sec = std::stoul(argv[++i]);
    }
    
    std::cout << "==========================================" << std::endl;
    std::cout << "       DITO SIG Producer (Optimized)" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Brokers: " << brokers << std::endl;
    std::cout << "Topic: " << topic << std::endl;
    std::cout << "Target QPS: " << target_qps << std::endl;
    std::cout << "Duration: " << duration_sec << " seconds (" 
              << duration_sec / 3600.0 << " hours)" << std::endl;
    std::cout << "Press Ctrl+C to stop..." << std::endl;
    std::cout << "==========================================" << std::endl;
    
    // 设置信号处理
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    
    // Kafka配置优化
    Configuration config = {
        { "bootstrap.servers", brokers },
        { "acks", "1" },
        { "linger.ms", "5" },  // 减少延迟
        { "batch.num.messages", "1000" },
        { "queue.buffering.max.messages", "1000000" },
        { "queue.buffering.max.kbytes", "262144" },  // 256MB
        { "compression.type", "lz4" },
        { "message.send.max.retries", "5" },
        { "retry.backoff.ms", "100" },
        { "socket.keepalive.enable", "true" },
        { "max.in.flight.requests.per.connection", "1000000" },
        { "socket.timeout.ms", "30000" }
    };
    
    try {
        // 创建生产者
        HighPerformanceProducer producer(config, topic);
        
        // 预热
        std::cout << "Warming up..." << std::endl;
        for (int i = 0; i < 100 && g_running; ++i) {
            producer.produce_single(i + 1);
        }
        producer.flush();
        std::cout << "Warm up completed." << std::endl;
        
        // 运行生产循环
        produce_with_rate_control(producer, target_qps, duration_sec);
        
        // 优雅关闭
        std::cout << "\nFlushing remaining messages..." << std::endl;
        producer.flush();
        
        // 最终统计
        auto end_time = steady_clock::now();
        auto total_elapsed = duration_cast<seconds>(end_time - steady_clock::now()).count();
        
        std::cout << "\n\n=== FINAL STATISTICS ===" << std::endl;
        std::cout << "Total messages sent: " << g_total_sent.load() << std::endl;
        std::cout << "Total failed: " << g_total_failed.load() << std::endl;
        std::cout << "Success rate: "
                  << (g_total_sent.load() + g_total_failed.load() > 0 ? 
                      (100.0 * g_total_sent.load() / (g_total_sent.load() + g_total_failed.load())) : 100.0)
                  << "%" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "\nFatal error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nProducer stopped gracefully." << std::endl;
    return 0;
}