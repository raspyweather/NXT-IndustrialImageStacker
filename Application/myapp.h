#ifndef MYAPP_H
#define MYAPP_H

// Include framework headers
#include <resultsourcecollection.h>
#include <vapp.h>

// Include own headers
#include "myengine.h"

#include "action.h"
#include "configurablebool.h"
#include "configurableint64.h"
#include "myresultimage.h"

#include <QLoggingCategory>
#include <QTimer>

#include <camera.h>


/**
 * @brief The app-specific app object
 *
 * The app object serves as central object in the vision app. It's inheritance of VApp gives basic system
 * functionality, such as listing in the REST-Interface / GUI and, probably most importantly allows the
 * usage of interaction elements such as actions, configurables etc.
 */
class MyApp : public IDS::NXT::VApp {
    // This Qt macro is needed for the signal/slot mechanism
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param argc count of command line arguments
     * @param argv list of command line arguments
     */
    MyApp(int& argc, char** argv);

protected slots:
    /**
     * @brief Called for new images
     * @param image new image
     *
     * This function is called whenever there's a new image which is to be processed by this vision app.
     * The image is provided as a shared pointer. As long as this pointer is kept alive, the image data will
     * not be overwritten by the framework. For an effective software freerun though, the framework must be
     * told that the image processing is done, which can be done with the methods visionDone, visionOK or
     * visionFailed of the image object. Alternatively, the pointer can simply be destructed, which signalizes
     * that the vision app ignored the image and is nearly equivalent with a call to visionDone.
     */
    void imageAvailable(std::shared_ptr<IDS::NXT::Hardware::Image> image) override;

    /**
     * @brief Called for abort-requests
     *
     * This function is called whenever the framework requires the vision to abort all executing image processing.
     */
    void abortVision() override;

private slots:

    void timerChanged(qint64 value);

    void triggerImage();

    void resetImageBuffers();

private:
    /**
     * @brief Collection of results
     *
     * This object stores all results of the image processing. It is held as a shared pointer as it needs to be
     * used in any engine available.
     */
    IDS::NXT::ResultSourceCollection _resultcollection;

    MyEngine _engine;

    IDS::NXT::ConfigurableInt64 _imageSlider;
    IDS::NXT::ConfigurableBool _drawresult;
    IDS::NXT::ConfigurableBool _enablemin;
    IDS::NXT::ConfigurableBool _enablemax;

    IDS::NXT::Action _reset;

    QTimer _timer;

    std::unique_ptr<uint8_t[]> _maxImageBuffer;
    std::unique_ptr<uint8_t[]> _minImageBuffer;
    size_t _imageBufferSize;

    MyResultImage _resultmaximage;
    MyResultImage _resultminimage;
};

#endif // MYAPP_H
