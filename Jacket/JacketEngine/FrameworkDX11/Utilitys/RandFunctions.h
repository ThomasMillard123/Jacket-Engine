#pragma once
#include <random>
#include<algorithm>
#include<vector>
namespace Engine::Utilitys::RandFunc {

    //rand int
    template<typename T>
    T random(T range_from, T range_to) {
        std::random_device   rand_dev;
        std::mt19937                        generator(rand_dev());
        std::uniform_int_distribution<T>    distr(range_from, range_to);
        return distr(generator);
    }
   
    //rand float,double
    template<typename T>
    T randomFloat(T range_from, T range_to) {
        std::random_device   rand_dev;
        std::mt19937                        generator(rand_dev());
        std::uniform_real_distribution<T>    distr(range_from, range_to);
        return distr(generator);
    }
    //rand bool
    static bool RandomBool(float P) {
        std::random_device   rand_dev;
        std::mt19937  generator(rand_dev());
        std::bernoulli_distribution distr(std::clamp(P,0.0f,1.0f));
        return distr(generator);
    }

    //seeded 
    static std::mt19937 generatorStatic;
    static int seed = 0;

    template<typename T>
    T random(T range_from, T range_to, int Seed) {
        //std::random_device   rand_dev;
        if (Seed != seed) {
            generatorStatic.seed(Seed);
            seed = Seed;
        }
        std::uniform_int_distribution<T>    distr(range_from, range_to);
        return distr(generatorStatic);
    }

    template<typename T>
    T randomFloat(T range_from, T range_to, int Seed=0) {
        //std::random_device   rand_dev;
        if (Seed != seed && Seed !=0) {
            generatorStatic.seed(Seed);
            seed = Seed;
        }
        std::uniform_real_distribution<T>    distr(range_from, range_to);
       
        return distr(generatorStatic);
    }

    static void SetSeed(int Seed) {
        generatorStatic.seed(0);
        seed = Seed;
        generatorStatic.seed(seed);
    }
    static int GetSeed() { return seed; }
    static  std::mt19937 getRandEnine() {
        return generatorStatic;
    }

}