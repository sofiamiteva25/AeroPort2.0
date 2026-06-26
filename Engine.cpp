#include "Engine.h"
Engine* Engine::engine = nullptr;
Engine::Engine() {
    logI = std::make_unique<LogInterface>();

}
Engine* Engine::getEngine()
{
    if (engine == nullptr) {
        engine = new Engine();
    }
    return engine;
}

void Engine::command(std::string msg)
{ 
    static const std::vector<std::string> knownCommands = {
        // serializer
        "Save", "Load", "PrintState",
        // auth
        "Login", "Logout", "SignUp", "PrintInfo", "Help",
        // admin
        "BuildRunway", "BuildHangar", "CloseRunway", "ChangeWeather",
        "CloneAircraft", "SendToHangar", "RetrieveFromHangar",
        "ScheduleFlight", "CancelFlight", "FlightRevenue",
        "PrintFleet", "AirportReport", "AuditAirline",
        "BuyAircraft", "RegisterAirline",
        // passenger
        "AddFunds", "ListFlightsByDestination", "FilterFlightsByPrice",
        "MyTickets", "BookTicket", "UpgradeTicket",
        "CancelTicket", "RefundTicket", "AddLuggage", "GetBalance",
        // traffic control
        "ListAirspace", "ListRunways", "AssignRunway",
        "DelayFlight", "FreeRunway", "Undo",
        // general
        "Exit"
    };
    std::string userChoice;
    do {
		if (logI->isLogged()) {
            logI->help();
            std::cin >> userChoice;
		}
		else {
			while (userChoice != "Login" && userChoice != "SignUp" && userChoice != "Load") {
				std::cout << "You must log in or register first.\n";
				std::cout << "Enter 'Login', 'SignUp', or 'Load': ";
				std::cin >> userChoice;
			}
		}
        bool known = std::find(knownCommands.begin(), knownCommands.end(), userChoice)
            != knownCommands.end();

        if (!known) {
            std::cout << "Unknown command. Try again.\n";
            continue;
        }
        engine->handleLog(userChoice);
        engine->handleSerializer(userChoice);
        engine->handleAdmin(userChoice);
        engine->handlePassenger(userChoice);
        engine->handleTrafficControl(userChoice);

    } while (userChoice != "Exit");
}


