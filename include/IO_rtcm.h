#ifndef IO_RTKLIB_IO_RTCM_H_
#define IO_RTKLIB_IO_RTCM_H_
#include "include/Rtklib/rtklib.h"
namespace KPL_IO
{
    extern void SDK_init(const char *mode, const char *ant, double *refx, double *enu, double cut, double intv);
    extern void SDK_terminate();
    extern void SDK_restart();
    extern void SDK_setintv(double intv);
    extern int IO_inputObsData(uint8_t data);
    extern int IO_inputEphData(uint8_t data);
    extern int IO_inputSsrData(uint8_t data);
}
#endif