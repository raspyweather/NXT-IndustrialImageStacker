#include "imagefilters.h"
#include <algorithm>

#include <arm_neon.h>

ImageFilters::ImageFilters()
{}

void ImageFilters::max(const uint8_t* inputImageA,const uint8_t* inputImageB, uint8_t* output, size_t size)
{
    size_t rest = size % 16;
    size_t i = 0;
    for (; i < size-rest; i += 16) {
        auto loader = vld1q_u8(inputImageA + i);

        auto loader2 = vld1q_u8(inputImageB + i);

        auto max = vmaxq_u8(loader, loader2);

        vst1q_u8(output + i, max);
    }
    for (; i < size; i++) {
        output[i] = std::max(inputImageA[i], inputImageB[i]);
    }
}

void ImageFilters::min(const uint8_t* inputImageA,const uint8_t* inputImageB, uint8_t* output, size_t size)
{
    size_t rest = size % 16;
    size_t i = 0;
    for (; i < size-rest; i += 16) {
        auto loader = vld1q_u8(inputImageA + i);

        auto loader2 = vld1q_u8(inputImageB + i);

        auto max = vminq_u8(loader, loader2);

        vst1q_u8(output + i, max);
    }
    for (; i < size; i++) {
        output[i] = std::max(inputImageA[i], inputImageB[i]);
    }
}


