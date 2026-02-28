g++ -std=c++11 -O3 -pthread -DNDEBUG -march=native sim1.cpp  -I../include  -L../lib -lcppkafka -lrdkafka++ -lrdkafka -o dito_producer
