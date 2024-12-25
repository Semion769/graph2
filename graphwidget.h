#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <QVector>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QQueue>
#include <QHBoxLayout>
class Node;
class Edge;
class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void addEdge(Node* startNode, Node* endNode);


public slots:
    void addNode();
    void onaddEdge();
    void onRemoveNode();
    void onRemoveEdge();
    void onResetGraph();
    void checkAlg();

private:
    void djkstra(Node* startNode, Node* endNode);
    void findShortPath(std::map<Node*, double> dist, std::map<Node*, Node*> prev, Node* endNode, Node* startNode);

signals:
private:
    QGraphicsScene * scene;
    QVector<Node*> nodes_;
    QVector<Edge*> edges_;
    QGraphicsTextItem* pathItem_;


    int nodeId;

};

#endif // GRAPHWIDGET_H
