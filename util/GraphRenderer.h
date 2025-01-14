#ifndef QT_PROJECT_GRAPHRENDERER_H
#define QT_PROJECT_GRAPHRENDERER_H
#include <string>
#include <fstream>
#include <stdexcept>
#include <filesystem>

class GraphRenderer {
private:
    std::string _temp_dir;

public:
    explicit GraphRenderer(const std::string& temp_dir);

    ~GraphRenderer();

    void render(const std::string& dot_content, const std::string& output_file);
};

#endif //QT_PROJECT_GRAPHRENDERER_H
