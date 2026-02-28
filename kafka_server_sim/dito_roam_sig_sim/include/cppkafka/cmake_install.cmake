# Install script for directory: /home/ekko/third_party/cppkafka-0.4.1/include/cppkafka

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppkafka" TYPE FILE FILES
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/buffer.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/clonable_ptr.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/configuration.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/configuration_base.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/configuration_option.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/consumer.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/cppkafka.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/error.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/event.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/exceptions.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/group_information.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/header.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/header_list.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/header_list_iterator.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/kafka_handle_base.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/logging.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/macros.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/message.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/message_builder.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/message_internal.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/message_timestamp.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/metadata.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/producer.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/queue.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/topic.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/topic_configuration.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/topic_partition.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/topic_partition_list.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppkafka/utils" TYPE FILE FILES
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/utils/backoff_committer.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/utils/backoff_performer.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/utils/buffered_producer.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/utils/compacted_topic_processor.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/utils/consumer_dispatcher.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/utils/poll_interface.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/utils/poll_strategy_base.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/utils/roundrobin_poll_strategy.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppkafka/detail" TYPE FILE FILES
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/detail/callback_invoker.h"
    "/home/ekko/third_party/cppkafka-0.4.1/include/cppkafka/detail/endianness.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppkafka" TYPE FILE FILES "/home/ekko/third_party/cppkafka-0.4.1/build/include/cppkafka/cppkafka.h")
endif()

