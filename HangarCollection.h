#pragma once
#include "Hangar.h"

class HangarCollection {
	static std::vector<std::unique_ptr<Hangar>> hangars;
public:
	static const std::unique_ptr<Hangar>& getHangarById(std::string _id);
	static const std::vector <std::unique_ptr<Hangar>>& getAllHangars();
	static void addHangar(std::unique_ptr<Hangar> hangar);
	static void printAllHangars(std::ostream& os);
	static bool hangarId(std::string id);
};
