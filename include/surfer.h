#ifndef SFMLSURFER_SURFER_H
#define SFMLSURFER_SURFER_H

#include <string>
class Surfer {
  public:
    static void runFile(std::string path);
    static void runPrompt();
    static void run(std::string source);
    static void error(int line, std::string message);
    static void report(int line, std::string where, std::string message);

  private:
    static bool hadError;
};

#endif // !SFMLSURFER_SURFER_H
