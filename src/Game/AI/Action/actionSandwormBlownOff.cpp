#include "Game/AI/Action/actionSandwormBlownOff.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actSandworm.h"

namespace uking::action {

SandwormBlownOff::SandwormBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SandwormBlownOff::~SandwormBlownOff() = default;

bool SandwormBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SandwormBlownOff::sub_710023F15C(const sead::Vector3f& a, const sead::Vector3f& b,
                                      const sead::Vector3f& c) {
    if (sub_710072E928(a, b, nullptr, nullptr, nullptr, 0.5f))
        return false;
    {
        sead::Vector3f below = b;
        below.y -= 6.0f;
        if (sub_710072E928(b, below, nullptr, nullptr, nullptr, 0.5f))
            return false;
    }
    if (sub_710072E928(b, c, nullptr, nullptr, nullptr, 0.5f))
        return false;
    sead::Vector3f below = c;
    below.y -= 6.0f;
    return !sub_710072E928(c, below, nullptr, nullptr, nullptr, 0.5f);
}

void SandwormBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* life = actor->getLife();
    _100 = life ? *life : 1;
    _f4 = _f8 = *mTimer_s;
    _fc = -1.0f;
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor)) {
        sandworm->_15b0 = *mTargetSandOffset_s;
        sandworm->_1638 = true;
        sandworm->_15ac = *mSandOffsetSpeed_s;
        sandworm->_1638 = true;
    }
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _104 = true;
    if (auto* model = mActor->getModel()) {
        _80.search(model, "Spine_4");
        _b8.search(model, "Spine_8");
    }
    _f0 = 0;
}

void SandwormBlownOff::leave_() {
    _80.getKey().reset();
    _b8.getKey().reset();
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
        sandworm->_15a8 = 0;
}

void SandwormBlownOff::loadParams_() {
    getStaticParam(&mLimitDamage_s, "LimitDamage");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mDamageASName_s, "DamageASName");
    getStaticParam(&mSmallDamageASName_s, "SmallDamageASName");
    getStaticParam(&mDamageRigidName_s, "DamageRigidName");
}

void SandwormBlownOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
