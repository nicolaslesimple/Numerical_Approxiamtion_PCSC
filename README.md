# PCSC2017_Group5
This is the project for the EPFL class Programming Concepts in Scientific Computing - Master 1 Class - Computer Science and Engineering

In order to be able to easily share the code between the two members of the group, the version control system GitHub has been used. To access to the repository containing the program one simply has to open a terminal window and to type git clone https://github.com/nicolaslesimple/Numerical_Approxiamtion_PCSC/. By doing so the user is able to download the project to the newly generated folder PCSC2017\_Group5.


The program could be used simply by importing the project repository in CLion and to run the project. Once the project was launched the user had the possibility to choose between executing the program by using manual inputs into the terminal (by hitting 1) or using the information saved in the config.dat file (by hitting 2). However, both ways of doing lead to the same functionalities. 


For the user that chose the manual entries the usage was straightforward and guided by the content on the terminal window which explicitly mentioned how the user could first choose between using sin(pi*x) or sin(x)*cos(3*pi*x) as the function to interpolate. 

In the next step, the user was asked to hit 1. to perform a Least Squares data approximation, type 2. to appreciate the graphs of Fourier data approximation, 3. to compute the Lagrange polynomial data approximation, 4. for the PieceWise Least Squares data approximation and finally 5. for the PieceWise Lagrange data approximation.

The config.dat file contained four lines. The first field, labeled with Approximation Method, should contain a number between 1 and 5. In this line, the user could choose between the five possible approximation techniques. Moreover, the second field was used to specify which function the user wanted to interpolate. The third and fourth fields were not necessarily used by all the approximation methods. For instance, the Fourier approximation did not need these last two lines so one could give random numbers in these containers (as long as there were some values). This was also true for the Lagrange approximation code. The other methods, like Least Squares and Piece Wise Lagrange, needed the first three lines in order to specify the degree of the polynomial function to interpolate. Finally, Least Squares approximation by pieces needed all the four lines. In this specific case, all four fields were necessary since the method needed to know the degree and the number of intervals to compute.


By doing all the steps as mentioned in the two previous paragraphs all the programs should work well and give a qualified approximation of the function. 


During the execution of the program, the user had to follow the instructions on the terminal. However, it is important to know the pipeline of execution, meaning that once everything was entered the program took a few seconds to compute the answer. Following to this step, a graph appeared on the screen for 20 seconds. Once the first graph disappeared the testing part of the program was launched and showed some graphs which only appear 5 seconds to increase the execution speed of the program. In normal execution, 5 graphs should successively appear (corresponding to each interpolation method). However the different with the graphs before was that this time the graphs only compared the expected data with the interpolation results. As a final step, once the graphs disappeared the terminal gave the last information about the accuracy of the model by displaying of the accuracy of the predictions in comparison to the real data (with a tolerance of epsilon = 0.2).                                
This lasted for 20 seconds again and was then followed by a displaying of the accuracy of the prediction in comparison to the real data.
