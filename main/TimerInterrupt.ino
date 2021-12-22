void initTimerInterrupt()
{
    Timer1.initialize(10000);
    Timer1.attachInterrupt(timerForSegment);
}

void timerForSegment()
{
    startTimer();
}