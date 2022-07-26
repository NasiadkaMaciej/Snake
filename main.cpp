#include <SFML/Graphics.hpp>
#include <iostream>

#define up		0
#define right	1
#define down	2
#define left	3

sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
int blockSize=32;
int N=desktopMode.width/blockSize, M=desktopMode.height/blockSize;

int dir=right, length=4, speed=10;
struct Snake{
	int x,y;
}snakeBlock[100];

struct Fruit{
	int x,y;
}f;

void Tick(){
	for (int i=length; i>0; i--){
		snakeBlock[i].x=snakeBlock[i-1].x;
		snakeBlock[i].y=snakeBlock[i-1].y;
	}

	switch (dir){
	case up:	snakeBlock[0].y-=1;	break;
	case right:	snakeBlock[0].x+=1;	break;
	case down:	snakeBlock[0].y+=1;	break;
	case left:	snakeBlock[0].x-=1;	break;
	default:	break;
	}

	if((snakeBlock[0].x==f.x) && (snakeBlock[0].y==f.y)){
		length++;
		f.x=rand() % N;
		f.y=rand() % M;
	}

	if(snakeBlock[0].x>=N) snakeBlock[0].x=0;
	else if(snakeBlock[0].x<0) snakeBlock[0].x=N;
	if(snakeBlock[0].y>=M) snakeBlock[0].y=0;
	else if(snakeBlock[0].y<0) snakeBlock[0].y=M;

	for(int i=1; i<length;i++)
		if((snakeBlock[0].x==snakeBlock[i].x) && (snakeBlock[0].y==snakeBlock[i].y))
			length=i;
}

int changeDir(int direction){
	if((direction==left && dir==right) || (direction==right && dir==left))return dir;
	else if((direction==up && dir==down) || (direction==down && dir==up)) return dir;
	else{ dir=direction; return direction;}
}

void toggleSpeed(int s){
	if(s==up) speed=30;
	if(s==down) speed=10;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height, desktopMode.bitsPerPixel), "Snake - Macieson", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	srand(time(NULL));

	sf::Texture tBg, tSnake, tApple;
	tBg.loadFromFile("bg.png");
	tSnake.loadFromFile("snake.png");
	tApple.loadFromFile("apple.png");
	sf::Sprite sBg(tBg), sSnake(tSnake), sApple(tApple);

	sBg.setScale(2,2);
	sSnake.setScale(2,2);
	sApple.setScale(2,2);

	sf::Clock clock;
	float prevTime, time;

	f.x=rand() % N;
	f.y=rand() % M;

	snakeBlock[0].x=rand() % N;
	snakeBlock[0].y=rand() % M;

    while (window.isOpen())
    {
		time=clock.getElapsedTime().asSeconds();
		clock.restart();
		time+=prevTime;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::KeyPressed)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))		toggleSpeed(up);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))		toggleSpeed(down);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::W))		changeDir(up);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::D))		changeDir(right);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::S))		changeDir(down);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::A))		changeDir(left);
        }

		if(time*speed>1){
			time=0; Tick();
		}

        window.clear();
		for(int i=0; i<N;i++)
			for(int j=0; j<M; j++){
				sBg.setPosition(i*blockSize, j*blockSize);
				window.draw(sBg);
			}
		for(int i=0; i<length; i++){
			sSnake.setPosition(snakeBlock[i].x*blockSize, snakeBlock[i].y*blockSize);
			window.draw(sSnake);
		}
		sApple.setPosition(f.x*blockSize, f.y*blockSize);
		window.draw(sApple);
        window.display();
		prevTime=time;
    }
    return 0;
}