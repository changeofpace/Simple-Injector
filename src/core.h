#ifndef CORE_H
#define CORE_H

#include <QVector>
#include <QString>

#include <Windows.h>

/*
 * TODO:
 *  General
 *      - Detect and handle WoW64 processes / payloads.
 *      - Use NTAPI instead of OpenProcess to obtain process handle.
 *
 *  Injection Options
 *      - Manual map injection.
 *      - Write the payload image into a VirtualAllocEx buffer and CreateRemoteThread at EntryPoint (TLS?).
 *      - Erase PE header.
 *      - Unlink injected DLL from PEB module list (if not manually mapped).
 */

namespace core {

struct ActiveProcess
{
    DWORD pid;
    QString name;
};

bool EnableDebugPrivilege();
bool GetActiveProcesses(QVector<ActiveProcess>& ActiveProcesses);
bool CreateRemoteThreadUsingLoadLibrary(DWORD ProcessID, QString PayloadPath);

} // namespace core

#endif // CORE_H
