#ifndef _ERROR_HANDLE_H_
#define _ERROR_HANDLE_H_

typedef enum error_handle_type_e
{
    normal = 0,
    data_err,  //模块接收到的数据不符合规范
    trans_err, //与模块通讯出错
    module_err //模块其他行为不符合预期
}error_handle_type;

#endif