# Part 2

## Video Demo

YouTube link to your [Video Demo](https://youtube.com). <-change

## Minimum Requirements

### Completed

List of all the features completed.

1. Generate random gameboard based on user's input
2. Show gameboard that was generated
3. Customization of settings including game board dimensions and number of zombies. (dimensions have to be odd, zombie from 1 to 9 only)
4. Create Alien and spawn it on the centre of the board.
5. Generate and display Life and attack for Alien 
6. Generate and display Life , attack and range for Zombie randomly.
7. Alien leaves trails when it moves. 
8. Starts Alien's attack from 0 at each turn.
9. Arrow Object allows Alien to increase attack by 20 and move towards that direction.
10. Zombie movement and attack behaviour.
11. Condition which caused Alien to be stopped.
12. Trail resets with game objects before Zombie's turn.
13. Alien attack behaviour.
14. Alien and Zombie take turns.
15. Display zombie on game board with numbers.
16. Completed Game objects function.
17. Completed game controls.
18. Completed Save and Load.
19. Completed Alien Win and Lose Condition.
20. Completed Play again Feature.

## Additional Features

No additional features has been implemented.

## Contributions

### Emily Phang Ru Ying

1. Create and spawn Alien.
2. Alien movement and attack behaviour.
3. Generates and display life, attack or range for Alien and Zombie.
4. Create Alien Win and Lose Condition.
5. Completed Play again feature.

### Lim Cai Qing

1. Customization of settings.
2. Implement game objects.
3. Resets Alien's trail with random game objects before Zombie's turn.
4. Implement game controls.

### Teo Yu Jie

1. Randomly generate game board.
2. Show game board.
3. Zombie movement and attack behaviour.
4. Alien and Zombie take turns.
5. Save and Load.

## Problems Encountered & Solutions

1. Playing around upper border will make Alien not able to continue it's turn. Fixed by changing the comparison in moveValidation.
2. Playing around bottom border will make program ends. Fixed by changing the comparison in moveValidation.
3. Zombies may sometimes collapsed with each other. Fixed by checking the validLocation for zombie.
4. When zombie died due to Alien's attack, Alien's turn end. But it should continue not end turn. Fixed by returning false for attack zombie and making alien to continue moving in the same direction if zombie dies.
5. When zombie die, the display of the zombie will turn up again on the game board but it should not. Fixed by setting only zombies with more than 0 life are able to move.