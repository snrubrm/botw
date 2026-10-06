#include "Game/AI/Action/actionWaterUpDownMoveBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <prim/seadStringUtil.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

WaterUpDownMoveBase::WaterUpDownMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterUpDownMoveBase::~WaterUpDownMoveBase() = default;

bool WaterUpDownMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterUpDownMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    mFlags.reset(Flag::Changeable);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _74.changeMotionType(controller, ksys::act::MotionType::Hover);
    f32 depth;
    if (mActor->getDepthInWater() > 0.0f)
        depth = mActor->getDepthInWater();
    else
        depth = sub_71002B37F8() - mActor->getMtx().m[1][3];
    _6c = depth - *mInWaterDepth_s;
    _7c._0 = -1.0f;
    _7c._4 = 0.5f;
    _7c.sub_7100700634(mActor);
}

f32 WaterUpDownMoveBase::sub_71002B37F8() {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    sead::Vector3f start;
    mActor->getMtx().getTranslation(start);
    sead::Vector3f end = start;
    end.y -= 10.0f;
    query.setStart(start);
    query.setEnd(end);
    query.enableLayer(ksys::phys::ContactLayer::EntityWater);
    f32 y = 0.0f;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        sead::Vector3f hit;
        query.getHitPosition(&hit);
        y = hit.y;
    }
    return y;
}

void WaterUpDownMoveBase::leave_() {
    _74.resetMotionType(mActor->getCharacterController());
}

void WaterUpDownMoveBase::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mWaterFloatRadius_s, "WaterFloatRadius");
    getStaticParam(&mWaterFloatCycleTime_s, "WaterFloatCycleTime");
    getStaticParam(&mASName_s, "ASName");
}

void WaterUpDownMoveBase::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    auto* as_list = mActor->getASList();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0x2f, &query, 0, 0))
        m32(&query);
    if (as_list->x(0x2f, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        m33(controller);
    else
        m34(controller);
    if (isFinishedAS(0, 0))
        setFinished();
    _7c.sub_7100700640(mActor);
}

void WaterUpDownMoveBase::m32(ksys::as::ASList::Unk4* query) {
    f32 depth = 0.0f;
    sead::StringUtil::tryParseF32(&depth, query->name);
    sub_71002B390C(depth, query->_10);
}

void WaterUpDownMoveBase::m33(ksys::phys::CharacterController* controller) {
    sub_71002B3ACC(controller);
    sub_7100738660(controller, *mRotReduceRatio_s);
}

void WaterUpDownMoveBase::m34(ksys::phys::CharacterController* controller) {
    sub_71002B3F78(controller);
    sub_7100738660(controller, *mRotReduceRatio_s);
}

}  // namespace uking::action
