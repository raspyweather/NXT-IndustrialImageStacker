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
  , _enablemin{"enablemin", true}
  , _enablemax{"enablemax", true}
  , _reset("reset")
  , _imageBufferSize(0)
  , _resultmaximage("resultmaximage")
  , _resultminimage("resultminimage")
{
    // at this point all result sources must be created.
    _resultcollection.createSource("visionduration", IDS::NXT::ResultType::String);

    _imageSlider.setRange(0, 5000);
    _imageSlider.setUnit(IDS::NXT::Unit::Milliseconds);

    _resultmaximage.setTitle("max");
    _resultminimage.setTitle("min");

    IDS::NXT::Hardware::Trigger::getInstance().setTriggerType(IDS::NXT::TriggerType::Software);

    connect(&_timer, &QTimer::timeout, this, &MyApp::triggerImage);
    connect(&_imageSlider, &IDS::NXT::ConfigurableInt64::changed, this, &MyApp::timerChanged);
    connect(&_reset, &IDS::NXT::Action::executionDemanded, this, &MyApp::resetImageBuffers);
    timerChanged(_imageSlider);
}

void MyApp::imageAvailable(std::shared_ptr<IDS::NXT::Hardware::Image> image) {
    _engine.handleImage(image);

    const auto imagePtr = reinterpret_cast<uint8_t*>(image->buffer());
    auto size = image->size();

    if (!_maxImageBuffer) {
        qCDebug(lc) << "Image Size" << size;
        _imageBufferSize = size;
        _maxImageBuffer = std::make_unique<uint8_t[]>(size);
    }
    if (!_minImageBuffer) {
        qCDebug(lc) << "Image Size" << size;
        _imageBufferSize = size;
        _minImageBuffer = std::make_unique<uint8_t[]>(size);
    }

    if (_enablemax){
        ImageFilters::max(_maxImageBuffer.get(), imagePtr, _maxImageBuffer.get(), size);
    }
    if (_enablemin){
        ImageFilters::min(_minImageBuffer.get(), imagePtr, _minImageBuffer.get(), size);
    }

    if (_drawresult && _enablemax) {
        QImage myImage(_maxImageBuffer.get(), image->width(), image->height(), QImage::Format_RGB888);
        _resultmaximage.setImage(myImage, image);
    }
    if (_drawresult && _enablemin) {
        QImage myImage(_minImageBuffer.get(), image->width(), image->height(), QImage::Format_RGB888);
        _resultminimage.setImage(myImage, image);
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

void MyApp::resetImageBuffers(){
    if (_maxImageBuffer){
        for (size_t i = 0; i<_imageBufferSize;i++){
            _maxImageBuffer[i] = 0;
        }
    }
    if (_minImageBuffer){
        for (size_t i = 0; i<_imageBufferSize;i++){
            _minImageBuffer[i] = 255;
        }
    }
}
