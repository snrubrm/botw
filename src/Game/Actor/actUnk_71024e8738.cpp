#include <basis/seadNew.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include "Game/Actor/actArmorBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

Unk_71024e8738::Unk_71024e8738() = default;

bool Unk_71024e8738::m5(ksys::act::BaseProc* proc) {
    return false;
}

void Unk_71024e8738::sub_7100E4DA54(sead::Heap* heap, gsys::Model* model) {
    sub_7100E4DB7C();
    const s32 count = model->getTotalBoneNum();
    if (count > 0) {
        auto* pairs = new (heap, 8, std::nothrow) Pair[count];
        if (pairs)
            mPairs.setBuffer(count, pairs);
    }
    mState = 1;
}

void Unk_71024e8738::sub_7100E4DB7C() {
    if (mState != 0) {
        mPairs.freeBuffer();
        mState = 0;
    }
}

}  // namespace uking::act
