#include <iostream>
#include "include/Rtklib/rtklib_fun.h"
#include "include/IO_rtcm.h"
using namespace KPL_IO;
void *pthread_brd(void *)
{
    const char *c_path = "119.96.165.202:8605";
    stream_t m_unsyncConn;
    strinit(&m_unsyncConn);
    if (!stropen(&m_unsyncConn, STR_TCPCLI, STR_MODE_RW, c_path))
    {
        std::cout << "***ERROR(v_openRnx):can't reach the observation " << c_path << endl;
        exit(1);
    }
    strsettimeout(&m_unsyncConn, 60000, 10000); /// 60s for timeout 10s for reconnect
    unsigned char buff[1024] = {0};
    while (1)
    {
        int nread = strread(&m_unsyncConn, buff, 1024);
        for (int i = 0; i < nread; ++i)
        {
            IO_inputEphData(buff[i]);
        }
        if (nread == 0)
            sleepms(10);
    }
}
void *pthread_ssr(void *)
{
    const char *c_path = "test:test@119.96.237.211:8005/SSR_COM";
    stream_t m_unsyncConn;
    strinit(&m_unsyncConn);
    if (!stropen(&m_unsyncConn, STR_NTRIPCLI, STR_MODE_RW, c_path))
    {
        std::cout << "***ERROR(v_openRnx):can't reach the observation " << c_path << endl;
        exit(1);
    }
    strsettimeout(&m_unsyncConn, 60000, 10000); /// 60s for timeout 10s for reconnect
    unsigned char buff[1024] = {0};
    while (1)
    {
        int nread = strread(&m_unsyncConn, buff, 1024);
        for (int i = 0; i < nread; ++i)
        {
            IO_inputSsrData(buff[i]);
        }
        if (nread == 0)
            sleepms(10);
    }
}
int main(int argc, char *args[])
{
    const char *c_path = "test:test@119.96.165.202:8600/TEST";
    stream_t m_unsyncConn;
    strinit(&m_unsyncConn);
    if (!stropen(&m_unsyncConn, STR_NTRIPCLI, STR_MODE_RW, c_path))
    {
        std::cout << "***ERROR(v_openRnx):can't reach the observation " << c_path << endl;
        exit(1);
    }
    strsettimeout(&m_unsyncConn, 60000, 10000); /// 60s for timeout 10s for reconnect
    unsigned char buff[1024] = {0};
    double pos[3] = {-2258208.214700, 5020578.919700, 3210256.397500}, enu[3] = {0};
    SDK_init("kinematic", "", pos, enu, 7, 1.0);
    pthread_t pid_s, pid_e;
    pthread_create(&pid_s, NULL, pthread_ssr, NULL);
    pthread_create(&pid_e, NULL, pthread_brd, NULL);
    while (1)
    {
        int nread = strread(&m_unsyncConn, buff, 1024);
        for (int i = 0; i < nread; ++i)
        {
            IO_inputObsData(buff[i]);
        }
        if (nread == 0)
            sleepms(10);
    }
}