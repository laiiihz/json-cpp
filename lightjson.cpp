//
// Created by laihz on 18-11-17.
//

#include "lightjson.h"
#include <assert.h>

#define EXPECT(c,ch)    do{assert(*c->json==(ch));c->json++;}while(0)

class light_context{
public:const char* json;
};

static void light_parse_whitespace(light_context* c){
    const char* p=c->json;
    while(*p==' '||*p=='\t'||*p=='\r')p++;
    c->json=p;
}

static int light_parse_null(light_context* c,light_value* value){
    EXPECT(c,'n');
    if(c->json[0]!='u'||c->json[1]!='l'||c->json[2]!='l')return LIGHT_PARSE_INVALID_VALUE;
    c->json+=3;
    value->type=LIGHT_NULL;
    return LIGHT_PARSE_OK;
}
static int light_parse_true(light_context* c,light_value* value){
    EXPECT(c,'t');
    if(c->json[0]!='r'||c->json[1]!='u'||c->json[2]!='e')return LIGHT_PARSE_INVALID_VALUE;
    c->json+=3;
    value->type=LIGHT_TRUE;
    return LIGHT_PARSE_OK;
}

static int light_parse_false(light_context* c,light_value* value){
    EXPECT(c,'f');
    if(c->json[0]!='a'||c->json[1]!='l'||c->json[2]!='s'||c->json[3]!='e')return LIGHT_PARSE_INVALID_VALUE;
    c->json+=4;
    value->type=LIGHT_FALSE;
    return LIGHT_PARSE_OK;
}

//todo add light parse false

static int light_parse_value(light_context* c,light_value* value){
    switch (*c->json){
        case 'n':return light_parse_null(c,value);
        case 't':return light_parse_true(c,value);
        case 'f':return light_parse_false(c,value);
        case '\0':return LIGHT_PARSE_EXPECT_VALUE;
        default:return LIGHT_PARSE_INVALID_VALUE;
    }
}

int light_parse(light_value *value, const char* json){
    light_context c;
    int ret;
    assert(value!=NULL);
    c.json=json;
    value->type=LIGHT_NULL;
    light_parse_whitespace(&c);
    if((ret=light_parse_value(&c,value))==LIGHT_PARSE_OK){
        light_parse_whitespace(&c);
        if(*c.json!='\0')ret=LIGHT_PARSE_ROOT_NOT_SINGULAR;
    }
    return  ret;
}

light_type light_get_type(const light_value *value){
    assert(value!=NULL);
    return value->type;
}