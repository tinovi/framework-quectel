////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Georgi Angelov
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#ifndef LDEV_h
#define LDEV_h

#include <Arduino.h>

#define DEFAULT_AT_TIMEOUT 1000

class LDEV
{

public:
    LDEV() {}

    const char *version() { return os_get_firmware(); }
    void version(String &s) { s = os_get_firmware(); }

    void urc(void (*onUrc)(ST_MSG *msg)) { setOnUrc(onUrc); }
    int sim(){ return os_ril_get_sim(); }

    void Sleep() { Ql_SleepEnable(); }
    void noSleep(bool f = true)
    {
        if (f)
            Ql_SleepDisable();
        else
            Ql_SleepEnable();
    }

    bool enterPin(const char *pin)
    {
        if (pin)
        {
            char CMD_CPIN[32];
            Ql_sprintf(CMD_CPIN, "AP+CPIN =\"%s\"\n", pin);
            return Ql_RIL_SendATCmd(CMD_CPIN, strlen(CMD_CPIN), NULL, NULL, DEFAULT_AT_TIMEOUT) == RIL_AT_SUCCESS;
        }
        return false;
    }

    int getSimStatus()
    {
        return os_ril_get_sim(); // 0 = READY,
    }

    void waitSimReady(const char *pin)
    {
        if (pin)
        {
            if (false == enterPin(pin))
            {
                while (true)
                    Ql_Sleep(1000); // no exit
            }
        }
        os_ril_wait_sim();
    }

    static int GET_QCGDEFCONT(char *line, u32 len, void *user)
    {
        int res = isAtEnd(line, len);
        if (RIL_ATRSP_CONTINUE != res)
            return res;
        char *h = Ql_RIL_FindString(line, len, (char *)"+QCGDEFCONT:");
        if (h && user)
        {
            char *p1 = NULL;
            char *p2 = NULL;
            p1 = Ql_strstr(h, ":");
            p2 = Ql_strstr(p1 + 1, "\r\n");
            if (p1 && p2)
                Ql_memcpy((char *)user, p1 + 2, p2 - p1 - 2);
        }
        return RIL_ATRSP_CONTINUE;
    }


    ///return IP, IPV6, IPV4V6, Non-IP
    bool getDefaultApnType(char *type)
    {
        if (type)
        {
            char cmd[16];
            Ql_sprintf(cmd, "AT+QCGDEFCONT?\n");
            return Ql_RIL_SendATCmd(cmd, strlen(cmd), GET_QCGDEFCONT, type, DEFAULT_AT_TIMEOUT) == RIL_AT_SUCCESS;
        }
        return false;
    }

    bool saveDefaultApn(const char *type, const char *apn, const char *user, const char *pass)
    { //AT+QCGDEFCONT="IP","apn","user","pass"
        if (NULL == type || NULL == apn)
            return false;
        char cmd[256];
        Ql_sprintf(cmd, "AT+QCGDEFCONT=\"%s\",\"%s\"", type, apn);
        if (user)
        {
            Ql_strcat(cmd, (char *)",\"");
            Ql_strcat(cmd, (char *)user);
            Ql_strcat(cmd, (char *)"\"");
            if (pass)
            {
                Ql_strcat(cmd, (char *)",\"");
                Ql_strcat(cmd, (char *)pass);
                Ql_strcat(cmd, (char *)"\"");
            }
        }
        Ql_strcat(cmd, (char *)"\n");
        return Ql_RIL_SendATCmd(cmd, strlen(cmd), NULL, NULL, DEFAULT_AT_TIMEOUT) == RIL_AT_SUCCESS;
    }


    int getRssi(){
        s32 ret;
        RIL_NW_GetCSQ(&ret);
        return ret;
    }

    void reset() { Ql_Reset(0); }
    void off() { Ql_PowerDown(0); }
    int wakeupReason() { return Ql_GetWakeUpReason(); }
    int powerReason() { return Ql_GetPowerOnReason(); }
    unsigned int battery()
    {
        unsigned int value;
        return 0 == Ql_GetPowerVol(&value) ? value : 0;
    }

    /* UID is U32[4] */
    void getUid(void *buffer) // [16]
    {
        if (buffer)
            memcpy(buffer, os_get_uid(), 4 * sizeof(uint32_t));
    }
    void getUid(String &s) // return hex string
    {
        char buf[16], hex[3];
        getUid(buf);
        for (int i = 0; i < 16; i++)
        {
            sprintf(hex, "%02X", buf[i]);
            s += hex;
        }
    }

    void getImei(char *imei) // [16]
    {
        if (imei)
        {
            memset(imei, 0, 16);
            int res = RIL_GetIMEI(imei);
        }
    }
    void getImei(String &s)
    {
        char imei[32];
        getImei(imei);
        s = imei;
    }

    bool getImsi(char *buffer) { return os_ril_get_imsi(buffer); }
    void getImsi(String &s)
    {
        char buffer[32];
        os_ril_get_imsi(buffer);
        s = buffer;
    }

    bool getIccid(char *buffer) { return os_ril_get_iccid(buffer); }
    void getIccid(String &s)
    {
        char buffer[32];
        os_ril_get_iccid(buffer);
        s = buffer;
    }

    bool getMccMnc(char *buffer) { return os_ril_get_mcc_mnc(buffer); }
    void getMccMnc(String &s)
    {
        char buffer[32];
        os_ril_get_mcc_mnc(buffer);
        s = buffer;
    }

    bool send(const char *cmd, u32 timeout = 300, Callback_ATResponse callback = NULL, void *user = NULL)
    {
        return Ql_RIL_SendATCmd((char *)cmd, Ql_strlen(cmd), callback, user, timeout) == RIL_AT_SUCCESS;
    }
    bool send(String cmd, u32 timeout = 300, Callback_ATResponse callback = NULL, void *user = NULL)
    {
        return send(cmd.c_str(), timeout, callback, user);
    }

    bool band(int band) { return os_ril_set_band(band); }

    int cereg(bool wait = true)
    {
        if (wait)
            os_ril_wait_cereg();
        return os_ril_get_cereg();
    }

    bool dns(const char *dns_1 = NULL, const char *dns_2 = NULL)
    {
        return os_ril_set_dns(dns_1, dns_2); // NULL, NULL = google
    }
};

#endif