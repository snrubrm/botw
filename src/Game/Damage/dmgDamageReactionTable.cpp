#include <utility/aglParameter.h>
#include "Game/Damage/dmgInfoManager.h"

namespace uking::dmg {

void DamageReactionTable::sub_71006681D4() {}

void DamageReactionTable::stubbed() {}

bool DamageReactionTable::isReady() {
    return true;
}

s32 DamageReactionTable::sub_71006681E4(const sead::SafeString& name) const {
    const u32 hash = agl::utl::ParameterBase::calcHash(name);
    for (s32 i = 0; i < mItems.size(); ++i) {
        if (mItems[i].mField_0 == s32(hash))
            return i;
    }
    return -1;
}

DamageInfoMgr::Unk868::Unk868() = default;
DamageInfoMgr::Unk868::~Unk868() = default;
void DamageInfoMgr::Unk868::sub_71006682C0() {
    Entry entry;
    mBuckets[0].fill(entry);
    mBuckets[1].fill(entry);
}

void DamageInfoMgr::Unk868::sub_71006685C0() {}

}  // namespace uking::dmg
