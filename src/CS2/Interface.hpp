#pragma once
#include <Windows.h>

#include "CEngineClient.hpp"
#include "Schema.hpp"

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

    Schema::CSchemaSystem     *SchemaSystem = CreateInterface<Schema::CSchemaSystem>("schemasystem.dll", "SchemaSystem_001");
    CS2::Class::CEngineClient *EngineClient = CreateInterface<CS2::Class::CEngineClient>("engine2.dll", "Source2EngineToClient001");
} // namespace CS2::Interface
