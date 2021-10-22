// Include the own header
#include "myvision.h"

// Include Qt headers
#include <QImage>

void MyVision::process()
{
    auto img = image();

    // do something
    _resultImage = img->getQImage().copy();

    img->visionOK("", "");
}

void MyVision::abort()
{
    // Call the base class
    Vision::abort();
}

QImage MyVision::getResultImage() const
{
    return _resultImage;
}
