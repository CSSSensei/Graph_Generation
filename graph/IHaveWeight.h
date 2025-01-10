#ifndef QT_PROJECT_IHAVEWEIGHT_H
#define QT_PROJECT_IHAVEWEIGHT_H

class IHaveWeight {
private:
    int _weight;

public:
    IHaveWeight(int weight) : _weight(weight) {}

    virtual int getWeight() const;
};

#endif //QT_PROJECT_IHAVEWEIGHT_H
