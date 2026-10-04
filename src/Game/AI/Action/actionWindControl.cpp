#include "Game/AI/Action/actionWindControl.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WindControl::WindControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}


bool WindControl::init_(sead::Heap* heap) {
    _118.sub_71010C42B4();
    if (mActor) {
        if (mActor->getName() == "WindGeneratorLength")
            _118._80 = true;
    }
    return true;
}

void WindControl::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _110 = actor->hasPlacementLinkForBasicSig() ? 0.0f : *mMaxRadSpeed_s;
    if (!mTargetNodeName_s.isEmpty() && !_20._8) {
        _20.setName(mTargetNodeName_s);
        actor->boneHandleStuff(&_20, false);
    }
    _1a0 = 0.1f;
    _1a4 = 1.0f;
}

void WindControl::leave_() {
    if (_20._8)
        mActor->sub_71011DA868(&_20);
    _118.destroy(false);
}

void WindControl::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMaxRadSpeed_s, "MaxRadSpeed");
    getStaticParam(&mRadAccel_s, "RadAccel");
    getStaticParam(&mTemperature_s, "Temperature");
    getStaticParam(&mUseEnvTemperature_s, "UseEnvTemperature");
    getStaticParam(&mIsModelControlOnly_s, "IsModelControlOnly");
    getStaticParam(&mTargetNodeName_s, "TargetNodeName");
}

void WindControl::calc_() {
    ksys::act::ai::Action::calc_();
}

bool WindControl::hasUpdateForPreDeleteCb() {
    return true;
}

bool WindControl::updateForPreDelete() {
    return _118.sub_71010C4284();
}

}  // namespace uking::action
