#ifndef QT_PROJECT_UI_H
#define QT_PROJECT_UI_H
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <cstdlib>
#include <QPixmap>
#include <QLineEdit>
#include <QCheckBox>
#include "GraphRenderer.h"
#include "ImageRenderer.h"
#include "../graph/Graph.h"
#include "../graph/Edge.h"
#include "../graph/Vertex.h"
#include "../graph/DirectedEdge.h"
#include "../algorithms/GraphColoring.h"
#include "../algorithms/GraphColoring.h"
#include "../test/test.h"

class UI : public QMainWindow {
    Q_OBJECT
public:
    UI(int argc, char *argv[], QApplication& app);
    ~UI();
    void run();

private:
    void addVertex();
    void addEdge();
    void removeVertex();
    void generateGraph();
    void coloringGraph();

private:
    QApplication& app_;
    std::unique_ptr<Graph<int>> graph_;
    bool is_graph_directed_;
    bool is_graph_bidirectional_;
    std::unique_ptr<GraphRenderer> graphRenderer_;

    // UI Components
    std::unique_ptr<QWidget> centralWidget_;
    std::unique_ptr<QHBoxLayout> mainLayout_;
    std::unique_ptr<QLabel> imageLabel_;
    std::unique_ptr<QVBoxLayout> menuLayout_;
    std::unique_ptr<QCheckBox> check_box_graph_directed_;
    std::unique_ptr<QCheckBox> check_box_graph_bidirectional_;
    std::unique_ptr<QHBoxLayout> layout_generate_graph_menu_;
    std::unique_ptr<QLabel> count_of_vertex_label_;
    std::unique_ptr<QLineEdit> enter_count_of_vertex_;
    std::unique_ptr<QLabel> probability_of_edge_;
    std::unique_ptr<QLineEdit> enter_probability_of_edge_;
    std::unique_ptr<QPushButton> button_generate_graph_;
    std::unique_ptr<QHBoxLayout> layout_add_vertex_line_;
    std::unique_ptr<QPushButton> button_add_vertex_;
    std::unique_ptr<QLineEdit> enter_line_vertex_name_;
    std::unique_ptr<QHBoxLayout> layout_add_edge_line_;
    std::unique_ptr<QPushButton> button_add_edge_;
    std::unique_ptr<QLineEdit> enter_line_edge_name_from_;
    std::unique_ptr<QLineEdit> enter_line_edge_name_to_;
    std::unique_ptr<QHBoxLayout> layout_remove_vertex_line_;
    std::unique_ptr<QPushButton> remove_vertex_;
    std::unique_ptr<QLineEdit> enter_line_remove_vertex_name_;
    std::unique_ptr<QPushButton> button_coloring_graph_;
};

class StartDialog : public QDialog {
    Q_OBJECT
public:
    StartDialog(QWidget *parent = nullptr) : QDialog(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QPushButton *testButton = new QPushButton("Провести тест", this);
        QPushButton *uiButton = new QPushButton("Открыть программу", this);

        layout->addWidget(testButton);
        layout->addWidget(uiButton);

        setLayout(layout);
        setWindowTitle("Выбор действия");

        connect(testButton, &QPushButton::clicked, this, &StartDialog::runTest);
        connect(uiButton, &QPushButton::clicked, this, &StartDialog::openUI);
    }

private slots:
    void runTest() {
        run_test();       // тест
        accept();         // закрыть диалог
    }

    void openUI() {
        close();
    }
};

#endif //QT_PROJECT_UI_H
