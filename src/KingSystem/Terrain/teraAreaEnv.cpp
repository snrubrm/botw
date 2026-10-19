#include "KingSystem/Terrain/teraAreaEnv.h"

namespace ksys::tera {

AreaEnvEntry0* AreaEnvGetter::sub_710107C9C4(s32 index) {
    if (static_cast<u32>(index) > 0x3f)
        return nullptr;
    return mData->mEntries0[index];
}

AreaEnvEntry1* AreaEnvGetter::sub_710107C9F4(s32 index) {
    if (static_cast<u32>(index) > 0x1f)
        return nullptr;
    return mData->mEntries1[index];
}

AreaEnvEntry2* AreaEnvGetter::sub_710107CA24(s32 index) {
    if (static_cast<u32>(index) > 0x1f)
        return nullptr;
    return mData->mEntries2[index];
}

}  // namespace ksys::tera
