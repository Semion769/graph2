#include "node.h"

Node::Node(int id, int x, int y)
    : QGraphicsEllipseItem(x-15, y-15, 30, 30), id_(id), idText_(nullptr)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    idText_ = new QGraphicsTextItem(QString::number(id_), this);
    idText_->setParent(this);
    idText_->setDefaultTextColor(Qt::white);
    idText_->setPos(x-idText_->boundingRect().width()/2, y-idText_->boundingRect().height()/2);





}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value){
    if (change == ItemPositionChange){
        emit positionChanged();
    }
    return QGraphicsItem::itemChange(change, value);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if (isSelected()) {
        painter->setPen(QPen(Qt::red, 2));
        painter->setBrush(QBrush(Qt::black));
    } else {
        painter->setPen(QPen(Qt::black));
        painter->setBrush(QBrush(Qt::black));
    }
    painter->drawEllipse(rect());
}


int Node::getId(){
    return id_;
}




void Node::addEdge(Edge* edge){
    nodeEdges_.push_back(edge);
}

void Node::removeEdge(Edge* edge){
    nodeEdges_.removeOne(edge);
}

QVector<Edge*> Node::getNodeEdges(){
    return nodeEdges_;
}

