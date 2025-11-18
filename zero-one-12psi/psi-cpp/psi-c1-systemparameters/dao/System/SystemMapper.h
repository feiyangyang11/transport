
























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
#ifndef _SYSTEMMAPPER_H_
#define _SYSTEMMAPPER_H_

#include "Mapper.h"
#include "domain/do/System/SystemDO.h"


class SystemMapper : public Mapper<PtrSystemDO> {
public:
    PtrSystemDO mapper(ResultSet* resultSet)  const override  {
        PtrSystemDO sysDO = std::make_shared<SystemDO>();
        sysDO->setId(resultSet->getString("id"));
        sysDO->setInfo(resultSet->getString("info"));
        sysDO->setName(resultSet->getString("name"));
        sysDO->setRemark(resultSet->getString("data"));
        return sysDO;
    }
};


#endif // !_SYSTEMMAPPER_H_
