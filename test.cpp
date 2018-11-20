//
// Created by laihz on 18-11-17.
//


#include <iostream>
#include <cstdio>
#include <iomanip>
#include "lightjson.h"

static int main_ret=0;      //主函数返回值
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

#define TEST_ERROR(error,json)\
    do{\
        light_value value;\
        value.type=LIGHT_FALSE;\
        EXPECT_EQ_INT(error,light_parse(&value,json));\
        EXPECT_EQ_INT(LIGHT_NULL,light_get_type(&value));\
    }while(0)


    static void test_parse_null(){
        light_value value;
        value.type=LIGHT_TRUE;
        EXPECT_EQ_INT(LIGHT_PARSE_OK,light_parse(&value,"null"));
        EXPECT_EQ_INT(LIGHT_NULL,light_get_type(&value));
    }
    static void test_parse_true(){
        light_value value;
        value.type=LIGHT_TRUE;
        EXPECT_EQ_INT(LIGHT_PARSE_OK,light_parse(&value,"true"));
        EXPECT_EQ_INT(LIGHT_TRUE,light_get_type(&value));

    }
    static void test_parse_false(){
        light_value value;
        value.type=LIGHT_TRUE;
        EXPECT_EQ_INT(LIGHT_PARSE_OK,light_parse(&value,"false"));
        EXPECT_EQ_INT(LIGHT_FALSE,light_get_type(&value));
    }
    static void test_parse_expect_value(){
        TEST_ERROR(LIGHT_PARSE_EXPECT_VALUE,"");
        TEST_ERROR(LIGHT_PARSE_EXPECT_VALUE," ");
    }
    static void test_parse_invalid_value(){
        TEST_ERROR(LIGHT_PARSE_INVALID_VALUE,"nul");
    }
    static void test_parse_root_not_singular(){
       TEST_ERROR(LIGHT_PARSE_ROOT_NOT_SINGULAR,"null x");
    }
    static void test_parse(){
        test_parse_null();
        test_parse_false();
        test_parse_true();
        test_parse_expect_value();
        test_parse_invalid_value();
        test_parse_root_not_singular();
    }

    int main(){
        test_parse();
        std::cout<<test_pass<<"/"<<test_count<<"("
        <<std::fixed<<std::setprecision(2)<<test_pass*100.0/test_count<<"% passed)"<<std::endl;
        return main_ret;
    }
