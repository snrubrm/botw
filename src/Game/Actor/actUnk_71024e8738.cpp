#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include "Game/Actor/actArmorBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

Unk_71024e8738::Unk_71024e8738() = default;

bool Unk_71024e8738::m5(ksys::act::BaseProc* proc) {
    return false;
}

void Unk_71024e8738::sub_7100E4DB7C() {
    if (mState != 0) {
        if (mPairs) {
            delete[] mPairs;
            mPairs = nullptr;
            mCapacity = 0;
        }
        mState = 0;
    }
}

}  // namespace uking::act
