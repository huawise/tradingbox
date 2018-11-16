#include "TradeEngine.h"
#include "DataType.h"

namespace QCTech
{
	TradeEngine::TradeEngine()
	{

	}

	TradeEngine::~TradeEngine()
	{
	}

	void TradeEngine::AddGateway(TradeGateway& gateway)
	{
		m_mapTradeGateway.emplace(gateway.GetGatewayName(), gateway);
	}

	TradeGateway* TradeEngine::GetGateway(std::string gatewayName)
	{
		auto it = m_mapTradeGateway.find(gatewayName);
		if (it != m_mapTradeGateway.end())
		{
			return &it->second;
		}
		return nullptr;
	}

	void TradeEngine::Connect(std::string gatewayName)
	{
		auto gw = GetGateway(gatewayName);
		if (gw != nullptr)
		{
			gw->Connect();
		}
	}

	void TradeEngine::Disconnect()
	{
		for (auto& it : m_mapTradeGateway)
		{
			it.second.Disconnect();
		}
	}

	void TradeEngine::Disconnect(std::string gatewayName)
	{
		auto gw = GetGateway(gatewayName);
		if (gw != nullptr)
		{
			gw->Disconnect();
		}
	}

	void TradeEngine::QryAccount()
	{
		for (auto& it: m_mapTradeGateway)
		{
			it.second.QryAccount();
		}
	}

	void TradeEngine::InsertOrder(StructInsertOrderReq& stOrderReq, std::string gatewayName)
	{
		auto gw = GetGateway(gatewayName);
		if (gw != nullptr)
		{
			gw->InsertOrder(stOrderReq);
		}
	}

	void TradeEngine::Connect()
	{
		for (auto& it: m_mapTradeGateway)
		{
			it.second.Connect();
		}
	}
}