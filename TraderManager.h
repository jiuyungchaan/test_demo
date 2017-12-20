#ifndef _TRADER_MANAGER_H
#define _TRADER_MANAGER_H

#include "COXTrader.h"
#include <map>
#include <string>
#include <boost/thread.hpp>

class TraderManager {
public:
	static TraderManager *GetInstance();
	virtual ~TraderManager();

	COXTrader *GetTrader(const std::string &account_id);

private:
	TraderManager();

	/// multi-trader would not work
	std::map<std::string, COXTrader*> trader_map_;
	COXTrader *trader_;
	char trader_user_id_[32];
	boost::mutex mutex_;
};

#endif