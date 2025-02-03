# Introduction
This is a simple memory game for those who know numbers in binary.

The game will display a series of numbers in 4-bit, 5-bit or n-bit binary format one after the other with each number being displayed only for some seconds or depending on the level. There will be a supplementary document which contains the corresponding value to be entered for the observed number series. All the values in the supplementary sheet will be written in decimal format. The game's goal is to read the number series displayed in binary and enter the corresponding value from the series table correctly. The time displayed and the size of the table changes based on the difficulty.

Eg: For 4 bit game the numbers displayed maybe,
0010 -> 1011 -> 0010 -> 1010 -> 0000 -> 1101 -> 1100 -> 1111 -> 0101 -> 1110

The reference sheet will have many number series table as shown below,

| COL1 | COL2 | COL3 | COL4 |
| :--: | :--: | :--: | :--: |
|  3   |  4   |  2   |  11  |
|  5   |  3   |  11  |  15  |
|  12  |  2   |  2   |  1   |
|  7   |  12  |  10  |  4   |
|  1   |  6   |  0   |  10  |
|  10  |  3   |  13  |  8   |
|  6   |  15  |  12  |  12  |
|  9   |  10  |  15  |  7   |
|  11  |  1   |  5   |  4   |
|  0   |  5   |  14  |  15  |

The value to be entered for the corresponding number series column is given below,
Input to be entered for 2 input mode,

| COL1 | COL2 | COL3 | COL4 |
| :--: | :--: | :--: | :--: |
|  0   |  1   |  1   |  0   |

Or
Input to be entered for 3 input mode

| COL1 | COL2 | COL3 | COL4 |
| :--: | :--: | :--: | :--: |
|  2   |  1   |  0   |  2   |

For the above game round, the corresponding decimal values series for the binary numbers is given by the 3rd column and hence the value to be entered will be 1.

# Design
The game is designed such that the inputs and outputs of the game can be defined so as to adapt the description of the hardware. For example, the game could be run on arduino with 4 leds for displaying the binary digits and 2 input buttons or the game could be run on a linux terminal with the binary numbers displayed on the terminal and entered in the keyboard characters as inputs. The game's core is a logic engine that need not be changed with the need for input and output to be defined. This is inspired by a callback model which makes the whole system flexible and modular.

