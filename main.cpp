//Robin Paul
//Lab #3

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Creature class definition
class Creature {
private:
    string name;
    string type;
    int strength;
    int health;

public:
    // Constructor
    Creature(string n = "", string t = "", int s = 0, int h = 0) : name(n), type(t), strength(s), health(h) {}

    // Mutator function to set all member variables
    void setCreature(string n, string t, int s, int h) {
        name = n;
        type = t;
        strength = s;
        health = h;
    }

    // Accessor functions
    int getHealth() const { return health; }
    int getStrength() const { return strength; }
    string getName() const { return name; }
    string getType() const { return type; }

    // Function to return damage
    int getDamage() const {
        return (rand() % strength) + 1;
    }

    // Function to return creature details as a string
    string toString() const {
        stringstream ss;
        ss << fixed << setprecision(2) << left;
        ss << setw(10) << name << setw(15) << type << setw(10) << strength << setw(10) << health;
        return ss.str();
    }
};

// Army class definition
class Army {
private:
    Creature creatures[10];
    int currentCount;

public:
    // Constructor
    Army() : currentCount(0) {}

    // Function to update the entire army
    void updateArmy(const string names[], const string types[], int count) {
        currentCount = (count < 10) ? count : 10;
        for (int i = 0; i < currentCount; ++i) {
            int strength = rand() % 151 + 50;
            int health = rand() % 151 + 50;
            creatures[i].setCreature(names[i], types[i], strength, health);
        }
    }

    // Function to print the list of all creatures
    void printArmy(bool withDamage = false) const {
        if (currentCount == 0) {
            cout << "No creatures in the army." << endl;
            return;
        }

        // Header
        cout << setw(10) << left << "Name" 
             << setw(15) << left << "Type" 
             << setw(10) << right << "Strength" 
             << setw(10) << right << "Health";
        if (withDamage) {
            cout << setw(10) << right << "Damage";
        }
        cout << endl;

        // Print each creature's details
        for (int i = 0; i < currentCount; ++i) {
            cout << creatures[i].toString();
            if (withDamage) {
                cout << setw(10) << right << creatures[i].getDamage();
            }
            cout << endl;
        }
    }
};

// Enum for menu options
enum MenuOptions { PRINT = 1, UPDATE, PRINT_DAMAGE, QUIT };

// Display the main menu
void displayMainMenu() {
    cout << "\n\nMenu:\n";
    cout << "1. Print the list of creatures\n";
    cout << "2. Update the array of creatures\n";
    cout << "3. Print damage for all creatures\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// Main function with menu
int main() {
    srand(static_cast<unsigned int>(time(0)));

    Army army;
    const string names[] = {"Orson", "Nara", "Boris", "Elia", "Gora"};
    const string types[] = {"Centaur", "Elf", "Troll", "Fairy", "Dragon"};

    MenuOptions choice;
    int choiceInput;

    // Set fixed-point and precision only once
    cout << fixed << setprecision(2);

    do {
        displayMainMenu();
        cin >> choiceInput;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear(); // clear the error flag
            cin.ignore(1000, '\n'); // ignore the remaining input
            continue;
        }

        choice = static_cast<MenuOptions>(choiceInput);

        switch (choice) {
            case PRINT:
                army.printArmy();
                break;
            case UPDATE:
                army.updateArmy(names, types, 5);
                cout << "Army updated.\n";
                break;
            case PRINT_DAMAGE:
                army.printArmy(true);
                break;
            case QUIT:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                cin.clear(); // clear the error flag
                cin.ignore(1000, '\n'); // ignore the remaining input
        }
    } while (choice != QUIT);

    return 0;
}

