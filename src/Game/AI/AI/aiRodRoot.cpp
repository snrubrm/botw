#include "Game/AI/AI/aiRodRoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h"
#include "Game/AI/aiXlinkHandle.h"

namespace uking::ai {

RodRoot::RodRoot(const InitArg& arg) : WeaponRootAI(arg), _f0() {}

RodRoot::~RodRoot() {
    xlink::kill(_f0.mELink);
}

bool RodRoot::init_(sead::Heap* heap) {
    *mMagicCreateUnit_a = &_118;
    return WeaponRootAI::init_(heap);
}

// NON_MATCHING: the original keeps the 1-based counter (`sub w1, w20, #1` per call); clang rewrites the loop
// around the 0-based value
void RodRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
    if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor)) {
        if (auto* rod = weapon->getParam()->getRes().mGParamList->getRod())
            _114 = rod->mChargeMagicNum.ref();
    }
    _110 = -1;
    sub_71005531E8();
    sub_71005535F8();
    for (s32 i = 1; i <= _114; ++i) {
        sub_7100553E5C(i - 1);
        if (i > 7)
            break;
    }
}

void RodRoot::leave_() {
    if (_118._8.isAllocatedOrFailed())
        _118._8.deleteProc();
    for (s32 i = 0; i < _114; ++i) {
        if (i <= 7) {
            if (_118._18[i].isAllocatedOrFailed())
                _118._18[i].deleteProc();
        }
    }
    WeaponRootAI::leave_();
    _110 = -1;
}

void RodRoot::loadParams_() {
    WeaponRootAI::loadParams_();
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

void RodRoot::calc_() {
    WeaponRootAI::calc_();
    sub_71005539C0();
    sub_71005531E8();
    sub_7100553CF0();
}

}  // namespace uking::ai
