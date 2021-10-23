#pragma once

#include <stdint.h>
#include <cstddef>

class ImageFilters
{
public:
    static void max(const uint8_t* inputImageA,const uint8_t* inputImageB, uint8_t* output, size_t size);
    static void min(const uint8_t* inputImageA,const uint8_t* inputImageB, uint8_t* output, size_t size);
private:
    ImageFilters();
};

