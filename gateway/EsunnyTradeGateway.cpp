#include "TradeGateway.h"
#include "EsunnyTradeGateway.h"
#include <iTapTradeAPI.h>
#include <iTapAPIError.h>


namespace QCTech
{
	EsunnyTradeGateway::EsunnyTradeGateway(std::string gatewayName)
	{
		m_gatewayName = gatewayName;
	}
	EsunnyTradeGateway::~EsunnyTradeGateway()
	{
	
	}

	
	void EsunnyTradeGateway::LoadConfigure()
	{
		// TODO::从持久化配置接口中读取配置信息，持久化配置接口可以是数据库或者是配置文件
		m_host = "61.163.243.173";
		m_port = 8383;

		strncpy_s(m_stAppInfo.AuthCode
			, "67EA896065459BECDFDB924B29CB7DF1946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC5211AF9FEE541DDE41BCBAB68D525B0D111A0884D847D57163FF7F329FA574E7946CED32E26C1EAC946CED32E26C1EAC733827B0CE853869ABD9B8F170E14F8847D3EA0BF4E191F5D97B3DFE4CCB1F01842DD2B3EA2F4B20CAD19B8347719B7E20EA1FA7A3D1BFEFF22290F4B5C43E6C520ED5A40EC1D50ACDF342F46A92CCF87AEE6D73542C42EC17818349C7DEDAB0E4DB16977714F873D505029E27B3D57EB92D5BEDA0A710197EB67F94BB1892B30F58A3F211D9C3B3839BE2D73FD08DD776B9188654853DDA57675EBB7D6FBBFC"
			, sizeof(m_stAppInfo.AuthCode));
		strncpy_s(m_stAppInfo.KeyOperationLogPath, "\\log", sizeof(m_stAppInfo.KeyOperationLogPath));
		
		strncpy_s(m_stLoginAuth.UserNo, "Q517608434", sizeof(m_stLoginAuth.UserNo));
		strncpy_s(m_stLoginAuth.Password, "302469", sizeof(m_stLoginAuth.Password));
		m_stLoginAuth.ISModifyPassword = APIYNFLAG_NO;
	}

	void EsunnyTradeGateway::Connect()
	{
		TAPIINT32 rtn = TAPIERROR_SUCCEED;
		LoadConfigure();

		std::cout << "易盛交易接口9.0（" << GetITapTradeAPIVersion() << "）" << std::endl;

		// 实例化TradeAPI交易接口实例
		m_pTradeApi = CreateITapTradeAPI(&m_stAppInfo, rtn);
		if (m_pTradeApi == nullptr)
		{
			std::cout << "创建TradeAPI实例失败。错误码：" << rtn << std::endl;
			return;
		}

		// 设置API的回调接口对象
		rtn = m_pTradeApi->SetAPINotify(this);
		if (rtn != TAPIERROR_SUCCEED)
		{
			std::cout << "设置API的回调接口对象。错误码：" << rtn << std::endl;
			return;
		}

		//设定服务器IP、端口
		rtn = m_pTradeApi->SetHostAddress(m_host.c_str(), m_port);
		if (rtn != TAPIERROR_SUCCEED)
		{
			std::cout << "连接交易服务器失败。错误码：" << rtn << std::endl;
			return;
		}

		//登录服务器
		rtn = m_pTradeApi->Login(&m_stLoginAuth);
		if (rtn != TAPIERROR_SUCCEED) {
			std::cout << "登录失败。错误码:" << rtn << std::endl;
			return;
		}
		return;
	}

