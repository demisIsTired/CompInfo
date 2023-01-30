/*
** EPITECH PROJECT, 2023
** Rush_3
** File description:
** test
*/

#include "IMonitorDisplay.hpp"
#include "IMonitorModule.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
        return 84;
    if (strcmp(argv[1], "-i") == 0) {
        std::cout << "Usage" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideHostname" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideUsername" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideOs" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideKernel" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideDate" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideCPU" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideNCPU" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideNet" << std::endl;
        std::cout << "  --> ./MyGKrellm -graphical -hideRam" << std::endl;
        std::cout << "  --> ./MyGKrellm -text" << std::endl;
    }
    if (strcmp(argv[1], "-graphical") == 0)
        sfml(argv);
    if (strcmp(argv[1], "-text") == 0)
        ncurses();
    return 0;
}
