After you have initialized a new project with the 'parrotMinidroneHoverStart' command, that project will be stored by default in the folder 'MATLAB\Projects\examples\parrotMinidroneHover'.
In the project folder, find the folder 'controller', which has a Simulink file called 'flightControlSystem.slx'. This is the file that cointains the controller to be deployed onto the hardware. 
Replace that file by the one with the same name on this zip folder.

Now, you can implement your controllers and observers in the block 'Controller', with all the variables easily accessible. You can then select which controllers are used (default or yours) by appropriately setting the Switch blocks. 

The scripts 'readSimulationData.m' and 'readDroneOnBoardData.m' read and plot the variables logged during the Simulation or during the actual flight, respectively. 
You can add more of your own logged variables and proceed in a similar manner. These scripts assume that the data is logged as 'Structure with time' (it is an option for the 'Scope' or 'To Workspace' blocks).  