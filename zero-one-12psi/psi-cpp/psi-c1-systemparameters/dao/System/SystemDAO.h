#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/10/13 21:38:24

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _SYSTEMDAO_H_
#define _SYSTEMDAO_H_

#include "BaseDAO.h"
#include "domain/dto/System/SystemDTO.h"
#include "domain/do/System/SystemDO.h"
#include "domain/query/System/SystemQuery.h"

class SystemDAO : public BaseDAO {
private:

public:
    // 统计数据条数
    uint64_t count();
    // 获取数据库的所有字段
    list<PtrSystemDO> selectAllSys();
    // 通过id来修改字段
    oatpp::Int32 updateById(const list<PtrSystemDO>& data);
};

#endif // !_SYSTEMDAO_H_