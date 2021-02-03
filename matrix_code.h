#ifndef MATRIX_CODE_H
#define MATRIX_CODE_H

#include <stdint.h>
#include <stdlib.h>

#define MATRIX_BUF_LEN     (8)

// calculate check sum for chunk of MATRIX_BUF_LEN len
uint16_t MATRIX_calculate_sum(const void *data);

// check and restore (if possible) chunk of data, followed by check sum
// return:
//         rc=0 - data vlaid
//         rc>0 - data corrupted and restored
//         rc<0 - data fully corrupted
int MATRIX_check_data(void *data);

#endif