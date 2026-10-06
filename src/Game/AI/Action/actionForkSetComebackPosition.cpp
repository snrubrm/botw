#include "Game/AI/Action/actionForkSetComebackPosition.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

ForkSetComebackPosition::ForkSetComebackPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSetComebackPosition::~ForkSetComebackPosition() = default;

bool ForkSetComebackPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetComebackPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkSetComebackPosition::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetComebackPosition::loadParams_() {}

// NON_MATCHING: same arithmetic and call sequence; the original does not keep the cross product's y in a register
// across the atan2f call but recomputes `dir.x * ez.z - dir.z * ez.x` for the sign test (it saves d8-d10, we save d8/d9).
void ForkSetComebackPosition::calc_() {
    ksys::act::acc::PlayerBase player;
    if (!player.getPlayerFromPlayerInfo())
        return;
    auto* actor = mActor;
    if (!actor->get68f())
        return;

    const auto& player_mtx = player.getActorMtx();
    sead::Vector3f pos;
    player_mtx.getTranslation(pos);
    const sead::Vector3f dir{actor->getMtx()(0, 2), actor->getMtx()(1, 2), actor->getMtx()(2, 2)};
    const f32 dot = dir.dot(sead::Vector3f::ez);
    sead::Vector3f cross;
    cross.setCross(sead::Vector3f::ez, dir);
    f32 angle = std::atan2(cross.length(), dot);
    if (cross.y < 0.0f)
        angle = -angle;
    player.setRestartBuf(pos, sead::Mathf::rad2deg(angle));
}

}  // namespace uking::action
