#pragma once
#include <Windows.h>

// 前置声明
namespace CS2::Schema
{
    class CSchemaSystem;
} // namespace CS2::Schema

namespace CS2::Interface
{
    typedef void *(*CreateInterfaceFn)(const char *pName, int *pReturnCode);
    typedef void *(*InstantiateInterfaceFn)();

    class InterfaceReg
    {
    public:
        InstantiateInterfaceFn *m_CreateFn;
        const char             *m_pName;
        InterfaceReg           *m_pNext;
    };

    template <typename T>
    T *CreateInterface(const char *pModuleName, const char *pInterfaceName)
    {
        CreateInterfaceFn createInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(pModuleName), "CreateInterface");
        int               returnCode      = 0;
        return (T *)createInterface(pInterfaceName, &returnCode);
    }

    // CEngineClient
    class CEngineClient
    {
    public:
        bool IsInGame()
        {
            return Virtual::Call<32, bool>(this);
        }

        bool IsConnected()
        {
            return Virtual::Call<33, bool>(this);
        }

        SIZE GetScreenSize()
        {
            // size.cx = width
            // size.cy = height
            SIZE size = {};
            Virtual::Call<50, void>(this, &size.cx, &size.cy);
            return size;
        }
    };

    Schema::CSchemaSystem *SchemaSystem = CreateInterface<Schema::CSchemaSystem>("schemasystem.dll", "SchemaSystem_001");
    CEngineClient         *EngineClient = CreateInterface<CEngineClient>("engine2.dll", "Source2EngineToClient001");
} // namespace CS2::Interface
