#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QVariant>
#include <QPainter>

class Edge;
class Node : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit Node(int id, int x, int y);

    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);
    QVector<Edge*> getNodeEdges();
    int getId();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int id_;
    QGraphicsTextItem* idText_;
    QVector<Edge*> nodeEdges_;




signals:
    void positionChanged();
    void clicked(Node* node);

};

#endif // NODE_H
