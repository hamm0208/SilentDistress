#include "Monster.h"
#include "Player.h"
#include <thread>
#include <chrono>

//Default constructor
Monster::Monster():Entity(), fComboAttack(3) {
    fWeapon = nullptr;
    fSkillSet[0] = { "Claw Swipe", 5 };
    fSkillSet[1] = { "Bite", 8 };
    fSkillSet[2] = { "Claw of the damned", fWeapon->getDamage() };
    fSkillSet[3] = { "Fatal Lunge", 15 };
    fSkillSet[4] = { "Tail Sweep", 7 };
    fSkillSet[5] = { "Charge", 10 };
}
//Overloaded constructor
Monster::Monster(string pName, int pAttackDamage, int pHealth, Weapon* pWeapon):Entity(pName, pAttackDamage, pHealth), fWeapon(pWeapon), fComboAttack(3) {
    fSkillSet[0] = { "Claw Swipe", 5 };
    fSkillSet[1] = { "Bite", 8 };
    fSkillSet[2] = { "Claw of the damned", fWeapon->getDamage()};
    fSkillSet[3] = { "Fatal Lunge", 15 };
    fSkillSet[4] = { "Tail Sweep", 7 };
    fSkillSet[5] = { "Charge", 10 };
};

//Destructor
Monster::~Monster() {
    if (fWeapon != nullptr) {
        delete fWeapon;
    }
}
//Getter for fWeapons
Weapon* Monster::getWeapon(){
    return fWeapon;
}

void Monster::addComboAttack(const string& actionName, int damage) {
    Attacks newAttack = { actionName, damage };
    fComboAttack.Push(newAttack);  // Adds the attack to the stack
}

void Monster::selectRandomCombo() {
    // Clear previous combo stack
    while (!fComboAttack.IsEmpty()) {
        fComboAttack.Pop();
    }

    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Array to keep track of selected attacks to avoid duplicates
    bool selected[6] = { false, false, false, false, false, false };

    // Randomly select 3 different attacks from the skillset
    for (int i = 0; i < 3; ++i) {
        int index;
        do {
            index = rand() % 6;  // Randomly pick an index from 0 to 5
        } while (selected[index]); // Ensure it's not already selected

        selected[index] = true; // Mark this attack as selected
        addComboAttack(fSkillSet[index].name, fSkillSet[index].damage); // Add attack to combo stack
    }
}

void Monster::executeCombo(Player& pPlayer) {
    int totalDamage = 0;
    while (!fComboAttack.IsEmpty()) {
        Attacks action = fComboAttack.Pop();
        cout << getName() << " performs: " << action.name << " with damage: " << action.damage << endl;
        pPlayer.TakeDamage(action.damage);
        this_thread::sleep_for(chrono::milliseconds(1000));
        totalDamage+=action.damage;
    }
    cout << getName() << " has dealt " << to_string(totalDamage);
}

//Jumpscare 1
void Monster::Jumpscare1(){
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("jumpscare.wav")) {
        cerr << "Error loading sound file!" << endl;
        return;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(100);  // Adjust volume as needed
    string asciiArt = R"(
                 ___====-_  _-====___
           _--^^^#####//      \\#####^^^--_
        _-^##########// (    ) \\##########^-_
       -############//  |\^^/|  \\############-
     _/############//   (@::@)   \\############\_
    /#############((     \\//     ))#############\
   -###############\\    (oo)    //###############-
  -#################\\  / VV \  //#################-
 -###################\\/      \//###################-
_#/|##########/\######(   /\   )######/\##########|\#_
|/ |#/\#/\#/\/  \#/\##\  |  |  /##/\#/  \/\#/\#/\#| \|
`  |/  V  V  `   V  \#\| |  | |/#/  V   '  V  V  \|  '
   `   `  `      `   / | |  | | \   '      '  '   '
                    (  | |  | |  )
                   __\ | |  | | /__
                  (vvv(VVV)(VVV)vvv)
------------------------------------------------------------
    )";
    system("CLS");
    sound.play();
    bool ChangingColour = true;
    for (int x = 0; x < 20; x++) {
        cout << asciiArt;
        this_thread::sleep_for(chrono::milliseconds(200));
        if (x == 19) {
            break;
        }
        system("CLS");
        //Interchang colour from red to green
        if (ChangingColour) {
            system("Color 0A");
        }
        else {
            system("Color 0C");
        }
        ChangingColour = !ChangingColour;
    }
    this_thread::sleep_for(chrono::seconds(1));  // Pause before message
    cout << "\nYou feel a chill down your spine...\n";
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "A dark voice whispers, \"I'm coming for you...\"\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Run... if you think you can escape...\n";
    cout << "\n\n";
    for (int x = 0; x < 20; x++) {
        if (ChangingColour) {
            system("Color 0A");
        }
        else {
            system("Color 0C");
        }
        ChangingColour = !ChangingColour;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    while (sound.getStatus() == sf::Sound::Playing) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    system("PAUSE");
    system("CLS");
    system("Color 0E"); //Back to default colour
}

