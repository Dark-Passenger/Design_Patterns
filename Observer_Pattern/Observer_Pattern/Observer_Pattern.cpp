// Observer_Pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <sys/types.h>
#include <sys/timeb.h>

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

class Subject;

class Observer
{
public:
  virtual void update(Subject*) = 0;
};

class Subject
{
private:
  std::vector<Observer*> observers;

public:
  virtual void Attach(Observer* observer)
  {
    observers.push_back(observer);
  }

  virtual void Detach(Observer* observer)
  {
    auto itr = std::find(observers.begin(), observers.end(), observer);
    if (itr != observers.end())
      observers.erase(itr);
  }

  virtual void Notify()
  {
    for (auto&& observer : observers)
    {
      observer->update(this);
    }
  }
};

class ClockTimer : public Subject
{
private:
  char tmpBuf[128];

public:
  ClockTimer() { _strtime_s(tmpBuf); }
  int GetHour()
  {
    char timebuf[128];
    strncpy_s(timebuf, tmpBuf, 2);
    timebuf[2] = NULL;
    return atoi(timebuf);

  }

  int GetMinute()
  {
    char timebuf[128];
    strncpy_s(timebuf, tmpBuf + 3, 2);
    timebuf[2] = NULL;
    return atoi(timebuf);

  }

  int GetSecond()
  {
    char timebuf[128];
    strncpy_s(timebuf, tmpBuf + 6, 2);
    timebuf[2] = NULL;
    return atoi(timebuf);
  }

  void Tick()
  {
    _tzset();
    _strtime_s(tmpBuf);

    Notify();
  }
};

class DigitalClock : public Observer
{
private:
  std::shared_ptr<ClockTimer> subject;

public:
  DigitalClock(std::shared_ptr<ClockTimer> _subject) : subject(std::move(_subject))
  {
    subject->Attach(this);
  }

  ~DigitalClock()
  {
    subject->Detach(this);
  }

  virtual void update(Subject *theChangedSubject) override
  {
    if (theChangedSubject == subject.get())
      draw();
  }

  void draw()
  {
    const int hour = subject->GetHour();
    const int min = subject->GetMinute();
    const int second = subject->GetSecond();

    std::cout << "Digital time is " << hour << "." << min << "." << second << std::endl;
  }
};

class AnalogClock : public Observer
{
private:
  std::shared_ptr<ClockTimer> subject;

public:
  AnalogClock(std::shared_ptr<ClockTimer> _subject) : subject(std::move(_subject))
  {
    subject->Attach(this);
  }

  ~AnalogClock()
  {
    subject->Detach(this);
  }

  virtual void update(Subject *theChangedSubject) override
  {
    if (theChangedSubject == subject.get())
      draw();
  }

  void draw()
  {
    const int hour = subject->GetHour();
    const int min = subject->GetMinute();
    const int second = subject->GetSecond();

    std::cout << "Analog time is " << hour << "." << min << "." << second << std::endl;
  }
};

int main()
{
  auto timer = std::make_shared<ClockTimer>();
  
  DigitalClock dc(timer);
  AnalogClock ac(timer);
  
  timer->Tick();
  
  std::cout << "after some time " << std::endl;
  std::this_thread::sleep_for(2s);
  
  timer->Tick();

  return 0;
}