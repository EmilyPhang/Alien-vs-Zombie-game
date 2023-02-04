# Alien vs. Zombie

Alien vs. Zombie is a text-based version game. In this game, the player navigates an alien on a path to destroy zombies. It combines several elements of role-playing game, path-planning, and strategy to provide a unique gaming experience.

![Alt text](/image.png) <- change


YouTube link to [Video Demo](https://youtu.be/7w4Kk9M5Xk0). <- change

## Compilation Instructions

To compile this program, type the following in the terminal

 For CMD or PowerShell (in Windows)

              g++ pf\*.cpp main.cpp 

 For Bash (in MacOS or Linux)

             g++ pf/*.cpp main.cpp 

*********************************************************

## User Manual

Please provide the user manual on how to use your program.

Player will be able to choose whether they want to use the default game board or change the settings according to their preferences. The rows and columns can only be odd number whereas the minimum number of zombie is 1 and maximum is 9.

Player will begin the game as an Alien. The Alien will win if the Alien defeated all the zombies without dying. ALien will lose if its life becomes 0 without defeating all the zombies. 

There are a few commands for Alien in our game. One can view the commands by typing help.

Alien can move and attack, Alien moves by continuously thrusting in one of the FOUR (4) directions (i.e., up, down, left, or right). However, alien will be stopped by one of the following events:
1. It hits the border of the game board.
2. It hits the Rock object.
3. It hits and attacks Zombie, but Zombie survives the attack.

Alien can choose to move up, down, left and right by typing "up", "down", "left" or "right" in the command. When Alien meets with an arrow, it will adds 20 attack to the Alien and the Alien will proceed to move in the direction of the arrow. 

When Alien encounters a health pack, it adds 20 life to Alien with 100 as the max capacity of Alien's Life.

When Alien encounters a pod, it instantly inflicts 10 damage to Zombie.

When Alien hits a rock. Alien's turn will end and a random object will spawn on the position of the rock.

Alien can choose to switch the direction of an arrow by typing "arrow" as a command.The player will be asked to enter the row and column of the arrow object to switch, followed by the direction of the arrow object to switch to.

Player can type "save" as a command to save the current game to a file. Player can "type" load as a command to load a saved game from a file. Player can  quit the game while still in play by typing "quit" as a command.

That's all for user manual. Have fun playing!


## Progress Log

- [Part 1](PART1.md)
- [Part 2](PART2.md)

## Contributors

- Emily Phang Ru Ying
- Lim Cai Qing
- Teo Yu Jie


