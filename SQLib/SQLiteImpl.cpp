#include "SQLiteImpl.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>

namespace sql {

	static int Callback(void* ptr, int ac, char** av, char** column_name) 
	{
		auto* sqlite_impl = static_cast<SQLiteImpl*>(ptr);
		column_t column;
		for (int i = 0; i < ac; i++)
		{
			name_value_t tmp = { column_name[i], sqlite_impl->GetValue(av[i]) };
			column.push_back(tmp);
		}
		sqlite_impl->table_.push_back(column);
		return 0;
	}

	SQLiteImpl::SQLiteImpl(const std::string& file)
	{
		if (sqlite3_open(file.c_str(), &db_) != SQLITE_OK)
		{
			throw std::runtime_error("error");
		}
	}

	SQLiteImpl::~SQLiteImpl()
	{
		sqlite3_close(db_);
	}

	bool SQLiteImpl::ExecuteString(const std::string& cmd)
	{
		table_.clear();
		error_.clear();
		char* error_adress;
		auto result = sqlite3_exec(db_, cmd.c_str(), Callback, this, &error_adress);
		if (result != SQLITE_OK)
		{
			error_ = error_adress;
			sqlite3_free(error_adress);
			return false;
		}
		return true;
	}

	sql::value_t SQLiteImpl::GetValue(const std::string& str) const
	{
		if (str.empty())
		{
			return nullptr;
		}
		std::istringstream iss { str };
		std::int64_t i;
		iss >> i;
		if (iss.eof())
		{
			return i;
		}
		std::istringstream iss2 { str };
		double d;
		iss2 >> d;
		if (iss2.eof())
		{
			return d;
		}
		return str;
	}

} // End namespace sql.
