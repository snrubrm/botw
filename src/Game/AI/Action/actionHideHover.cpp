#include "Game/AI/Action/actionHideHover.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

HideHover::HideHover(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HideHover::~HideHover() = default;

bool HideHover::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HideHover::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sub_710072BB70(actor, &_70, *mIsKeepLifeGage_s, mEffectName_s.isEmpty());
    if (auto* lod = actor->getLodState())
        lod->mFlags26.set(0x1);
    _48 = *mTimer_s;
    _7c = true;
    _7d = false;
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
}

void HideHover::leave_() {
    _50.fadeXLink();
    auto* actor = mActor;
    if (auto* lod = actor->getLodState())
        lod->mFlags26.reset(0x1);
    sub_710072BEC4(actor, &_70, *mIsKeepLifeGage_s);
}

void HideHover::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mEffectName_s, "EffectName");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsKeepLifeGage_s, "IsKeepLifeGage");
}

void HideHover::calc_() {
    if (_7c) {
        _7c = false;
    } else if (!_7d) {
        _7d = true;
        if (!mEffectName_s.isEmpty())
            xlinkSearchAndEmit(mActor, mEffectName_s.cstr(), 2, &_50);
    }
    ksys::Timer::update(&_48, -1.0f);
    if (_48 <= 0.0f)
        setFinished();
}

}  // namespace uking::action
