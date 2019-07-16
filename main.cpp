#include<SFML/Graphics.hpp>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<ctime>
#include<windows.h>

using namespace sf;
//using namespace std;
int n;
bool Live=false;
void Menu()
{
    bool Level=false;
    RenderWindow menu(VideoMode(500,500),"SFML");
    Texture NewGametex,Exittex,Easytex,Normaltex,Hardtex;
    NewGametex.loadFromFile("NewGame.png");
    Exittex.loadFromFile("Exit.png");
    Easytex.loadFromFile("Easy.png");
    Normaltex.loadFromFile("Normal.png");
    Hardtex.loadFromFile("Hard.png");
    Sprite NewGame(NewGametex),Easy(Easytex),Normal(Normaltex),Hard(Hardtex),Exit(Exittex);
    NewGame.setPosition(50,50);
    Easy.setPosition(100,100);
    Normal.setPosition(100,150);
    Hard.setPosition(100,200);
    Exit.setPosition(50,100);
    RectangleShape Background(Vector2f (500,500));
    Background.setFillColor(Color::Blue);
    Background.setPosition(0,0);
    bool menuIsOpen = true;
    while(menuIsOpen)
    {
        if(IntRect(50,50,100,50).contains(Mouse::getPosition(menu)))
        {
            NewGame.setColor(Color::Yellow);
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                Exit.setPosition(50,250);
                Level=true;
            }
        }
        if(IntRect(100,100,50,50).contains(Mouse::getPosition(menu)) && Mouse::isButtonPressed(Mouse::Left))
        {
            n=5;
            menuIsOpen=false;

        }
        if(IntRect(100,150,50,50).contains(Mouse::getPosition(menu)) && Mouse::isButtonPressed(Mouse::Left))
        {
            n=10;
            menuIsOpen=false;

        }
        if(IntRect(100,200,50,50).contains(Mouse::getPosition(menu)) && Mouse::isButtonPressed(Mouse::Left))
        {
            n=15;
            menuIsOpen=false;

        }
        if(IntRect(50,100,50,50).contains(Mouse::getPosition(menu))&& Mouse::isButtonPressed(Mouse::Left))
        {
            //Live=true;
            menu.close();
        }
        if(IntRect(50,250,50,50).contains(Mouse::getPosition(menu))&& Mouse::isButtonPressed(Mouse::Left))
        {
            //Live=true;
            menu.close();
        }
        menu.clear();
        menu.draw(Background);
        if(Level==true)
        {
            menu.draw(Easy);
                menu.draw(Normal);
                menu.draw(Hard);
        }
        menu.draw(NewGame);
        menu.draw(Exit);
        menu.display();
    }
}

int main()
{
    int xForRand[2];
    int yForRand[2];
    int x[2];
    int y[2];
    int temp=0;
    srand(time(0));
    int posx;
    int posy;
    bool yes=true;
    RenderWindow window(VideoMode(500,500),"SFML");
    RectangleShape shape[10][10];
    bool press[10][10];
                for(int i=0;i<10;++i)
                 {
                   for(int j=0;j<10;++j)
                     {
                         shape[i][j].setSize(Vector2f(50,50));
                         shape[i][j].setFillColor(Color(255,i*20,j*20));
                         shape[i][j].setPosition(50*i,50*j);
                         press[i][j]=false;
                     }
                   }
    std::cout<<"Press Space for bland rect"<<std::endl;
    Menu();
     while(window.isOpen())
     {
         Event evt;
         while(window.pollEvent(evt))
         {
             if(evt.type==Event::Closed/* && Live */|| Event::KeyPressed && evt.key.code==Keyboard::Escape)
             {
                 window.close();
             }
         }
         for(int i=0;i<10;++i)
                 {
                   for(int j=0;j<10;++j)
                     {
                         if(press[i][j]==false)
                         {
                         shape[i][j].setSize(Vector2f(50,50));
                        // shape[i][j].setFillColor(Color(255,20*i,20*j));
                         shape[i][j].setPosition(50*i,50*j);
                         shape[i][j].setOutlineThickness(0);
                         }
                     }
                   }
         Vector2i localCursor=Mouse::getPosition(window);
          if(localCursor.x>0 && localCursor.x<500 && localCursor.y>0 && localCursor.y<500 )
          {
              shape[localCursor.x/50][localCursor.y/50].setSize(Vector2f(40,40));
              shape[localCursor.x/50][localCursor.y/50].setOutlineThickness(5);
              shape[localCursor.x/50][localCursor.y/50].setOutlineColor(Color::Yellow);
              posx=localCursor.x/50;
              posy=localCursor.y/50;
          }
          if(Keyboard::isKeyPressed(Keyboard::Space))
          {
              for(int i=0;i<n;++i)
              {
                  xForRand[0]=rand()%10;
                  yForRand[0]=rand()%10;
                  xForRand[1]=rand()%10;
                  yForRand[1]=rand()%10;
                  shape[xForRand[0]][yForRand[0]].setFillColor(Color(255,20*xForRand[1],20*yForRand[1]));
                  shape[xForRand[1]][yForRand[1]].setFillColor(Color(255,20*xForRand[0],20*yForRand[0]));
                  Sleep(100);
              }
          }
          if(Mouse::isButtonPressed(Mouse::Left))
          {
              press[localCursor.x/50][localCursor.y/50]=true;
              temp++;
              Sleep(150);
          }
          if(temp==1 && yes==true)
              {
                  x[0]=localCursor.x/50;
                  y[0]=localCursor.y/50;
                  yes=false;
              }

          if(temp==2)
          {
              x[1]=localCursor.x/50;
              y[1]=localCursor.y/50;
              std::swap(shape[x[0]][y[0]],shape[x[1]][y[1]]);
              press[x[0]][y[0]]=false;
              press[x[1]][y[1]]=false;
              temp=0;
              yes=true;
          }
         window.clear();
         for(int i=0;i<10;++i)
         {
             for(int j=0;j<10;++j)
             {
                 window.draw(shape[i][j]);
             }
         }
         window.display();
     }
}
