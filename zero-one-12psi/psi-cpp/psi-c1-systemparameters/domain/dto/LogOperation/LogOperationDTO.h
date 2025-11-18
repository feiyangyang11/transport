
#ifndef _LOGOPERATION_DTO_
#define _LOGOPERATION_DTO_

#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class LogOperationAddDTO :public oatpp::DTO
{
	DTO_INIT(LogOperationAddDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("log.field.user"),true);
	API_DTO_FIELD_REQUIRE(String, info, ZH_WORDS_GETTER("log.field.info"),true);
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class LogOperationDTO :public LogOperationAddDTO
{
	DTO_INIT(LogOperationDTO, LogOperationAddDTO);
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("log.field.id"));
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("log.field.time"));
};

class LogOperationPageDTO :public PageDTO<LogOperationDTO::Wrapper>
{
	DTO_INIT(LogOperationPageDTO, PageDTO<LogOperationDTO::Wrapper>);
};

class LogOperationResponseDTO :public oatpp::DTO
{
	DTO_INIT(LogOperationResponseDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, operationTime, ZH_WORDS_GETTER("log.field.time"),true);
};

class LogOperationResultDTO :public oatpp::DTO
{
	DTO_INIT(LogOperationResultDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, operationTime, ZH_WORDS_GETTER("log.field.time"), true);
	API_DTO_FIELD_REQUIRE(String, clearedCount, ZH_WORDS_GETTER("log.delete.clearedcount"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_LOGOPERATION_DTO_


