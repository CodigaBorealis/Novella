## Getting started

The engine is built around the idea of making each scene a self contained unit of storytelling, much like how the page of a book is. It declares what exists during that specific moment of the game and how its arranged visually, it does not describe behaviour, it does however, contain the paths that lead to both the resources and the scripts used.

### Creating a project

- Create a new folder
- Add a file with the extension .nvp at the root
- Configure your projects according to 'nproject.md'

### Creating your first scene

- Create a text file with the extension .nsc anywhere within the folder where the .nvp file is located
- Populate it following the guide on 'nscene.md'
- Add the scene location to your project file
- Create an Engine object inside your program
- Use the method .loadScene() passing the name of the scene you want to load

### Creating a script

- Make a new text file with the extension .nsc
- Write your script using the guide on 'nscript.md'
- Include your script source in the scripts section of the scene you want to use the script on
