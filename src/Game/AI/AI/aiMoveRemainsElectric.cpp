#include "Game/AI/AI/aiMoveRemainsElectric.h"
#include "Game/AI/aiUnk_710073033C.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

MoveRemainsElectric::MoveRemainsElectric(const InitArg& arg) : RailMoveRemains(arg) {}

MoveRemainsElectric::~MoveRemainsElectric() = default;

bool MoveRemainsElectric::init_(sead::Heap* heap) {
    return RailMoveRemains::init_(heap);
}

void MoveRemainsElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRemains::enter_(params);
}

void MoveRemainsElectric::leave_() {
    RailMoveRemains::leave_();
}

void MoveRemainsElectric::loadParams_() {
    RailMoveRemains::loadParams_();
    getStaticParam(&mReactiveRange_s, "ReactiveRange");
    getStaticParam(&mDemoCallWaitTime_s, "DemoCallWaitTime");
    getStaticParam(&mCannonOffset_s, "CannonOffset");
    getStaticParam(&mWeakPointOffset_s, "WeakPointOffset");
    getMapUnitParam(&mIsJoinRemainsBattle_m, "IsJoinRemainsBattle");
}

bool MoveRemainsElectric::m40() {
    auto& player = ksys::act::PlayerInfo::getSomeProcLink();
    if (!player.hasProc())
        return false;
    return !sub_710073033C(mActor, &player, *mReactiveRange_s);
}

f32 MoveRemainsElectric::m43() {
    if (auto* as_list = mActor->getASList()) {
        if (as_list->_14.isValid())
            return as_list->sub_710115D2D4().length();
    }
    return RailMoveRemains::m43();
}

}  // namespace uking::ai
