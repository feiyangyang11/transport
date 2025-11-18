#ifndef _LOGOPERATION_QUERY
#define _LOGOPERATION_QUERY

#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class LogOperationQuery :public PageQuery
{
	DTO_INIT(LogOperationQuery, PageQuery);
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("log.field.id"));
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("log.field.user"));
	API_DTO_FIELD_DEFAULT(String, begintime, ZH_WORDS_GETTER("log.field.begintime"));
	API_DTO_FIELD_DEFAULT(String, endtime, ZH_WORDS_GETTER("log.field.endtime"));
	API_DTO_FIELD_DEFAULT(String, info, ZH_WORDS_GETTER("log.field.info"));
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_LOGOPERATION_QUERY

