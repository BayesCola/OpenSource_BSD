#pragma once

#include "SolveReDefinition.h"
// Has To Be Behind 'SolveReDefinition.h'
#include <list>
#include <memory>

#include "ThostFtdcMdApi.h"
#include "Strategy.h"

using strategy_list = std::list<std::shared_ptr<CStrategy>>;

class CMdBroadCast : private CThostFtdcMdSpi
{
// Observer Pattern Demand
public:
	void	notify_mtk_data(mtk_data* data);
	void	attach_observer(CStrategy* stg);
	void	dettach_observer(CStrategy* stg);

	const strategy_list& get_strategy_list() const;
private:
	strategy_list	list_;

// MD Interface Business
public:
	bool initial_md_broadcast();
	void release_md_broadcast();

	bool get_ready_subscribe();
	bool subscribe_instruments(char* *needed_ins, int ins_count);

private:
	//���ͻ����뽻�׺�̨������ͨ������ʱ������δ��¼ǰ���÷���������
	void OnFrontConnected() override;
	//��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	//����ر���Ӧ
	void OnRtnDepthMarketData(mtk_data *pDepthMarketData) override;

private:
	CThostFtdcMdApi* md_api_;
	bool is_ready_subscribe_{ false };
};