#include <SFML/Graphics.hpp>
#include <time.h>
#include "Flappy.h"

using namespace sf;

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(800,800),"Flappy Bird",Style::Close);
    Texture t1, t2, t3;
    t1.loadFromFile("Mapa.png");
    t2.loadFromFile("Tlo.png");
    t3.loadFromFile("Ptak.png");

    Sprite mapa(t1);
    Sprite tlo(t2);
    Sprite ptak(t3);
    ptak.setOrigin(30,30);

    int Field[7];
    int Puzzle[7];
    float timer=0, delay=0.01;

    for(int i=0; i<7; i++)
    {
        Field[i]=i*150;
        Puzzle[i]= rand()%600;
    }

    Clock clock;

    int x=100, y=300;
    float dx=0, dy=0;
    bool isJump=false;

    while(window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type == Event::Closed)
            {
                window.close();
            }
        }

        if(Tick(timer, delay))
        {
            for(int i=0;i<7;i++)
            {
                Field[i]+=-1;
            }
            if(Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
            if(Keyboard::isKeyPressed(Keyboard::Left)) x-=3;
            if(Keyboard::isKeyPressed(Keyboard::Space)) isJump=true;

            dy+=0.2;
            y+=dy;
            if(y>770) y=769;
            if(y<30) y=31;
            if(isJump)
            {
                dy=-4;
                isJump=false;
            }
            timer=0;
        }

        for(int i=0;i<7;i++)
        {
            if(Field[i]==-250)
            {
                Field[i]=800;
                Puzzle[i]=rand()%600;
            }
        }

        window.clear(Color::Black);
        for(int i=0;i<7;i++)
        {
           if(i%2==0)
           {
               tlo.setPosition(Field[i],0);
               tlo.setTextureRect(IntRect(0,Puzzle[i],150,800));
               window.draw(tlo);
           }
           if(i%2==1)
           {
                   mapa.setPosition(Field[i],0);
                   mapa.setTextureRect(IntRect(0,Puzzle[i],150,800));
                   window.draw(mapa);
           }
        }
        ptak.setPosition(x,y);
        window.draw(ptak);
        window.display();
    }
}