/* Test Case #1: Initial Program Start and Menu Display
Input:Running the program
Output:
Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice:

Test Case #2: Attempting to Print the List of Creatures Before Updating
Input: 1
Output: 
Enter your choice: 1       
No creatures in the army.

Test Case #3: Updating the Army with Predefined Creatures
Input: 2
Output:
Enter your choice: 2
Army updated.

Test Case #4: Print the List of Creatures After Updating
Input: 1 after updating (2 and then 1)
Output:
Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 2
Army updated.


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 1
Name      Type             Strength    Health
Orson     Centaur        176       178       
Nara      Elf            162       168       
Boris     Troll          58        77        
Elia      Fairy          149       192       
Gora      Dragon         74        84

Test case #5: Displaying the List of Creatures with Damage Values
Input: 2 and then 1 and then 3 (Damage)
Output: 
Enter your choice: 2
Army updated.


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 1
Name      Type             Strength    Health
Orson     Centaur        146       69        
Nara      Elf            78        140       
Boris     Troll          142       160       
Elia      Fairy          174       136       
Gora      Dragon         144       61        


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 3
Name      Type             Strength    Health    Damage
Orson     Centaur        146       69                55
Nara      Elf            78        140               36
Boris     Troll          142       160               28
Elia      Fairy          174       136              144
Gora      Dragon         144       61                36

Test Case #6: Attempting to Enter an Invalid Menu Option
Input: 5 (Invalid Input) 
Output:
Enter your choice: 5
Invalid choice. Please try again.

Test Case #7: Entering a Non-integer Value for Menu Selection
Input: a (invalid input)
Output:
Enter your choice: a
Invalid input. Please enter a valid number.

Test Case #8: Verify Army Values Are Within Expected Ranges (50-200)
Input: 2 and then 1
Output: 
Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 1
Name      Type             Strength    Health
Orson     Centaur        178       144       
Nara      Elf            195       198       
Boris     Troll          198       143       
Elia      Fairy          78        158       
Gora      Dragon         123       152

Test Case #9:  Exiting the Program
Input: 4 
Output: 
Enter your choice: 4
Exiting program.


...Program finished with exit code 0
Press ENTER to exit console.

Test Case #10: Testing Multiple Sequential Menu Selections
Input: 2, 1, 3, 4 
Output: 
Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 2
Army updated.


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 3
Name      Type             Strength    Health    Damage
Orson     Centaur        125       198               77
Nara      Elf            128       173               68
Boris     Troll          146       116               51
Elia      Fairy          199       156               78
Gora      Dragon         128       53                64


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 1
Name      Type             Strength    Health
Orson     Centaur        125       198       
Nara      Elf            128       173       
Boris     Troll          146       116       
Elia      Fairy          199       156       
Gora      Dragon         128       53        


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 4
Exiting program.


...Program finished with exit code 0
Press ENTER to exit console.

Test Case #11: Checking How the Program Handles Maximum Army Capacity
Input: Modifying army.updateArmy(names, types, 5); to army.updateArmy(names, types, 12); and modifying the predefined arrays names and types to include more than 10 entries 
Output: Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 2
Army updated.


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 1
Name      Type             Strength    Health
Orson     Centaur        129       157       
Nara      Elf            154       61        
Boris     Troll          92        67        
Elia      Fairy          146       172       
Gora      Dragon         156       95        
Lina      Goblin         109       79        
Koda      Ogre           168       91        
Mira      Sprite         83        138       
Tara      Phoenix        97        117       
Zane      Unicorn        77        90

Test Case #12: Verifying Damage Values Are Always Between 1 and Creature's Strength
Input: 2 and then 1 and then selected 3 multiple times (5+ times)
Output:
Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 2
Army updated.


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 1
Name      Type             Strength    Health
Orson     Centaur        137       182       
Nara      Elf            149       115       
Boris     Troll          157       105       
Elia      Fairy          168       98        
Gora      Dragon         100       183       


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 3
Name      Type             Strength    Health    Damage
Orson     Centaur        137       182               78
Nara      Elf            149       115              123
Boris     Troll          157       105               48
Elia      Fairy          168       98               127
Gora      Dragon         100       183               35


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 3
Name      Type             Strength    Health    Damage
Orson     Centaur        137       182               99
Nara      Elf            149       115               13
Boris     Troll          157       105               54
Elia      Fairy          168       98               113
Gora      Dragon         100       183               72


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 3
Name      Type             Strength    Health    Damage
Orson     Centaur        137       182              134
Nara      Elf            149       115              103
Boris     Troll          157       105               93
Elia      Fairy          168       98               124
Gora      Dragon         100       183               33


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 3
Name      Type             Strength    Health    Damage
Orson     Centaur        137       182              137
Nara      Elf            149       115               73
Boris     Troll          157       105                6
Elia      Fairy          168       98                76
Gora      Dragon         100       183               18


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 3
Name      Type             Strength    Health    Damage
Orson     Centaur        137       182               28
Nara      Elf            149       115               12
Boris     Troll          157       105              107
Elia      Fairy          168       98               134
Gora      Dragon         100       183               79


Menu:
1. Print the list of creatures
2. Update the array of creatures
3. Print damage for all creatures
4. Exit
Enter your choice: 3
Name      Type             Strength    Health    Damage
Orson     Centaur        137       182              105
Nara      Elf            149       115               69
Boris     Troll          157       105               55
Elia      Fairy          168       98                39
Gora      Dragon         100       183               37



*/


