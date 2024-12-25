#include "edge.h"
#include "graphwidget.h"
Edge::Edge(Node* v1, Node* v2, double weight)
    : QGraphicsLineItem(), startNode(v1), endNode(v2), weight_(weight)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(Qt::black));
    weightLabel_ = new QGraphicsTextItem(QString::number(weight));
    weightLabel_->setParentItem(this);
    QObject::connect(startNode, &Node::positionChanged, this, &Edge::updatePos);
    QObject::connect(endNode, &Node::positionChanged, this, &Edge::updatePos);

    updatePos();

}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if (isSelected()) {
        painter->setPen(QPen(Qt::red, 1));

    } else {
        painter->setPen(QPen(Qt::black));

    }
    painter->drawLine(line());
}

Node* Edge::start(){
    return startNode;
}

Node* Edge::end(){
    return endNode;
}

double Edge::getWeight(){
    return weight_;
}


void Edge::updatePos(){

    if (startNode && endNode){

        QPointF startPos = startNode->mapToScene(startNode->rect().center());
        QPointF endPos = endNode->mapToScene(endNode->rect().center());
        QPoint offset(7, 7);
        QLineF line(startPos+offset, endPos+offset);
        setLine(line);
        if (weightLabel_){
            QPointF textPos = line.center();
            weightLabel_->setPos(textPos);

        }

    }
}
