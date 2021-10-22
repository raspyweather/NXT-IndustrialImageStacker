#include "myapp.h"

MyApp::MyApp(int &argc, char **argv)
    : IDS::NXT::VApp{argc, argv},
      _engine{_resultcollection}
{
    // at this point all result sources must be created.
    _resultcollection.createSource("visionduration", IDS::NXT::ResultType::String);
}

void MyApp::imageAvailable(std::shared_ptr<IDS::NXT::Hardware::Image> image)
{
    _engine.handleImage(image);
}

void MyApp::abortVision()
{
    _engine.abortVision();
}
