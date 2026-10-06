#include "Game/AI/Action/actionWaterUpDownAnmDrivenMove.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

WaterUpDownAnmDrivenMove::WaterUpDownAnmDrivenMove(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WaterUpDownAnmDrivenMove::~WaterUpDownAnmDrivenMove() = default;

bool WaterUpDownAnmDrivenMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterUpDownAnmDrivenMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

f32 WaterUpDownAnmDrivenMove::sub_71002B7EEC() {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    sead::Vector3f start;
    mActor->getMtx().getTranslation(start);
    sead::Vector3f end = start;
    end.y -= 10.0f;
    query.setStart(start);
    query.setEnd(end);
    query.enableLayer(ksys::phys::ContactLayer::EntityWater);
    f32 y;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        sead::Vector3f hit;
        query.getHitPosition(&hit);
        y = hit.y;
    } else {
        y = end.y - 1.0f;
    }
    return y;
}

void WaterUpDownAnmDrivenMove::leave_() {
    _54.resetMotionType(_54.sub_710072ACF8(mActor));
}

void WaterUpDownAnmDrivenMove::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mTargetDepth_s, "TargetDepth");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void WaterUpDownAnmDrivenMove::calc_() {
    ksys::act::ai::Action::calc_();
}

void WaterUpDownAnmDrivenMove::m32(ksys::phys::CharacterController* controller) {
    sub_7100738AA8(mActor, *mRotReduceRatio_s);
}

}  // namespace uking::action
