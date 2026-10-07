#include "Game/Actor/actHorseRideInfo.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseRider.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseUnit.h"

namespace uking::act {

Unk_710244eaa0::~Unk_710244eaa0() = default;

void Unk_710244eaa0::m4() {
    if (!_1e8)
        return;
    if (mLeft.bone._8)
        mLeft.actor->sub_71011DA868(&mLeft.bone);
    if (mRight.bone._8)
        mRight.actor->sub_71011DA868(&mRight.bone);
}

bool Unk_710244eaa0::m5(const ksys::act::ActorConstDataAccess& accessor) {
    if (_1e8) {
        f32 angle = 0.0f;
        if (accessor.getGParamList()->getHorseUnit()->mRiddenAnimalType.ref() == 10) {
            angle = sead::Mathf::deg2rad(
                mActor->getParam()->getRes().mGParamList->getHorseRider()->mFootRotAngleForKuma.ref());
        }
        mLeft._b8 = angle;
        mLeft._d4 = 0;
        mRight._b8 = angle;
        mRight._d4 = 0;
    }
    return true;
}

void Unk_710244eaa0::m6() {
    if (_1e8) {
        mLeft._d4 = 1;
        mRight._d4 = 1;
    }
}

// NON_MATCHING: register allocation / store scheduling of the two foot setups (the original keeps only the GParam
// object in a callee-saved register)
bool Unk_710244eaa0::m7() {
    const auto* rider = mActor->getParam()->getRes().mGParamList->getHorseRider();
    if (rider->mLeftFootNode.ref().isEmpty()) {
        _1e8 = false;
        return true;
    }
    _1e8 = !rider->mRightFootNode.ref().isEmpty();
    if (_1e8) {
        mLeft.actor = mActor;
        mLeft.axis = &rider->mLeftFootRotAxis.ref();
        mLeft.ratio = rider->mFootRotRatio.ref();
        mLeft.retRatio = rider->mFootRetRotRatio.ref();
        mLeft.name = &rider->mLeftFootNode.ref();
        mLeft.bone.setName(rider->mLeftFootNode.ref());
        mLeft._c8 = 0;

        mRight.axis = &rider->mRightFootRotAxis.ref();
        mRight.actor = mActor;
        mRight.ratio = rider->mFootRotRatio.ref();
        mRight.retRatio = rider->mFootRetRotRatio.ref();
        mRight.name = &rider->mRightFootNode.ref();
        mRight.bone.setName(rider->mRightFootNode.ref());
        mRight._c8 = 0;
    }
    return true;
}

void Unk_710244eaa0::m8() {
    if (!_1e8)
        return;
    mLeft._c8 = 0;
    if (mLeft.bone._8)
        mLeft.actor->sub_71011DA868(&mLeft.bone);
    mRight._c8 = 0;
    if (mRight.bone._8)
        mRight.actor->sub_71011DA868(&mRight.bone);
}

void Unk_710244eaa0::m9() {
    if (_1e8) {
        mLeft.sub_71006E1984();
        mRight.sub_71006E1984();
    }
}

}  // namespace uking::act
