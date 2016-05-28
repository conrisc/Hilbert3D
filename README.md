# Hilbert3D
[C] Program generating a 3D Hilbert curve

Program rysujący krzywą Hilberta w 3D. 
Generuje on plik .eps , który po przekonwertowaniu na .pdf przedstawia krzywą Hilberta w 3D.

Program przyjmuje 9 argumentów w podanej kolejności: <b>n s u d x y z aplha beta</b>
gdzie:
n — rząd krzywej 
s — rozmiar obrazka (w pt)
u — długość krawędzi sześcianu w który jest wpisana krzywa (w pt)
d — odegłość obserwatora od płaszczyzny rzutu (w pt)
(x,y,z) — współrzędne początku układu współrzędnych obiektu (w pt)
alpha — kąt obrotu (w stopniach) układu współrzędnych obiektu względem osi OX
beta — kąt obrotu (w stopniach) układu współrzędnych obiektu względem osi OY

Przykładowe dane wejściowe(jedna linijka == jeden przyklad):
4 500 150 400 0 0 10 32.5 -38
4 2000 800 1000 0 0 10 32.5 -38
3 500 150 220 50 50 50 -60 60
2 500 200 250 35 50 10 32.5 -38
5 500 180 200 0 0 5 0 0
5 500 200 210 0 0 5 10 -10

![example_1](img/SC-1.png)

![example_2](img/SC-2.png)
