#include "KingSystem/ActorSystem/actFarActorMerge.h"
#include <gsys/gsysModel.h>

namespace ksys::act {

FarActorMerge::FarActorMerge() = default;

FarActorMerge::~FarActorMerge() {
    cleanup();
}

void FarActorMerge::cleanup() {
    if (!mFlags.isOn(2) || !_58)
        return;

    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.state == 1) {
            entry._60.sub_7100FDD264();
            gsys::Model::sub_7100BF69F8(entry.model);
            entry.model = nullptr;
        }
    }
    mEntries.freeBuffer();
    mHandle.requestUnload2();
    _58 = nullptr;
    _60 = nullptr;
}

void FarActorMerge::sub_710124ABC0(const sead::SafeString& name, sead::Heap* heap) {}

void FarActorMerge::requestDraw() {
    if (!mFlags.isOnAll(3))
        return;

    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.state != 0 && mLoadedEntries.isOnBit(i))
            entry.model->requestDraw();
    }
}

// NON_MATCHING: the original keeps the search result in a state value (found / not found / skip) and tests it after
// the loop; the search itself and the loop bounds match.
bool FarActorMerge::x(s32 id) {
    if (!mFlags.isOnAll(3))
        return false;

    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.state != 1 || !mLoadedEntries.isOnBit(i))
            continue;

        s32 a = 0;
        s32 b = entry.info->num_ids - 1;
        s32 idx = -1;
        while (a < b) {
            const s32 m = (a + b) / 2;
            const s32 c = entry.ids[m] - id;
            if (c == 0) {
                idx = m;
                break;
            }
            if (c < 0)
                a = m + 1;
            else
                b = m;
        }
        if (idx < 0 && entry.ids[a] == id)
            idx = a;
        if (idx >= 0)
            return true;
    }
    return false;
}

}  // namespace ksys::act
