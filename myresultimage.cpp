#include "myresultimage.h"

#include <QLoggingCategory>
#include <QPainter>
#include <QRawFont>

static QLoggingCategory lc{"classifier.ResultImageHeatMap"};

MyResultImage::MyResultImage(const QByteArray& name)
  : ResultImage(name) {}

QImage MyResultImage::getImage() const {
    if (!_image.isNull()) {
        return _image;
    }

    return QImage{};
}

void MyResultImage::setImage(const QImage& image, const std::shared_ptr<IDS::NXT::Hardware::Image>& nxtImage) {
    _image = image;
    setModified(nxtImage->key());
}
