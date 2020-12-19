<img src="https://static.tildacdn.com/tild3333-3362-4731-a261-323535333532/_.svg"  alt="Логотип МГУ" height="100" />

# Разработка параллельной версии программы для вычисления определенного интеграла с использованием метода трапеций.

Для выполнения практических заданий используются суперкомпьютерные вычислительные ресурсы факультета ВМК - Bluegene/P и Polus.
http://hpc.cs.msu.ru

## В каждой задаче требуется:
1) Реализовать параллельную версию предложенного алгоритма с использованием технологий OpenMP и MPI (DVMH, OpenACC).
2) Начальные параметры для задачи подбираются таким образом, чтобы:
- Задача помещалась в оперативную память одного процессора.
- Время решения задачи было в примерном диапазоне 5 сек - 15 минут.
3) Исследовать масштабируемость полученной параллельной программы: построить графики зависимости времени исполнения от числа ядер/процессоров для различного объёма входных данных.
Для каждого набора входных данных найти количество ядер/процессоров, при котором время выполнения задачи перестаёт уменьшаться.
Оптимальным является построение трёхмерного графика: по одной из осей время работы программы, по другой - количество ядер/процессоров и по третьей - объём входных данных.
Каждый прогон программы с новыми параметрами рекомендуется выполнять несколько раз с последующим усреднением результата (для избавления от случайных выбросов).
Для замера времени рекомендуется использовать вызовы функции omp_get_wtime или MPI_Wtime, общее время работы должно определяться временем самого медленного из процессов/нитей.
Количество ядер/процессоров рекомендуется задавать в виде p=2n, n=0, 1, 2, ... , k, где k определяется доступными ресурсами.
4) Определить основные причины недостаточной масштабируемости программы при максимальном числе используемых ядер/процессоров.
5) Сравнить эффективность OpenMP и MPI-версий параллельной программы.
6) Подготовить отчет о выполнении задания, включающий: описание реализованного алгоритма, графики зависимости времени исполнения от числа ядер/процессоров для различного объёма входных данных, текст программы.


## Требуется:
1.	Реализовать параллельные алгоритм нахождения определенного интеграла методом трапеций с помощью технологий параллельного программирования OpenMP и MPI. 
2.	Сравнить их эффективность. 
3.	Исследовать масштабируемость полученных программ и построить графики зависимости времени выполнения программ от числа используемых ядер и объёма входных данных.


## Алгоритм нахождения интеграла прост:
1. Разбиваем весь интервал интегрирования на n отрезков
2. Для каждого такого отрезка посчитаем площадь трапеции
3. Суммируем полученные площади со знаком +/- в зависимости от расположения трапеции

## Описание параллельного алгоритма
Ключевая идея заключается в подсчете площади каждой отдельной трапеции независимо от других на разных потоках/узлах.
Для варьирования объема вычислений будем изменять величину n (количество трапеций).

В OpenMP версии программы использую #pragma omp parallel reduction.


## Выводы
Выполнена работа по разработке параллельной версии алгоритма алгоритма нахождения определенного интеграла методом трапеций. 
Изучены технологии написания параллельных алгоритмов OpenMP и MPI. Проанализировано время выполнения алгоритмов на различных вычислительных системах (Polus, Bluegene).
Технология OpenMP оказалась очень удобной в использовании и быстрой в освоении, причем дает колоссальный прирост производительности на рассчитанных на многопоточные вычисления системах, в том числе и на персональных компьютерах. 
MPI можно назвать более низкоуровневой технологией: разработка MPI-программы знакомит с основами взаимодействия вычислительных узлов суперкомпьютера. При этом MPI заточена именно на многопроцессорные системы и наибольшую скорость работы показала именно MPI-реализация, запущенная на наибольшем числе вычислителей суперкомпьютера Bluegene.

