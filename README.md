# Novella
## THIS PROJECT IS STILL UNDER ACTIVE DEVELOPMENT

Novella is a  W.I.P component-based visual novel engine that aims to make developing vns accessible to everyone

## Dependencies

Novella relies on the following open-source libraries:

- [Raylib] - The Heart of the engine, manages all low level operations like input handling, window rendering and OpenGL drawing
- [nlohmann/json] - Used for the internal implementation of the interaction system

## Try it out

**Platform Support:** this project has been tested to work on arch based linux distributions, windows support is not yet guaranteed

1. **Clone the repository:**
```bash
   git clone https://github.com/CodigaBorealis/Novella.git
   cd Novella
```
2. **Install required libraries:**
```bash
sudo pacman -S raylib nlohmann-json
```
3. **Build the project:**
```bash
mkdir build && cd build
cmake ..
make
```
4. **Run:**

- Play around with the bundled example files

## License

MIT

**Feel free to fork this project or contribute to it!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [Raylib]: <https://github.com/raysan5/raylib>
   [nlohmann/json]: <https://github.com/nlohmann/json>