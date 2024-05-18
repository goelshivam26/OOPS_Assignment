#include <bits/stdc++.h>
using namespace std;

// in this we have a hotel database as a singleton class

//                   Hotel Database
//                /       |      \           \
            //               /        |       \          \ 
            //              /         |        \          \ 
            //             /          |         \          \
            //  Hotel Manager   Feedback Manger  \     User Manager
//                                    \
            //                              Reservation Manager

// Forward declarations
class HotelManager;
class UserManager;
class ReservationManager;
class FeedbackManager;

// Singleton Class or you can say that global point access for all operations
// HotelDatabase has a User manager ( HAS A relationship)
// HotelDatabase has a Reservation manager ( HAS A relationship)
// HotelDatabase has a Feedback manager ( HAS A relationship)
// HotelDatabase has a Hotel manager ( HAS A relationship)
class HotelDatabase
{
private:
    static HotelDatabase *instance;
    HotelManager *hotelManager;
    UserManager *userManager;
    ReservationManager *reservationManager;
    FeedbackManager *feedbackManager;

    HotelDatabase(HotelManager *hm, UserManager *um,
                  ReservationManager *rm, FeedbackManager *fm)
        : hotelManager(hm), userManager(um), reservationManager(rm), feedbackManager(fm) {}

public:
    static HotelDatabase *getInstance(HotelManager *hm = nullptr, UserManager *um = nullptr,
                                      ReservationManager *rm = nullptr, FeedbackManager *fm = nullptr)
    {
        if (!instance)
        {
            instance = new HotelDatabase(hm, um, rm, fm);
        }
        return instance;
    }

    HotelManager *getHotelManager() { return hotelManager; }
    UserManager *getUserManager() { return userManager; }
    ReservationManager *getReservationManager() { return reservationManager; }
    FeedbackManager *getFeedbackManager() { return feedbackManager; }
};

HotelDatabase *HotelDatabase::instance = nullptr;

// Abstract base class User
class User
{
protected:
    int userID;
    string username;
    string password;
    string email;
    string role;

public:
    virtual void registerUser() = 0;
    virtual void login() = 0;
    virtual void updateDetails() = 0;

    // getter functions
    int getUserID() const { return userID; }
    string getRole() { return role; }

    // setter functions
    void setUserID(int id) { userID = id; }
    void setUsername(const string &name) { username = name; }
    void setPassword(const string &pass) { password = pass; }
    void setEmail(const string &mail) { email = mail; }
};

// Hotel class store all hotel details
class Hotel
{
private:
    int hotelID;
    string name;
    string location;
    int numberOfRooms;
    int availableRooms;
    vector<int> ratings;

public:
    Hotel(int id, const string &n, const string &loc, int rooms)
        : hotelID(id), name(n), location(loc), numberOfRooms(rooms), availableRooms(rooms) {}

    int getHotelID() const { return hotelID; }
    void getDetails() const
    {
        cout << "Hotel ID: " << hotelID << ", Name: " << name << ", Location: " << location << ", Available Rooms: " << availableRooms << endl;
    }
    int getAvailableRooms() const { return availableRooms; }
    void updateDetails(const string &n, const string &loc, int rooms)
    {
        name = n;
        location = loc;
        numberOfRooms = rooms;
        availableRooms = rooms;
    }
    void bookRoom()
    {
        if (availableRooms > 0)
        {
            availableRooms--;
            cout << "Room booked successfully. Rooms left: " << availableRooms << endl;
        }
        else
        {
            cout << "No rooms available." << endl;
        }
    }
    void addRating(int rating)
    {
        ratings.push_back(rating);
    }
    float getAverageRating() const
    {
        if (ratings.empty())
            return 0;
        int sum = accumulate(ratings.begin(), ratings.end(), 0);
        return static_cast<float>(sum) / ratings.size();
    }
};

// Reservation class stores reservation status
class Reservation
{
private:
    int reservationID;
    int userID;
    int hotelID;
    int roomNumber;
    string status;

public:
    Reservation(int resID, int uID, int hID, int roomNo)
        : reservationID(resID), userID(uID), hotelID(hID), roomNumber(roomNo), status("Booked") {}

    string getStatus() const { return status; }
};

// Feedback class
class Feedback
{
private:
    int feedbackID;
    int userID;
    int hotelID;
    int rating;
    string comment;

public:
    Feedback(int fbID, int uID, int hID, int rate, const string &com)
        : feedbackID(fbID), userID(uID), hotelID(hID), rating(rate), comment(com) {}

    string getFeedback() const
    {
        return "Rating: " + to_string(rating) + ", Comment: " + comment;
    }
};

// User Management class that handles all user related activiy
class UserManager
{
private:
    vector<class User *> users;

public:
    void addUser(class User *user) { users.push_back(user); }
    vector<class User *> getUsers() { return users; }
    class User *getUserById(int userID)
    {
        for (auto &user : users)
        {
            if (user->getUserID() == userID)
            {
                return user;
            }
        }
        return nullptr;
    }
    void deleteUserById(int userID)
    {
        users.erase(remove_if(users.begin(), users.end(),
                              [userID](class User *user)
                              { return user->getUserID() == userID; }),
                    users.end());
    }
};

