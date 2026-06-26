## Getting started

The engine is built around the idea of making each scene a self contained unit of storytelling, much like how the page of a book is. It declares what exists during that specific moment of the game and how its arranged visually, it does not describe behaviour, it does however, contain the paths that lead to both the resources and the scripts used.

### Creating your first scene

- Create a text file with the extension .nsc
- Populate it following the guide on 'sceneLanguage.md'
- Create an Engine object inside your program
- Use the method .loadSceneFromFile() passing the location of your file as a parameter

