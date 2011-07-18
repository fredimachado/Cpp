/**
 * Studying C++
 * Class inheritance
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

class CelestialBody
{
    public:
        CelestialBody(double mass)
            : _mass(mass)
        {
            printf("Creating celestial body of mass %g.\n", _mass);
        }

        ~CelestialBody()
        {
            printf("Destroying celestial body of mass %g.\n", _mass);
        }

    private:
        const double _mass;
};

class Star: public CelestialBody
{
    public:
        Star(double mass, double brightness)
            : CelestialBody(mass), _brightness(brightness)
        {
            printf("Creating a star of brightness %g.\n", _brightness);
        }

        ~Star()
        {
            printf("Destroying a star of brightness %g.\n", _brightness);
        }

    private:
        const double _brightness;
};

int main ()
{
    printf("Entering main.\n");
    Star aStar(1234.5, 0.1);
    printf("Exiting main.\n");
}