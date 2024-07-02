## PROJECT DETAILS
* This assignment was completed on Windows, using Visual Studio 2022, and was written in C++.
* This assignment used the provided Visual Studio project (i3d_visualstudio), and no other 
  configurations were made. No compiler options were changed.
  
<img width="353" alt="3d_graphics_assignment" src="https://github.com/MarcoNadalin/3dGraphics_Assignment_2/assets/50226612/08fafb0c-15d9-4aa4-9949-33624273eb42">

## HOW TO RUN
1. Run the executable named "i3d64dbg.exe" in this directory.

## HOW TO RUN (ALTERNATIVE)
2. Alternatively, you could open the project by clicking on "vs\i3d.sln" and then run it within Visual Studio, 
   but beware, this was completed on Visual Studio 2022 and upgraded windows sdk. 

## CONTROLS
w - go forwards
s - go backwards
a - turn left
d - turn right

spacebar - shoot

r - toggle between rocket and bullet
x - spawn turret

## OTHER GAME RULES
1. To start the game, press the spacebar
2. If you lose, press 'r' to restart the game
3. A turret costs 2 points to spawn
4. A point is earned once an asteroid is destroyed
5. The number of asteroids needed to be destroyed per wave is equal to the wave number 
   (e.g. to progress from wave 5, 5 asteroids must be destroyed by the player)
6. Asteroids can either have 2 or 3 hit points, depending on the radius
7. turrets are destroyed when they collide with an asterorid
8. bullets and rockets are destroyed as soon as they leave the arena.

## OTHER NOTES
1. Player acceleration is a bit hard to notice, but decelleration is more obvious. 
   this was done on purpose. The spaceship is quick to reach top speed, but slow to come to a stop.
2. When asteroids bounce off walls, the direction they are spinning is reversed. 
   This was intentional, as it looked strange otherwise.
3. Asteroids spawn on any point on the 'circle' outside the arena, and they move 
   to the position of the player at the time they are spawned.

CREDITS:
"Star Wars: X-Wing Cockpit" (https://skfb.ly/6BQRJ) by Daniel is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).
