#include <iostream>
#include "../../include/Point3D.hpp"
#include "../../include/Vector3D.hpp"

struct Projectile {
    raytracer::maths::Point3D<double> position_;
    raytracer::maths::Vector3D<double> velocity_;
    Projectile(const raytracer::maths::Point3D<double> &position, const raytracer::maths::Vector3D<double> &velocity) :
    position_(position),
    velocity_(velocity) {

    }
};

struct Environment {
    raytracer::maths::Vector3D<double> gravity_;
    raytracer::maths::Vector3D<double> wind_;
    Environment(const raytracer::maths::Vector3D<double> &gravity, const raytracer::maths::Vector3D<double> &wind) :
    gravity_(gravity),
    wind_(wind) {}
};

void tick(Environment& env, Projectile& projectile) {
    projectile.position_ = projectile.position_ + projectile.velocity_;
    projectile.velocity_ = projectile.velocity_ + env.gravity_ + env.wind_;
}

int main(int argc, char** argv)
{
    auto projectile = Projectile(raytracer::maths::Point3D<double>(0.0, 1.0, 0.0),
        normalize(raytracer::maths::Vector3D<double>(1.0, 1.0, 0.0)));

    auto environment = Environment(raytracer::maths::Vector3D<double>(0.0, -0.1, 0.0),
        raytracer::maths::Vector3D<double>(-0.001, 0.0, 0.0));

    unsigned steps = 0;
    while (projectile.position_.y() > 0.0) {
        steps++;
        tick(environment, projectile);
        // std::cout << "Current position: " << projectile.position_ << std::endl;
    }
    std::cout << steps << " steps required before the projectile hit the ground." <<std::endl;
    std::cout << "Projectile's position: " << projectile.position_ << "." <<std::endl;
    return 0;
}