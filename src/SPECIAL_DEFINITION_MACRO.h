#ifndef SPECIAL_DEFINITION_MACRO_H_
#define SPECIAL_DEFINITION_MACRO_H_

// 禁止类的默认拷贝构造函数
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete; \
    void operator=(const TypeName&) = delete;
#endif


#endif // !SPECIAL_DEFINITION_MACRO_H_

