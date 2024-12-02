/*
 Emily Lopez
 Protector.h
*/
#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
    class Lord;

    class Protector {
        friend std::ostream& operator<<(std::ostream& os,
            const Protector& theProtector);
    public:
        Protector(const std::string& name, double hisStrength);
        double getStrength() const;
        void setStrength(double newStrength);
        void setStatus(double strength);
        void setLord(Lord* lordPtr);
        Lord* getLord() const;
        const std::string& getName() const;
        bool runaway();
        virtual void defend() const = 0;
    private:
        std::string name;
        double hisStrength;
        Lord* lord;
    };

    class Wizard : public Protector {
    public:
        using Protector::Protector;
        void defend() const override;
    };
    class Warrior : public Protector {
    public:
        using Protector::Protector;
        void defend() const override;
    };
    class Archer : public Warrior {
        using Warrior::Warrior;
        void defend() const override;
    };
    class Swordsman : public Warrior {
        using Warrior::Warrior;
        void defend() const override;
    };
}
