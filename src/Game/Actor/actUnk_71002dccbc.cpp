#include "Game/Actor/actUnk_71002dccbc.h"

namespace uking::act {

void Unk_71002dccbc::sub_71002DC32C() {
    for (auto& entry : mEntries) {
        entry.link.reset();
        entry.flags = 0;
        entry._12 = 0;
    }
}

void Unk_71002dccbc::sub_71002DCBDC(u16 flags) {
    for (auto& entry : mEntries) {
        entry.flags &= ~flags;
        if (entry.flags == 0) {
            entry.link.reset();
            entry._12 = 0;
        }
    }
}

// NON_MATCHING: the original keeps a redundant `and w8, w8, #0xffff` after each flag test
bool Unk_71002dccbc::sub_71002DCCBC(s32 flags) {
    for (auto& entry : mEntries) {
        if (entry.link.hasProcInCalcState() && (entry.flags & flags))
            return false;
    }
    return true;
}

}  // namespace uking::act