void Engine::handleAdmin(std::string msg)
{
    auto* admin = const_cast<Administrator*>(Administrator::getInstance());
    if (admin == nullptr) return;
    try {
        if (msg == "BuildRunway") {
            unsigned int length;
            bool ils, heavy, vip;
            std::cout << "Length: ";
            std::cin >> length;
            std::cout << "ILS";
            std::cin >> ils;
            std::cout << "Heavy";
            std::cin >> heavy;
            std::cout << "VIP";
            std::cin >> vip;
            admin->buildRunway(length, ils, heavy, vip);
            return;
        }
        else if (msg == "BuildHangar") {
            std::string id;
            int capacity;
            double tax;
            std::cout << "Hangar ID: ";
            std::cin >> id;
            std::cout << "Capacity: ";
            std::cin >> capacity;
            std::cout << "Tax: ";
            std::cin >> tax;
            admin->buildHangar(id, capacity, tax);
            return;
        }
        else if (msg == "CloseRunway") {
            int id;
            std::cout << "Runway ID: ";
            std::cin >> id;
            admin->closeRunway(id);
            return;
        }
        else if (msg == "ChangeWeather") {
            int w;
            std::cout << "Weather condition";
            std::cin >> w;
            admin->changeWeather(static_cast<WeatherCondition>(w));
            return;
        }
        else if (msg == "CloneAircraft") {
            int planeId, count;
            std::cout << "Plane ID: ";
            std::cin >> planeId;
            std::cout << "Count: ";
            std::cin >> count;
            int id = planeId;
            int cnt = count;
            admin->cloneAircraft(id, cnt);
            return;
        }
        else if (msg == "SendToHangar") {
            int planeId;
            std::string hangarId;
            std::cout << "Plane ID: ";
            std::cin >> planeId;
            std::cout << "Hangar ID: ";
            std::cin >> hangarId;
            admin->sentPlaneToHangar(planeId, hangarId);
            return;
        }
        else if (msg == "RetrieveFromHangar") {
            int planeId;
            std::string hangarId;
            std::cout << "Plane ID: ";
            std::cin >> planeId;
            std::cout << "Hangar ID: ";
            std::cin >> hangarId;
            admin->retrivePlaneFromHangar(planeId, hangarId);
            return;
        }
        else if (msg == "ScheduleFlight") {
            std::string flightId, destination;
            int planeId;
            double price;
            std::cout << "Flight ID: ";
            std::cin >> flightId;
            std::cout << "Plane ID: ";
            std::cin >> planeId;
            std::cout << "Price: ";
            std::cin >> price;
            std::cout << "Destination: ";
            std::cin >> destination;
            admin->scheduleFlight(flightId, planeId, price, destination);
            return;
        }
        else if (msg == "CancelFlight") {
            std::string flightId;
            std::cout << "Flight ID: ";
            std::cin >> flightId;
            admin->cancelFlight(flightId);
            return;
        }
        else if (msg == "FlightRevenue") {
            std::string flightId;
            std::cout << "Flight ID: ";
            std::cin >> flightId;
            std::cout << "Revenue: " << admin->flightRevenue(flightId) << '\n';
            return;
        }
        else if (msg == "PrintFleet") {
            std::string airline;
            std::cout << "Airline name: ";
            std::cin >> airline;
            admin->printFleet(std::cout, airline);
            return;
        }
        else if (msg == "AirportReport") {
            admin->airportReport(std::cout);
            return;
        }
        else if (msg == "AuditAirline") {
            std::string airline;
            std::cout << "Airline name: ";
            std::cin >> airline;
            admin->auditAirline(std::cout, airline);
            return;
        }
        else if (msg == "BuyAircraft") {
            std::string airline, model;
            int capacity;
            std::cout << "Airline name: ";
            std::cin >> airline;
            std::cout << "Model: ";
            std::cin >> model;
            std::cout << "Capacity: ";
            std::cin >> capacity;
            admin->buyAircraft(airline, model, capacity);
            return;
        }
        else if (msg == "RegisterAirline") {
            std::string name;
            double balance;
            std::cout << "Airline name: ";
            std::cin >> name;
            std::cout << "Balance: ";
            std::cin >> balance;
            admin->registerAirline(name, balance);
            return;
        }
    }
    catch (MyException& e) {
        std::cout << e.what() << '\n';
        return;
    }
}

void Engine::handlePassenger(std::string msg)
{
    auto* passenger = dynamic_cast<Passenger*>(logI->getUser());
    if (passenger == nullptr)
        return;
    try {
        if (msg == "AddFunds") {
            double amount;
            std::cout << "Amount: ";
            std::cin >> amount;
            passenger->addFunds(amount);
            std::cout << "New balance: " << passenger->getBalance() << '\n';
            return;
        }
        else if (msg == "ListFlightsByDestination") {
            std::string destination;
            std::cout << "Destination: ";
            std::cin >> destination;
            auto flights = passenger->listFlightByDestination(destination);
            for (const auto& f : flights)
                std::cout << *f << '\n';
            return;
        }
        else if (msg == "FilterFlightsByPrice") {
            double maxPrice;
            std::cout << "Max price: ";
            std::cin >> maxPrice;
            auto flights = passenger->filterFlightsByPrice(maxPrice);
            if (flights.empty()) {
                std::cout << "No flights in budget.\n";
                return;
            }
            for (const auto& f : flights)
                std::cout << *f << '\n';
            return;
        }
        else if (msg == "MyTickets") {
            auto tickets = passenger->myTickets();
            if (tickets.empty()) {
                std::cout << "No tickets.\n";
                return;
            }
            for (const auto& t : tickets)
                std::cout << *t << '\n';
            return;
        }
        else if (msg == "BookTicket") {
            std::string flightId, type;
            std::cout << "Flight ID: ";
            std::cin >> flightId;
            std::cout << "Type: ";
            std::cin >> type;
            passenger->bookTicket(flightId, type);
            return;
        }
        else if (msg == "UpgradeTicket") {
            std::string flightId, newType;
            std::cout << "Flight ID: ";
            std::cin >> flightId;
            std::cout << "New type: ";
            std::cin >> newType;
            passenger->upgradeTicket(flightId, newType);
            return;
        }
        else if (msg == "CancelTicket") {
            std::string flightId;
            std::cout << "Flight ID: ";     std::cin >> flightId;
            passenger->cancelTicket(flightId);
            return;
        }
        else if (msg == "RefundTicket") {
            std::string flightId;
            std::cout << "Flight ID: ";     std::cin >> flightId;
            passenger->refundTicket(flightId);
            return;
        }
        else if (msg == "AddLuggage") {
            std::string flightId;
            int amount;
            std::cout << "Flight ID: ";     std::cin >> flightId;
            std::cout << "Luggage amount: "; std::cin >> amount;
            passenger->addLuggage(flightId, amount);
            return;
        }
        else if (msg == "GetBalance") {
            std::cout << "Balance: " << passenger->getBalance() << '\n';
            return;
        }
    }
    catch (MyException& e) {
       std:: cout << e.what() << '\n';
        return;
    }
}

