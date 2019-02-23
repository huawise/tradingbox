#include "TradeGateway.h"

namespace QCTech {
TradeGateway::TradeGateway() {}
TradeGateway::TradeGateway(std::string name) : m_gatewayName(name) {}

TradeGateway::~TradeGateway() {}

void TradeGateway::OnLogin(StructAccountInfo& stAccInfo) {}

}  // namespace QCTech