// Hotel Management class that handles all CRUD operations on Hotel
class HotelManager
{
private:
    vector<class Hotel *> hotels;

public:
    void addHotel(class Hotel *hotel) { hotels.push_back(hotel); }
    vector<class Hotel *> getHotels() { return hotels; }
    class Hotel *getHotelById(int hotelID)
    {
        for (auto &hotel : hotels)
        {
            if (hotel->getHotelID() == hotelID)
            {
                return hotel;
            }
        }
        return nullptr;
    }
    void deleteHotelById(int hotelID)
    {
        hotels.erase(remove_if(hotels.begin(), hotels.end(),
                               [hotelID](class Hotel *hotel)
                               { return hotel->getHotelID() == hotelID; }),
                     hotels.end());
    }
};

// Reservation Management class that handles reservation operations
class ReservationManager
{
private:
    vector<class Reservation *> reservations;

public:
    void addReservation(class Reservation *reservation) { reservations.push_back(reservation); }
    vector<class Reservation *> getReservations() { return reservations; }
};

// Feedback Management class that handles feedback facility
class FeedbackManager
{
private:
    vector<class Feedback *> feedbacks;

public:
    void addFeedback(class Feedback *feedback) { feedbacks.push_back(feedback); }
    vector<class Feedback *> getFeedbacks() { return feedbacks; }
};

// User roles implementation
// 1. normaluser means customer that uses our system for booking hotels
class NormalUser : public User
{
public:
    NormalUser() { role = "NormalUser"; }
    void registerUser() override
    {
        auto db = HotelDatabase::getInstance();
        userID = db->getUserManager()->getUsers().size() + 1;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Email: ";
        cin >> email;
        db->getUserManager()->addUser(this);
        cout << "Normal User Registered Successfully" << endl;
    }
    void login() override
    {
        string user, pass;
        cout << "Enter Username: ";
        cin >> user;
        cout << "Enter Password: ";
        cin >> pass;
        if (username == user && password == pass)
        {
            cout << "Normal User Logged in Successfully" << endl;
        }
        else
        {
            cout << "Login Failed" << endl;
        }
    }
    void updateDetails() override
    {
        cout << "Enter new Username: ";
        cin >> username;
        cout << "Enter new Password: ";
        cin >> password;
        cout << "Enter new Email: ";
        cin >> email;
        cout << "Normal User Details Updated Successfully" << endl;
    }
    void  searchHotelsbyname();
    void bookRoom();
    void giveFeedback();
};

// 2. Hotel Agent means user that uses our system for managing hotels
class HotelAgent : public User
{
private:
    vector<class Hotel *> hotels;

public:
    HotelAgent() { role = "HotelAgent"; }
    void registerUser() override
    {
        auto db = HotelDatabase::getInstance();
        userID = db->getUserManager()->getUsers().size() + 1;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Email: ";
        cin >> email;
        db->getUserManager()->addUser(this);
        cout << "Hotel Agent Registered Successfully" << endl;
    }
    void login() override
    {
        string user, pass;
        cout << "Enter Username: ";
        cin >> user;
        cout << "Enter Password: ";
        cin >> pass;
        // Login logic here
        if (username == user && password == pass)
        {
            cout << "Hotel Agent Logged in Successfully" << endl;
        }
        else
        {
            cout << "Login Failed" << endl;
        }
    }
    void updateDetails() override
    {
        cout << "Enter new Username: ";
        cin >> username;
        cout << "Enter new Password: ";
        cin >> password;
        cout << "Enter new Email: ";
        cin >> email;
        cout << "Hotel Agent Details Updated Successfully" << endl;
    }

    void addHotel();
    void updateHotel();
};

// 3. administrator means that approve hotel delete user and delete hotel
class Administrator : public User
{
public:
    Administrator() { role = "Administrator"; }
    void registerUser() override
    {
        auto db = HotelDatabase::getInstance();
        userID = db->getUserManager()->getUsers().size() + 1;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Email: ";
        cin >> email;
        db->getUserManager()->addUser(this);
        cout << "Administrator Registered Successfully" << endl;
    }
    void login() override
    {
        string user, pass;
        cout << "Enter Username: ";
        cin >> user;
        cout << "Enter Password: ";
        cin >> pass;
        if (username == user && password == pass)
        {
            cout << "Administrator Logged in Successfully" << endl;
        }
        else
        {
            cout << "Login Failed" << endl;
        }
    }
    void updateDetails() override
    {
        cout << "Enter new Username: ";
        cin >> username;
        cout << "Enter new Password: ";
        cin >> password;
        cout << "Enter new Email: ";
        cin >> email;
        cout << "Administrator Details Updated Successfully" << endl;
    }
    void approveHotel();
    void deleteUser();
    void deleteHotel();
};

