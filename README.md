# Snake
```
 _____             _        
/  ___|           | |       
\ `--. _ __   __ _| | _____ 
 `--. \ '_ \ / _` | |/ / _ \
/\__/ / | | | (_| |   <  __/
\____/|_| |_|\__,_|_|\_\___|

````
![Alt text](https://maciej.ml/projects/Snake/Snake.png)

Snake clone made in C++ with SFML.   
It's written rather poorly by enthusiast teenager.   

Eat apples and make your snake longer. But be careful not to bite yourself.   
Have a nice game!   

Arrows/WASD - moving   
Q - slow down   
E - speed up   

## Building
For Linux
````shell
g++ main.cpp -o Snake -lsfml-graphics -lsfml-window -lsfml-system
````
For Windows (Probably, I haven't tried yet)
````shell
g++ main.cpp -o Snake.exe
````
You need SFML installed do build this game

## To-Do
* [ ] Biting yourself cuts your snake in bitten place
* [ ] Displaying points and speed
* [ ] Better graphics
