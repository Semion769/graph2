# graph2
## установка
Для установки приложения выполните:
1. Склонируйте репозиторий: git clone https://github.com/Semion769/graph2.git
2. Откройте Qt Creator или другую среду разработки
3. Перейдите в папку graph2 и откройте файл task2.pro
4. Запустите проект

## Описание
Проект реализует граф с поиском кратчайшего пути от начальной до конечной точки. В проекте есть кнопки добавить вершину - добавляет вершину, удалить вершину - удаляет вершину(ы), 
добавить ребро - добавляет ребро(а), удалить ребро- удаляет ребро, кнопка запуска алгоритма и сброса графа. В проекте переопределены функции 
itemChange - для обновления ребер при изменении вершин и painter - для выделения ребер и вершин красным цветом. Вершины начинаются с 1. 
Ребра имеют вес. Результат алгоритма подсвечивает ребра крайшего пути красным цветом и на сцене появляется минимальное расстояние между двумя вершинами. 
Выделение 2 и больше вершин и ребер происходит через мышку и кнопу ctrl.

   

