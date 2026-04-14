#ifndef CPPEX_MATERIAL_HPP
#define CPPEX_MATERIAL_HPP

#include <sstream>
#include <string>

/**
 * Class representing a material with a name and density.
 */
class Material {
 protected:
  double density;
  std::string name;

 public:
  /**
   * Construct a material with a given density.
   *
   * @param name The name of the material.
   * @param density The density of the material.
   */
  Material(std::string name, double density) : name(name), density(density) {}

  std::string describe() const {
    std::stringstream stream;
    stream << name << " (density=" << density << " kg/m^3)";
    return stream.str();
  }
};

#endif