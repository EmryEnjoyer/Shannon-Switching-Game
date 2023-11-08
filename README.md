# Shannon Switching Game Solution
**Description**: This project contains implementation for a graph, a graph lexer, and a solution to the Shannon Switching Game.

The reason that the `Graphs` structure is slightly over-complicated is that I'm trying to form it into its own reusable module that I can just throw into my projects in the future.

## Structure
`/` is the project root
  - `/src` contains the source files for this project
    - `/src/Graphs` contains graph implementations
      - `/src/Graphs/Headers` contains headers for graphs
    - `/src/Headers` contains the headers for this project
  - `/input` contains input files for manual testing
  - `/build` contains the built executable

## Building the project
In a terminal with `/` as the current working directory, run the command `make build` to build the project. After running this command, `/build/ShannonSwitching` should be created. To clean this up in between builds, run `make clean`.

## Using the project
Usage is `./build/ShannonSwitching <short | cut> < <filename>`.