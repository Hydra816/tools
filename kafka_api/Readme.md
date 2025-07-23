# 简介

<mark>基于cppkafka开发的一套易用kafka接口</mark>



# 使用场景

多主机需要互相同步数据的场景

- 每台主机即是producer 又是 consumer
- 每台主机拥有不同的key和group id,并且所有主机向同一个topic生产和消费
- 通过key值来区分是否需要过滤（<mark>要过滤自己生产的消息,自己生产的消息自己无需同步</mark>）



# 注意

- 当消息较少时可降低代码中消费者`poll_batch` 方法给的`max_batch_size`，以提高拉取速度，另外提供了打印poll_batch使用时间的代码，需要时可使用
