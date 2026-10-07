#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys { class Message; }
namespace uking::ai {
class PriestBossPhaseSecond;
class PriestBossPhaseFourth;
}

// Two unnamed embedded objects of PriestBossPhaseFourth, identified by their
// SEAD RTTI vtables. Their internals are not yet recovered; these declarations
// retain the original out-of-line constructor and nonvirtual destructor calls.
class Unk_7102451070 {
public:
    // 0x710071cae8 / 0x710071cb94
    Unk_7102451070();
    ~Unk_7102451070();
    void sub_710071CE44();

private:
    friend class uking::ai::PriestBossPhaseSecond;
    friend class uking::ai::PriestBossPhaseFourth;
    u64 _0[2];
    /* 0x10 */ sead::Vector3f _10;
    u8 _1c[0x328 - 0x1c];
    /* 0x328 */ sead::BitFlag32 _328;
    u8 _32c[4];
};
KSYS_CHECK_SIZE_NX150(Unk_7102451070, 0x330);

class Unk_7102451050 {
public:
    // 0x710071bd3c / 0x710071bf08
    Unk_7102451050();
    ~Unk_7102451050();
    bool sub_710071C550(const ksys::Message& message);
    void sub_710071C034();

private:
    u64 _0[0x208 / sizeof(u64)];
};
KSYS_CHECK_SIZE_NX150(Unk_7102451050, 0x208);

// Declared-only polymorphic phase controllers. Their RTTI pair precedes the
// virtual destructors in the original vtables; payloads remain opaque.
class Unk_7102450e00 {
public:
    virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface*) const;
    virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const;
    Unk_7102450e00();
    virtual ~Unk_7102450e00();
private:
    u64 _8[(0x1e0 - 8) / sizeof(u64)];
};
KSYS_CHECK_SIZE_NX150(Unk_7102450e00, 0x1e0);

class Unk_7102450ed8 {
public:
    virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface*) const;
    virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const;
    Unk_7102450ed8();
    virtual ~Unk_7102450ed8();
private:
    u64 _8[(0x200 - 8) / sizeof(u64)];
};
KSYS_CHECK_SIZE_NX150(Unk_7102450ed8, 0x200);
