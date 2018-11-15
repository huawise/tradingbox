#pragma once
#include <iostream>
#include "DataType.h"

namespace QCTech {

	class TradeGateway
	{
	public:
		TradeGateway();
		TradeGateway(std::string name);
		virtual ~TradeGateway();
		const std::string GetGatewayName() const
		{
			return m_gatewayName;
		}
	public:
		virtual void Connect() = 0;
		virtual void InsertOrder(StructInsertOrderReq& stOrderReq) = 0;
		

	public:

	protected:
		std::string m_gatewayName;
	};

}