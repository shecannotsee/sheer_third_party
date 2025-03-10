#include <iostream>
#include <mini/ini.h>

int main() {
  {
    // first, create a file instance
    mINI::INIFile file("../myfile.ini");

    // next, create a structure that will hold data
    mINI::INIStructure ini;

    // now we can read the file
    file.read(ini);

    // read a value
    std::string& amountOfApples = ini["fruits"]["apples"];

    // update a value
    ini["fruits"]["oranges"] = "50";

    // add a new entry
    ini["fruits"]["bananas"] = "100";

    // write updates to file
    file.write(ini);
  }

  {
    // create a file instance
    mINI::INIFile file("../my_write_file.ini");

    // create a data structure
    mINI::INIStructure ini;

    // populate the structure
    ini["things"]["chairs"] = "20";
    ini["things"]["balloons"] = "100";

    // generate an INI file (overwrites any previous file)
    file.generate(ini);
  }


  return 0;
}
