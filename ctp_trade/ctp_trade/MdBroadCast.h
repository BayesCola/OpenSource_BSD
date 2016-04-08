#pragma once

#include "SolveReDefinition.h"
// Has To Be Behind 'SolveReDefinition.h'
#include <deque>

#include "ThostFtdcMdApi.h"
#include "CppReadWriteLock.hpp"

using mtk_type = CThostFtdcDepthMarketDataField;

class CMdBroadCast : private CThostFtdcMdSpi
{
public:
	bool initial_md_broadcast();
	void release_md_broadcast();

	bool get_ready_subscribe();
	bool subscribe_instruments(char* *needed_ins, int ins_count);

	size_t get_mtk_size();
	const mtk_type get_mtk_head();
	void  pop_mtk_head();
	std::deque<mtk_type>  get_mtk_queue();

private:
	//���ͻ����뽻�׺�̨������ͨ������ʱ������δ��¼ǰ���÷���������
	void OnFrontConnected() override;
	//��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	//����ر���Ӧ
	void OnRtnDepthMarketData(mtk_type *pDepthMarketData) override;

private:
	CThostFtdcMdApi* md_api_;

	bool is_ready_subscribe_{ false };

	//CRWLock	queue_lock_;	// (Donnot Need It When One Producer And One Consumer Temporarily)
	std::mutex mtx_;
	std::deque<mtk_type> mtk_queue_;
};