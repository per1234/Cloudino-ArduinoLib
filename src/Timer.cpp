/*
  Timer.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, July 8, 2015
  Released into the public domain.
*/

#include "Timer.h"

Timer::Timer(){
}

void Timer::loop() {
    
    Timer::TimerInstance *aux=_ini;
    while(aux!=NULL)
    {
        unsigned long t=millis();
        if(t-aux->ltime>=aux->time)
        {
            aux->fn();
            aux->ltime+=aux->time;
            if(aux->n>0)aux->n--;
        }
        if(aux->n==0)
        {
            timer_callback fn2=aux->fn2;
            aux=_deleteTimer(aux->id);
            if(fn2!=NULL)fn2();
        }else
        {
            aux=aux->next;
        }   
    }
}

int Timer::setTimer(unsigned long d, timer_callback f, int n) {
    return setTimer(d,f,n,NULL);
}

int Timer::setTimer(unsigned long d, timer_callback f, int n, timer_callback f2) {
    Timer::TimerInstance *inst=new Timer::TimerInstance(d,f,n,f2);
    inst->id=_idc;
    _idc++;
    if(_ini==NULL)
    {
        _ini=inst;
        _end=inst;
    }else
    {
        _end->next=inst;
        _end=inst;
    }
    return inst->id;
}

int Timer::setInterval(unsigned long d, timer_callback f) {
    return setTimer(d,f,-1);
}

int Timer::setTimeout(unsigned long d, timer_callback f) {
    return setTimer(d,f,1);
}

void Timer::deleteTimer(int id) {
    _deleteTimer(id);
}


