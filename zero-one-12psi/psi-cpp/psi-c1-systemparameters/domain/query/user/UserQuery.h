#ifndef _USERQUERY_H_
#define _USERQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class UserQuery : public PageQuery
{
	DTO_INIT(UserQuery, PageQuery);
	//用户名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("user.field.name"));
	//用户账号
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("user.field.user"));
	//手机号码
	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("user.field.tel"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("user.field.data"));
};


//class UserQuery : public PageQuery
//{
//	DTO_INIT(UserQuery, PageQuery);
//	//用户名称
//	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("user.field.name"));
//	//用户账号
//	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("user.field.user"));
//	//手机号码
//	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("user.field.tel"));
//	//备注信息
//	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("user.field.data"));
//};



#include OATPP_CODEGEN_END(DTO)

#endif // !_USERQUERY_H