void Engine::handleTrafficControl(std::string msg)
{
    auto* traffic = dynamic_cast<TrafficControl*>(logI->getUser());
    if (traffic == nullptr) return;

    try {
        if (msg == "ListAirspace") {
            traffic->listAirspace();
            return;
        }
        else if (msg == "ListRunways") {
            traffic->listRunways();
            return;
        }
        else if (msg == "AssignRunway") {
            std::string flightId;
            int runwayId;
            std::cout << "Flight ID: ";     
            std::cin >> flightId;
            std::cout << "Runway ID: ";     
            std::cin >> runwayId;
            traffic->assignRunway(flightId, runwayId);
            return;
        }
        else if (msg == "DelayFlight") {
            std::string flightId, reason;
            std::cout << "Flight ID: ";     
            std::cin >> flightId;
            std::cout << "Reason: ";       
            std::cin >> reason;
            traffic->delayFlight(flightId, reason);
            return;
        }
        else if (msg == "FreeRunway") {
            int runwayId;
            std::cout << "Runway ID: ";    
            std::cin >> runwayId;
            traffic->freeRunway(runwayId);
            return;
        }
        else if (msg == "Undo") {
            traffic->undo();
            return;
        }
    }
    catch (const MyException& e) {
        std::cout << e.what() << '\n';
        return;
    }
}

void Engine::handleLog(std::string msg)
{
    try {
        if (msg == "Login") {
            std::string name, password;
            std::cout << "Name: ";     
            std::cin >> name;
            std::cout << "Password: ";  
            std::cin >> password;
            logI->logIn(name, password);
            return;
        }
        else if (msg == "Logout") {
            logI->logout();
            std::cout << "Logged out.\n";
            return;
        }
        else if (msg == "PrintInfo") {
            logI->printInfo();
            return;
        }
        else if (msg == "Help") {
            logI->help();
            return;
        }
        else if (msg == "SignUp") {
            std::string name, password, type;
            double balance = 0.0;
            std::cout << "Name: ";     
            std::cin >> name;
            std::cout << "Password: ";  
            std::cin >> password;
            std::cout << "Type (Passenger/TrafficControl): "; 
			std::cin >> type;
            if (type == "Passenger") {
                std::cout << "Balance: ";
                std::cin >> balance;
                logI->signUp(name, password, type, balance);
            }
            else {
                logI->signUp(name, password, type);
            }
            return;
        }
    }
    catch (const MyException& e) {
        std::cout <<e.what() << '\n';
        return;
    }
}

void Engine::handleSerializer(std::string msg)
{
    const std::string SAVE_FILE = "airport.txt";
    try {
        if (msg == "Save") {
            ProjectSerializer::save(SAVE_FILE);
        }
        else if (msg == "Load") {
            ProjectSerializer::load(SAVE_FILE);
        }
        else if (msg == "PrintState") {
            ProjectSerializer::printState(std::cout);
        }
    }
    catch (const MyException& e) {
        std::cout << e.what() << '\n';
    }
}

