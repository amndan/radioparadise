// system
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

// write/write
#include <unistd.h>

// system command
#include <stdlib.h>

// defines
#define GPIO_1 "19"
#define GPIO_2 "13"
#define GPIO_3 "26"

// definitions
char getGpioState();

// global
std::vector<std::string> gpios;

// main
int main(int argc, char** argv)
{
  gpios.push_back(GPIO_1);
  gpios.push_back(GPIO_2);
  gpios.push_back(GPIO_3);

  for(int i = 0; i < gpios.size(); i++)
  {
    std::string mode = "in";
    std::stringstream ss; 
    int fd = open("/sys/class/gpio/export", O_RDWR);
    write(fd, gpios.at(i).c_str(), gpios.at(i).length());
    close(fd);
    usleep(100000);
    ss << "/sys/class/gpio/gpio" << gpios.at(i) << "/direction";
    fd = open(ss.str().c_str(), O_RDWR);
    
    std::cout << fd << ";  " << ss.str().c_str() << std::endl;
    
    if(write(fd, mode.c_str(), mode.length()) != mode.length())
    {
      std::cout << mode.length() << " ; " << write(fd, mode.c_str(), mode.length()) << std::endl;
    }
    
    close(fd);
  }
  
  system("mpc play");

  while(1)
  {
    static int state = 0;
    static int lastState = 0;
    lastState = state;
    state = (int) getGpioState();
    if(lastState != state)
    {
      system("mpc play");
      std::cout << "switched state to: " << state << std::endl;
      if(state == 5)
      {
        system("mpc next");
      }
      else if (state == 2)
      {
        system("mpc prev");
      }
    }
    usleep(200000);
  }
  
  return 0;
}

char getGpioState()
{
  char state = 0x00;  
  char buf[1];
  
  for(int i = 0; i < gpios.size(); i++)
  { 
    std::stringstream ss; 
    ss << "/sys/class/gpio/gpio" << gpios.at(i) << "/value";      
    int fd = open(ss.str().c_str(), O_RDWR);
    read(fd, &buf, 1);
    if(buf[0] == '1') state = state | (1 << i);
    close(fd);
  }
  return state;
}
