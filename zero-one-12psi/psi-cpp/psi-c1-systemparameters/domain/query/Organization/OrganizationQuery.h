#ifndef ORGANIZATIONQUERY_H
#define ORGANIZATIONQUERY_H

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class OrganizationQuery : public oatpp::DTO
{
	DTO_INIT(OrganizationQuery, DTO);

	//组织ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("organization.field.id"));
	//组织名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("organization.field.name"));
	//所属ID(PID)
	API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("organization.field.pid"));
	//组织排序
	API_DTO_FIELD_DEFAULT(String, sort, ZH_WORDS_GETTER("organization.field.sort"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("organization.field.data"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !ORGANIZATIONQUERY_H
