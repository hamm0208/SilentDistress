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

void Monster::Jumpscare(){
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("jumpscare.wav")) {
        std::cerr << "Error loading sound file!" << std::endl;
        return;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(110);  // Adjust volume as needed
    string asciiArt = R"(
               .-"------"-.
              /            \
             |              |
             |,  .-.  .-. ,|
             | )(__/  \__)( |
             |/     /\     \|
             (_     ^^     _)
              \__|IIIIII|__/
               | \IIIIII/ |
               \          /
                `--------`
                  |    |
                  |    |
                  |    |
------------------------------------------
    )";
    sound.play();
    for (const auto& line : asciiArt) {
        cout << line;
        this_thread::sleep_for(chrono::milliseconds(1));  // Adjust delay as needed
    }
    this_thread::sleep_for(std::chrono::seconds(1));  // Pause before message
    cout << "\nYou feel a chill down your spine...\n";
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << "A dark voice whispers, \"I'm coming for you...\"\n";
    this_thread::sleep_for(std::chrono::milliseconds(1500));
    cout << "Run... if you think you can escape...\n";
    this_thread::sleep_for(std::chrono::milliseconds(2000));

    cout << "\n\n";
    while (sound.getStatus() == sf::Sound::Playing) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Monster::Ambush(Player& pPlayer) {

    // Determine the damage to inflict on the player
    int damage = getAttackDamage() + (rand() % 5); // Base damage + random up to 5
    int staminaLoss = 10 + (rand() % 5);       // Stamina loss between 10 and 15

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
};

bool Monster::DisturbRest(Player& pPlayer) {
    // Simulate the disturbance
    if (pPlayer.getfIsResting()) {
        cout << "\nAs you attempt to rest, you hear rustling in the bushes...\n";
        this_thread::sleep_for(chrono::milliseconds(1500));
        cout << "Suddenly, the shadows shift, and you sense a presence lurking nearby!\n";
        this_thread::sleep_for(chrono::milliseconds(1500));

        // Determine if the disturbance leads to an ambush
        int chanceOfDamage = rand() % 100;
        if (chanceOfDamage < 40) {
            cout << "The creature lunges at you, catching you off guard!\n";
            pPlayer.TakeDamage(10);
            pPlayer.DecreaseStamina(10);
            cout << "You feel a sharp pain as it claws at you, causing 10 damage!\n";
        }
        else {
            cout << "You manage to wake up just in time to see the monster retreat into the shadows.\n";
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
        cout << "You lose " << 10 << " stamina from the disturbance!" << endl;
        pPlayer.DecreaseStamina(10);
        pPlayer.setIsResting(false);
        return true;
    }
    else {
        return false;
    }
}