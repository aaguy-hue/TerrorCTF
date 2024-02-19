#include <array>      // Allows for use of std::array
#include <string>     // Allows for use of std::string
#include <chrono>     // To pause execution after dialogue
#include <thread>     // To pause execution after dialogue
#include <cstring>    // Allows for use of strcat()
#include <fstream>    // Allows for opening files
#include <iostream>   // Allows for console I/O
#include <algorithm>  // Allows for use of std::min and std::all_of
#include <functional> // Allows for use of std::function

/*


Program: Press wasd to move around the map, move your character onto n to open the shopping menu, a to open the tailor shop menu, m to open the museum menu, etc. You will sometimes have random encounters where you will encounter a bug (or a fish if you're next to a river), you can use a net to catch both, which you get from nook's cranny, but nook's cranny only let's you buy stuff if you're wearing good clothes, so you have to head over to able sisters to buy some clothes first.

Goal: You want to donate all bugs and fish in the game to the museum.


. is grass            1x1
r is rock             1x1
t is tree             1x1
s is town square      3x3
n is general store    2x2
a is tailor shop      2x2
m is museum           2x2
w is water            1x1
p is player           1x1

map is 15x15

.wwww.....w....
....w.....w....
....w.tt..w....
....w.mm..wwwww
....w.mm.......
....w...sss..nn
....w...sss..nn
.tt.w...sss....
....w........aa
....w...t....aa
..t.wwwwwwwwwww
....w.........w
t...w..t......w
wwwww.........w
......tt......w

*/

void waitsecond() {
    std::chrono::seconds onesec(1);
    std::this_thread::sleep_for(onesec);
}

void speak(const std::string person, const std::string dialogue, const int newLinesStart=0, const int newLinesEnd=1, const bool wait=true, const int speed=1000) {
    std::chrono::milliseconds duration(std::min(175, (int)(speed/dialogue.length())));

    for (int i = 0; i < newLinesStart; i++) {
        std::cout << "\n";
    }
    
    std::cout << person << ": ";
    for (char const &ch: dialogue) {
        std::cout << ch;
        std::flush(std::cout);
        std::this_thread::sleep_for(duration);
    }
    
    for (int i = 0; i < newLinesEnd; i++) {
        std::cout << "\n";
    }

    if (wait) { waitsecond(); }
}

std::string loadflag() {
    std::ifstream flagfile("flag.txt");

    if (!flagfile) {
        return "Please create a flag.txt file for debugging.";
    }

    std::string flag;
    flagfile >> flag;

    flagfile.close();
    return flag;
}

unsigned long loadpass() {
    std::ifstream passfile("vaultpass.txt");

    if (!passfile) {
        std::cout << "Please create a vaultpass.txt file for debugging.";
        return -1;
    }

    std::string tmp;
    passfile >> tmp;
    passfile.close();
    
    unsigned long pass = std::stoul(tmp, nullptr, 16);

    return pass;
}

bool isHexChar(char ch) {
    std::array<char, 16> hexchars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (char c : hexchars) {
        if (ch == c) {
            return true;
        }
    }
    
    return false;
}

bool isHex(std::string input) {
    if (input.length() != 7) { return false; }

    std::string unprefixed = input.substr(2);

    if (input.substr(0, 2) == "0x" && std::all_of(unprefixed.begin(), unprefixed.end(), isHexChar)) {
        return true;
    }
    return false;
}

int menu(const std::string phrase, const int optionsAmount) {
    int retval;
    do {
        std::cout << "Where would you like to go? ";
        if (!(std::cin >> retval)) {
            std::cin.clear();             // Clear the error flag on cin
            std::cin.ignore(10000,'\n');  // Ignore non-number stuff, go to next line
        }
    } while (retval > optionsAmount && retval < 0);

    return retval;
}

bool yesno(const std::string person, const std::string question) {
    char ch;
    while (ch != 'y' && ch != 'n') {
        speak(person, question + " [y/n] ", 0, 0);
        std::cin.get(ch);
        std::cin.clear();             // Clear the error flag on cin
        std::cin.ignore(10000,'\n');  // Ignore extra chars, go to next line
    }

    return ch == 'y';
}

std::string askQuestion(const std::string person, const std::string question) {
    speak(person, question+" ", 0, 0);
    
    std::string ans = "";
    while (std::all_of(ans.begin(), ans.end(), isspace) && ans.length() < 1) {
        std::getline(std::cin, ans);
    }

    return ans;
}

std::string askQuestion(const std::string person, const std::string question, std::function<bool(std::string)> callback) {
    speak(person, question+" ", 0, 0);
    
    std::string ans = "";
    while (std::all_of(ans.begin(), ans.end(), isspace) && ans.length() < 1 && !callback(ans)) {
        std::getline(std::cin, ans);
    }

    return ans;
}

int optionsMenu(int money) {
    if (money < 0) {
        std::cout << "\n\nMoney: ∞";
    }
    else {
        std::cout << "\n\nMoney: $" << money << "\n";
    }
    
    std::cout << "\n0) Access Tom Nook's Vault\n1) General Store\n2) Tailor Shop\n3) Museum\n4) End Program\n";

    return menu("Where would you like to go?", 4);
}

