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
#define EXPECT_EQ_DOUBLE(expect,actual) EXPECT_EQ_BASE((expect)==(actual),expect,actual,"%.17g");

#define TEST_ERROR(error,json)\
    do{\
        light_value value;\
        value.type=LIGHT_FALSE;\
        EXPECT_EQ_INT(error,light_parse(&value,json));\
        EXPECT_EQ_INT(LIGHT_NULL,light_get_type(&value));\
    }while(0)

#define TEST_NUMBER(expect, json)\
    do {\
        light_value value;\
        EXPECT_EQ_INT(LIGHT_PARSE_OK, light_parse(&value, json));\
        EXPECT_EQ_INT(LIGHT_NUMBER, light_get_type(&value));\
        EXPECT_EQ_DOUBLE(expect,  light_get_number(&value));\
    } while(0)

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

        /*invalid numbers*/
        TEST_ERROR(LIGHT_PARSE_INVALID_VALUE,"+0");  //自然数不包含加号
        TEST_ERROR(LIGHT_PARSE_INVALID_VALUE,"+12");
        TEST_ERROR(LIGHT_PARSE_INVALID_VALUE,"123.");
        TEST_ERROR(LIGHT_PARSE_INVALID_VALUE,".1234");//在小数点前和后至少有一个数字

    }
    static void test_parse_root_not_singular(){
       TEST_ERROR(LIGHT_PARSE_ROOT_NOT_SINGULAR,"null x");
    }

    static void test_parse_number(){
        TEST_NUMBER(0.0,"0");
        TEST_NUMBER(0.0,"-0");
        TEST_NUMBER(0.0,"0.0");
        TEST_NUMBER(1.0,"1");
        TEST_NUMBER(-1.0,"-1");
        TEST_NUMBER(1.5,"1.5");
        TEST_NUMBER(-1.5,"-1.5");
        TEST_NUMBER(3.121212,"3.121212");
        TEST_NUMBER(1E10,"1E10");
        TEST_NUMBER(1e10,"1e10");
        TEST_NUMBER(-1E+10, "-1E+10");
        TEST_NUMBER(-1E-10, "-1E-10");
        TEST_NUMBER(1.234E+10, "1.234E+10");
        TEST_NUMBER(1.234E-10, "1.234E-10");
        TEST_NUMBER(0.0, "1e-10000");

        TEST_NUMBER(1.0000000000000002,"1.0000000000000002");
        TEST_NUMBER( 4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
        TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
        TEST_NUMBER( 2.2250738585072009e-308, "2.2250738585072009e-308");  /* Max subnormal double */
        TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
        TEST_NUMBER( 2.2250738585072014e-308, "2.2250738585072014e-308");  /* Min normal positive double */
        TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
        TEST_NUMBER( 1.7976931348623157e+308, "1.7976931348623157e+308");  /* Max double */
        TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");


    }
    static void test_parse(){
        test_parse_null();
        test_parse_false();
        test_parse_true();
        test_parse_expect_value();
        test_parse_invalid_value();
        test_parse_root_not_singular();
        test_parse_number();
    }

    int main(){
        test_parse();
        std::cout<<test_pass<<"/"<<test_count<<"("
        <<std::fixed<<std::setprecision(2)<<test_pass*100.0/test_count<<"% passed)"<<std::endl;
        return main_ret;
    }
