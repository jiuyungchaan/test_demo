#include "TraderManager.h"

using namespace std;

TraderManager *p_instance_ = NULL;

TraderManager::TraderManager() : trader_(NULL), trader_user_id_{0} {}

TraderManager::~TraderManager() {}

TraderManager *TraderManager::GetInstance() {
	if (p_instance_ == NULL) {
		p_instance_ = new TraderManager();
	}
	return p_instance_;
}

COXTrader *TraderManager::GetTrader(const string &account_id) {
	boost::unique_lock<boost::mutex> trader_lock(mutex_);
	if (trader_ != NULL) {
		if (strcmp(trader_user_id_, account_id.c_str()) == 0) {
			return trader_;
		}
		else {
			/// if UserID not match, initialize a dummy trader which does not login
			COXTrader *dummy_trader = new COXTrader(account_id.c_str());
			return dummy_trader;
		}
	}
	else {
		snprintf(trader_user_id_, sizeof(trader_user_id_), "%s", account_id.c_str());
		trader_ = new COXTrader(account_id.c_str());
		trader_->Init();
		return trader_;
	}
	/*
	map<string, COXTrader*>::iterator it = trader_map_.find(account_id);
	if (it != trader_map_.end()) {
		return it->second;
	}
	else {
		COXTrader *trader = new COXTrader(account_id.c_str());
		trader->Init();
		trader_map_.insert(pair<string, COXTrader*>(account_id, trader));
		return trader;
	}
	*/
}
