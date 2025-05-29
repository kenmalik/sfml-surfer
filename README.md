# SFML Surfer

SFML Surfer is a CLI program which renders HTML and CSS as SFML components.

![Demo GIF](https://raw.githubusercontent.com/kenmalik/sfml-surfer/main/assets/demo.gif)

## Building

Building this project requires SFML and CMake.

To build, run the following commands from the project's root directory:

```
mkdir build && cd build
cmake ..
make
```

## Usage

To run the tool interactively, use the command with no arguments:

```
./sfml-surfer
```

To read an HTML file, use the `-f` flag:

```
./sfml-surfer -f [HTML_FILE]
```

To provide a CSS file, use the `-s` flag:

```
./sfml-surfer -f [HTML_FILE] -s [CSS_FILE]
```

Inline CSS styles are also supported.

## Note

This was a project from my Data Structures and Algorithms course in community
college. The prompt was to create something with SFML which emphasized one of
the data structures we covered in class. I opted to do an HTML renderer as an
exercise in creating/using trees.
