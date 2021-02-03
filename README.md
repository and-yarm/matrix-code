# matrix-code

matix-based error-correction code

## how it works

the lib calculates check sum for each chunk of data. chunk len is 8 bytes. sum len is 2 bytes. 
using calculated sum lib able to fix about 80% of one-bit data corruption.

## how sum is calculated

incoming data chunk represented as matrix. for each row and column of the matrix we calculate a parity, like this:

```
0 0 0 0 0 0 0 0 | 0
0 0 0 0 0 0 0 1 | 1
0 0 0 0 0 0 1 1 | 0
0 0 0 0 0 1 1 1 | 1
0 0 0 0 0 0 0 0 | 0
0 0 0 0 0 0 0 0 | 0
0 0 0 0 0 0 0 0 | 0
0 0 0 0 0 0 0 0 | 0
----------------
0 0 0 0 0 1 0 1
```

## how correction performed

1. calculing sum for incoming chunk+inconig sum
2. if sum is 0 - no errors
3. if sum is not 0 - intersection of rised bits will show corrupted bit

for example let's corrupt first byte

```
0 0 0 0 0 0 1 0 0 | 1
0 0 0 0 0 0 0 1 1 | 0
0 0 0 0 0 0 1 1 0 | 0
0 0 0 0 0 1 1 1 1 | 0
0 0 0 0 0 0 0 0 0 | 0
0 0 0 0 0 0 0 0 0 | 0
0 0 0 0 0 0 0 0 0 | 0
0 0 0 0 0 0 0 0 0 | 0
0 0 0 0 0 1 0 1  
---------------
0 0 0 0 0 0 1 0
```

## how to build

```gcc main.c matrix_code.c -I. -o matrix```

## how to run test

```matrix-code$ ./matrix 
matrix based error-correction code selftest
step 1: no added errror suc[100] fix[0] err[0]
step 2: one bit corrupted suc[0] fix[82] err[18] match[100]
step 3: two bit corrupted suc[1] fix[2] err[97] match[1]
step 4: three bit corrupted suc[0] fix[8] err[92] match[6]```
