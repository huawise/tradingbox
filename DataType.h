#pragma once

#include <iostream>

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


}