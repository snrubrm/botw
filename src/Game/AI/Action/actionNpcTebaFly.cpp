#include "Game/AI/Action/actionNpcTebaFly.h"
#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
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

// NON_MATCHING: same instructions; the original stores x / y of `_88` as one `stp s0, s1` pair
void NpcTebaFly::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::gdt::getBoolByKey("Wind_Relic_Rescued", false))
        mActor->emitBasicSigOn();
    else
        mActor->emitBasicSigOff();

    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    _88 = sub_710020827C();
    _b0.value = _b0.prev_value = 0.0f;
    _c0.value = _c0.prev_value = 0.0f;
    sub_710073FA90(&_cc, mActor);
    _a0 = -1.0f;
    _a4 = -1.0f;
    _a8 = -1.0f;
    playAS("Teba_BattleFly", true, 0, 0, -1.0f);
}

sead::Vector3f NpcTebaFly::sub_710020827C() {
    sead::Vector3f pos = sead::Vector3f::zero;
    if (auto* obj = mActor->getMapObject()) {
        if (auto* link_data = obj->getLinkData()) {
            if (auto* object = link_data->sub_7100D4EFA4("RemainsWind")) {
                ksys::act::ActorConstDataAccess accessor;
                object->getActorWithAccessor(accessor);
                if (accessor.hasProc())
                    pos = accessor.getActorMtx().getTranslation();
            }
        }
    }
    return pos;
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
