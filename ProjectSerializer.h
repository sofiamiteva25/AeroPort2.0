#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class ProjectSerializer
{
public:
    static void save(const std::string& filepath);
    static void load(const std::string& filepath);
    static void printState(std::ostream& os = std::cout);

private:
    static const char SEP;

    static void savePlanes   (std::ofstream& out);
    static void saveRunways  (std::ofstream& out);
    static void saveHangars  (std::ofstream& out);
    static void saveFlights  (std::ofstream& out);
    static void saveTickets  (std::ofstream& out);
    static void saveAirlines (std::ofstream& out);
    static void saveUsers    (std::ofstream& out);

    static void loadPlanes   (std::ifstream& in);
    static void loadRunways  (std::ifstream& in);
    static void loadHangars  (std::ifstream& in);
    static void loadFlights  (std::ifstream& in);
    static void loadTickets  (std::ifstream& in);
    static void loadAirlines (std::ifstream& in);
    static void loadUsers    (std::ifstream& in);

    static std::vector<std::string> split(const std::string& line);
    static std::vector<std::string> readSection(std::ifstream& in);
};
