#include <cstdlib>


#include <TradeEngine.h>
#include <EsunnyTradeGateway.h>
#include <CtpTradeGateway.h>

using namespace QCTech;

class TradingTest
{
public:
	TradingTest()
	{
		// 挂载交易网关
		TNgine.AddGateway(ctpTradeGateway);
		TNgine.AddGateway(esunnyTradeGateway);
		// 连接全部交易接口
		TNgine.Connect();
	}
	void TestInsertOrder();

private:
	// 实例化交易引擎
	TradeEngine TNgine;

	// 实例化CTP交易网关
	CtpTradeGateway ctpTradeGateway;
	// 实例化易盛交易网关
	EsunnyTradeGateway esunnyTradeGateway;

};

void TradingTest::TestInsertOrder()
{
	StructInsertOrderReq stOrderReq;
	TNgine.InsertOrder(stOrderReq, esunnyTradeGateway.GetGatewayName());
}

int main(int argc, char* argv[])
{
	TradingTest t;

	int nCmd = 0;
	while (true)
	{
		std::cout << std::flush
			<< "-------------------------------------\n"
			<< " 1.委托下单\n"
			<< " 2.委托撤单\n"
			<< " 3.获取资金信息\n"
			<< " 4.获取持仓信息\n"
			<< " 5.获取商品信息\n"
			<< "-------------------------------------\n"
			<< std::endl;
		std::cin >> nCmd;
		switch (nCmd)
		{
		case 1:
			t.TestInsertOrder();
			break;
		default:
			break;
		}
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