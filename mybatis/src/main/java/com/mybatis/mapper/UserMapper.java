package com.mybatis.mapper;

import com.mybatis.entity.User;

public interface UserMapper {
    User selectById(Integer id);
}