#ifndef QT_PROJECT_IEXECUTABLE_H
#define QT_PROJECT_IEXECUTABLE_H
#include <string>
#include "../graph/Graph.h"
#include "../graph/Edge.h"
#include "../graph/Vertex.h"

template <class T>
class Graph;

template <class T>
class IExecutable {
public:
    virtual ~IExecutable() = default;

    virtual void execute(Graph<T>& graph) = 0;

};
#endif //QT_PROJECT_IEXECUTABLE_H
