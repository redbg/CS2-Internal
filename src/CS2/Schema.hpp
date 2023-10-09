#pragma once
#include <Windows.h>
#include <stdint.h>
#include <stdio.h>

#include "SDK.hpp"
#include "Virtual.hpp"

namespace CS2::Schema
{
    class CSchemaSystem;
    class CSchemaSystemTypeScope;
    class CSchemaType_XXX;
    struct SchemaClassInfoData_t;
    struct SchemaClassFieldData_t;
    struct SchemaBaseClassInfoData_t;

    class CSchemaSystem
    {
    public:
        char                                      pad[0x190];
        SDK::CUtlVector<CSchemaSystemTypeScope *> m_TypeScope; // 0x190

    public:
        CSchemaSystemTypeScope *FindTypeScopeForModule(const char *moduleName)
        {
            return Virtual::Call<0xD, CSchemaSystemTypeScope *>(this, moduleName, nullptr);
        }
    };

    class CSchemaSystemTypeScope
    {
    public:
        void *vt;            // 0x00
        char  m_Name[0x100]; // 0x08
        // CUtlTSHash<CSchemaClassBinding> 0x588
        // CUtlTSHash<CSchemaEnumBinding>  0x2DD0

        SchemaClassInfoData_t *FindDeclaredClass(const char *className)
        {
            if (this == nullptr)
                return nullptr;

            SchemaClassInfoData_t *classInfo = nullptr;
            Virtual::Call<2, void *>(this, &classInfo, className);
            return classInfo;
        }
    };

    class CSchemaType_XXX
    {
    public:
        virtual void           *VirtualFunction_0() {} // 0x00
        const char             *m_TypeName;            // 0x08
        CSchemaSystemTypeScope *m_TypeScope;           // 0x10
    };

    struct SchemaClassFieldData_t
    {
        const char      *m_FieldName;  // 0x00
        CSchemaType_XXX *m_SchemaType; // 0x08
        int32_t          m_Offset;     // 0x10
        int32_t          pad0;         // 0x14
        int64_t          pad1;         // 0x18
    };

    struct SchemaBaseClassInfoData_t
    {
        uint64_t               pad0;        // 0x00
        SchemaClassInfoData_t *m_ClassInfo; // 0x08
    };

    struct SchemaClassInfoData_t
    {
        uint64_t                   pad0;            // 0x00
        const char                *m_ClassName;     // 0x08
        const char                *m_ModuleName;    // 0x10
        uint32_t                   m_SizeOf;        // 0x18
        uint16_t                   m_FieldsCount;   // 0x1C
        uint16_t                   pad1;            // 0x1E
        uint64_t                   pad2;            // 0x20
        SchemaClassFieldData_t    *m_Fields;        // 0x28
        uint64_t                   pad3;            // 0x30
        SchemaBaseClassInfoData_t *m_BaseClassInfo; // 0x38
        char                       pad4[0x28];      // 0x40

        // https://github.com/a2x/cs2-dumper
        void Dump()
        {
            if (this == nullptr)
                return;

            printf("// SchemaClassInfoData_t: 0x%p\r\n", this);
            printf("// m_ClassName: %s\r\n", this->m_ClassName);
            printf("// m_ModuleName: %s\r\n", this->m_ModuleName);
            printf("// m_SizeOf: 0x%X\r\n", this->m_SizeOf);
            printf("// m_FieldsCount: %d\r\n", this->m_FieldsCount);
            if (this->m_BaseClassInfo != nullptr)
                printf("// BaseClass: %s\r\n", this->m_BaseClassInfo->m_ClassInfo->m_ClassName);

            printf("namespace %s {\r\n", this->m_ClassName);
            for (size_t i = 0; i < this->m_FieldsCount; i++)
            {
                printf("    constexpr std::ptrdiff_t %s = 0x%X; // %s \r\n",
                       this->m_Fields[i].m_FieldName,
                       this->m_Fields[i].m_Offset,
                       this->m_Fields[i].m_SchemaType->m_TypeName);
            }
            printf("}\r\n\r\n");

            if (this->m_BaseClassInfo != nullptr)
                this->m_BaseClassInfo->m_ClassInfo->Dump();
        }
    };

} // namespace CS2::Schema
