#pragma once
#include <QImage>

#include "image.h"
#include "resultimage.h"

class MyResultImage : public IDS::NXT::ResultImage {
    Q_OBJECT
public:
    MyResultImage(const QByteArray& name);

    void setImage(const QImage& image, const std::shared_ptr<IDS::NXT::Hardware::Image>& nxtImage);

    QImage getImage() const override;

private:
    QImage _image;
};
