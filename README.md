# sheer_third_party

- sheer_third_party is a package manager for C/C++ that attempts to support all packages by fetching their source code and compiling them locally.
- Currently, all build scripts are written in shell, but due to the characteristics of shell scripting, we are gradually replacing shell with Lua for build functionalities.
- Considering that some libraries might be large and a single build might not be completed in one go, we are planning to implement a feature to record the build steps in a file and enable build recovery.
