#include <SFML/Graphics.hpp>
#include "Flappy.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800,800),"Flappy Bird",Style::Close);
    Texture t1;
    t1.loadFromFile("testMapa.png");

    Sprite mapa(t1);
    mapa.setTextureRect(IntRect(0,400,150,800));

    int Field[7];
    float timer=0, delay=0.009;

    for(int i=0; i<7; i++)
    {
        Field[i]=i*150;
    }

    Clock clock;

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
            timer=0;
        }

        for(int i=0;i<7;i++)
        {
            if(Field[i]==-250)
            {
                Field[i]=800;
            }
        }

        window.clear(Color::Black);
        for(int i=0;i<7;i++)
        {
            mapa.setPosition(Field[i],0);
            window.draw(mapa);
        }
        window.display();
    }
}
