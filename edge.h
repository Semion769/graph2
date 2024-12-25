#ifndef EDGE_H
#define EDGE_H

#include <QWidget>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPainter>
#include "node.h"


class Edge : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit Edge(Node* v1, Node* v2, double weight);
    void updatePos();
    Node* start();
    Node* end();

    double getWeight();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Node* startNode;
    Node* endNode;
    QGraphicsTextItem* weightLabel_;
    double weight_;

signals:
};

#endif // EDGE_H
