// Include the own header
#include "myengine.h"

// Include framework headers
#include <resultsource.h>

// Include local headers
#include "myvision.h"

// static QLoggingCategory lc{"stack.MyEngine"};

MyEngine::MyEngine(IDS::NXT::ResultSourceCollection& resultcollection)
  : _resultcollection{resultcollection} {}

std::shared_ptr<IDS::NXT::Vision> MyEngine::factoryVision() {
    // Simply construct a vision object, we may give further parameters, such as not-changing
    // parameters or shared (thread-safe!) objects.
    return std::make_shared<MyVision>();
}

void MyEngine::setupVision(std::shared_ptr<IDS::NXT::Vision> vision) {
    // Here we could set changing parameters, such as current configurable values
    if (vision) {
        auto obj = std::static_pointer_cast<MyVision>(vision);
    }
}

void MyEngine::handleResult(std::shared_ptr<IDS::NXT::Vision> vision) {
    // Get the finished vision object
    auto obj = std::static_pointer_cast<MyVision>(vision);

    // Fill ResultSources of the collection
    _resultcollection.addResult("visionduration", QString::number(obj->timeNeeded()), "resultPart", vision->image());

    // Signal that all parts of the image are finished
    _resultcollection.finishedAllParts(obj->image());

    // Remove the image pointer from the vision object and thereby allow the framework to
    // reuse the image buffer.
    obj->setImage(nullptr);
}
