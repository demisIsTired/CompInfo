/*
** EPITECH PROJECT, 2023
** B-PDG-300-LYN-3-1-PDGRUSH3-dylan.winter
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

struct NetworkStats {
    unsigned long long oldSent, oldRec, currentSent, currentRec, prevSent, prevRec;
};

bool get_network_stats(const std::string &ifname, NetworkStats &stats);


#endif /* !NETWORK_HPP_ */
