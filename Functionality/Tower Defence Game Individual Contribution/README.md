# Interactive Digital Media Project
For this team project, we were given free reign as to what product we wanted to create, as well as what game engine and language we wished to use.
Since all of the team had a background in unity design, it was a unanimous choice.
Unfortunately this course was not a cross disciplanray one, and all team members had programming backgrounds, so it was a challenge in the design aspect of the game.
Unlike the level design course found in this functionality folder, which had pre existing art to use, our team had to source all of the assets ourselves.
Our team used pre-existing public assets found online as a basis, and used shader software to build off of that. It is important to note that the majority of the art used in this game was from a public source.
It was also unfortunate that a member of our 4-person group became unavailable to work with, so it then became the responsibility of the remaining 3 members of the group to pick up the slack.

## Individual Contribution
As for my contribution, I worked soley on the HUD and the Tower Behaviour for this game, with the other members working on the enemy AI and the game grid. You can find the c# scripts of my individual contributions in this folder. The full game and build is not provided.

### UI Scripts
Earlier in my University Program, I took a course in UX/UI Design, and so I was eager to showcase my abilities in this area of our game. The UX course focused on the design of everything, which complemented well with trying to implement it techincally using c# code. The game uses a combination of buttons, scroll pages and pop-up window, with the intention of providing an intuitive user experience that is not overwhelming.
The following UI functionality can be found in our tower defence game <br />
* A Play button which spawns an increasing number of enemies
* A Tower button which, when presed, open and closes a scroll menu which contains the placeable towers of our game
* A number of tower buttons which can be pressed, which opens a pop-up window with details and immersive lore about the respective tower.
* A health and currency meter, which rises and falls as the player loses/gains health or currency.
* An upgrade pop-up window which appears when a placed tower on the map grid is clicked. The tower can then be upgraded to increase its power, or sold to remove it from the grid and gain a portion of the invested money back.

Below is a vimeo link showcasing the UI of this game <br />
https://vimeo.com/1020122146?share=copy

### Unit Scripts
I utilised OOP techniques to make a generalised tower, which then was able to be utilised by towers that had specific functionality.
In the following Vimeo Link, you can find a video showcasing the different functionality of the towers. NOTE: Due to other aspects of the game, some towers functionality won't be showcased, but their functionality can be found in the c# files, found in the 'Units' Folder. <br />
https://vimeo.com/1020123509?share=copy
<br />The 'Units' scripts also contain some rudementary projectile targeting functionality for resepctive towers, which can be seen in the video link.
