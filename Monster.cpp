#include "Monster.h"
#include "Player.h"
#include <thread>
#include <chrono>

//Default constructor
Monster::Monster():Entity(){
    fWeapon = nullptr;
}
//Overloaded constructor
Monster::Monster(string pName, int pAttackDamage, int pHealth, Weapon* pWeapon):Entity(pName, pAttackDamage, pHealth), fWeapon(pWeapon){};

Monster::~Monster() {
    if (fWeapon != nullptr) {
        delete fWeapon;
    }
}
//Getter for fWeapons
Weapon* Monster::getWeapon(){
    return fWeapon;
}

void Monster::Jumpscare1(){
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("jumpscare.wav")) {
        std::cerr << "Error loading sound file!" << std::endl;
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
    system("Color 0E");
}

void Monster::Jumpscare2() {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("jumpscare2.wav")) {
        std::cerr << "Error loading sound file!" << std::endl;
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

bool Monster::DisturbRest(Player& pPlayer, int pChance) {
    srand(static_cast<unsigned int>(time(0)));
    if (rand() % 100 < pChance) {
        if (pPlayer.getfIsResting()) {
            system("CLS");
            cout << "\nAs you attempt to rest, you hear rustling in the bushes...\n";
            this_thread::sleep_for(chrono::milliseconds(1500));
            cout << "Suddenly, the shadows shift, and you sense a presence lurking nearby!\n";
            this_thread::sleep_for(chrono::milliseconds(1500));

            // Determine if the disturbance leads to an ambush
            int chanceOfDamage = rand() % 100;
            if (chanceOfDamage < 40) {
                cout << "The creature lunges at you, catching you off guard!\n";
                pPlayer.TakeDamage(10);
                cout << "You feel a sharp pain as it claws at you, causing 10 damage!\n";
            }
            else {
                cout << "You manage to wake up just in time to see the monster retreat into the shadows.\n";
                this_thread::sleep_for(chrono::milliseconds(1500));
            }
            cout << "You lose " << 1 << " stamina from the disturbance!" << endl;
            pPlayer.DecreaseStamina(1);
            pPlayer.setIsResting(false);
            cout << endl;
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}