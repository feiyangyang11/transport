#pragma once

#ifndef _USERVO_H_
#define _USERVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/user/UserDTO.h"
using namespace oatpp;
#include OATPP_CODEGEN_BEGIN(DTO)

class UserJsonVO : public JsonVO<UserDTO::Wrapper>
{
	DTO_INIT(UserJsonVO, JsonVO<UserDTO::Wrapper>);
	//状态码、响应信息、返回数据
	API_DTO_FIELD_DEFAULT(Int32, code, "code");
	API_DTO_FIELD_DEFAULT(String, message, "message");
	API_DTO_FIELD_DEFAULT(String, data, "data");

};

class UserDetailJsonVO : public JsonVO<UserDetailDTO::Wrapper>
{
	DTO_INIT(UserDetailJsonVO, JsonVO<UserDetailDTO::Wrapper>);
};

class UserPageJsonVO : public JsonVO<UserPageDTO::Wrapper>
{
	DTO_INIT(UserPageJsonVO, JsonVO<UserPageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif // !_USERVO_H	