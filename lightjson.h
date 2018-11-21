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
    double n;
};


enum{   LIGHT_PARSE_OK=0,
        LIGHT_PARSE_EXPECT_VALUE,
        LIGHT_PARSE_INVALID_VALUE,
        LIGHT_PARSE_ROOT_NOT_SINGULAR
};

int light_parse(light_value* value, const char* json);

light_type light_get_type(const light_value* value);
double light_get_number(const light_value* value);
#endif //UNTITLED1_LIGHTJSON_H
