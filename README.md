# Pong (Module 4, OEP {2})
#### Tate Osborne ~ November 19, 2021
Grab a friend a play the classic Pong game!

In this project, I have created the famous _Pong_ game of two paddles that shift on the outside of the
screen to rally a ball back and forth.

#### Screens
The game has three screens:
- `Welcome screen`: This screen displays the game title, the controls, and the score you need to win.
- `Game Screen`: This screen has the game on it. It is on this screen that you can control the paddles 
  and hit the ball back and forth. If a point is scored, the scoreboard (displayed at the top), is updated.
  The game screen is active until a player has reached the target score.
- `End Screen`: This screen is displayed once the target score has been reached and it just thanks the user(s)
  for playing and shows the final score.
  
#### Rules
This game has two sides, so it is ideally for two players. That said, you can play against yourself if
you control both paddles. There is a `home` (left) player and an `away` (right) player. The first player to
score 5 points wins. Once a player has reached 5 points, the screen will change from the game screen to the
end screen.
  
#### Controls
There are multiple buttons / controls that can be used to navigate the game. These are as follows:
- `b`: You must press `b` to begin the game. This key transitions from the welcome screen to the game screen.
- `space bar`: Pressing `space bar` will play the game and initial ball movement and allow you to move the
  paddles. The game will be stopped after each point is scored, to ensure both players are ready before beginning
  the next round.
- `w`: Use `w` to move the home paddle up.
- `s`: Use `s` to move the home paddle down.
- `up arrow`: Use the `up arrow` to move the away paddle up.
- `down arrow`: Use the `down arrow` to move the away paddle down.
- `esc`: You can press `esc` at any time to exit the game.

```
I believe I deserve the full 50 points on this OEP. My reasoning is that I had to implement specific methods
so that I could create interactions in the game. Furthermore, figuring out how to get the ball to act realistically (i.e.
making the ball move in a random direction upon beginning, having it bounce off the paddles like in the game, and having
the velocity of the ball increase over time to make the round difficult as the rally goes on) took a good chunk of time
and trial and error.. I have included multiple screens that work independently of one-another (i.e. you cannot move the
paddles until you're on the game screen and space bar has been pressed). Lastly, I have included 7 keyboard
functionalities which is beyond the required two in the spec sheet. 
```
