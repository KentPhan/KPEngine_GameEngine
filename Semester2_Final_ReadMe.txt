GamePlay:
When you start up the game. Press Enter to Start.

Use A and D to move left and right.
Use W to jump.

Get to the Key to Win.

Press Enter to go back to the start screen after winning

You can quit the game at anytime by pressing ESC or Q

--------------------------------------------------------------------------
Extra things I implemented that are Special?

- Input System
- Unit Test Project
- Platformer Physics?
- Handling of Destroying of Objectsish.


Things I did that I'm iffy about:

- I broke the Physics Step into 2 to make it work with the collision system. First I would calculate forces. Then Perform collisions and modify collisions based off of those forces. Then I would apply final position
- The manner in which I retrive components from the Game side could be better in my opinion. I could us some interface inheritance between components and how I retrive components could not be so hard coded.
- Cleaning up objects. I'm kind of cleaning up and destroying objects at the whim of my SmartPointers. Still thinking about how a proper clean up or destroy process would work.


To my knowledge I don't have any memory leaks or notable warnings.

---------------------------------------------------------------------------
If you have feedback for how I implemented somethings. Please do give it! I don't mind you commiting directly to this ReadMe if you want to give feedback.

I was told we would get extra points if we did both 2.08 and 2.10?

Hope there aren't any problems and have a great summer!