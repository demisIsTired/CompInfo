/*
** EPITECH PROJECT, 2023
** B-PDG-300-LYN-3-1-PDGRUSH3-dylan.winter
** File description:
** Network
*/

#include "Network.hpp"
#include "IMonitorModule.hpp"


std::vector<unsigned long long> parse_network_stats(const std::string& line) {
    std::vector<unsigned long long> values;
    size_t end = line.find(':');
    if (end == std::string::npos) {
        return values;
    }
    std::istringstream ss(line.substr(end + 1));
    unsigned long long value;
    while (ss >> value) {
        values.push_back(value);
    }
    return values;
}

bool get_network_stats(const std::string &ifname, NetworkStats &stats) {
    std::ifstream net_dev("/proc/net/dev");
    if (!net_dev) {
        std::cerr << "Failed to open /proc/net/dev\n";
        return false;
    }

    std::string line;
    long long totalSent = 0;
    long long totalRec = 0;

    while (std::getline(net_dev, line)) {

        size_t end = line.find(':');
        if (end == std::string::npos)
            continue;
        std::vector<unsigned long long> values = parse_network_stats(line);
        // stats.rx_bytes = values[0];
        // stats.rx_packets = values[1];
        // stats.tx_bytes = values[8];
        // stats.tx_packets = values[9];

        totalRec += values[0];
        totalSent += values[8];

        // printf("rx_bytes: %llu\n", stats.rx_bytes);
        // printf("rx_packets: %llu\n", stats.rx_packets);
        // printf("tx_bytes: %llu\n", stats.tx_bytes);
        // printf("tx_packets: %llu\n", stats.tx_packets);
    }

    if (stats.oldRec) {
        stats.prevRec = stats.currentRec;
        stats.prevSent = stats.currentSent; 
        stats.currentRec = totalRec - stats.oldRec;
        stats.currentSent = totalSent - stats.oldSent;
    } else {
        stats.currentRec = 0;
        stats.currentSent = 0;
    }

    stats.oldRec = totalRec;
    stats.oldSent = totalSent;


    net_dev.close();
    return false;
}