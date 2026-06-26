# Novella
## THIS PROJECT IS STILL UNDER ACTIVE DEVELOPMENT

> A work-in-progress visual novel engine focused on declarative scenes and a 
> simple and safe scripting language

<p align="center">
  <img src="assets/demo.gif" alt="Novella demo" width="800">
</p>

## Implemented
   - Label and Sprite components
   - Resource loading
   - Rendering and audio
   - Parser for both the scene and scripting language

## Working on

   - Scripting interpreter
   - Engine API
   - Runtime Environment
   - Safe handles to manipulate resources
   - Saving/Loading

> Scenes describe UI and resources, while Scripts define behaviour trough a simple engine API
## Examples

### Making a scene

```nscene
Window{
   
    width = 1280
    height = 720
    title = "My VN"
}

Resources{

    texture background = "bg.png"
    font ui = "font.ttf"
}

Components{

   Sprite bg{
        texture = background
   }

   Label title{

      font = ui
      size = 40 #Avoid negative values
      text = "did you know that sometimes you may or you may not"

      renderLayer = -10

      layout{

            anchor = Center
            offset = (1,2)
        }
    }
}
```

### Calling the components in a script(intended API)
```nscript
module Main:

   fn main():

      var button = getButton("play");

      onClick(button, INPUT.MOUSE.LEFT, startGame());

   endFunction

   fn startGame():

      showMessage("Starting game!");

   endFunction;

endModule

```
## Documentation

- Scene declaration
- Components
- Scripting language
- Engine API

see the '/docs' directory
## Try it out

**Platform Support:** Tested on Arch Linux. Other Linux distributions may work are currently untested. Windows suppport is planned in the future.

1. **Clone the repository:**
```bash
   git clone https://github.com/CodigaBorealis/Novella.git
   cd Novella
```
2. **Install required libraries:**
```bash
sudo pacman -S raylib
```
3. **Build the project:**
```bash
mkdir build && cd build
cmake ..
make
```
4. **Run:**

- Play around with the bundled example files
## Dependencies

Novella wouldn't be possible without:

- [Raylib] - The Heart of the engine, manages all low level operations like input handling, window rendering and OpenGL drawing

## License

MIT

**Feel free to fork this project or contribute to it!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [Raylib]: <https://github.com/raysan5/raylib>
