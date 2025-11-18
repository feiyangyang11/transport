/*
@author: AC
@date:2025/10/17
@file:PeriodDO.h
*/

#ifndef _PERIOD_QUERY_H_
#define _PERIOD_QUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 分页查询结账信息
*/
/*class PeriodQuery : public PageQuery {
	DTO_INIT(PeriodQuery, PageQuery);
	// 结账日期
	DTO_FIELD(String, data) {
		info->description = ZH_WORDS_GETTER("period.field.data");
	}
	// 操作日期
	DTO_FIELD(String, time) {
		info->description = ZH_WORDS_GETTER("period.field.time");
	}
	// 操作人
	DTO_FIELD(String, user) {
		info->description = ZH_WORDS_GETTER("period.field.user");
	}
};*/




#include OATPP_CODEGEN_END(DTO)

#endif