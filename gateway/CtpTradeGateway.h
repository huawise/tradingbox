
#pragma once
#include <iostream>
#include "TradeGateway.h"
#include "esunny/iTapTradeApi/include/iTapTradeAPI.h"

namespace QCTech {
using namespace ITapTrade;

class CtpTradeGateway : public TradeGateway {
 public:
  CtpTradeGateway(std::string gatewayName = "CTP");
  virtual ~CtpTradeGateway();

 public:
  virtual void LoadConfigure();
  virtual void Connect();
  virtual void InsertOrder(StructInsertOrderReq& stOrderReq);

 public:
};
}  // namespace QCTech