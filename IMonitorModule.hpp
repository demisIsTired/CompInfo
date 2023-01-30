/*
** EPITECH PROJECT, 2023
** B-PDG-300-LYN-3-1-PDGRUSH3-dylan.winter
** File description:
** IMonitorModule
*/

#ifndef IMONITORMODULE_HPP_
#define IMONITORMODULE_HPP_

#include <ncurses.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>
#include <ctime>
#include <fstream>
#include <sys/types.h>
#include <pwd.h>
#include <sys/sysinfo.h>
#include <sstream>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include "Network.hpp"

class IMonitorModule
{
public:
    IMonitorModule()
    {
        for (int i = 0; i < 100; i++)
        {
            lastIdle[i] = 0;
            lastSum[i] = 0;
        }
    }
    ~IMonitorModule() {
    }

    int getCores()
    {
        long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
        return nprocs;
    }

    std::string getUsername()
    {
        struct passwd *pw = getpwuid(getuid());
        return pw->pw_name;
    }

    std::string getHostname()
    {
        char hostname[256];
        gethostname(hostname, 256);
        return hostname;
    }

    std::string getOSName()
    {
        struct utsname unameData;
        uname(&unameData);
        return unameData.sysname;
    }

    std::string getKernelVersion()
    {
        struct utsname unameData;
        uname(&unameData);
        return unameData.release;
    }

    std::string getDateTime()
    {
        std::time_t time = std::time(nullptr);
        std::tm localTime = *std::localtime(&time);
        char dateTime[20];
        std::strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", &localTime);
        return dateTime;
    }

    std::string getCPUModel()
    {
        std::string line;
        std::string mod;
        std::ifstream file("/proc/cpuinfo");
        while (std::getline(file, line))
            if (line.find("model name") != std::string::npos)
            {
                mod = line.substr(line.find(':') + 2);
                break;
            }
        file.close();
        return mod;
    }

    std::string getCPUFrequency()
    {
        std::string line;
        std::string freq;
        std::ifstream file("/proc/cpuinfo");
        while (std::getline(file, line))
            if (line.find("cpu MHz") != std::string::npos)
            {
                freq = line.substr(line.find(':') + 2);
                break;
            }
        file.close();
        return freq;
    }

    double calc(const std::string &input, int indx)
    {
        std::stringstream ss(input);
        int a, b, c, d, e, f, g, h, i, j;
        ss >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j;
        double sum = a + b + c + d + e + f + g + h + i + j;
        double idle = double(d);

        double res = 100 - (idle - lastIdle[indx]) * 100.0 / (sum - lastSum[indx]);
        lastIdle[indx] = idle;
        lastSum[indx] = sum;
        usleep(30000);
        return res;
    }

    double getCPUActivity()
    {
        std::string line;
        std::string activity;
        std::ifstream file("/proc/stat");
        while (std::getline(file, line))
        {
            if (line.find("cpu ") != std::string::npos)
            {
                activity = line.substr(5);
                break;
            }
        }
        file.close();
        return calc(activity, 0);
    }

    double getNCPUActivity(int n)
    {
        std::string line;
        std::string activity;
        std::ifstream file("/proc/stat");
        while (std::getline(file, line))
        {
            if (line.find("cpu" + std::to_string(n)) != std::string::npos)
            {
                activity = line.substr(5);
                break;
            }
        }
        file.close();
        return calc(activity, n + 1);
    }

    std::string getRAMTotalSize()
    {
        struct sysinfo info;
        std::stringstream ss;

        sysinfo(&info);
        long totalRAM = info.totalram;
        ss << (totalRAM / (1024 * 1024));
        return ss.str();
    }

    std::string getRAMUsedSize()
    {
        struct sysinfo info;
        std::stringstream ss;

        sysinfo(&info);
        long usedRAM = (info.totalram - info.freeram);
        ss << (usedRAM / (1024 * 1024));
        return ss.str();
    }

    std::string getRAMUnusedSize()
    {
        struct sysinfo info;
        std::stringstream ss;

        sysinfo(&info);
        long unusedRAM = info.freeram;
        ss << (unusedRAM / (1024 * 1024));
        return ss.str();
    }

    std::string getPourcentage(std::string str1, std::string str2)
    {
        std::stringstream ss;
        double num1 = std::atof(str1.c_str());
        double num2 = std::atof(str2.c_str());

        ss << std::fixed << std::setprecision(2) << ((num1 / num2) * 100);
        return ss.str();
    }

    void getNetwork()
    {
        std::ifstream file("/proc/net/dev");
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string str;
            iss >> str;
            if (str.find(":") != std::string::npos)
            {
                iss >> _bytesReceived >> _packetsReceived >> _bytesTransmitted >> _packetsTransmitted;
                break;
            }
        }
        file.close();
        usleep(30000);
    }

    std::string _bytesReceived, _packetsReceived, _bytesTransmitted, _packetsTransmitted;
    double *lastSum = new double[100];
    double *lastIdle = new double[100];
    NetworkStats stats;
};

void ncurses();

#endif /* !IMONITORMODULE_HPP_ */