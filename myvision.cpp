// Include the own header
#include "myvision.h"

// Include Qt headers
#include <QDateTime>
#include <QImage>

// static QLoggingCategory lc{"stack.MyVision"};

void MyVision::process() {
    auto img = image();

    img->visionOK("", "");
}

void MyVision::abort() {
    // Call the base class
    Vision::abort();
}
