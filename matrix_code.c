#include <stdint.h>
#include <stdlib.h>
#include <matrix_code.h>

static int get_num_set_bits(const uint8_t d)
{
    int r = 0;
    for(size_t i = 0; i < 8; i++)
    {
        if(d & (1 << i))
        {
            r++;
        }
    }
    return r;
}

static int get_num_of_first_set_bit(const uint8_t d)
{
    int r = 0;
    for(size_t i = 0; i < 8; i++)
    {
        if(d & (1 << i))
        {
            return r;
        }
        r++;
    }
    return r;
}

uint16_t MATRIX_calculate_sum(const void *data)
{
    uint8_t x = 0;
    uint8_t y = 0;
    const uint8_t *d = (const uint8_t *)data;
        
    for(int i = 0; i < MATRIX_BUF_LEN; i++)
    {
        x ^= d[i];
        y |= (((get_num_set_bits(d[i])) & 1) ? (1 << i) : 0);
    }
    return (uint16_t)((x << 8) | y);
}

int MATRIX_check_data(void *data)
{
    uint8_t *d = (uint8_t *)data;
    const uint16_t rs = *(uint16_t*)(&d[MATRIX_BUF_LEN]);
    const uint16_t s = MATRIX_calculate_sum(d);
    const uint8_t x = (uint8_t)((rs ^ s) >> 8);
    const uint8_t y = (uint8_t)((rs ^ s) >> 0);
        
    if(x == 0 && y == 0)
    {
        return 0;
    }
    if(get_num_set_bits(x) == 1 && get_num_set_bits(y) == 1)
    {        
        d[get_num_of_first_set_bit(y)] ^=  x;
        return 1;
    }
    return -1;
}
