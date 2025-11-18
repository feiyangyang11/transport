

#pragma once
#ifndef _ROLEQUERY_H_
#define _ROLEQUERY_H_

#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)



// 角色分页查询参数
class RoleQuery : public PageQuery{
	DTO_INIT(RoleQuery, PageQuery);
	RoleQuery() {
		pageSize = 30;
	}
	// 角色名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("role.field.name"));
	// 角色备注
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("role.field.data"));
  
};

/*
// 角色分页查询参数
class RoleQuery : public PageQuery{
	DTO_INIT(RoleQuery, PageQuery)
	// 角色名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("role.field.name"));
	// 角色备注
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("role.field.data"));
  
};

*/

/**10/25 伞 一定要保留这个
 * 获取角色列表需要的参数
 */
class RoleListQuery : public oatpp::DTO {
	DTO_INIT(RoleListQuery, DTO);
	API_DTO_FIELD_REQUIRE(String, keyword, ZH_WORDS_GETTER("role.field.keyword"), false);
};
#include OATPP_CODEGEN_END(DTO)
#endif



















