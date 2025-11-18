/*
@author: AC
@date:2025/10/17
@file:PeriodDTO.h
*/

#ifndef _PERIOD_DTO_H_
#define _PERIOD_DTO_H_ 

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 新增结账的DTO
*/
class SavePeriodDTO : public oatpp::DTO {
	DTO_INIT(SavePeriodDTO, DTO);
	// 结账日期
	DTO_FIELD(String, data) = "";
	DTO_FIELD_INFO(data)
	{
		info->description = ZH_WORDS_GETTER("period.field.data");
		info->required = true;
	}
public:
	SavePeriodDTO() {
		data = "";
	}
	SavePeriodDTO(String& data) {
		this->data = data;
	}
};

/*
* 结账的DTO
*/
class PeriodDTO : public oatpp::DTO {
	DTO_INIT(PeriodDTO, DTO);

	// 结账日期
	DTO_FIELD(String, data) = "";
	DTO_FIELD_INFO(data)
	{
		info->description = ZH_WORDS_GETTER("period.field.data");
		info->required = true;
	}

	// 操作日期
	DTO_FIELD(String, time)="";
    DTO_FIELD_INFO(time)
    {
        info->description = ZH_WORDS_GETTER("period.field.time");
        info->required = true;
    }
	// 操作人
    DTO_FIELD(String, user)="";
    DTO_FIELD_INFO(user)
    {
        info->description = ZH_WORDS_GETTER("period.field.user");
        info->required = true;
    }
};


// 分页查询条件DTO
class PeriodRecordPageReqDTO : public oatpp::DTO {
	DTO_INIT(PeriodRecordPageReqDTO, DTO)
	// 页码（默认第1页）
	DTO_FIELD(Int32, pageIndex) = 1;
	// 每页条数（默认30条）
	DTO_FIELD(Int32, pageSize) = 30;
};






#include OATPP_CODEGEN_END(DTO)

#endif