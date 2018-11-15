#include <cstdlib>
#include <map>
#include <functional>
#include <iostream>
#include <string>

#include "TradeEngine.h"
#include "EsunnyTradeGateway.h"
#include "CtpTradeGateway.h"

using namespace QCTech;

class TradingTest
{
public:
	TradingTest()
	{
		menuAppend("断开连接", std::bind(&TradingTest::TestDisconnect, this));
		menuAppend("委托下单", std::bind(&TradingTest::TestInsertOrder, this));
	}
	void TestInit()
	{
		// 挂载交易网关
		//TNgine.AddGateway(ctpTradeGateway);
		TNgine.AddGateway(esunnyTradeGateway);
		// 连接全部交易接口
		TNgine.Connect();
	}

	void MenuDisplay()
	{
		std::cout << std::flush << "-------------------------------------" << std::endl;
		for (auto it= m_vctMenuItemFunc.begin(); it!= m_vctMenuItemFunc.end(); ++it)
		{
			std::cout << it->title.c_str() << std::endl;
		}
		std::cout << std::flush << "-------------------------------------" << std::endl;
	}

	void RunTest(int index)
	{
		try
		{
			auto it = m_vctMenuItemFunc.at(index);
			it.func(*this);
		}
		catch (std::exception& e)
		{
			std::cout << "没有这个选项!" << std::endl;
		}
	}

	void TestDisconnect();
	void TestInsertOrder();
	

private:
	// 实例化交易引擎
	TradeEngine TNgine;

	// 实例化CTP交易网关
	//CtpTradeGateway ctpTradeGateway;
	// 实例化易盛交易网关
	EsunnyTradeGateway esunnyTradeGateway;

	struct stMenuItem
	{
		std::string title;
		std::function<void(TradingTest&)> func;
	};

	std::vector<stMenuItem> m_vctMenuItemFunc;

	inline void menuAppend(const std::string& title, std::function<void(TradingTest&)> func)
	{
		stMenuItem st;
		st.title = " " + std::to_string(m_vctMenuItemFunc.size()) + "." + title;
		st.func = func;

		m_vctMenuItemFunc.emplace_back(st);
	}

};

void TradingTest::TestDisconnect()
{
	TNgine.Disconnect();
}

void TradingTest::TestInsertOrder()
{
	StructInsertOrderReq stOrderReq;
	TNgine.InsertOrder(stOrderReq, esunnyTradeGateway.GetGatewayName());
}

int main(int argc, char* argv[])
{
	TradingTest t;
	t.MenuDisplay();
	t.TestInit();
	int nCmd = 0;
	while (true)
	{
		std::cin >> nCmd;
		t.RunTest(nCmd);
		t.MenuDisplay();
	}

	system("pause");

	return 0;
}



/*
<Step 1> 准备阶段
1.设置连接配置信息
1.1.程序里面默认配置信息
1.2.主窗口输入配置。配置项：账号，密码
2.初始化API相关参数
3.连接服务器
3.1.连接失败处理
4.登录服务器
4.1.登录失败处理
5.拉取合约信息

<Step 2> 交互阶段
1.委托下单
2.委托撤单
3.获取资金信息
4.获取持仓信息
5.获取商品信息
*/