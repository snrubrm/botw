#include "Game/AI/Action/actionNpcTebaFly.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

NpcTebaFly::NpcTebaFly(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NpcTebaFly::~NpcTebaFly() = default;

bool NpcTebaFly::init_(sead::Heap* heap) {
    sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NpcTebaFly::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NpcTebaFly::leave_() {
    ksys::act::ai::Action::leave_();
}

void NpcTebaFly::loadParams_() {
    getStaticParam(&mTurnEnableFrame_s, "TurnEnableFrame");
    getStaticParam(&mStartTurnDist_s, "StartTurnDist");
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mInterpolateTurnFrameForMaxSpeed_s, "InterpolateTurnFrameForMaxSpeed");
    getStaticParam(&mInterpolateMoveFrameForMaxSpeed_s, "InterpolateMoveFrameForMaxSpeed");
    getStaticParam(&mTurnEndRad_s, "TurnEndRad");
    getStaticParam(&mMoveSpeedMin_s, "MoveSpeedMin");
    getStaticParam(&mMoveSpeedMax_s, "MoveSpeedMax");
    getStaticParam(&mTurnReduceSpeedRatio_s, "TurnReduceSpeedRatio");
    getStaticParam(&mEvacuateRemainsDist_s, "EvacuateRemainsDist");
    getStaticParam(&mTargetPosRatio_s, "TargetPosRatio");
    getStaticParam(&mPlayerApproachCannonDist_s, "PlayerApproachCannonDist");
}

// NON_MATCHING: float register allocation / frame size (the original keeps only d8-d11 live).
bool NpcTebaFly::sub_7100208D90(sead::Vector3f* out) {
    auto* obj = mActor->getMapObject();
    if (!obj)
        return false;
    auto* link_data = obj->getLinkData();
    if (!link_data)
        return false;
    const sead::Vector3f player_pos = getPlayerPosition();
    const s32 count = link_data->mObjects.size();
    bool found = false;
    f32 nearest = 10000.0f;
    for (s32 i = 0; i < count; ++i) {
        auto* object = link_data->mObjects(i);
        if (!object)
            continue;
        if (sead::SafeString(object->getUnitConfigName()) != "RemainsWind_Battery_A_01")
            continue;
        ksys::act::ActorConstDataAccess accessor;
        object->getActorWithAccessor(accessor);
        if (!accessor.isStateCalc())
            continue;
        const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
        const f32 distance = (player_pos - pos).length();
        if (distance < nearest) {
            nearest = distance;
            found = true;
            *out = pos;
        }
    }
    return found;
}

void NpcTebaFly::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
