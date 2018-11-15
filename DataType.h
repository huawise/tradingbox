#pragma once

#include <iostream>
#include <cstring>

namespace QCTech {

	struct StructInsertOrderReq
	{
		double price;
		int volume;

		StructInsertOrderReq()
		{
			memset(this, 0, sizeof(StructInsertOrderReq));
		}
	};

	struct StructAccountInfo
	{
		std::string AccountID;
		std::string UserName; 
		std::string TradingDay;
		
	};


}