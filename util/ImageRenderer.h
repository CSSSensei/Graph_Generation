#ifndef QT_PROJECT_IMAGERENDERER_H
#define QT_PROJECT_IMAGERENDERER_H
#include <QLabel>
#include <string>

class ImageRenderer{
public:
    ImageRenderer() = delete;

    static void render(QLabel& image_holder, const std::string& filename);
};
#endif //QT_PROJECT_IMAGERENDERER_H
