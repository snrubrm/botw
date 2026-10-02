#include "Game/AI/AI/aiRailMoveWithClose.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

RailMoveWithClose::RailMoveWithClose(const InitArg& arg) : RailMove(arg) {}

RailMoveWithClose::~RailMoveWithClose() = default;

bool RailMoveWithClose::init_(sead::Heap* heap) {
    return RailMove::init_(heap);
}

void RailMoveWithClose::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMove::enter_(params);
}

void RailMoveWithClose::leave_() {
    RailMove::leave_();
}

void RailMoveWithClose::loadParams_() {
    RailMove::loadParams_();
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mSpeed_s, "Speed");
}

void RailMoveWithClose::m38() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    f32 progress = 0;
    sead::Vector3f rail_pos;
    if (sub_710032C984(&progress, &rail_pos, pos))
        sub_710032BCAC(progress);

    if (!_40.sub_7100EEBB74())
        sub_710032CA64();
    else if ((rail_pos - pos).length() > *mOnRailDistance_s)
        sub_7100537354(rail_pos, pos);
    else
        sub_710032C088();
}

f32 RailMoveWithClose::m35() {
    sead::Vector3f rail_pos;
    sub_710032C5BC(&rail_pos);
    const f32 dist = (mActor->getMtx().getTranslation() - rail_pos).length();
    const f32 t = sead::Mathf::clamp((dist - *mOnRailDistance_s) / (*mFarDistance_s - *mOnRailDistance_s),
                                     0.0f, 1.0f);
    return *mSpeed_s * (1.0f - t);
}

}  // namespace uking::ai
