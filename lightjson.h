//
// Created by laihz on 18-11-17.
//

#ifndef LIGHTJSON_H__
#define LIGHTJSON_H__

#include <iostream>



enum light_type{    LIGHT_NULL,
                    LIGHT_FALSE,
                    LIGHT_TRUE,
                    LIGHT_NUMBER,
                    LIGHT_STRING,
                    LIGHT_ARRAY,
                    LIGHT_OBJECT
};

class light_value{
public :
    light_type type;
    union {             //n 和 结构体s共享内存
        double n;
        struct {
            char* s;
            size_t  length;
        }s;
    }un;
};


enum{   LIGHT_PARSE_OK=0,
        LIGHT_PARSE_EXPECT_VALUE,
        LIGHT_PARSE_INVALID_VALUE,
        LIGHT_PARSE_ROOT_NOT_SINGULAR,
        LIGHT_PARSE_NUMBER_TOO_BIG
};
#define light_init(value)           do{(value)->type=LIGHT_NULL;}while(0)

int light_parse(light_value* value, const char* json);
void light_free(light_value *value);

light_type light_get_type(const light_value* value);


#define light_set_null(value)           light_free(value)
int light_get_boolean(const light_value *value);
void light_set_boolean(const light_value* value,int b);              //布尔类型设置

double light_get_number(const light_value* value);                  //浮点类型设置
void  light_set_number(const light_value* value,double number);

const  char* light_get_string(const light_value *value);            //字符串类型设置
size_t  light_get_string_length(const light_value* value);
void light_set_string(const light_value* value, const char* s,size_t length);

#endif //UNTITLED1_LIGHTJSON_H