int nookscranny(int money, const bool goodclothes) {
    if (!goodclothes) {
        speak("Timmy", "Welcome to Nook's Cranny! Here's our selec-", 2);
        speak("Timmy", "Hold up, you can't walk into our store with torn up clothes like that!");
        speak("Tommy", "You can visit the tailor shop and get some decent clothes first.");
    }
    else {
        speak("Timmy", "Welcome to Nook's Cranny! Here's our selection of items today:", 2);
        std::cout << "1) Flag - $100,000,000,000,000 (100 trillion USD)\n";
        waitsecond();
        speak("Tommy", "...it seems that all other items have suspiciously disappeared.", 0, 2);

        bool buyflag = yesno("Timmy", "Would you like to buy the flag?");

        if (buyflag) {
            if (money < 0) {
                speak("Tommy", "Thanks for your purchase! Here's your flag:");
                std::cout << loadflag() << "\n";
                money = 0;
            }
            else {
                speak("Tommy", "Thanks for your purcha- Oh! You don't have enough money in your pockets. Our store doesn't offer a line of credit, so please come back when you have enough money.");
            }
        }
        else {
            speak("Timmy", "Oh! Didn't catch your eye? We'll see you next time!");
        }
    }

    return money;
}

int ablesisters(int money, const bool goodclothes) {
    speak("Mabel", "Welcome to Able Sisters, where we sell fashions made lovingly by hand!", 2);
    
    if (!goodclothes) {
        speak("Sable", "ᵐᵃᵇᵉˡ, ᵖˡᵉᵃˢᵉ ᵍᵉᵗ ᵗʰᵉˢᵉ ᶜᵘˢᵗᵒᵐᵉʳˢ ˢᵒᵐᵉ ᵈᵉᶜᵉⁿᵗ ᶜˡᵒᵗʰᵉˢ");
        speak("Mabel", "You know what, we'll give you these wonderful clothes for just $1 since you're a first time customer. We look forward to seeing you again!");
        --money;
        speak("Sable", "ⁱ ᵈᵒⁿ'ᵗ");
    }
    else {
        speak("Sable", "ᵐᵃᵇᵉˡ, ᵖˡᵉᵃˢᵉ ᵍᵉᵗ ᵗʰᵉˢᵉ ᵖᵉᵒᵖˡᵉ ᵒᵘᵗ ᵒᶠ ᵒᵘʳ ˢᵗᵒʳᵉ");
        speak("Mabel", "ᵒᵏ ᶠⁱⁿᵉ");
        speak("Mabel", "It seems that we're out of stock today. Unfortunately, we will not be able to sell anything.");
    }

    return money;
}

void donateSpecimen() {
    unsigned long pass = loadpass();
    char* donation = &askQuestion("Blathers", "What would you like to donate?")[0];

    speak("Blathers", "Yay! Now we'll have the following specimen:", 0, 1, false);
    printf(donation);
    speak("Blathers", "Why, you don't seem to have any specimens on you! Please leave.", 1);
}

int museum(int money) {
    speak("Blathers", "Hello! Welcome to the Animal Crossing Museum! Currently, the only specimen in the museum is an owl.", 2);

    bool donate = yesno("Blathers", "Would you like to donate something?");
    if (donate) {
        donateSpecimen();
    }
    else {
        speak("Blathers", "Oh well. I look forward to seeing you again.");
    }

    return money;
}

int vault(int money) {
    if (money < 0) {
        speak("GUARD 1", "Mr.Nook, you already claimed your money.");
        return -1;
    }

    speak("GUARD 2", "Yo GUARD 1, I heard this rumor that Mr.Nook hid his password on a sticker in the museum.", 2);
    speak("GUARD 1", "Shut up GUARD 2, there's a random kid here.");

    speak("GUARD 1", "Hey kid, only Tom Nook may enter this vault.");
    bool enter = yesno("GUARD 1", "Are you Tom Nook?");
    if (enter) {
        speak("GUARD 1", "Bruh take this kid away, I was literally joking earlier, he's obviously not Mr.Nook.");
        speak("GUARD 2", "WAIT! It might be Mr.Nook in disguise. Just ask him for the password.");
        
        std::string tmp = askQuestion("GUARD 1", "Ok fine. What's Tom Nook's favorite 7-digit hexadecimal number, kid? Format: 0xDEADBEEF.", &isHex);

        int pass = std::stoul(tmp, nullptr, 16);
        unsigned long actualPass = loadpass();
        
        if (actualPass == -1) {
            speak("SYSTEM", "Unable to load vault password. Please leave immediately.");
            return money;
        }

        if (pass == actualPass) {
            speak("GUARD 1", "I- I'm sorry Mr.Nook! I couldn't recognize your greatness. Please spare me and my family. Here is your money.");

            money = -1;

            speak("SYSTEM", "Gained access to infinite money.");
        }
        else {
            speak("GUARD 1", "What did I tell you? This kid is obviously not Mr.Nook.");
        }

    }
    else {
        speak("GUARD 1", "Then get out of here!");
    }

    return money;
}

int main() {
    std::string map = "THE ISLAND\n---------------\n.wwww.....w....\n....w.....w....\n....w.tt..w....\n....w.mm..wwwww\n....w.mm.......\n....w...sss..nn\n....w...sss..nn\n.tt.w...sss....\n....w........aa\n....w...t....aa\n..t.wwwwwwwwwww\n....w.........w\nt...w..t......w\nwwwww.........w\n......tt......w";

    std::cout << map;

    int location;
    int money = 1;
    bool goodclothes = false;

    while ((location = optionsMenu(money)) != 4) {
        if (location == 0) {
            // money = -1;
            money = vault(money);
        }
        else if (location == 1) {
            int tmp = money;
            money = nookscranny(money, goodclothes);
            if (tmp != money) { break; }
        }
        else if (location == 2) {
            int tmp = money;
            money = ablesisters(money, goodclothes);
            if (tmp != money) { goodclothes = true; }
        }
        else if (location == 3) {
            money = museum(money);
        }
    }

    return 0;
}