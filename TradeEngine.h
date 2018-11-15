#pragma once

#include <unordered_map>
#include "TradeGateway.h"
#include "DataType.h"

namespace QCTech
{
	class TradeEngine
	{
	public:
		TradeEngine();
		virtual ~TradeEngine();
		
		// 添加交易网关
		void AddGateway(TradeGateway& gw);
		
		// 获取交易网关
		TradeGateway* GetGateway(std::string gatewayName);

	public:
		// 连接全部交易网关
		void Connect();
		// 按名称连接交易网关
		void Connect(std::string gatewayName);
		
		// 断开连接
		void Disconnect();
		void Disconnect(std::string gatewayName);

		void InsertOrder(StructInsertOrderReq& stOrder, std::string gatewayName);
	private:
		std::unordered_map<std::string, TradeGateway&> m_mapTradeGateway;
	};
}