#include"http_server_ph.h"

namespace http_demo{
class MyRestfulServiceImpl : public MyRestfulService{
pubilc:
    MyRestfulServiceImpl(){};
    virtual ~MyRestfulServiceImpl(){};
    void getstats(google::protobuf::RpcController* cntl_base,
                      const LTCHttpRequest*, LTCHttpResponse*,
                      google::protobuf::Closure* done){

                        brpc::ClosureGuard done_guard(done);
                        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
                        cntl->response_attachment().append("hello world");
}

    void getcpuuseage(google::protobuf::RpcController* cntl_base,
                      const LTCHttpRequest*, LTCHttpResponse*,
                      google::protobuf::Closure* done){

                        brpc::ClosureGuard done_guard(done);
                        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
                        cntl->response_attachment().append("hello world");

}


};

class MyDefaultImpl : public MyDefaultImpl{
    MyDefaultImpl(){};
    virtual ~MyDefaultImpl(){};
    void default_method(google::protobuf::RpcController* cntl_base,
                      const LTCHttpRequest*, LTCHttpResponse*,
                      google::protobuf::Closure* done){

                        brpc::ClosureGuard done_guard(done);
                        brpc::Controller* cntl = 
                            static_cast<brpc::Controller*>(cntl_base);
                        const std::string& method =  cntl->http_request().unresolved_path();
                        cntl->response_attachment().append("Get method: ");
                        cntl->response_attachment().append(method);

}
};
}//namespace

int main()
{
    brpc::Server server;
    
}