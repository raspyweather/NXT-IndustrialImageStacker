#pragma once

// Include std headers
#include <memory>

// Include framework headers
#include <engine.h>
#include <resultsourcecollection.h>
#include "customresultimage.h"
/**
 * @brief The app-specific engine
 */
class MyEngine : public IDS::NXT::Engine
{
    // This Qt macro is needed for the signal/slot mechanism
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param resultcollection The result collection object
     *
     * This function constructs the engine object.
     */
    MyEngine(IDS::NXT::ResultSourceCollection& resultcollection);

protected:
    /**
     * @brief Factory function for vision objects
     * @return Factored vision object
     *
     * This method factors a vision object, which depends on our implementation. This method
     * is called whenever the framework needs a new vision object, these objects are reused.
     * Do not set up changing variables inside of the vision object, this should be done in setupVision.
     */
    virtual std::shared_ptr<IDS::NXT::Vision> factoryVision() override;

    /**
     * @brief Setup of a vision object
     * @param vision Vision object to be set up
     *
     * This method sets up a vision object. This method is called when a new image should be processed.
     * Inside this method, every variable of the vision object should be set.
     * As the vision object will run in a different thread context, use thread-safe variables, e.g. simple copies.
     */
    virtual void setupVision(std::shared_ptr<IDS::NXT::Vision> vision) override;

    /**
     * @brief Handle the result of a vision object
     * @param vision Finished vision object
     *
     * This method handles a finished vision object and reads the results. These results can then be further
     * processed and/or written to the ResultSourceCollection.
     * After that, the image can be deleted (set to nullptr) from the vision object.
     */
    virtual void handleResult(std::shared_ptr<IDS::NXT::Vision> vision) override;

private:
    /**
     * @brief Collection of results
     *
     * This object stores all results of the image processing.
     */
    IDS::NXT::ResultSourceCollection& _resultcollection;

    /**
     * @brief Result image
     *
     * This image is displayed separately in the NXT Cockpit
     * In this example we will use the result image to display the ROI image
     */
    CustomResultImage _resultImage;
};
