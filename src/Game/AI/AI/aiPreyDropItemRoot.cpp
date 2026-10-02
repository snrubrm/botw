#include "Game/AI/AI/aiPreyDropItemRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

PreyDropItemRoot::PreyDropItemRoot(const InitArg& arg) : PreyRoot(arg) {}

PreyDropItemRoot::~PreyDropItemRoot() = default;

bool PreyDropItemRoot::init_(sead::Heap* heap) {
    if (!PreyRoot::init_(heap))
        return false;
    _22c = true;
    return true;
}

// NON_MATCHING: scheduling (the target stores _230 after loading the interval)
void PreyDropItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyRoot::enter_(params);
    if (_22c)
        sub_71004FAE28();
    _230 = 0;
    const f32 interval = *mForceDeleteInterval_s;
    if (interval < 0.0f)
        _220 = ksys::Timer(1.0f, 1.0f, 0.0f);
    else
        _220 = ksys::Timer(interval, interval);
}

void PreyDropItemRoot::calc_() {
    PreyRoot::calc_();
    if (_230 >= *mMaxDropCount_s) {
        _220.update();
        if (_220.value <= sead::Mathf::epsilon() && !isCurrentChild("強制消去"))
            changeChild("強制消去");
    }
}

void PreyDropItemRoot::leave_() {
    if (auto* object = mActor->getMapObject())
        object->setRevivalFlagValueIf(ksys::map::ActorData::Flag::RevivalEnable, true);
    PreyRoot::leave_();
}

void PreyDropItemRoot::loadParams_() {
    PreyRoot::loadParams_();
    getStaticParam(&mMaxDropCount_s, "MaxDropCount");
    getStaticParam(&mForceDeleteInterval_s, "ForceDeleteInterval");
    getStaticParam(&mInitialVelocity_s, "InitialVelocity");
}

}  // namespace uking::ai