// User roles implementation
// search hotel by customer
void NormalUser:: searchHotelsbyname()
{
    auto db = HotelDatabase::getInstance();
    for (const auto &hotel : db->getHotelManager()->getHotels())
    {
        hotel->getDetails();
    }
}

// bookroom by customer
void NormalUser::bookRoom()
{
    auto db = HotelDatabase::getInstance();
    int hotelID;
    cout << "Enter Hotel ID to book a room: ";
    cin >> hotelID;
    auto hotel = db->getHotelManager()->getHotelById(hotelID);
    if (hotel)
    {
        hotel->bookRoom();
        db->getReservationManager()->addReservation(new Reservation(db->getReservationManager()->getReservations().size() + 1, userID, hotelID, hotel->getAvailableRooms()));
    }
    else
    {
        cout << "Hotel not found." << endl;
    }
}

// feedback by customer
void NormalUser::giveFeedback()
{
    auto db = HotelDatabase::getInstance();
    int hotelID, rating;
    string comment;
    cout << "Enter Hotel ID to give feedback: ";
    cin >> hotelID;
    cout << "Enter rating (1-5): ";
    cin >> rating;
    cout << "Enter comment: ";
    cin.ignore();
    getline(cin, comment);

    auto feedback = new Feedback(db->getFeedbackManager()->getFeedbacks().size() + 1, userID, hotelID, rating, comment);
    db->getFeedbackManager()->addFeedback(feedback);

    auto hotel = db->getHotelManager()->getHotelById(hotelID);
    if (hotel)
    {
        hotel->addRating(rating);
        cout << "Feedback added. Average rating: " << hotel->getAverageRating() << endl;
    }
    else
    {
        cout << "Hotel not found." << endl;
    }
}

// search hotel by location
void NormalUser:: searchHotelsByLocation() {
    std::string location;
    std::cout << "Enter location to search hotels: ";
    std::cin >> location;
    auto db = HotelDatabase::getInstance();
    db->getHotelManager()->listHotelsByLocation(location);
}

// add hotel by hotel agent
void HotelAgent::addHotel()
{
    auto db = HotelDatabase::getInstance();
    int hotelID;
    string name, location;
    int numberOfRooms;
    cout << "Enter Hotel ID: ";
    cin >> hotelID;
    cout << "Enter Hotel Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Hotel Location: ";
    getline(cin, location);
    cout << "Enter Number of Rooms: ";
    cin >> numberOfRooms;

    auto hotel = new Hotel(hotelID, name, location, numberOfRooms);
    db->getHotelManager()->addHotel(hotel);
    cout << "Hotel added successfully." << endl;
}

// update hotel by hotel agent
void HotelAgent::updateHotel()
{
    auto db = HotelDatabase::getInstance();
    int hotelID;
    cout << "Enter Hotel ID to update: ";
    cin >> hotelID;
    auto hotel = db->getHotelManager()->getHotelById(hotelID);
    if (hotel)
    {
        string name, location;
        int numberOfRooms;
        cout << "Enter new Hotel Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter new Hotel Location: ";
        getline(cin, location);
        cout << "Enter new Number of Rooms: ";
        cin >> numberOfRooms;

        hotel->updateDetails(name, location, numberOfRooms);
    }
    else
    {
        cout << "Hotel not found." << endl;
    }
}

// Approve hotel by administrator
void Administrator::approveHotel()
{
    cout << "Approve Hotel" << endl;
}

// delete user by administrator
void Administrator::deleteUser()
{
    auto db = HotelDatabase::getInstance();
    int userID;
    cout << "Enter User ID to delete: ";
    cin >> userID;
    db->getUserManager()->deleteUserById(userID);
    cout << "User deleted successfully." << endl;
}

// delete hotel by administrator
void Administrator::deleteHotel()
{
    auto db = HotelDatabase::getInstance();
    int hotelID;
    cout << "Enter Hotel ID to delete: ";
    cin >> hotelID;
    db->getHotelManager()->deleteHotelById(hotelID);
    cout << "Hotel deleted successfully." << endl;
}

// Main function
int main()
{
    HotelManager hotelManager;
    UserManager userManager;
    ReservationManager reservationManager;
    FeedbackManager feedbackManager;

    // Instance of HotelDatabase
    HotelDatabase::getInstance(&hotelManager, &userManager, &reservationManager, &feedbackManager);

    User *admin = new Administrator();
    admin->registerUser();
    admin->login();
    auto administrator = dynamic_cast<Administrator *>(admin);
    administrator->deleteUser();
    administrator->deleteHotel();

    User *agent = new HotelAgent();
    agent->registerUser();
    agent->login();
    auto hotelAgent = dynamic_cast<HotelAgent *>(agent);
    hotelAgent->addHotel();
    hotelAgent->updateHotel();

    User *user = new NormalUser();
    user->registerUser();
    user->login();
    auto normalUser = dynamic_cast<NormalUser *>(user);
    normalUser-> searchHotelsbyname();
    normalUser->bookRoom();
    normalUser->giveFeedback();

    return 0;
}
