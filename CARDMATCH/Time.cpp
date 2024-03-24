#include "Time.h"

Time::Time(long s, long p, bool perf) : start(s), pause(p), isPerfCounter(perf), lag(0)
{ }