#include <SFML/Graphics.hpp>
#include <time.h>
#include "Flappy.h"
#include <iostream>

using namespace sf;
using namespace std;

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

    Font f1;
    f1.loadFromFile("arial.ttf");
    Text text;
    text.setFont(f1);
    text.setFillColor(Color::Black);

    int Field[7];
    int Puzzle[7];
    float timer=0, delay=0.009;
    unsigned int score=0, highscore=getHighscore();

    for(int i=0; i<7; i++)
    {
        Field[i]=i*150;
        Puzzle[i]= rand()%570;
    }

    Clock clock;

    int x=100, y=300;
    float dx=0, dy=0;
    char goNext = NULL;
    bool isJump=false, gameOver=false, isPause=false, next=false, next1=false;

    y=597-Puzzle[1];

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
                if(isPause==false)
                    Field[i]+=-1;
            }
            if(Keyboard::isKeyPressed(Keyboard::Right) && isPause==false) x+=3;
            if(Keyboard::isKeyPressed(Keyboard::Left) && isPause==false) x-=3;
            if(Keyboard::isKeyPressed(Keyboard::Space) && isPause==false) isJump=true;

            dy+=0.2;
            y+=dy;
            if(y>770) y=769;
            if(y<30) y=31;
            if(isJump)
            {
                dy=-4;
                isJump=false;
            }
            next1=false;
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

        for(int i=0;i<6;i++)
        {
            if(i%2==1)
            {
                if(x>=(Field[i]+26) && x<=(Field[i]+118))
                {
                    if(y>504-Puzzle[i] && y<690-Puzzle[i])
                    {
                        goNext = i;
                    }
                    else
                        gameOver=true;
                }
            }
        }

        if(!(goNext==NULL))
        {
            int i=goNext;
            if(x>=(Field[i]+118)&&x<=(Field[i]+119))
            {
                if(next1==false)
                {
                    next=true;
                }
            }
            goNext=NULL;
        }

        if(next)
        {
            score+=1;
            next=false;
            next1=true;
        }

        if(gameOver)
        {
            isPause=true;
            if(highscore<score)
            {
                setNewHighscore(score);
                //add game over screen
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

        unsigned int hScore = static_cast<unsigned int>(score);
        string _str = to_string(hScore);
        text.setString(_str);
        text.setCharacterSize(20);
        text.setPosition(0.f,0.f);
        window.draw(text);

        ptak.setPosition(x,y);
        window.draw(ptak);
        window.display();
    }
}
