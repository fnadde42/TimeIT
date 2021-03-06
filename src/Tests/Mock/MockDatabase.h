#ifndef MOCKDATABASE_H_
#define MOCKDATABASE_H_

#include "IDatabase.h"

namespace Test
{
using namespace DB;

class MockDatabase: public IDatabase
{
public:
	MockDatabase();
	virtual ~MockDatabase();

	virtual std::shared_ptr<IAutotrackAccessor> getAutotrackAccessor();
	virtual std::shared_ptr<ITimeAccessor> getTimeAccessor();
	virtual std::shared_ptr<IExtendedTaskAccessor> getExtendedTaskAccessor();
	virtual std::shared_ptr<ITaskAccessor> getTaskAccessor();
	virtual std::shared_ptr<ISettingsAccessor> getSettingsAccessor();
	virtual bool isThreadSafe();
	virtual void beginTransaction();
	virtual void endTransaction();
};

} /* namespace Test */
#endif /* MOCKDATABASE_H_ */
