#pragma once

#include <cstdint>

typedef pthread_t Tid;

typedef uint32_t UINT;
typedef int64_t	 TIME;
typedef int32_t  INT;
typedef int64_t	 INT64;
typedef int32_t	 INT32;
typedef uint8_t	 BYTE;

#ifndef DELETE_PTR
#define DELETE_PTR(x) if((x)) { delete (x); (x)=nullptr;}
#endif

#ifndef DELETE_PTR_ARR
#define DELETE_PTR_ARR(x) if((x)) { delete[] (x); (x)=nullptr;}
#endif
