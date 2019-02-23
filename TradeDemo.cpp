#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "CtpTradeGateway.h"
#include "EsunnyTradeGateway.h"
#include "TradeEngine.h"

using namespace QCTech;

class TradingTest {
 public:
  TradingTest() {}

  void TestCaseRegister(const std::string& title,
                        std::function<void(TradingTest&)> func) {
    stMenuItem st;
    st.title = " " + std::to_string(m_vctMenuItemFunc.size()) + "." + title;
    st.func = func;
    m_vctMenuItemFunc.emplace_back(st);
  }

  void TestInit() {
    TestCaseRegister("[SUBTEST]易胜交易接口测试",
                     std::bind(&TradingTest::SubTestEsunnyTradeGateway, this));
    TestCaseRegister("连接接口", std::bind(&TradingTest::TestDisconnect, this));
    TestCaseRegister("断开连接", std::bind(&TradingTest::TestDisconnect, this));
    TestCaseRegister("查询账号", std::bind(&TradingTest::QryAccount, this));
    TestCaseRegister("委托下单",
                     std::bind(&TradingTest::TestInsertOrder, this));
    // 挂载交易网关
    // TNgine.AddGateway(ctpTradeGateway);
    TNgine.AddGateway(esunnyTradeGateway);
  }

  void TestCaseDisplay() {
    std::cout << std::flush << "-------------[ 交易网关测试 ]-------------"
              << std::endl;
    for (auto it = m_vctMenuItemFunc.begin(); it != m_vctMenuItemFunc.end();
         ++it) {
      std::cout << it->title.c_str() << std::endl;
    }
    std::cout << std::flush << "-----------------------------------------"
              << std::endl;
  }

  void RunTestCase(int index) {
    try {
      auto it = m_vctMenuItemFunc.at(index);
      it.func(*this);
    } catch (std::exception& e) {
      std::cout << "没有这个选项!" << std::endl;
    }
  }
  void SubTestEsunnyTradeGateway();
  void QryAccount();
  void TestDisconnect();
  void TestInsertOrder();

 private:
  // 实例化交易引擎
  TradeEngine TNgine;

  // 实例化CTP交易网关
  // CtpTradeGateway ctpTradeGateway;
  // 实例化易盛交易网关
  EsunnyTradeGateway esunnyTradeGateway;

  struct stMenuItem {
    std::string title;
    std::function<void(TradingTest&)> func;
  };

  std::vector<stMenuItem> m_vctMenuItemFunc;
};

void TradingTest::TestDisconnect() { TNgine.Disconnect(); }

void TradingTest::QryAccount() { TNgine.QryAccount(); }

void TradingTest::TestInsertOrder() {
  StructInsertOrderReq stOrderReq;
  TNgine.InsertOrder(stOrderReq, esunnyTradeGateway.GetGatewayName());
}

void TradingTest::SubTestEsunnyTradeGateway() {
  EsunnyTradeGateway es;

  int nCmd = 0;
  do {
    std::cout << "------- [SubTestCase] -------\n"
              << "0.[Return to Main Menu]\n"
              << "1.Connect\n"
              << "2.Disconnect\n"
              << "3.QryAccount\n"
              << "4.QryFund\n"
              << "5.QryPosition\n"
              << "6.InsertOrder\n"
              << "7.CancelOrder\n"
              << "-----------------------------" << std::endl;
    std::cin >> nCmd;

    switch (nCmd) {
      case 0:
        std::cout << "Exit" << std::endl;
        break;
      case 1:
        es.Connect();
        break;
      case 2:
        es.Disconnect();
        break;
      case 3:
        es.QryAccount();
        break;
      case 4:
        es.QryFund();
        break;
      case 5:
        es.QryPosition();
        break;
      case 6: {
        StructInsertOrderReq req;
        std::cout << "InsertOrder: Direction[buy|sell] ExchangeID CommodityID "
                     "ContractID OrderPrice OrderQty"
                  << std::endl;
        std::string dir_;
        std::cin >> dir_;
        if (dir_ == "buy" || dir_ == "sell") {
          req.Direction =
              dir_ == "buy" ? DirectionType::BUY : DirectionType::SELL;
        } else {
          break;
        }
        std::cin >> req.ExchangeID >> req.CommodityID >> req.ContractID >>
            req.OrderPrice >> req.OrderQty;

        es.InsertOrder(req);
      } break;
      case 7: {
        StructCancelOrderReq req;
        std::cout << "Order Id: ";
        std::cin >> req.OrderId;
        if (req.OrderId.length() < 8) {
          es.CancelOrder(req);
        }
      } break;
      default:
        std::cout << "选项不存在" << std::endl;
        break;
    }

  } while (nCmd != 0);

  es.Disconnect();
}

int main(int argc, char* argv[]) {
  TradingTest test;
  test.TestInit();
  int nCmd = 0;
  while (true) {
    test.TestCaseDisplay();
    std::cin >> nCmd;
    test.RunTestCase(nCmd);
  }

  system("pause");

  return 0;
}
