#ifndef _LOGOPERATION_VO
#define _LOGOPERATION_VO

#include"../../GlobalInclude.h"
#include"../../dto/LogOperation/LogOperationDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class LogOperationPageJsonVO : public JsonVO<LogOperationPageDTO::Wrapper>
{
	DTO_INIT(LogOperationPageJsonVO, JsonVO<LogOperationPageDTO::Wrapper>);
};

class LogOperationResponseJsonVO : public JsonVO<LogOperationResponseDTO::Wrapper>
{
	DTO_INIT(LogOperationResponseJsonVO, JsonVO<LogOperationResponseDTO::Wrapper>);
};

class LogOperationResultJsonVO : public JsonVO<LogOperationResultDTO::Wrapper>
{
	DTO_INIT(LogOperationResultJsonVO, JsonVO<LogOperationResultDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)


#endif // !_LOGOPERATION_VO