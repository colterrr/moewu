#ifndef _ERROR_HANDLE_H_
#define _ERROR_HANDLE_H_

typedef enum error_handle_type_e
{
    normal = 0,
    data_error,
    module_error,
    trans_error
}error_handle_type;

#endif