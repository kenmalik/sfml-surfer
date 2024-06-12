#ifndef SFMLSURFER_SURFER_H
#define SFMLSURFER_SURFER_H

#include "css-scanner.h"
#include "token.h"
#include <string>
#include <vector>

class Surfer {
  public:
    static void runFile(std::string htmlPath, std::string cssPath);
    static void runFile(std::string path);
    static void runPrompt();
    static void run(std::string source);
    static void error(int line, std::string message);
    static void report(int line, std::string where, std::string message);
    static void display(const std::vector<Token> *tokens);

  private:
    static bool hadError;

    static constexpr float SCREEN_WIDTH = 1400;
    static constexpr float SCREEN_HEIGHT = 1000;

    static std::string cssPath;
    static std::vector<Ruleset> readCssFile();
};

#endif // !SFMLSURFER_SURFER_H
