/*
** EPITECH PROJECT, 2023
** B-PDG-300-LYN-3-1-PDGRUSH3-dylan.winter
** File description:
** sfml
*/

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "IMonitorDisplay.hpp"
#include "IMonitorModule.hpp"


float mapValueToRange(float value, float inMin, float inMax, float outMin, float outMax) {
  return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

void update_text(sf::RenderWindow &window, IMonitorDisplay *monitorDisplay, IMonitorModule module)
{
    sf::Text hostname;
    sf::Text username;
    sf::Text os;
    sf::Text kernel;
    sf::Text date;
    sf::Text cpuModel;
    sf::Text cpuFrequency;
    sf::Text cpuActivity;
    sf::Text ramInfo;
    sf::Text cpuNAcitvity;
    std::string ram;
    sf::Text netInfo;
    sf::Text percentage;
    std::string net;

    hostname = monitorDisplay->setText(hostname, monitorDisplay->getFont(), 410, 150, "Hostname: " + module.getHostname(), 15);
    username = monitorDisplay->setText(username, monitorDisplay->getFont(), 410, 175, "Username: " + module.getUsername(), 15);
    os = monitorDisplay->setText(os, monitorDisplay->getFont(), 410, 200, "Os: " + module.getOSName(), 15);
    kernel = monitorDisplay->setText(kernel, monitorDisplay->getFont(), 410, 225, "Kernel: " + module.getKernelVersion(), 15);
    date = monitorDisplay->setText(date, monitorDisplay->getFont(), 410, 250, "Date & Time: " + module.getDateTime(), 15);
    cpuModel = monitorDisplay->setText(cpuModel, monitorDisplay->getFont(), 10, 20, "CPU Model: " + module.getCPUModel(), 15);
    cpuFrequency = monitorDisplay->setText(cpuFrequency, monitorDisplay->getFont(), 10, 40, "CPU Frequency: " + module.getCPUFrequency(), 15);
    cpuActivity = monitorDisplay->setText(cpuActivity, monitorDisplay->getFont(), 10, 60, "CPU: " + std::to_string(int(module.getCPUActivity())) + "%", 15);
    module.getNetwork();
    ram = "RAM Total Size (Bytes): ";
    ram += module.getRAMTotalSize();
    ram += "\n\nRAM Used Size (Bytes): ";
    ram += module.getRAMUsedSize();
    // ram += "      ";
    // ram += module.getPourcentage(module.getRAMUsedSize(), module.getRAMTotalSize());
    // ram += "%";
    ram += "\n\nRAM Unused Size (Bytes): ";
    ram += module.getRAMUnusedSize();
    // ram += "      ";
    // ram += module.getPourcentage(module.getRAMUnusedSize(), module.getRAMTotalSize());
    // ram += "%";
    net += "Network:\n\n";
    net += "Receiveing (Bytes/s)   ";
    net += std::to_string(module.stats.currentRec);
    // net += "Packets Received: ";
    // net += std::to_string(module.stats.rx_packets);
    net += "\n\nSending (Bytes/s)            ";
    net += std::to_string(module.stats.currentSent);
    // net += "\nPackets Transmitted: ";
    // net += std::to_string(module.stats.tx_packets);
    long dif = module.stats.currentSent - module.stats.prevSent;
    if (monitorDisplay->dots.size() + monitorDisplay->dotsRed.size() < 4500) {
        for (int i = 0; i < std::min(int(abs(dif)), 10000); i += 500) {
            if (dif < 0) {
                monitorDisplay->addPoint(mapValueToRange(float(module.stats.currentSent - (i + 1)), 0.00, 80000.00, 780, 710));
            } else {
                monitorDisplay->addPoint(mapValueToRange(float(module.stats.currentSent + (i + 1)), 0.00, 80000.00, 780, 710));
            }
        }
        monitorDisplay->addPoint(mapValueToRange(float(module.stats.currentSent), 0.00, 80000.00, 780, 710));
        dif = module.stats.currentRec - module.stats.prevRec;
        for (int i = 0; i < std::min(int(abs(dif)), 10000); i += 500) {
            if (dif < 0) {
                monitorDisplay->addPointRed(mapValueToRange(float(module.stats.currentRec - (i + 1)), 0.00, 80000.00, 780, 710));
            } else {
                monitorDisplay->addPointRed(mapValueToRange(float(module.stats.currentRec + (i + 1)), 0.00, 80000.00, 780, 710));
            }
        }
        monitorDisplay->addPointRed(mapValueToRange(float(module.stats.currentRec), 0.00, 80000.00, 780, 710));
    }
    // printf("%ld\n", dif);
    
    ramInfo = monitorDisplay->setText(ramInfo, monitorDisplay->getFont(), 410, 430, ram, 14);
    netInfo = monitorDisplay->setText(netInfo, monitorDisplay->getFont(), 410, 590, net, 14);
    if (!monitorDisplay->hideNCPU)
        for (int i = 0; i < module.getCores(); i++)
        {
            double per = module.getNCPUActivity(i);
            cpuNAcitvity = monitorDisplay->setText(cpuActivity, monitorDisplay->getFont(), 10, 100 * (i + 1) + 50, std::to_string(int(per)) + "%", 20);
            window.draw(cpuNAcitvity);
            monitorDisplay->displayBox(window, per, 150, 100 * (i + 1) + 30);
        }

    std::string percent_str = module.getPourcentage(module.getRAMUsedSize(), module.getRAMTotalSize());
    double percent_double = std::stod(percent_str);
    int per = int(350 * (double(double(percent_double) / double(100))));
    percentage = monitorDisplay->setText(percentage, monitorDisplay->getFont(), 410 + per - 20, 330, percent_str + "%", 12);

    if (!monitorDisplay->hideHostname)
        window.draw(hostname);
    if (!monitorDisplay->hideUsername)
        window.draw(username);
    if (!monitorDisplay->hideOs)
        window.draw(os);
    if (!monitorDisplay->hideKernel)
        window.draw(kernel);
    if (!monitorDisplay->hideDate)
        window.draw(date);
    if (!monitorDisplay->hideCPU) {
        window.draw(cpuModel);
        window.draw(cpuFrequency);
        window.draw(cpuActivity);
    }
    if (!monitorDisplay->hideRam)
        window.draw(ramInfo);
    if (!monitorDisplay->hideNet)
        window.draw(netInfo);
    window.draw(percentage);
}

void init_class(IMonitorDisplay *monitorDisplay, IMonitorModule monitorModule, long nb_modules)
{

    sf::Font *font = new sf::Font;
    font->loadFromFile("code.ttf");
    monitorDisplay->setFont(font);
    sf::Texture texture;
    texture.loadFromFile("deer2.png");
    monitorDisplay->texture = texture;

    // for (long i = 0; i < nb_modules; i++)
    // {
    //     sf::RectangleShape rectangle(sf::Vector2f(400, 90));
    //     sf::RectangleShape rectangle2(sf::Vector2f(400, 90));
    //     rectangle.setPosition(0, 100 * i + 5);
    //     rectangle2.setPosition(400, 100 * i + 5);
    //     rectangle.setOutlineThickness(5);
    //     rectangle.setFillColor(sf::Color::Black);
    //     rectangle.setOutlineColor(sf::Color::Black);
    //     rectangle2.setOutlineThickness(5);
    //     rectangle2.setFillColor(sf::Color::Black);
    //     rectangle2.setOutlineColor(sf::Color::Black);
    //     monitorDisplay->addObject(rectangle);
    //     monitorDisplay->addObject(rectangle2);
    // }

    if (!monitorDisplay->hideNCPU) {
        for (long i = 1; i < monitorModule.getCores() + 1; i++) {
            sf::Text text;
            text.setFont(*font);
            text.setPosition(10, 100 * i + 10);
            text.setCharacterSize(20);
            text.setString("Core " + std::to_string(int(i)));
            monitorDisplay->addText(text);
        }
    }
}

void sfml(char **argv)
{
    IMonitorDisplay monitorDisplay;
    IMonitorModule monitorModule;

    long nb_modules = std::min(monitorModule.getCores() + 1, 8);
    long size_y = nb_modules * 100;
    int frame_index = 0;
    NetworkStats stats;

    sf::RenderWindow window(sf::VideoMode(800, size_y), "50/50");
    window.setFramerateLimit(60);

    checkHide(argv, &monitorDisplay);
    init_class(&monitorDisplay, monitorModule, nb_modules);
    setHideButtons(&monitorDisplay);
    monitorModule.stats = stats;
    monitorModule.stats.oldRec = 0;
    monitorModule.stats.oldSent = 0;
    monitorModule.stats.prevRec = 0;
    monitorModule.stats.prevSent = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && 
                (event.key.code == sf::Keyboard::Escape || 
                event.key.code == sf::Keyboard::Q)))
                    window.close();
            // if (event.type == sf::Event::MouseButtonPressed)
            //     getPress(&monitorDisplay, window);
        }


        window.clear(sf::Color::Black);
        get_network_stats("lo", monitorModule.stats);
        monitorDisplay.reduceXPositions();

        //setPosition(730, 510);
        frame_index = monitorDisplay.display_background(window, frame_index, 800, size_y);
        monitorDisplay.draw(window, &monitorDisplay);
        update_text(window, &monitorDisplay, monitorModule);
        monitorDisplay.displayRamBox(window, std::stod(monitorModule.getPourcentage(monitorModule.getRAMUsedSize(), monitorModule.getRAMTotalSize())), 410, 350);
        window.display();
    }
}
