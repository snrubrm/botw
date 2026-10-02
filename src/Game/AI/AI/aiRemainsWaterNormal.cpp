#include "Game/AI/AI/aiRemainsWaterNormal.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

RemainsWaterNormal::RemainsWaterNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWaterNormal::~RemainsWaterNormal() = default;

bool RemainsWaterNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = false;
    if (mActor->getName().endsWith("_Far"))
        _58 = true;

    const sead::Vector3f half_width = *mInsideAreaWidth_s * 0.5f;
    _5c.set(*mInsideAreaCenter_s - half_width, half_width + *mInsideAreaCenter_s);
    const sead::Vector3f half_width_02 = *mInsideAreaWidth02_s * 0.5f;
    _74.set(*mInsideAreaCenter02_s - half_width_02, half_width_02 + *mInsideAreaCenter02_s);
    changeChild("待機");
}

void RemainsWaterNormal::calc_() {
    if (_58 || mActor->get1a0())
        return;
    if (auto* obj = mActor->getMapObject()) {
        if (obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
            return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (sub_710054B518()) {
            ksys::act::ai::InlineParamPack params;
            params.addBool(false, "IsTargetLost", -1);
            changeChild("パオーン", &params);
        } else {
            changeChild("待機");
        }
        return;
    }

    if (!child->isChangeable())
        return;

    if (isCurrentChild("パオーン")) {
        child->setDynamicParam(!sub_710054B518(), "IsTargetLost");
    } else if (isCurrentChild("待機") && sub_710054B518()) {
        ksys::act::ai::InlineParamPack params;
        params.addBool(false, "IsTargetLost", -1);
        changeChild("パオーン", &params);
    }
}

void RemainsWaterNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterNormal::loadParams_() {
    getStaticParam(&mInsideAreaWidth_s, "InsideAreaWidth");
    getStaticParam(&mInsideAreaCenter_s, "InsideAreaCenter");
    getStaticParam(&mInsideAreaWidth02_s, "InsideAreaWidth02");
    getStaticParam(&mInsideAreaCenter02_s, "InsideAreaCenter02");
}

// NON_MATCHING: block layout of the BoundBox3f::isInside chains (the original shares one
// "return false" block)
bool RemainsWaterNormal::sub_710054B518() {
    const auto& player_pos = getPlayerPosition();
    sead::Matrix34f inv;
    sead::Matrix34CalcCommon<f32>::inverse(inv, mActor->getMtx());
    sead::Vector3f pos;
    pos.setMul(inv, player_pos);
    return _5c.isInside(pos) || _74.isInside(pos);
}

}  // namespace uking::ai
