#include "core.h"

#include <TlHelp32.h>

bool core::EnableDebugPrivilege()
{
    bool result = false;
    LUID luid = {};

    if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
    {
        HANDLE hToken = 0;
        if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
        {
            TOKEN_PRIVILEGES tokenPrivileges;
            tokenPrivileges.PrivilegeCount = 1;
            tokenPrivileges.Privileges[0].Luid = luid;
            tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (AdjustTokenPrivileges(hToken,
                                      FALSE,
                                      &tokenPrivileges,
                                      sizeof(TOKEN_PRIVILEGES),
                                      0,
                                      0))
                result = true;
            CloseHandle(hToken);
        }
    }

    return result;
}

bool core::GetActiveProcesses(QVector<ActiveProcess>& ActiveProcesses)
{
    ActiveProcesses.clear();
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32 pe32 = {};
    pe32.dwSize = sizeof(PROCESSENTRY32);

    for (Process32First(hSnapshot, &pe32); Process32Next(hSnapshot, &pe32); /**/)
        ActiveProcesses.push_back(ActiveProcess{pe32.th32ProcessID,
                                                QString::fromWCharArray(pe32.szExeFile)});

    return true;
}

bool core::CreateRemoteThreadUsingLoadLibrary(DWORD ProcessID, QString PayloadPath)
{
    bool result = false;

    if (HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID))
    {
        if (LPVOID threadBase = VirtualAllocEx(hProcess,
                                               nullptr,
                                               PayloadPath.size(),
                                               MEM_RESERVE | MEM_COMMIT,
                                               PAGE_READWRITE))
        {
            if (WriteProcessMemory(hProcess,
                                   threadBase,
                                   PayloadPath.toStdString().c_str(),
                                   PayloadPath.size(),
                                   nullptr))
            {
                // TODO: LoadLibraryW doesn't work, but CreateRemoteThread succeeds (even when
                // toStdWString is used in WPM above.
                if (LPVOID loadLibBase = GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA"))
                {
                    if (HANDLE hThread = CreateRemoteThread(hProcess,
                                                            nullptr,
                                                            0,
                                                            LPTHREAD_START_ROUTINE(loadLibBase),
                                                            threadBase,
                                                            0,
                                                            nullptr))
                    {
                        result = true;
                        CloseHandle(hThread);
                    }
                }
            }
        }
        CloseHandle(hProcess);
    }

    return result;
}
