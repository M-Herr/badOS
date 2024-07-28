#pragma once

#include <Types.hpp>

struct InterruptServiceFrame
{
    uint16_t ip;
    uint16_t cs;
    uint16_t flags;
    uint16_t sp;
    uint16_t ss;
};

struct ISRBase 
{
    //__attribute__((interrupt))
    virtual void operator()() = 0;
};

struct ISRProgrammable : public ISRBase
{
    virtual void operator()() override
    {
        
    }
};

struct ISRKeyboard : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRCOM1 : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRCOM2 : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRLPT2 : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRFloppyDisk : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRLPT1 : public ISRBase 
{
    virtual void operator()() override
    {

    }
};


struct ISRCMOSRealTimeClock : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRPeripherals : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRPS2Mouse : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRFPU : public ISRBase 
{
    virtual void operator()() override
    {

    }
};

struct ISRATA : public ISRBase 
{
    virtual void operator()() override
    {

    }
};


extern "C" {
    __attribute__((noreturn))
    void default_isr_handler(void);
}