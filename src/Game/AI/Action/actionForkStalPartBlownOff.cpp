#include "Game/AI/Action/actionForkStalPartBlownOff.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkStalPartBlownOff::ForkStalPartBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkStalPartBlownOff::~ForkStalPartBlownOff() = default;

bool ForkStalPartBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalPartBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const auto* life = actor->getLife();
    if ((life ? f32(*life) : 1.0f) / f32(actor->getMaxLife()) <= *mLifeRate_s)
        sub_7100166114();
    mFlags.set(Flag::Changeable);
}

void ForkStalPartBlownOff::leave_() {
    auto* actor = mActor;
    if (_50 > 0) {
        _50 = 0;
        sub_71007275C8(sub_7100724D7C(actor));
    }
    sub_7100738DC8(actor);
}

void ForkStalPartBlownOff::loadParams_() {
    getStaticParam(&mShootParts_s, "ShootParts");
    getStaticParam(&mShootSpeed_s, "ShootSpeed");
    getStaticParam(&mLifeRate_s, "LifeRate");
    getStaticParam(&mBaseNodeName_s, "BaseNodeName");
    getStaticParam(&mShootDir_s, "ShootDir");
}

void ForkStalPartBlownOff::calc_() {
    if (_50 > 0 && --_50 == 0)
        sub_71007275C8(sub_7100724D7C(mActor));
}

}  // namespace uking::action
