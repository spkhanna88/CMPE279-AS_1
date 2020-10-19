# CMPE279-AS_1-2

-> Participants : 

1. Surbhi Vasudeva - 013832026
2. Akshay Bhope - 013778973

-> Environment Setup :

EC2 instance - Amazon Linux 2 AMI (HVM), SSD Volume Type (Free Tier)
Compiler installed - gcc (sudo yum install gcc)

-> Running the code :

sudo gcc -o server server.c
sudo ./server

-> Observations :

1. Even after setting the uid to 99999, we were not able to see the change while printing the uid. Then tried to compile and run the same using sudo command and it displayed the uid set by us.

2. Printing the uid, pid and ppid helped us to determine the correct placement of the new code.


-> References :

1. https://docs.oracle.com/cd/E19455-01/806-0626/6j9vgh6ap/index.html
2. https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm
3. https://stackoverflow.com/questions/21248840/example-of-waitpid-in-use
4. https://www.geeksforgeeks.org/fork-system-call/
