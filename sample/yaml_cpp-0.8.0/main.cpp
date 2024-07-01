#include <yaml-cpp/yaml.h>

#include <fstream>
#include <iostream>

int main() {
  YAML::Node config = YAML::LoadFile("../config.yaml");

  if (config["lastLogin"]) {
    std::cout << "Last logged in: " << config["lastLogin"].as<std::string>() << "\n";
  }

  const std::string username = config["username"].as<std::string>();
  const std::string password = config["password"].as<std::string>();

  std::cout << username << password << std::endl;

  config["lastLogin"] = "2024-06-25";

  std::ofstream fout("../config-update.yaml");
  fout << config;

  return 0;
}
