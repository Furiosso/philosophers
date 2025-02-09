# Philosophers Tester  
A semi-automatic tester for checking 42's philosophers project.  
It allows you to test 2 scenarios:  
1. when your program should stop, either due to death, enough eaten, or bad input  
    - to be checked manually by the user, based on the expected result listed in yes-die.txt.  
2. when no philosophers should die  
	- this is checked automatically if the program runs for x seconds (default 10) without death.  

More tests can be added by editing the appropriate ```.txt``` files with the input and expected outcome.

![screenshot of tester being run](https://i.imgur.com/iAfsRWM.png)


## Usage

If you haven't already, run ```make``` in your philo directory to create your ```./philo``` executable.  
Then from within the LazyPhilosophersTester directory, run ```./test.sh``` to start the tester.  
Tester takes an optional 2nd argument of the path to your ```philo``` executable.  

Example:  
```bash
./test.sh ../philo
```
If not provided, the tester assumes the path is ```../philo``` - i.e. in same directory as tester directory.

### Adding tests
If you wish to add your own tests, open either:
1. ```no-die.txt``` for tests where philos aren't supposed to die, or
2. ```yes-die.txt``` for tests where the program should stop (death, eaten enough, error).  

The 1st line should be your test case, separated by spaces. This is what is inputted into your program.  
The 2nd line should be the expected outcome. This is outputted during the tester for checking purposes.  

Example:  
```text
4 310 200 100
a philo should die
5 800 200 200 7
no one should die, simulation should stop after 7 eats
```
