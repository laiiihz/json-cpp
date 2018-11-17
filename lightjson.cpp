//
// Created by laihz on 18-11-17.
//

#include "lightjson.h"
#include <assert.h>

#define EXPECT(c,ch)    do{assert(*c->json==(ch));c->json++;}while(0)

class light_context{
public:const char* json;
};

int light_parse(light_value *value, const char* json){

}

light_type light_get_type(const light_value *value){

}