/*
 Emily Lopez
 Noble.h
*/
#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Protector;
    class Noble {
        friend std::ostream& operator<<(std::ostream& os,
            const Noble& theNoble);
    public:
        // constructor
        Noble(const std::string& name);
        // name getter
        const std::string getName() const;
        // strength getter
        virtual double getStrength() const = 0;
        // change strength
        virtual void updateStrength(double winner, double loser) = 0;
        // status getter
        bool getStatus() const;
        // status setter
        void setStatus();
        // update to dead status
        void death();
        // display a battle
        void battle(Noble& rhs);
        // defend
        virtual void defend() const = 0;
        // display a Noble using output operator
        virtual void displayNoble(std::ostream& os) const = 0;
    private:
        std::string name;
        bool alive;
    };

    class Lord : public Noble {
    public:
        //constructor
        Lord(const std::string& name);
        // hire
        bool hires(Protector& aProtector);
        // fire
        bool fires(Protector& aProtector);
        // strength getter
        double getStrength() const override;
        // change strength
        void updateStrength(double winner, double loser) override;
        // removes a protector
        bool remove(Protector& aProtector);
        // defend
        void defend() const;
        // display a Noble using output operator
        void displayNoble(std::ostream& os) const ;
    private:
        std::vector<Protector*> army;
    };
    class PersonWithStrengthToFight : public Noble {
    public:
        // constructor
        PersonWithStrengthToFight(const std::string& name, double hisStrength);
        // strength getter
        double getStrength() const override;
        // change strength
        void updateStrength(double winner, double loser) override;
        // defend
        void defend() const;
        // display a Noble using output operator
        void displayNoble(std::ostream& os) const;
    private:
        double hisStrength;
    };
}