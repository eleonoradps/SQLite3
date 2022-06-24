#include "SQLib.h"
#include "SQLiteImpl.h"

namespace sql {

	std::shared_ptr<sql::SQLib> CreateSQLiteDB(const std::string& file)
	{
		return std::make_shared<SQLiteImpl>(file);
	}

} // End namespace sql.
