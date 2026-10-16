#include "Game/Actor/Action/actionWaterExplode.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/World/worldElementWater.h"

namespace uking::action {

WaterExplode::WaterExplode(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterExplode::~WaterExplode() = default;

bool WaterExplode::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: instruction scheduling of the create-arg stores (same size, same calls)
void WaterExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    {
        ElementWaterCreateArg arg;
        arg.actor = mActor;
        mActor->getMtx().getTranslation(arg.position);
        arg.direction = sead::Vector3f::ey;
        arg._20 = *mRadius_s;
        arg.flags = 7;
        arg._24 = *mSpeed_s * 30.0f;
        ElementWater::create(&arg);
    }

    sead::Vector3f dir = {0.0f, 0.70710677f, 0.70710677f};
    ksys::util::sub_71011EF010(
        &dir, sead::Mathf::deg2rad(sead::GlobalRandom::instance()->getF32Range(0.0f, 360.0f)));
    {
        ElementWaterCreateArg arg;
        arg.actor = mActor;
        mActor->getMtx().getTranslation(arg.position);
        arg.direction = dir;
        arg._20 = *mRadius_s;
        arg.flags = 7;
        arg._24 = *mSpeed_s * 30.0f;
        ElementWater::create(&arg);
    }
    ksys::util::sub_71011EF010(&dir, sead::Mathf::deg2rad(120.0f));
    {
        ElementWaterCreateArg arg;
        arg.actor = mActor;
        mActor->getMtx().getTranslation(arg.position);
        arg.direction = dir;
        arg._20 = *mRadius_s;
        arg.flags = 7;
        arg._24 = *mSpeed_s * 30.0f;
        ElementWater::create(&arg);
    }
    ksys::util::sub_71011EF010(&dir, sead::Mathf::deg2rad(120.0f));
    {
        ElementWaterCreateArg arg;
        arg.actor = mActor;
        mActor->getMtx().getTranslation(arg.position);
        arg.direction = dir;
        arg._20 = *mRadius_s;
        arg.flags = 7;
        arg._24 = *mSpeed_s * 30.0f;
        ElementWater::create(&arg);
    }

    setFinished();
}

void WaterExplode::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterExplode::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeed_s, "Speed");
}

void WaterExplode::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
