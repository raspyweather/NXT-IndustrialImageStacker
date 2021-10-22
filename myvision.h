#pragma once

#include <QImage>

// Include framework headers
#include <vision.h>


/**
 * @brief The app-specific vision object
 */
class MyVision : public IDS::NXT::Vision
{
    // this Qt macro is needed for the signal/slot mechanism
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    MyVision() = default;

    /**
     * @brief Start the image processing
     */
    void process() override;
    /**
     * @brief Abort the image processing
     */
    void abort() override;

    /**
     * @brief Getter for the result image
     */
    QImage getResultImage() const;
private:
    QImage _resultImage;
};
