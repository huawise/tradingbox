#include "gateway/CtpTradeGateway.h"
#include "TradeGateway.h"

namespace QCTech {
CtpTradeGateway::CtpTradeGateway(std::string gatewayName) {
  m_gatewayName = gatewayName;
}

CtpTradeGateway::~CtpTradeGateway() {}

void CtpTradeGateway::LoadConfigure() {}

void CtpTradeGateway::Connect() {
  std::cout << __FUNCTION__ << std::endl;
  LoadConfigure();
}

void CtpTradeGateway::InsertOrder(StructInsertOrderReq& stOrderReq) {
  std::cout << __FUNCTION__ << std::endl;
}
}  // namespace QCTech
