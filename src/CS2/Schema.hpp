#pragma once
#include <Windows.h>
#include <stdint.h>
#include <stdio.h>

#include "SDK.hpp"
#include "Virtual.hpp"

#include "Interface.hpp"

#define SCHEMA(type, name, field_name, class_name, module_name)                                               \
    std::add_lvalue_reference_t<type> name()                                                                  \
    {                                                                                                         \
        return *(type *)((uint64_t)this + CS2::Schema::GetSchemaOffset(module_name, class_name, field_name)); \
    }

namespace CS2::Schema
{
    class CSchemaSystem;
    class CSchemaSystemTypeScope;
    class CSchemaType_XXX;
    struct SchemaClassFieldData_t;
    struct SchemaBaseClassInfoData_t;
    struct SchemaStaticFieldData_t;
    struct SchemaClassInfoData_t;

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

    struct SchemaStaticFieldData_t
    {
        const char      *m_FieldName;  // 0x0000
        CSchemaType_XXX *m_SchemaType; // 0x0008
        void            *m_Instance;   // 0x0010

        uint64_t pad_0x18; // 0x0018
        uint64_t pad_0x20; // 0x0020
    };

    // https://github.com/neverlosecc/source2gen/blob/main/include/sdk/interfaces/schemasystem/schema.h
    // https://github.com/bruhmoment21/cs2-sdk/blob/v2/cs2-sdk/sdk/include/interfaces/schemasystem.hpp
    struct SchemaClassInfoData_t
    {
        uint64_t    pad0;         // 0x00
        const char *m_ClassName;  // 0x08
        const char *m_ModuleName; // 0x10

        int32_t m_SizeOf;      // 0x18
        int16_t m_FieldsCount; // 0x1C
        int16_t m_StaticCount; // 0x1E

        int16_t m_MetadataCount;    // 0x20
        int8_t  m_AlignOf;          // 0x22 没有父类的时候,这个值为:-1
        int8_t  m_BaseClassesCount; // 0x23 有父类的时候,这个值为:1
        int16_t pad2;               // 0x24
        int16_t pad3;               // 0x26

        SchemaClassFieldData_t    *m_Fields;       // 0x28
        SchemaStaticFieldData_t   *m_StaticFields; // 0x30
        SchemaBaseClassInfoData_t *m_BaseClasses;  // 0x38

        void                   *pad4;         // 0x40
        void                   *m_Metadata;   // 0x48 SchemaMetadataSetData_t
        CSchemaSystemTypeScope *m_TypeScope;  // 0x50
        CSchemaType_XXX        *m_SchemaType; // 0x58 CSchemaType_DeclaredClass
        uint64_t                m_ClassFlags; // 0x60 SchemaClassFlags_t

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
            printf("// m_StaticCount: %d\r\n", this->m_StaticCount);
            printf("// m_MetadataCount: %d\r\n", this->m_MetadataCount);
            printf("// m_AlignOf: %d\r\n", this->m_AlignOf);
            printf("// m_BaseClassesCount: %d\r\n", this->m_BaseClassesCount);
            printf("// pad2: %d\r\n", this->pad2);
            printf("// pad3: %d\r\n", this->pad3);
            if (this->m_BaseClasses != nullptr)
                printf("// BaseClass: %s\r\n", this->m_BaseClasses->m_ClassInfo->m_ClassName);

            printf("namespace %s {\r\n", this->m_ClassName);
            for (size_t i = 0; i < this->m_FieldsCount; i++)
            {
                printf("    constexpr std::ptrdiff_t %s = 0x%X; // %s \r\n",
                       this->m_Fields[i].m_FieldName,
                       this->m_Fields[i].m_Offset,
                       this->m_Fields[i].m_SchemaType->m_TypeName);
            }
            printf("}\r\n\r\n");

            if (this->m_BaseClasses != nullptr)
                this->m_BaseClasses->m_ClassInfo->Dump();
        }
    };

    int32_t GetSchemaOffset(const char *moduleName, const char *className, const char *fieldName)
    {
        SchemaClassInfoData_t *classInfo = CS2::Interface::SchemaSystem->FindTypeScopeForModule(moduleName)->FindDeclaredClass(className);

        for (int16_t i = 0; i < classInfo->m_FieldsCount; i++)
        {
            if (std::string(fieldName) == classInfo->m_Fields[i].m_FieldName)
            {
                return classInfo->m_Fields[i].m_Offset;
            }
        }

        return 0;
    }

} // namespace CS2::Schema
