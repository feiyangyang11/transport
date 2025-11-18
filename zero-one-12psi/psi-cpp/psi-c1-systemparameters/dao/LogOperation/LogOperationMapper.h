#ifndef _LOGOPERATION_MAPPER_
#define _LOGOPERATION_MAPPER_

#include "Mapper.h"
#include "../../domain/do/LogOperation/LogOperationDO.h"

class LogOperationMapper : public Mapper<LogOperationDO>
{
public:
	LogOperationDO mapper(ResultSet* resultSet) const override
	{
		LogOperationDO data;
		data.setId(resultSet->getString(1));
		data.setTime(resultSet->getString(2));
		data.setUser(resultSet->getString(3));
		data.setInfo(resultSet->getString(4));
		return data;
	}
};

class PtrLogOperationMapper : public Mapper<PtrLogOperationDO>
{
public:
	PtrLogOperationDO mapper(ResultSet* resultSet) const override
	{
		PtrLogOperationDO data;
		data->setId(resultSet->getString(1));
		data->setTime(resultSet->getString(2));
		data->setUser(resultSet->getString(3));
		data->setInfo(resultSet->getString(4));
		return data;
	}
};


#endif // !_LOGOPERATION_MAPPER_
