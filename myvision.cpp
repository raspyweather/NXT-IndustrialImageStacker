// Include the own header
#include "myvision.h"

// Include Qt headers
#include <QImage>

void MyVision::process()
{
    auto img = image();

    // do something

    img->visionOK("", "");
}

void MyVision::abort()
{
    // Call the base class
    Vision::abort();
}
