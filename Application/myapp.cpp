#include "myapp.h"

#include <trigger.h>
#include <triggertype.h>
#include <ImageFilters/imagefilters.h>

static QLoggingCategory lc{"stack.myapp"};

MyApp::MyApp(int& argc, char** argv)
  : IDS::NXT::VApp{argc, argv}
  , _engine{_resultcollection}
  , _imageSlider{"intervall", 100}
  , _drawresult{"drawresult", false}
  , _resultimage("myresultimage")
  , _reset("reset") {
    // at this point all result sources must be created.
    _resultcollection.createSource("visionduration", IDS::NXT::ResultType::String);

    _imageSlider.setRange(0, 5000);
    _imageSlider.setUnit(IDS::NXT::Unit::Milliseconds);

    IDS::NXT::Hardware::Trigger::getInstance().setTriggerType(IDS::NXT::TriggerType::Software);

    connect(&_timer, &QTimer::timeout, this, &MyApp::triggerImage);
    connect(&_imageSlider, &IDS::NXT::ConfigurableInt64::changed, this, &MyApp::timerChanged);
    timerChanged(_imageSlider);
}

void MyApp::imageAvailable(std::shared_ptr<IDS::NXT::Hardware::Image> image) {
    _engine.handleImage(image);

    const auto imagePtr = reinterpret_cast<uint8_t*>(image->buffer());
    auto size = image->size();

    if (!_tmpMemory) {
        qCDebug(lc) << "Image Size" << size;

        _tmpMemory = std::make_unique<uint8_t[]>(size);
    }

    ImageFilters::max(_tmpMemory.get(), imagePtr, _tmpMemory.get(), size);

    // qCDebug(lc) << "MaxValues" << result[0] << imagePtr[0] << imagePtr[256];

    if (_drawresult) {
        QImage myImage(_tmpMemory.get(), image->width(), image->height(), QImage::Format_RGB888);
        _resultimage.setImage(myImage, image);
    }
}

void MyApp::abortVision() {
    _engine.abortVision();
}

void MyApp::timerChanged(qint64 value) {
    qCDebug(lc) << "timerChanged" << value;

    if (value == 0) {
        _timer.stop();
    } else {
        _timer.setInterval(value);
        _timer.start();
    }
}

void MyApp::triggerImage() {
    IDS::NXT::Hardware::Trigger::getInstance().trigger();
}
