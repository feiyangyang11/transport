#ifndef _LOGOPERATION_SERVICE_
#define _LOGOPERATION_SERVICE_

#include "../../domain/dto/LogOperation/LogOperationDTO.h"
#include "../../domain/query/LogOperation/LogOperationQuery.h"
#include "../../domain/vo/LogOperation/LogOperationVO.h"

class LogOperationService
{
public:
	//分页查询数据
	LogOperationPageDTO::Wrapper listAll(const LogOperationQuery::Wrapper& query);
	//保存新增数据
	LogOperationResponseDTO::Wrapper saveData(const LogOperationAddDTO::Wrapper& dto);
	//清空数据
	LogOperationResultDTO::Wrapper deleteAll();
};



#endif // !_LOGOPERATION_SERVICE_