	void EsunnyTradeGateway::InsertOrder(StructInsertOrderReq & stOrderReq)
	{
		std::cout << __FUNCTION__ << std::endl;
		//m_pTradeApi->InsertOrder();
	}



#pragma region Spi interfaces in ITapTradeAPINotify
	/**
	* @brief 连接成功回调通知
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnConnect()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	系统登录过程回调。
	* @details	此函数为Login()登录函数的回调，调用Login()成功后建立了链路连接，然后API将向服务器发送登录认证信息，
	*			登录期间的数据发送情况和登录的回馈信息传递到此回调函数中。
	* @param[in] errorCode 返回错误码,0表示成功。
	* @param[in] loginRspInfo 登陆应答信息，如果errorCode!=0，则loginRspInfo=NULL。
	* @attention	该回调返回成功，说明用户登录成功。但是不代表API准备完毕。
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	二次认证联系方式通知。
	* @details	登录完成后，如果需要二次认证（9.2.7后台），会收到联系方式的通知，可以选择通知消息的一个联系方式（邮箱或者电话）
	*			请求发送二次认证授权码（RequestVertificateCode）。
	* @param[in] errorCode 返回错误码,0表示成功。如果账户没有绑定二次认证联系方式，则返回10016错误。
	* @param[in] isLast,标识是否是最后一条联系信息。
	* @param[in]  认证方式信息，如果errorCode!=0，则ContactInfo为空。
	* @attention	该回调返回成功，说明需要二次认证，并且需要选择一个联系方式然后调用RequestVertificateCode。
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief	请求发送二次认证码应答。
	* @details	请求获取二次认证授权码，后台发送邮件或者短信，并给出应答，包含发送序号以及认证码有效期。
	*
	* @param[in] sessionID 请求二次认证码会话ID。
	* @param[in]  errorCode 如果没有绑定联系，返回10016错误.
	* @param[in]  rsp二次认证码有效期，以秒返回，在二次认证有效期内，可以重复设置二次认证码，但是不能再重新申请二次认证码。
	* @attention	该回调返回成功，说明需要二次认证，并且需要选择一个联系方式然后调用RequestVertificateCode。
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const TapAPIRequestVertificateCodeRsp *rsp)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief	API到期提醒回调
	* @details	此函数为Login()登录成功后，如果到期日与当前日期小于30天，则进行回调提醒。
	* @param[in] date 返回API授权到期日。
	* @param[in] days 返回还有几天授权到期。
	* @attention	该函数回调，则说明授权在一个月之内到期。否则不产生该回调。
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnExpriationDate(ITapTrade::TAPIDATE date, int days)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief	通知用户API准备就绪。
	* @details	只有用户回调收到此就绪通知时才能进行后续的各种行情数据查询操作。\n
	*			此回调函数是API能否正常工作的标志。
	* @attention 就绪后才可以进行后续正常操作
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnAPIReady()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	API和服务失去连接的回调
	* @details	在API使用过程中主动或者被动与服务器服务失去连接后都会触发此回调通知用户与服务器的连接已经断开。
	* @param[in] reasonCode 断开原因代码。
	* @ingroup G_T_Disconnect
	*/
	void TAP_CDECL EsunnyTradeGateway::OnDisconnect(ITapTrade::TAPIINT32 reasonCode)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 通知用户密码修改结果
	* @param[in] sessionID 修改密码的会话ID,和ChangePassword返回的会话ID对应。
	* @param[in] errorCode 返回错误码，0表示成功。
	* @ingroup G_T_UserInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 认证账户密码反馈
	* @param[in] sessionID 修改密码的会话ID,和AuthPassword返回的会话ID对应。
	* @param[in] errorCode 返回错误码，0表示成功。
	* @ingroup G_T_UserInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 设置用户预留信息反馈
	* @param[in] sessionID 设置用户预留信息的会话ID
	* @param[in] errorCode 返回错误码，0表示成功。
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @note 该接口暂未实现
	* @ingroup G_T_UserInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	返回用户信息
	* @details	此回调接口向用户返回查询的资金账号的详细信息。用户有必要将得到的账号编号保存起来，然后在后续的函数调用中使用。
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 返回资金账户的资金信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	用户资金变化通知
	* @details	用户的委托成交后会引起资金数据的变化，因此需要向用户实时反馈。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnFund(const ITapTrade::TapAPIFundData *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 返回系统中的交易所信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeSystem
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	返回系统中品种信息
	* @details	此回调接口用于向用户返回得到的所有品种信息。
	* @param[in] sessionID 请求的会话ID，和GetAllCommodities()函数返回对应；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Commodity
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 返回系统中合约信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Contract
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	返回新增合约信息
	* @details	向用户推送新的合约。主要用来处理在交易时间段中服务器添加了新合约时，向用户发送这个合约的信息。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Contract
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	订单操作应答
	* @details	下单、撤单、改单应答。下单都会有次应答回调，如果下单请求结构中没有填写合约或者资金账号，则仅返回错误号。
	* 撤单、改单错误由应答和OnRtnOrder，成功仅返回OnRtnOrder回调。
	* sessionID标识请求对应的sessionID，以便确定该笔应答对应的请求。
	*
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info 订单应答具体类型，包含订单操作类型和订单信息指针。
	* 订单信息指针部分情况下可能为空，如果为空，可以通过SessiuonID找到对应请求获取请求类型。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 返回新委托。新下的或者其他地方下的推送过来的。
	* @details	服务器接收到客户下的委托内容后就会保存起来等待触发，同时向用户回馈一个
	*			新委托信息说明服务器正确处理了用户的请求，返回的信息中包含了全部的委托信息，
	*			同时有一个用来标示此委托的委托号。
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	返回查询的委托信息
	* @details	返回用户查询的委托的具体信息。
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 返回查询的委托变化流程信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码，当errorCode==0时，info指向返回的委托变化流程结构体，不然为NULL；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info 返回的委托变化流程指针。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 返回查询的成交信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	推送来的成交信息
	* @details	用户的委托成交后将向用户推送成交信息。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnFill(const ITapTrade::TapAPIFillInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 返回查询的持仓
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 持仓变化推送通知
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 返回查询的持仓汇总
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryPositionSummary(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionSummary *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 持仓汇总变化推送通知
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnPositionSummary(const TapAPIPositionSummary *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 持仓盈亏通知
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}



	/**
	* @brief 返回系统中的币种信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeSystem
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief	交易消息通知
	* @details	返回查询的用户资金状态信息。信息说明了用户的资金状态，用户需要仔细查看这些信息。
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	交易消息通知
	* @details	用户在交易过程中可能因为资金、持仓、平仓的状态变动使账户处于某些危险状态，或者某些重要的信息需要向用户通知。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 历史委托查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 历史委托流程查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 历史成交查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 历史持仓查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 历史交割查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 资金调整查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 查询用户账单应答 Add:2013.12.11
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Bill
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 查询账户手续费计算参数 Add:2017.01.14
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Rent
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief 查询账户保证金计算参数 Add:2017.01.14
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Rent
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 港交所做市商双边报价应答 Add:2017.08.29
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HKMarket
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketInsertRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 港交所做市商双边撤单应答 Add:2017.08.29
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HKMarket
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 港交所询价通知 Add:2017.08.29
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HKMarket
	*/
	void TAP_CDECL EsunnyTradeGateway::OnHKMarketQuoteNotice(const ITapTrade::TapAPIOrderQuoteMarketNotice *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}



	/**
	* @brief 订单删除应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 订单录入应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 订单修改应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 订单转移应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 成交录入应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief 订单删除应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}



#pragma endregion

}