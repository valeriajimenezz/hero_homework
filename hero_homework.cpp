#include <iostream>
#include <string>

class GameObject {
public:
    int instanceId;
    virtual ~GameObject() {}
};

class Stats {
private:
    int health;
    int attackPoints;
public:
    Stats() {
        health = 100;
        attackPoints = 10;
    }
    
    int getHealth() { return health; }
    void setHealth(int h) { health = h; }
    
    int getAttackPoints() { return attackPoints; }
    void setAttackPoints(int a) { attackPoints = a; }
};

enum MarkType {
    SUPPORT,
    DPS,
    TANK
};

class SoulMark {
private:
    MarkType type;
    int powerBonus;
public:
    SoulMark(MarkType t) {
        type = t;
        powerBonus = 20;
    }
    
    void activatePower() {
        if (type == SUPPORT) {
            std::cout << "Healing allies for " << powerBonus << " HP!" << std::endl;
        } else if (type == DPS) {
            std::cout << "Boosting attack damage by " << powerBonus << "!" << std::endl;
        } else if (type == TANK) {
            std::cout << "Raising defense by " << powerBonus << "!" << std::endl;
        }
    }
};

class Weapon {
protected:
    std::string name;
    int baseDamage;
    
    Weapon(std::string n, int bd) {
        name = n;
        baseDamage = bd;
    }
    
public:
    virtual void attack() {
        std::cout << "Attacked with " << name << " for " << baseDamage << " damage!" << std::endl;
    }
    virtual ~Weapon() {}
};

class Sword : public Weapon {
private:
    int sharpness;
public:
    Sword(std::string n, int bd, int s) : Weapon(n, bd) {
        sharpness = s;
    }
    
    void attack() override {
        std::cout << "Slashed with " << name << " dealing " << (baseDamage + sharpness) << " damage!" << std::endl;
    }
};

class Potion {
private:
    int healthRestore;
    int attackBoost;
public:
    Potion(int hr, int ab) {
        healthRestore = hr;
        attackBoost = ab;
    }
    
    int getHealthRestore() { return healthRestore; }
    int getAttackBoost() { return attackBoost; }
};

class Guild {
public:
    std::string guildName;
    
    Guild(std::string name) {
        guildName = name;
    }
};

class Hero : public GameObject {
private:
    Stats stats;
    SoulMark soul;
    Weapon* weapon;
    Guild* guild;
    
public:
    Hero(MarkType markType) : soul(markType) {
        instanceId = 1;
        weapon = nullptr;
        guild = nullptr;
    }

    void equipWeapon(Weapon* w) {
        weapon = w;
    }

    void unequipWeapon() {
        weapon = nullptr;
    }

    void joinGuild(Guild* g) {
        guild = g;
    }

    void leaveGuild() {
        guild = nullptr;
    }

    void usePotion(Potion* p) {
        if (p != nullptr) {
            stats.setHealth(stats.getHealth() + p->getHealthRestore());
            stats.setAttackPoints(stats.getAttackPoints() + p->getAttackBoost());
            std::cout << "Used potion! HP +" << p->getHealthRestore() << ", Attack +" << p->getAttackBoost() << std::endl;
        }
    }

    void attack() {
        if (weapon != nullptr) {
            weapon->attack();
        } else {
            std::cout << "Hero attacks with bare hands!" << std::endl;
        }
        soul.activatePower();
    }

    ~Hero() override {
        std::cout << "Hero destroyed! Stats and SoulMark are automatically removed from memory." << std::endl;
    }
};

int main() {
    Guild* guild = new Guild("Knights of the Round");
    Hero* hero = new Hero(DPS);
    Sword* sword = new Sword("Excalibur", 20, 5);

    hero->joinGuild(guild);
    hero->equipWeapon(sword);
    
    Potion potion(50, 10);
    hero->usePotion(&potion);
    
    hero->attack();

    std::cout << "Guild name before hero dies: " << guild->guildName << std::endl;

    delete hero;

    std::cout << "Guild name after hero dies: " << guild->guildName << std::endl;

    delete guild;
    delete sword;

    return 0;
}
