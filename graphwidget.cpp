#include "graphwidget.h"
#include "node.h"
#include "edge.h"
#include <QInputDialog>
#include <limits>
#include <queue>
#include <QString>
#include <QList>
#include <QSet>

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget{parent}, nodeId(0), pathItem_(nullptr)
{
    scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);

    QPushButton* addButtonVertex = new QPushButton("Добавить вершину", this);
    QPushButton* removeButtonVertex = new QPushButton("Удалить вершину", this);
    QPushButton* addButtonEdge = new QPushButton("Добавить ребро", this);
    QPushButton* removeButtonEdge = new QPushButton("Удалить ребро", this);
    QPushButton* runDjkstra = new QPushButton("Запустить алгоритм дейкстры", this);
    QPushButton* resetGraph = new QPushButton("Сброс графа", this);


    QVBoxLayout* vbox = new QVBoxLayout(this);
    QHBoxLayout* hbox = new QHBoxLayout();




    vbox->addWidget(view);
    hbox->addWidget(addButtonVertex);
    hbox->addWidget(removeButtonVertex);
    hbox->addWidget(addButtonEdge);
    hbox->addWidget(removeButtonEdge);
    hbox->addWidget(runDjkstra);
    hbox->addWidget(resetGraph);
    vbox->addLayout(hbox);
    setLayout(vbox);

    QObject::connect(addButtonVertex, &QPushButton::clicked, this, &GraphWidget::addNode);
    QObject::connect(addButtonEdge, &QPushButton::clicked, this, &GraphWidget::onaddEdge);
    QObject::connect(removeButtonVertex, &QPushButton::clicked, this, &GraphWidget::onRemoveNode);
    QObject::connect(removeButtonEdge, &QPushButton::clicked, this, &GraphWidget::onRemoveEdge);
    QObject::connect(resetGraph, &QPushButton::clicked, this, &GraphWidget::onResetGraph);
    QObject::connect(runDjkstra, &QPushButton::clicked, this, &GraphWidget::checkAlg);



}



void GraphWidget::addNode(){
    int x = QRandomGenerator::global()->bounded(0, 400);
    int y = QRandomGenerator::global()->bounded(0, 400);


    nodeId++;
    Node* node = new Node(nodeId, x, y);
    scene->addItem(node);
    nodes_.push_back(node);




}

void GraphWidget::onaddEdge(){

    QList<QGraphicsItem*> selectItems = scene->selectedItems();  // почему в моем Qt я могу использовать QVector без явной конверсии в QList?

    if (selectItems.size()<2){
        QMessageBox::warning(this, "error", "Выбрано меньше 2 вершин");
    }
    else if (selectItems.size() == 2){
        Node* startNode = dynamic_cast<Node*> (selectItems[0]);
        Node* endNode = dynamic_cast<Node*> (selectItems[1]);

        if (!startNode || !endNode){
            QMessageBox::warning(this, "Ошибка", "Выбрано меньше 2 вершин");
            return;
        }
        bool ok;
        double weight = QInputDialog::getDouble(this, "Добавить вес", "Введите вес", 1.0, 0.0, 100.0, 2, &ok);
        if (!ok){
            return;
        }
        if (startNode && endNode){
            for (Edge* edge:edges_){
                if ((edge->start() == startNode && edge->end() == endNode) || (edge->start() == endNode && edge->end() == startNode)){
                    QMessageBox::warning(this, "ошибка", "ребро уже было добавлено");
                    return;
                }
            }
            Edge* edge = new Edge(startNode, endNode, weight);
            scene->addItem(edge);
            edges_.push_back(edge);
            startNode->addEdge(edge);
            endNode->addEdge(edge);
            scene->clearSelection();
            scene->update();




        }

    }else{
        QMessageBox::warning(this, "Ошибка", "Выбрано больше 2 вершин");
    }
}



void GraphWidget::onRemoveNode(){
    if (scene->selectedItems().isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Ничего не выбрано");

    }

    QList<QGraphicsItem*> selectedItems = scene->selectedItems();

    QSet<Node*> nodesToRemove;
    for (QGraphicsItem* item:selectedItems){
        Node* node = dynamic_cast<Node*>(item);
        if (!node){

            QMessageBox::warning(this, "Ошибка", "Вершины не выбраны");
            return;

        }
        else {
            nodesToRemove.insert(node);
        }


    }

    for (Node* node:nodesToRemove){
        QVector<Edge*> edgesToRemove = node->getNodeEdges();
        for (Edge* edge:edgesToRemove){

            edges_.removeOne(edge);


            Node* otherNode = (edge->start() == node) ? edge->end():edge->start();
            if (otherNode){
                otherNode->removeEdge(edge);
            }
            scene->removeItem(edge);
            delete edge;
        }
        nodes_.removeOne(node);
        scene->removeItem(node);
        delete node;
    }

}

