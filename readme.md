# C++20 MagicEnum
Here is a refactor version for magic_enum in c++20;
the core interface such as enum_name,enum_cast,enum_count and so on are rewrite here ;

# todo 
1. enum_fuse 
2. enum_switch
3. c++20 module

# 中文简介
1. 兼容测试 : 使用doctest(单头文件测试库) 兼容magic_enum目前已开发的功能的测试,原仓库的catch2 不支持c++20
2. 接口兼容 : 重写时兼容原有的开放接口
3. 接口分文件组织: 不同的接口分文件组织 如果仅仅使用某几个特定的接口可以只包含相应的文件
4. 注释详实,格式美观,保证可读性的基础上力求简洁

# 阅读源码的顺序
参考链接 : 
1. concept
2. check
3. enum_integer
4. enum_type_name
5. enum_core
6. enum_count
7. enum_name 
8. enum_names 
9. enum_value 
10. enum_entries 
11. enum_index
