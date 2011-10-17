#ifndef RANDOM_H_
#define RANDOM_H_


class Random
{
public:

    /**
     * Return a random float in [0 1].
     */

    static float randomFloat();
};


inline float Random::randomFloat()
{
    return static_cast<float> (random()) / static_cast<float> (RAND_MAX);
}


#endif
