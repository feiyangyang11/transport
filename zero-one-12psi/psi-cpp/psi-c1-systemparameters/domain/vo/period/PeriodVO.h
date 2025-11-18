/*
@author: AC
@date:2025/10/17
@file:PeriodVO.h
*/

#ifndef _PERIOD_VO_H_
#define _PERIOD_VO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/period/PeriodDTO.h"
#include "oatpp/core/data/mapping/type/Type.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include"../lib-oatpp/include/domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 显示JsonVO，用于响应给客户端的Json对象
 */
class PeriodJsonVO : public StringJsonVO {
	DTO_INIT(PeriodJsonVO, StringJsonVO);
};

/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
class PeriodPageJsonVO : public JsonVO<oatpp::Object<PeriodDTO>> {
    DTO_INIT(PeriodPageJsonVO, JsonVO<oatpp::Object<PeriodDTO>>);
};


// 单条结账记录VO
class PeriodRecordVO : public oatpp::DTO {
    DTO_INIT(PeriodRecordVO, DTO)
    DTO_FIELD(String, date);    // 结账日期
    DTO_FIELD(String, time);    // 操作时间
    DTO_FIELD(String, user);     // 操作人ID
};

// 分页响应VO
class PeriodRecordPageRespVO : public oatpp::DTO {
    DTO_INIT(PeriodRecordPageRespVO, DTO)
    DTO_FIELD(String, state) = "success";  // 状态（success/fail）
    DTO_FIELD(Int64, count);               // 总记录数
    DTO_FIELD(List<Object<PeriodRecordVO>>, info);  // 记录列表
};



#include OATPP_CODEGEN_END(DTO)

#endif 
