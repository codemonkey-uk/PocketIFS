// profile.h
// C/C++ port from PocketC of profile.i from PocketIFS
// (c) T.Frogley 2015

#ifndef PROFILE_H_INCLUDED
#define PROFILE_H_INCLUDED

#include <ctime>
#include <iostream>

clock_t profile_starttime;
int profile_operations;

void Profile_Start()
{
  profile_operations=0;
  profile_starttime=clock();
}
void Profile_Stop()
{
  int time;
  time=clock()-profile_starttime;
  std::cerr <<
    profile_operations <<
    " operations in " <<
    time <<
    " ticks.\n";
  if (time>profile_operations){
    std::cerr << " = " <<
      (float)time/profile_operations <<
      " ticks per operation";
  }
  else{
    std::cerr << " = " <<
      (float)profile_operations/time <<
      " operations per tick.\n";
  }
}

#endif // PROFILE_H_INCLUDED