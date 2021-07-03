This my 2nd Game in Console Games.

I have Really experienced diffrent kind of projects , games are not that easy to do because you are dealing with movements
behavior and coding.

brefiely you must have the total idea of the project before aheading for your first line of code.

basically Snake starts with a specific movement till you change it by clicking any arrow (up - down - left - right)
and this what function readmotion() does , it knows what arrow has been clicked , say we clicked up arrow , then you will find
that the boolean variable up = true , when going through the if-conditions we will find that up variable is marked as true which will make
our CurDirection variable = 1

if you went to the top of the code you will find an array defines the movement delta
for example assume we are in cell (1,2) by clicking up our cell must be (0,2) 
here we will find di[1] = -1 , dj[1] = 0 , where you must you ith cell to i-1 cell with the same j

function eat() simple knows the head of the snake if it equal the food position you increase the size of the snake by one dot
and you remove your food

function putstuff() randomly puts food in any cell in our grid.
