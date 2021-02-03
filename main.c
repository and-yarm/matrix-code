#include <stdint.h>
#include <stdlib.h>
#include <matrix_code.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    const int num_interations = 100;
    
    uint8_t p1[MATRIX_BUF_LEN + sizeof(uint16_t)];
    uint8_t p2[MATRIX_BUF_LEN];
    
    int suc, fix, err, match;

    printf("matrix based error-correction code selftest\r\n");

    printf("step 1: no added errror ");
    suc = fix = err = 0;
    for(int i = 0; i < num_interations; i++)
    {
        for(int j = 0; j < MATRIX_BUF_LEN; j++)
        {
            p1[j] = rand();
        }
        const uint16_t s = MATRIX_calculate_sum(p1);        
        memcpy(p1 + MATRIX_BUF_LEN, &s, sizeof(s));
        const int rc = MATRIX_check_data(p1);  
        if(rc == 0)
        {
            suc++;
        }
        else if(rc < 0)
        {
            err++;
        }
        else if(rc > 0)
        {
            fix++;
        }
    }
    printf("suc[%d] fix[%d] err[%d]\r\n", suc, fix, err);

    printf("step 2: one bit corrupted ");
    suc = fix = err = match = 0;
    for(int i = 0; i < num_interations; i++)
    {
        for(int j = 0; j < MATRIX_BUF_LEN; j++)
        {
            p1[j] = p2[j] = rand();
        }
        const uint16_t s = MATRIX_calculate_sum(p1);
        memcpy(p1 + MATRIX_BUF_LEN, &s, sizeof(s));
        p1[rand() % (sizeof(p1))] ^= (1 << (rand() % 8));            
        const int rc = MATRIX_check_data(p1);  
        match += (memcmp(p1, p2, MATRIX_BUF_LEN) == 0) ? 1 : 0;
        
        if(memcmp(p1, p2, MATRIX_BUF_LEN))
        {
            printf("\r\n");
            for(int i = 0 ; i < MATRIX_BUF_LEN; i++)
            {
                printf("    0x%02x 0x%02x\r\n", (int)(p1[i]), (int)(p2[i]));
            }
            printf("\r\n");
        }
        
        if(rc == 0)
        {
            suc++;
        }
        else if(rc < 0)
        {
            err++;
        }
        else if(rc > 0)
        {
            fix++;
        }
    } 
    printf("suc[%d] fix[%d] err[%d] match[%d]\r\n", suc, fix, err, match);

    printf("step 3: two bit corrupted ");
    suc = fix = err = match = 0;
    for(int i = 0; i < num_interations; i++)
    {
        for(int j = 0; j < MATRIX_BUF_LEN; j++)
        {
            p1[j] = p2[j] = rand();
        }
        const uint16_t s = MATRIX_calculate_sum(p1);
        memcpy(p1 + MATRIX_BUF_LEN, &s, sizeof(s));
        p1[rand() % sizeof(p1)] ^= (1 << (rand() % 8));  
        p1[rand() % sizeof(p1)] ^= (1 << (rand() % 8));   
        const int rc = MATRIX_check_data(p1);  
        match += (memcmp(p1, p2, MATRIX_BUF_LEN) == 0) ? 1 : 0;
        if(rc == 0)
        {
            suc++;
        }
        else if(rc < 0)
        {
            err++;
        }
        else if(rc > 0)
        {
            fix++;
        }
    } 
    printf("suc[%d] fix[%d] err[%d] match[%d]\r\n", suc, fix, err, match);

    printf("step 4: three bit corrupted ");
    suc = fix = err = match = 0;
    for(int i = 0; i < num_interations; i++)
    {
        for(int j = 0; j < MATRIX_BUF_LEN; j++)
        {
            p1[j] = p2[j] = rand();
        }
        const uint16_t s = MATRIX_calculate_sum(p1);
        memcpy(p1 + MATRIX_BUF_LEN, &s, sizeof(s));
        p1[rand() % sizeof(p1)] ^= (1 << (rand() % 8));  
        p1[rand() % sizeof(p1)] ^= (1 << (rand() % 8));   
        p1[rand() % sizeof(p1)] ^= (1 << (rand() % 8));   
        const int rc = MATRIX_check_data(p1);  
        match += (memcmp(p1, p2, MATRIX_BUF_LEN) == 0) ? 1 : 0;
        if(rc == 0)
        {
            suc++;
        }
        else if(rc < 0)
        {
            err++;
        }
        else if(rc > 0)
        {
            fix++;
        }
    } 
    printf("suc[%d] fix[%d] err[%d] match[%d]\r\n", suc, fix, err, match);

    return 0;
}
