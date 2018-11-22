//
// Created by laihz on 18-11-17.
//

#include "lightjson.h"
#include <assert.h>
#include <cmath>

#define EXPECT(c,ch)            do{assert(*c->json==(ch));c->json++;}while(0)

#define ISDIGIT(ch)             ((ch)>='0'&&(ch)<='9')
#define ISDIGIT1TO9(ch)     ((ch)>='1'&&(ch)<='9')


class light_context{
public:const char* json;
};

static void light_parse_whitespace(light_context* c){
    const char* p=c->json;
    while(*p==' '||*p=='\t'||*p=='\r')p++;
    c->json=p;
}

static int light_parse_literal(light_context* c,light_value* value, const char* literal,light_type type){
    size_t i;
    EXPECT(c,literal[0]);
    for(i=0;literal[i+1];i++)       //for 循环控制条件可以用字符表示，在字符为空时（\0）表示条件假，停止循环
        if(c->json[i]!=literal[i+1])
            return LIGHT_PARSE_INVALID_VALUE;
    c->json+=i;
    value->type=type;
    return LIGHT_PARSE_OK;
}

static int light_parse_number(light_context* c,light_value* value){
    char* end;
    const char *p=c->json;
    if(*p=='-')p++;
    if(*p=='0')p++;
    else {
        if(!ISDIGIT1TO9(*p))return LIGHT_PARSE_INVALID_VALUE;
        for(p++;ISDIGIT(*p);p++);
    }
    if(*p=='.'){
        p++;
        if(!ISDIGIT(*p))return LIGHT_PARSE_INVALID_VALUE;
        for(p++;ISDIGIT(*p);p++);
    }
    if(*p=='e'||*p=='E'){
        p++;
        if(*p=='+'||*p=='-')p++;
        if(!ISDIGIT(*p))return LIGHT_PARSE_INVALID_VALUE;
        for(p++;ISDIGIT(*p);p++);
    }
    /*
     *          http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf
     * */
    errno=0;
    value->un.n=strtod(c->json, nullptr);
    if(errno==ERANGE&&(value->un.n==HUGE_VAL||value->un.n==-HUGE_VAL))
        return LIGHT_PARSE_NUMBER_TOO_BIG;
    value->type=LIGHT_NUMBER;
    c->json=p;
    return LIGHT_PARSE_OK;
}
/*
 * double strtod(const char *str, char **endptr)
 *  把参数 str 所指向的字符串转换为
 *  一个浮点数（类型为 double 型）。
 *  如果 endptr 不为空，则指向转换
 *  中最后一个字符后的字符的指针会
 *  存储在 endptr 引用的位置。
 * */
static int light_parse_value(light_context* c,light_value* value){
    switch (*c->json){
        case 'n':return light_parse_literal(c,value,"null",LIGHT_NULL);
        case 't':return light_parse_literal(c,value,"true",LIGHT_TRUE);
        case 'f':return light_parse_literal(c,value,"false",LIGHT_FALSE);
        case '\0':return LIGHT_PARSE_EXPECT_VALUE;
        default:return light_parse_number(c,value);
    }
}


int light_parse(light_value *value, const char* json){
    light_context c;
    int ret;
    assert(value!= nullptr);
    c.json=json;
    value->type=LIGHT_NULL;
    light_parse_whitespace(&c);
    if((ret=light_parse_value(&c,value))==LIGHT_PARSE_OK){
        light_parse_whitespace(&c);
        if(*c.json!='\0'){
            value->type=LIGHT_NULL;
            ret=LIGHT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return  ret;
}

light_type light_get_type(const light_value *value){
    assert(value!= nullptr);
    return value->type;
}

double light_get_number(const light_value *value){
    assert(value!= nullptr&&value->type==LIGHT_NUMBER);
    return value->un.n;

}

void light_free(light_value* value){
    assert(value!= nullptr);
    if(value->type==LIGHT_STRING)
        delete(value->un.s.s);
    value->type=LIGHT_NULL;
}

void light_set_string( light_value* value , const char* s ,size_t length){
    assert(value!= nullptr&&(s!= nullptr||length==0));
    light_free(value);
    value->un.s.s=new char[length+1];
    memcpy(value->un.s.s,s,length);
    value->un.s.s[length]='\0';
    value->un.s.length=length;
    value->type=LIGHT_STRING;
}

void light_set_number(light_value *value, double number) {
    //TODO set number
}

int light_get_boolean(const light_value *value) {
    //TODO get boolean
    return 0;
}

size_t light_get_string_length(const light_value *value) {
    //TODO get string length
    return 0;
}

const char *light_get_string(const light_value *value) {
    //TODO get string
    return nullptr;
}

void light_set_boolean(light_value *value, int b) {
    //TODO set boolean
}
