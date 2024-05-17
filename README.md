# Multiplayer-Game-Using-Threads

## Introduction

This project features an implementation of a multiplayer game written in C++. Players navigate a two-dimensional grid to collect items and earn points. The game utilizes threading to handle player movement and item collection concurrently, providing an engaging and dynamic gameplay experience.

## Objective

The objective of this project is to create a multiplayer game where players can navigate a game board, collect items, and earn points. By implementing threading, the game aims to handle player movement and item collection concurrently, ensuring smooth gameplay and preventing conflicts between players.

## Methodologies

- **Dynamic Game Board Generation**: The game board is dynamically generated based on a calculation involving random numbers and player roll numbers.
- **Threaded Implementation**: Threading is used to handle player movement and item collection concurrently, ensuring smooth gameplay and preventing conflicts.
- **Message Passing**: To ensure thread safety and prevent conflicts, a message passing system is implemented between the main thread and player threads.
- **Scalability**: Thread attributes are used to set priorities for player threads based on game-related factors such as score or performance.

## Technologies Used

- C++: The game is implemented in C++ programming language.
- Threading: Threading is utilized to handle concurrent player movement and item collection.
- Standard Template Library (STL): STL is used for data structures and algorithms.

## Conclusion

The Game provides an interactive and engaging multiplayer gaming experience. By utilizing threading and message passing, the game ensures smooth gameplay and prevents conflicts between players. With dynamic game board generation and scalable thread priorities, the game offers a dynamic and enjoyable gaming experience for players of all levels.


