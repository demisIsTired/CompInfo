/*
** EPITECH PROJECT, 2023
** B-PDG-300-LYN-3-1-PDGRUSH3-dylan.winter
** File description:
** sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include "Network.hpp"

class IMonitorDisplay
{
public:
    IMonitorDisplay() {}
    ~IMonitorDisplay()
    {
        if (font != nullptr)
            delete font;
    };

    void addObject(sf::RectangleShape object)
    {
        objects.push_back(object);
    }

    void addSprite(sf::Sprite sprite)
    {
        sprites.push_back(sprite);
    }

    void addText(sf::Text text)
    {
        texts.push_back(text);
    }

    void draw(sf::RenderWindow &window, IMonitorDisplay *display)
    {
        for (auto &object : objects)
            window.draw(object);
        if (!display->hideNCPU)
            for (auto &text : texts)
                window.draw(text);
        for (auto &dot : dots)
            window.draw(dot);
        for (auto &dot : dotsRed)
            window.draw(dot);
        // window.draw(hide1);
        // window.draw(hide2);
        // window.draw(hide3);
        // window.draw(hide4);
        // window.draw(hide5);
        // window.draw(hide6);
        // window.draw(hide7);
        // window.draw(hide8);
        // window.draw(hide9);
    }

    void setFont(sf::Font *my_font)
    {
        font = my_font;
    }

    sf::Font *getFont()
    {
        return font;
    }

    sf::Text setText(sf::Text text, sf::Font *my_font, int x, int y, std::string string, int size)
    {
        text.setFont(*my_font);
        text.setPosition(x, y);
        text.setString(string);
        text.setCharacterSize(size);
        return text;
    }

    void displayBox(sf::RenderWindow &window, double percent, int x, int y)
    {
        sf::RectangleShape rect(sf::Vector2f(200, 50));
        sf::RectangleShape inside(sf::Vector2f(int(200 * (double(double(percent) / double(100)))), 48));

        rect.setPosition(x, y);
        rect.setOutlineThickness(1);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        inside.setPosition(x + 1, y + 1);
        inside.setFillColor(sf::Color::Red);

        window.draw(rect);
        window.draw(inside);
    }

    int display_background(sf::RenderWindow &window, int index, int x, int y)
    {
        sf::Sprite sprite(texture);
        int frameWidth = 600;
        int frameHeight = 800;
        int frameCount = 48;

        int pushY = (index / 6) * frameHeight;
        int pushX = frameWidth * (index % 6);

        sprite.setPosition(sf::Vector2f(0, 0));
        sprite.setColor(sf::Color(255, 255, 255, 80));
        sprite.setTextureRect(sf::IntRect(pushX, pushY, frameWidth, frameHeight));
        sprite.setScale(double(x) / double(frameWidth), double(y) / double(frameHeight));
        window.draw(sprite);

        index = (index + 1) % frameCount;
        return index;
    }

    void displayRamBox(sf::RenderWindow &window, double percent, int x, int y)
    {
        int widthUsed = int(350 * (double(double(percent) / double(100))));
        int widthFree = int(350 * (double(double(100 - percent) / double(100))));
        sf::RectangleShape rect(sf::Vector2f(350, 50));
        sf::RectangleShape insideUsed(sf::Vector2f(int(350 * (double(double(percent) / double(100)))), 50));
        sf::RectangleShape insideFree(sf::Vector2f(int(350 * (double(double(100 - percent) / double(100)))), 50));
        sf::Color skyBlue(0x89, 0xAB, 0xE3);
        sf::Color bubblegumPink(0xEA, 0x73, 0x8D);

        rect.setPosition(x, y);
        rect.setOutlineThickness(1);
        rect.setFillColor(sf::Color::Black);
        rect.setOutlineColor(sf::Color::White);
        insideUsed.setPosition(x + 1, y + 1);
        insideUsed.setFillColor(sf::Color::Red);
        insideFree.setPosition(x + 1 + widthUsed, y + 1);
        insideFree.setFillColor(sf::Color::Green);

        window.draw(rect);
        window.draw(insideUsed);
        window.draw(insideFree);
    }

    const int THRESHOLD = 410;
    const int X_POSITION = 700;
    const float RADIUS = 1.f;

    std::vector<sf::CircleShape> dots;
    std::vector<sf::CircleShape> dotsRed;

    void addPoint(int y)
    {
        sf::CircleShape dot(RADIUS);
        dot.setFillColor(sf::Color::Blue);
        dot.setPosition(X_POSITION - RADIUS, y - RADIUS);
        dots.push_back(dot);
    }

    void addPointRed(int y)
    {
        sf::CircleShape dot(RADIUS);
        dot.setFillColor(sf::Color::Red);
        dot.setPosition(X_POSITION - RADIUS, y - RADIUS);
        dotsRed.push_back(dot);
    }



    void reduceXPositions()
    {
        for (int i = 0; i < dots.size(); i++)
        {
            dots[i].move(-10.f, 0.f);
            if (dots[i].getPosition().x < THRESHOLD)
            {
                dots.erase(dots.begin() + i);
                i--;
            }
        }
        for (int i = 0; i < dotsRed.size(); i++)
        {
            dotsRed[i].move(-10.f, 0.f);
            if (dotsRed[i].getPosition().x < THRESHOLD)
            {
                dotsRed.erase(dotsRed.begin() + i);
                i--;
            }
        }
    }

    std::vector<sf::RectangleShape> objects;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> texts;
    sf::RectangleShape hide1;
    sf::RectangleShape hide2;
    sf::RectangleShape hide3;
    sf::RectangleShape hide4;
    sf::RectangleShape hide5;
    sf::RectangleShape hide6;
    sf::RectangleShape hide7;
    sf::RectangleShape hide8;
    sf::RectangleShape hide9;

    sf::RenderWindow window;
    sf::Texture texture;
    sf::Font *font = nullptr;
    int hideHostname = 0;
    int hideUsername = 0;
    int hideOs = 0;
    int hideKernel = 0;
    int hideDate = 0;
    int hideCPU = 0;
    int hideNCPU = 0;
    int hideNet = 0;
    int hideRam = 0;
};

void sfml(char **argv);
void setHideButtons(IMonitorDisplay *display);
void checkHide(char **argv, IMonitorDisplay *display);
void getPress(IMonitorDisplay *display, sf::RenderWindow &window);
#endif /* !SFML_HPP_ */