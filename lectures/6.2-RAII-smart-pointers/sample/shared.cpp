#include <memory>
#include <string>
#include <iostream>

class Cowboy {
  using ptr = std::shared_ptr<Cowboy>;
  std::string name;
  std::weak_ptr<Cowboy> partner;
public:
  
  Cowboy(std::string const& n) : name(n) {
    std::cout << name << std::endl;
  }
  ~Cowboy() { std::cout << "Delete " << name << std::endl; }
  friend void partner_up(ptr a, ptr b) {
    std::cout << "BFFs: " << a->name << " & " << b->name << std::endl;
    a->partner = b; b->partner = a;
  }
};

int main() {
  auto good = std::make_shared<Cowboy>("Alice");
  auto bad = std::make_shared<Cowboy>("Bob");
  //ugly
  partner_up(good, bad);
}
