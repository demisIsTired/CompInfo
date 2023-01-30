/*
** EPITECH PROJECT, 2023
** B-PDG-300-LYN-3-1-PDGRUSH3-dylan.winter
** File description:
** nothingToSeeHere
*/

#include "IMonitorModule.hpp"
#include "IMonitorDisplay.hpp"

void setHideButtons(IMonitorDisplay *display)
{
    sf::RectangleShape hide1(sf::Vector2f(50, 10));
    sf::RectangleShape hide2(sf::Vector2f(50, 10));
    sf::RectangleShape hide3(sf::Vector2f(50, 10));
    sf::RectangleShape hide4(sf::Vector2f(50, 10));
    sf::RectangleShape hide5(sf::Vector2f(50, 10));
    sf::RectangleShape hide6(sf::Vector2f(50, 10));
    sf::RectangleShape hide7(sf::Vector2f(50, 10));
    sf::RectangleShape hide8(sf::Vector2f(50, 10));
    sf::RectangleShape hide9(sf::Vector2f(50, 10));

    hide1.setFillColor(sf::Color::White);
    hide2.setFillColor(sf::Color::White);
    hide3.setFillColor(sf::Color::White);
    hide4.setFillColor(sf::Color::White);
    hide5.setFillColor(sf::Color::White);
    hide6.setFillColor(sf::Color::White);
    hide7.setFillColor(sf::Color::White);
    hide8.setFillColor(sf::Color::White);
    hide9.setFillColor(sf::Color::White);

    hide1.setPosition(730, 10);
    hide2.setPosition(730, 110);
    hide3.setPosition(730, 210);
    hide4.setPosition(730, 310);
    hide5.setPosition(730, 410);
    hide6.setPosition(340, 10);
    hide7.setPosition(340, 110);
    hide8.setPosition(730, 610);
    hide9.setPosition(730, 510);


    display->hide1 = hide1;
    display->hide2 = hide2;
    display->hide3 = hide3;
    display->hide4 = hide4;
    display->hide5 = hide5;
    display->hide6 = hide6;
    display->hide7 = hide7;
    display->hide8 = hide8;
    display->hide9 = hide9;
}

void checkHide(char **argv, IMonitorDisplay *display)
{
    for (int i = 2; argv[i]; i++)
    {
        if (!(strcmp(argv[i], "-hideHostname")))
            display->hideHostname = 1;
        if (!(strcmp(argv[i], "-hideUsername")))
            display->hideUsername = 1;
        if (!(strcmp(argv[i], "-hideOs")))
            display->hideOs = 1;
        if (!(strcmp(argv[i], "-hideKernel")))
            display->hideKernel = 1;
        if (!(strcmp(argv[i], "-hideDate")))
            display->hideDate = 1;
        if (!(strcmp(argv[i], "-hideCPU")))
            display->hideCPU = 1;
        if (!(strcmp(argv[i], "-hideNCPU")))
            display->hideNCPU = 1;
        if (!(strcmp(argv[i], "-hideNet")))
            display->hideNet = 1;
        if (!(strcmp(argv[i], "-hideRam")))
            display->hideRam = 1;
    }
}

void getPress(IMonitorDisplay *display, sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (display->hide1.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideHostname)
            display->hideHostname = 1;
        else
            display->hideHostname = 0;
    }
    if (display->hide2.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideUsername)
            display->hideUsername = 1;
        else
            display->hideUsername = 0;
    }
    if (display->hide3.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideOs)
            display->hideOs = 1;
        else
            display->hideOs = 0;
    }
    if (display->hide4.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideKernel)
            display->hideKernel = 1;
        else
            display->hideKernel = 0;
    }
    if (display->hide5.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideDate)
            display->hideDate = 1;
        else
            display->hideDate = 0;
    }
    if (display->hide6.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideCPU)
            display->hideCPU = 1;
        else
            display->hideCPU = 0;
    }
    if (display->hide7.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideNCPU)
            display->hideNCPU = 1;
        else
            display->hideNCPU = 0;
    }
    if (display->hide8.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideNet)
            display->hideNet = 1;
        else
            display->hideNet = 0;
    }
    if (display->hide9.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        if (!display->hideRam)
            display->hideRam = 1;
        else
            display->hideRam = 0;
    }
}