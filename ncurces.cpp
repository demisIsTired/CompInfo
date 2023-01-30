/*
** EPITECH PROJECT, 2023
** Rush_3
** File description:
** ncurces
*/

#include "IMonitorModule.hpp"

static void displayCpu(IMonitorModule IMM)
{
    int row = 29;

    mvprintw(22, 0, "________________________________________________________");
    mvprintw(24, 0, "CPU Information");

    mvprintw(26, 0, "CPU Model:");
    mvprintw(26, 25, IMM.getCPUModel().c_str());

    mvprintw(27, 0, "CPU Freqency:");
    mvprintw(27, 25, IMM.getCPUFrequency().c_str());

    mvprintw(28, 0, "CPU Activity:");
    std::stringstream ss;
    double cpu_activity = IMM.getCPUActivity();
    ss << std::fixed << std::setprecision(2) << cpu_activity;
    mvprintw(28, 25, ss.str().c_str());
    mvaddch(28, 31, '%');

    for (int i = 0; i < IMM.getCores(); i++)
    {
        mvprintw(row, 0, "Core");
        mvprintw(row, 5, std::to_string(i + 1).c_str());
        mvprintw(row, 6, " Activity:");

        double coreActivity = IMM.getNCPUActivity(i);
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << coreActivity;
        std::string coreActivityStr = ss.str();

        mvprintw(row, 25, coreActivityStr.c_str());
        mvaddch(row++, 31, '%');
    }
}

static void displayNetwork(IMonitorModule IMM)
{
    IMM.getNetwork();

    mvprintw(14, 0, "________________________________________________________");
    mvprintw(16, 0, "Network Informations");

    mvprintw(18, 0, "Bytes Received:");
    mvprintw(18, 25, IMM._bytesReceived.c_str());

    mvprintw(19, 0, "Bytes Transmitted:");
    mvprintw(19, 25, IMM._bytesTransmitted.c_str());

    mvprintw(20, 0, "Bytes Received:");
    mvprintw(20, 25, IMM._packetsReceived.c_str());

    mvprintw(21, 0, "Bytes Transmitted:");
    mvprintw(21, 25, IMM._packetsTransmitted.c_str());
}

static void displayRam(IMonitorModule IMM)
{
    mvprintw(7, 0, "________________________________________________________");
    mvprintw(9, 0, "RAM Informations");

    mvprintw(11, 0, "RAM total size (Bytes):");
    mvprintw(11, 25, IMM.getRAMTotalSize().c_str());

    mvprintw(12, 0, "RAM used size (Bytes):");
    mvprintw(12, 25, IMM.getRAMUsedSize().c_str());
    mvprintw(12, 32, IMM.getPourcentage(IMM.getRAMUsedSize(), IMM.getRAMTotalSize()).c_str());
    mvaddch(12, 38, '%');

    mvprintw(13, 0, "RAM unused size (Bytes):");
    mvprintw(13, 25, IMM.getRAMUnusedSize().c_str());
    mvprintw(13, 32, IMM.getPourcentage(IMM.getRAMUnusedSize(), IMM.getRAMTotalSize()).c_str());
    mvaddch(13, 38, '%');
}

static void displayBasic(IMonitorModule IMM)
{
    int ramUsedPourcentage = 0;
    int ramUnusedPourcentage = 0;

    mvprintw(0, 0, "General Informations");

    mvprintw(2, 0, "Host name:");
    mvprintw(2, 25, IMM.getHostname().c_str());

    mvprintw(3, 0, "User name:");
    mvprintw(3, 25, IMM.getUsername().c_str());

    mvprintw(4, 0, "Operating System:");
    mvprintw(4, 25, IMM.getOSName().c_str());

    mvprintw(5, 0, "Kernel version:");
    mvprintw(5, 25, IMM.getKernelVersion().c_str());

    mvprintw(6, 0, "Date and Time:");
    mvprintw(6, 25, IMM.getDateTime().c_str());
}

void ncurses(void)
{
    IMonitorModule IMM;

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    while (1)
    {
        displayBasic(IMM);
        displayRam(IMM);
        displayNetwork(IMM);
        displayCpu(IMM);
        refresh();

        char input = getch();
        if (input == 'Q' || input == 'q')
            break;
    }

    endwin();
}
