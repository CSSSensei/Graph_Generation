#include <iostream>
#include "GraphRenderer.h"

GraphRenderer:: GraphRenderer(const std::string& temp_dir) : _temp_dir(temp_dir) {
    if (!std::filesystem::exists(_temp_dir)) {
        if (!std::filesystem::create_directories(_temp_dir)) {
            throw std::runtime_error("Couldn't create a directory: " + _temp_dir);
        }
    }
}

GraphRenderer::~GraphRenderer() {
    std::filesystem::remove_all(_temp_dir);
}

void GraphRenderer::render(const std::string& dot_content, const std::string& output_file) {
    std::cout << dot_content;
    std::string dot_file = _temp_dir + "/temp_graph.dot";
    std::ofstream out(dot_file);
    if (!out) {
        throw std::runtime_error("Couldn't create temporary DOT file.");
    }
    out << dot_content;
    out.close();

    std::string command = "dot -Tpng " + dot_file + " -o " + _temp_dir + "/"+  output_file;
    int result = system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("Error when executing the Graphviz command.");
    }

    // std::remove(dot_file.c_str());
}
