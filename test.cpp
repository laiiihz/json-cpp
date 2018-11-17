//
// Created by laihz on 18-11-17.
//


#include <iostream>
#include <cstdio>
#include <iomanip>
#include "lightjson.h"

static int main_ret=0;
static int test_count=0;    //测试项目数
static int test_pass=0;     //测试通过数

#define EXPECT_EQ_BASE(equality,expect,actual,format)\
    do{\
        test_count++;\
        if(equality)\
            test_pass++;\
        else{\
            fprintf(stderr,"%s:%d:expect: " format " actual: " format "\n",__FILE__,__LINE__,expect,actual);\
            main_ret=1;\
        }\
    } while (0)

#define EXPECT_EQ_INT(expect,actual) EXPECT_EQ_BASE((expect)==(actual),expect,actual, "%d")

    static void test_parse_null(){
        light_value value;
        value.type=LIGHT_TRUE;
        EXPECT_EQ_INT(LIGHT_PARSE_OK,light_parse(&value,"null"));
        EXPECT_EQ_INT(LIGHT_NULL,light_get_type(&value));
    }

    static void test_parse(){
        test_parse_null();
    }

    int main(){
        test_parse();
        std::cout<<test_pass<<"/"<<test_count<<"("
        <<std::fixed<<std::setprecision(2)<<test_pass/test_count*100<<"% passed)";
    }