//Jumpscare 2
void Monster::Jumpscare2() {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("jumpscare2.wav")) {
        cerr << "Error loading sound file!" << endl;
        return;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(100);  // Adjust volume as needed
    string asciiArt = R"(
                                              ,--,  ,.-.
                ,                   \,       '-,-`,'-.' | ._
               /|           \    ,   |\         }  )/  / `-,',
               [ '          |\  /|   | |        /  \|  |/`  ,`
               | |       ,.`  `,` `, | |  _,...(   (      _',
   -ART BY-    \  \  __ ,-` `  ,  , `/ |,'      Y     (   \_L\
    -ZEUS-      \  \_\,``,   ` , ,  /  |         )         _,/
                 \  '  `  ,_ _`_,-,<._.<        /         /
                  ', `>.,`  `  `   ,., |_      |         /
                    \/`  `,   `   ,`  | /__,.-`    _,   `\
                -,-..\  _  \  `  /  ,  / `._) _,-\`       \
                 \_,,.) /\    ` /  / ) (-,, ``    ,        |
                ,` )  | \_\       '-`  |  `(               \
               /  /```(   , --, ,' \   |`<`    ,            |
              /  /_,--`\   <\  V /> ,` )<_/)  | \      _____)
        ,-, ,`   `   (_,\ \    |   /) / __/  /   `----`
       (-, \           ) \ ('_.-._)/ /,`    /
       | /  `          `/ \\ V   V, /`     /
    ,--\(        ,     <_/`\\     ||      /
   (   ,``-     \/|         \-A.A-`|     /
  ,>,_ )_,..(    )\          -,,_-`  _--`
 (_ \|`   _,/_  /  \_            ,--`
  \( `   <.,../`     `-.._   _,-`
   `           
    )";
    system("CLS");
    system("Color 0C");
    sound.play();
    cout << asciiArt;
    while (sound.getStatus() == sf::Sound::Playing) {
    }
    system("Color 0E");
}

//Ambush player
void Monster::Ambush(Player& pPlayer) {
    // Determine the damage to inflict on the player
    int damage = 8 + (rand() % 5);  // Base damage + random up to 5
    int staminaLoss = 1;                            // Stamina loss between 1 and 4

    // Reduce the player's health and stamina
    pPlayer.TakeDamage(damage);
    pPlayer.DecreaseStamina(staminaLoss);

    // Ambush text for horror effect
    cout << "\nAs you move through the darkness, a sudden chill freezes you in place...\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "A shadowy figure lunges at you from the shadows!\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "You feel a sharp pain as it claws at you, causing " << damage << " damage!\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Your strength fades, losing " << staminaLoss << " stamina in the struggle.\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    system("PAUSE");
    system("CLS");
};

//Distrub player's rest
bool Monster::DisturbRest(Player& pPlayer, int pChance) {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator with the current time

    if (rand() % 100 < pChance) {  // Check if the random chance triggers the monster's disturbance
        if (pPlayer.getfIsResting()) {  // Proceed only if the player is currently resting
            system("CLS");  // Clear the screen for dramatic effect
            cout << "\nAs you attempt to rest, you hear rustling in the bushes...\n";
            this_thread::sleep_for(chrono::milliseconds(1500));  // Pause for effect
            cout << "Suddenly, the shadows shift, and you sense a presence lurking nearby!\n";
            this_thread::sleep_for(chrono::milliseconds(1500));  // Pause again for suspense

            // Determine if the disturbance escalates into an ambush
            int chanceOfDamage = rand() % 100;  // Generate a random chance for taking damage
            if (chanceOfDamage < 40) {  // 40% chance that the player is attacked
                cout << "The creature lunges at you, catching you off guard!\n";
                pPlayer.TakeDamage(10);  // Apply 10 damage to the player
                cout << "You feel a sharp pain as it claws at you, causing 10 damage!\n";
            }
            else {
                cout << "You manage to wake up just in time to see the monster retreat into the shadows.\n";
                this_thread::sleep_for(chrono::milliseconds(1500));  // Pause before the next line
            }

            // Player loses 1 stamina point due to the disturbance
            cout << "You lose " << 1 << " stamina from the disturbance!" << endl;
            pPlayer.DecreaseStamina(1);  // Decrease stamina by 1
            pPlayer.setIsResting(false);  // End the player's resting state
            cout << endl;
            return true;  // Return true indicating a successful disturbance
        }
        else {
            return false;  // Player was not resting, no disturbance occurs
        }
    }
    else {
        return false;  // Disturbance chance did not trigger
    }
}

