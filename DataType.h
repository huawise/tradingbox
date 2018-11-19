#pragma once

#include <iostream>
#include <string>
#include <cstring>

namespace QCTech {

	enum class DirectionType
	{
		NONE	= 0,
		BUY		= 1,
		SELL	= 2,
	};

	struct StructInsertOrderReq
	{
		std::string 	ExchangeID;
		std::string 	CommodityID ;
		std::string 	ContractID;
		DirectionType 	Direction;
		double 			OrderPrice;
		int 			OrderQty;
	};

	struct StructCancelOrderReq
	{
		std::string 	OrderId;
	};

	struct StructAccountInfo
	{
		std::string AccountID;
		std::string UserName; 
		std::string TradingDay;
		
	};


}