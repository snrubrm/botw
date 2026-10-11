#include <Havok/Common/Serialize/Util/hkNativePackfileUtils.h>
#include "KingSystem/Physics/Ragdoll/physUnk_7102519b90.h"

namespace ksys::phys {

Unk_7102519b90::Unk_7102519b90() = default;
// Keep the vtable stores, as in GameDataFlagSelector (upstream 96101229).
Unk_7102519b90::~Unk_7102519b90() { ; }

void Unk_7102519b90::finalize_() {
    if (mEntries.isBufferReady()) {
        mEntries.freeBuffer();
        hkNativePackfileUtils::unloadInPlace(getRawData(), getRawSize());
    }
}

bool Unk_7102519b90::finishParsing_() {
    for (auto& entry : mEntries) {
        if (entry._8 && entry._28) {
            entry.sub_71012A7544();
            entry.sub_71012A734C();
        }
    }
    return true;
}

bool Unk_7102519b90::m7_() {
    bool result = true;
    for (auto& entry : mEntries) {
        if (entry._8 && entry._28)
            result &= entry.sub_71012A7738();
    }
    return result;
}

}  // namespace ksys::phys
