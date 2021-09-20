# ant_movements

**Test Task**:


На бесконечной координатной сетке находится муравей. Муравей может
перемещаться на 1 клетку вверх (x,y+1), вниз (x,y-1), влево (x-1,y),
вправо (x+1,y), по одной клетке за шаг.

Клетки, в которых сумма цифр в координате X плюс сумма цифр в
координате Y больше чем 25 недоступны
муравью. Например, клетка с координатами (59, 79) недоступна, т.к.
5+9+7+9=30, что больше 25.

Сколько клеток может посетить муравей если его начальная позиция
(1000,1000), (включая начальную клетку).


**Requirements**: C++20-capable compiler

**Dependencies** for rendering: SFML

**Building:**

* mkdir build
* cd build
* cmake ..
* make



**Building with rendering:**

* mkdir build
* cd build
* cmake -DRENDER=1 ..
* make



**Launch:**

./bin/ant_movements
