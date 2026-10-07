#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

// Two unnamed embedded objects of PriestBossPhaseFourth, identified by their
// SEAD RTTI vtables. Their internals are not yet recovered; these declarations
// retain the original out-of-line constructor and nonvirtual destructor calls.
class Unk_7102451070 {
public:
    // 0x710071cae8 / 0x710071cb94
    Unk_7102451070();
    ~Unk_7102451070();

private:
    u64 _0[0x330 / sizeof(u64)];
};
KSYS_CHECK_SIZE_NX150(Unk_7102451070, 0x330);

class Unk_7102451050 {
public:
    // 0x710071bd3c / 0x710071bf08
    Unk_7102451050();
    ~Unk_7102451050();

private:
    u64 _0[0x208 / sizeof(u64)];
};
KSYS_CHECK_SIZE_NX150(Unk_7102451050, 0x208);
