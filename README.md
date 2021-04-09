# How to use

* Create a controller based on the ```AGOAPController``` to let pawns execute a plan.
* use ```bExecuteEveryTick``` to control if your controller will execute the plan on every tick
* Create either a c++ class or a blueprint based on ```GOAPAction```.  
 I highly recommend creating those mostly in blueprints because then you have the easiest way to access all your assets
* Create a Blueprint based on your controller and add as many actions as you want
* Use ```UpdateGoals```, ```SetGoal```, ```UpdateReachedGoals``` & ```SetReachedGoals``` to start your pawn doing some actions


## Actions
An action is used to perform a single piece of a complete workflow.  
You can create as complex actions as you want.  
Actions are created just once per controller.

### Events
For now there are 2 events, which can be overridden. Execute and Tick. Both of them will get the pawn controlled currently by the pawn.  
The controller is the owner of the action, so you can get access to it by calling GetOwner or getting the controller from the pawn.  
![image](https://user-images.githubusercontent.com/6481850/114223613-549e9d00-9970-11eb-9d9b-acf8ee28eb86.png)

### Check Precondictions
optionally to the basic preconditions you can check with this function, if your pawn is able to fullfill this action.  
The default implementation returns ```true```.  
![image](https://user-images.githubusercontent.com/6481850/114223746-7861e300-9970-11eb-85dd-977e3c4ac30d.png)

### Get Cost
Every action has a cost, which by default returns the Property ```Cost```. The system wil try to find the next cheapest action.  
![image](https://user-images.githubusercontent.com/6481850/114223675-64b67c80-9970-11eb-8c29-37daaf0c7745.png)

### Class Defaults
Every action will tick with the ```FIntervalCountdown```.  
Cost will set the return value for the default implementation of the function ```Get Cost```.  
#### Preconditions
Every precondition has to be met to eventually execute this action.  
Give the precondition a unique name. We selected a FText to allow you to select from a StringTable to minimize mistakes from typos.  
Give the precondition a value. We wanted to give more freedom to the developers/designers which will set those values to have more varities of a goal for example. So you can reuse a name but set different "priorities" to it. For example you could add a goal to the value of 1 and with a timer you will raise this value so the pawn tries to execute a different action which is for example mor drastic since the goal wasn't reached yet.
#### Effects
Every of the effects will be applied once this action is markes as successfully finished. When an action is finished unsuccessfully, none of the effects are applied.  
![image](https://user-images.githubusercontent.com/6481850/114223855-9891a200-9970-11eb-984e-714e9889725c.png)
