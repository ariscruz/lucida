#include <gflags/gflags.h>
#include <glog/logging.h>

#include <thrift/lib/cpp2/server/ThriftServer.h>

#include "IMCHandler.h"
#include <folly/init/Init.h>

DEFINE_int32(port,
             8085,
             "Port for IMC service (default: 8085)");

DEFINE_int32(num_of_threads,
             4,
             "Number of threads (default: 4)");

using namespace apache::thrift;
using namespace apache::thrift::async;

using namespace cpp2;
//using namespace facebook::windtunnel::treadmill::services::imc;

int main(int argc, char* argv[]) {
  folly::init(&argc, &argv);

  auto handler = std::make_shared<IMCHandler>();
  auto server = folly::make_unique<ThriftServer>();

  server->setPort(FLAGS_port);
  server->setNWorkerThreads(FLAGS_num_of_threads);
  server->setInterface(std::move(handler));
  server->setIdleTimeout(std::chrono::milliseconds(0));
  server->setTaskExpireTime(std::chrono::milliseconds(0));

  server->serve();

  return 0;
}
