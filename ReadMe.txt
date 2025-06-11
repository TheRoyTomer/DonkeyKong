Welcome to Donkey Kong!
Mor Greenberg (212465678)
Roy Tomer (206364754)

Bonuses:

1. A unique explosion animation!
2. Animation for Mario's death.
3. Animation when an enemy dies from a hammer hit.
4. Extensive use of random numbers.
5. A comprehensive scoring system that includes various scenarios affecting the score.
6. Immortality Mode: If '+' exists in the level and Mario collects it, he becomes immune to enemy hits for 50 iterations. Mario is not immune to death caused by falling or explosions.
7. Special Immortal state Display in HUD: When Mario is in Immortality Mode, the HUD displays his status. In the last 10 iterations, a specific warning is shown to indicate that the effect is about to end.

Note:

1. Our jump and fall mechanics follow Mario's direction before he starts jumping or falling. Additionally, the player can change horizontal direction while jumping or falling.

2. According to our logic, we have disabled movement and key presses (w, s, x) that are not horizontal movements while jumping or falling.

3. In our jump function, the ascent part is handled in the jump function, but when we need to descend, we use the fall function. This means that the last action in the jump will be calling the fall function. Therefore, to avoid edge cases, the reset of jumpFlag and jumpStep will occur in the fall function.

4. The file is considered invalid in the following cases:

    a. Mario is missing.
    b. Pauline is missing.
    c. Donkey Kong is missing.
    d. The hammer is missing.
    e. The 'L' structure is missing.
    f. Pauline has no floor beneath her.
    g. One of the ghosts has no floor beneath it.

5. According to our understanding of the exercise specification, the project supports 'Q' as border characters and will replace them with spaces. As a result of this replacement, the screen will always maintain dimensions of 80x25.

6. The HUD (Heads-Up Display) on our screen is divided into three rows and two columns, with each cell displaying different game-related information. The first column has a width of 12, and the second column has a width of 7:

======================
   Lives    | Immortal
======================
   Score    |  Loops  
======================
   Hammer   |P pressed
======================

7. Scoring System Details

    a. Bonus for quick completion:
    The bonus is calculated by dividing 24,000 by the number of iterations it took the player to complete the level. The faster the player completes the level, the higher the bonus.

    b. Bonus for killing enemies:
    The player receives a 100-point bonus for each enemy killed using the hammer.

    c. Score deduction for losing lives:
    Each life lost deducts 250 points from the player's score.

    d. Bonus for completing a level without losing lives:
    If the player completes a level without losing any lives, they receive a 300-point bonus.

    e. Bonus for collecting '+': The player earns 200 points for collecting a '+' in the level.

8. The score will be updated in the HUD (Heads-Up Display) at the end of each level.

9. According to the exercise specification, the hammer only works in Mario's direction of movement. Therefore, when Mario is in the STAY state, he cannot use the hammer.

10. '+' does not have to appear in the level. If it is absent, the level will run without this feature.

11. In load mode, if in any stage results file doesn't match with current level run,stop the  Comparison.
