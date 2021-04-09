# How to use

* Create a controller based on the ```AGOAPController``` to let pawns execute a plan.
* use ```bExecuteEveryTick``` to control if your controller will execute the plan on every tick
* Create either a c++ class or a blueprint based on ```GOAPAction```.  
 I highly recommend creating those mostly in blueprints because then you have the easiest way to access all your assets
* Create a Blueprint based on your controller and add as many actions as you want
* Use ```UpdateGoals```, ```SetGoal```, ```UpdateReachedGoals``` & ```SetReachedGoals``` to start your pawn doing some actions