void GraphWidget::onRemoveEdge(){
    if (scene->selectedItems().isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Ничего не выбрано");
        return;
    }


     QList<QGraphicsItem*> selectedItems = scene->selectedItems();


    QSet<Edge*> edgesToRemove;
    for (QGraphicsItem* item:selectedItems){
        Edge* edge = dynamic_cast<Edge*>(item);
        if (!edge){
            QMessageBox::warning(this, "Ошибка", "Ребра не выбраны");
            return;
        }
        else{
            edgesToRemove.insert(edge);
        }
    }
    for (Edge* edge:edgesToRemove){
        Node* nodeStart = edge->start();
        Node* nodeEnd = edge->end();
        if (nodeStart){
            nodeStart->removeEdge(edge);

        }
        if (nodeEnd){
            nodeEnd->removeEdge(edge);
        }
        edges_.removeOne(edge);
        delete edge;
    }


}
void GraphWidget::onResetGraph(){
    for (Edge* edge: edges_){
        scene->removeItem(edge);
        delete edge;
    }
    edges_.clear();
    for (Node* node:nodes_){
        scene->removeItem(node);
        delete node;
    }



    if (pathItem_){
        scene->removeItem(pathItem_);
        delete pathItem_;
        pathItem_ = nullptr;
    }

    nodes_.clear();
    nodeId = 0;


}



void GraphWidget::checkAlg(){
    bool startOk, endOk;
    int startNodeId = QInputDialog::getInt(this, "Начальная вершина", "Введите начальную вершину", 1, 0, 1000, 0, &startOk);
    int endNodeId = QInputDialog::getInt(this, "Конечная вершина", "Введите конечную вершину", 1, 0, 1000, 0, &endOk);
    if (!startOk || !endOk){

        QMessageBox::warning(this, "Ошибка", "Неверная первая или последняя вершина");
        return;
    }else{
        Node* startNode = nullptr;
        Node* endNode = nullptr;
        for (Node* node:nodes_){

            if (!startNode || !endNode){

                if (node->getId() == startNodeId){
                    startNode = node;

                }
                if (node->getId() == endNodeId){
                    endNode = node;

                }
            }

        }
        if (!startNode || !endNode){
            QMessageBox::warning(this, "Ошибка", "Первой или последней вершины не существует");
            return;
        }
        djkstra(startNode, endNode);
    }
}


void GraphWidget::djkstra(Node* startNode, Node* endNode){


    std::map<Node*, double> dist;
    std::map<Node*, Node*> prev;
    QQueue<Node*> queue;
    for (Node* node:nodes_){
        dist[node] = std::numeric_limits<double>::infinity();
        prev[node] = nullptr;
    }
    dist[startNode] = 0;
    queue.enqueue(startNode);
    while(!queue.isEmpty()){
        Node* u = queue.dequeue();
        if (u == endNode) break;
        for (Edge* edge: u->getNodeEdges()){

            Node* v = (edge->start() == u)?edge->end():edge->start();
            if (!v) continue;
            double weight = edge->getWeight();
            double alt = dist[u]+weight;
            if (alt<dist[v]){
                dist[v] = alt;
                prev[v] = u;
                queue.enqueue(v);
            }
        }
    }
    findShortPath(dist, prev, endNode, startNode);



}


void GraphWidget::findShortPath(std::map<Node*, double> dist, std::map<Node*, Node*> prev, Node* endNode, Node* startNode ){
    if (pathItem_){
        scene->removeItem(pathItem_);
        delete pathItem_;
        pathItem_ = nullptr;
    }
    if (dist[endNode]!=std::numeric_limits<double>::infinity()){
        double pathLen = dist[endNode];

        QString pathText = QString("Длина пути:%1").arg(pathLen);
        pathItem_ = new QGraphicsTextItem(pathText);
        Node* current = endNode;
        while(current!=startNode){
            Node* p = prev[current];
            for (Edge* edge:p->getNodeEdges()){
                if ((edge->start() == current && edge->end() == p)||(edge->start() == p && edge->end() == current )){
                    edge->setSelected(true);
                    break;
                }else{
                    edge->setSelected(false);
                }
            }
            current = p;
        }
        scene->addItem(pathItem_);

    }else{
        QMessageBox::warning(this, "Ошибка", "Пути не существует");
    }
}




