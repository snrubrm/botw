#include "KingSystem/Terrain/teraAreaEnv.h"

namespace ksys::tera {

void* AreaEnvGetter::sub_710107C9C4(s32 index) {
    if (static_cast<u32>(index) > 0x3f)
        return nullptr;
    const u32 count = mData->mCount0;
    void** table = mData->mTable0;
    void** entry = count > index ? table + index : table;
    return *entry;
}

void* AreaEnvGetter::sub_710107C9F4(s32 index) {
    if (static_cast<u32>(index) > 0x1f)
        return nullptr;
    const u32 count = mData->mCount1;
    void** table = mData->mTable1;
    void** entry = count > index ? table + index : table;
    return *entry;
}

void* AreaEnvGetter::sub_710107CA24(s32 index) {
    if (static_cast<u32>(index) > 0x1f)
        return nullptr;
    const u32 count = mData->mCount2;
    void** table = mData->mTable2;
    void** entry = count > index ? table + index : table;
    return *entry;
}

}  // namespace ksys::tera
