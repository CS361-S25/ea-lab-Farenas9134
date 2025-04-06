#include <iostream>
#include <cstdint>
#include "Empirical/include/emp/math/Random.hpp"
using namespace std;

int main() {
    emp::Random random(1);

    class Organism {
        double behavior;
        public:
            Organism(double given_behavior) {
                behavior = given_behavior;
            }

            double GetBehavior() {
                return behavior;
            }

            Organism* reproduce(emp::Random random) {
                Organism* child = new Organism(GetBehavior());
                child->mutate(random);
                return child;
            }

            void mutate(emp::Random random) {
                behavior += random.GetRandNormal(0.0, 0.02);
            }
    };

    emp::vector<Organism*> population;

    for (int i = 0; i < 100; i++){
        population.push_back(new Organism(0.5));
    }

    Organism* TotalMax = population[1];

    for (int i = 0; i < 10000; i++){
        Organism* CurrentMax = population[0];
        Organism* CurrentLeast = population[0];

        for (Organism* candidate : population){
            if (candidate->GetBehavior() > CurrentMax->GetBehavior()){
                CurrentMax = candidate;
            }
            if (candidate->GetBehavior() < CurrentLeast->GetBehavior()){
                CurrentLeast = candidate;
            }
        }
        //population.pop_back(); How do we pop targeted element?
        Organism* child = CurrentMax->reproduce(random);
        int overwrite = random.GetUInt(0,100);
        population[overwrite] = child;

        if (TotalMax->GetBehavior() < child->GetBehavior()){
            TotalMax = child;
        }
    }

    cout << TotalMax->GetBehavior() << endl;

    return 0; 
}