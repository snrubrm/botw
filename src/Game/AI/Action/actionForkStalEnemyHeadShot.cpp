#include "Game/AI/Action/actionForkStalEnemyHeadShot.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_7100724C64.h"

namespace uking::action {

ForkStalEnemyHeadShot::ForkStalEnemyHeadShot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkStalEnemyHeadShot::~ForkStalEnemyHeadShot() = default;

bool ForkStalEnemyHeadShot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalEnemyHeadShot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkStalEnemyHeadShot::leave_() {
    auto* actor = mActor;
    if (_60 > 0) {
        _60 = 0;
        sub_71007275C8(sub_7100724D7C(actor));
    }
    sub_7100738DC8(actor);
}

void ForkStalEnemyHeadShot::loadParams_() {
    getStaticParam(&mVisibleCount_s, "VisibleCount");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mUseAddVec_s, "UseAddVec");
    getStaticParam(&mHeadBoneKey_s, "HeadBoneKey");
    getStaticParam(&mAddVec_s, "AddVec");
    getStaticParam(&mRotVec_s, "RotVec");
}

void ForkStalEnemyHeadShot::calc_() {
    if (_60 > 0 && --_60 == 0)
        sub_71007275C8(sub_7100724D7C(mActor));
}

}  // namespace uking::action
