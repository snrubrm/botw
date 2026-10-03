#include "Game/AI/AI/aiNPCMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::ai {

NPCMove::NPCMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCMove::~NPCMove() = default;

bool NPCMove::init_(sead::Heap* heap) {
    _2a8 = sead::DynamicCast<act::NPC>(mActor);
    if (mActor->getName() == "Npc_Strange_Beacon")
        _67 = true;
    return true;
}

void NPCMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCMove::loadParams_() {
    getStaticParam(&mTerritoryRange_s, "TerritoryRange");
    getStaticParam(&mDestination_s, "Destination");
    getStaticParam(&mMoveEndASName_s, "MoveEndASName");
}

void NPCMove::changeToTurnAround(const sead::Vector3f& rot) {
    const char* as_name = "Turn";
    if (_61 || _62)
        as_name = _120[11].getStringTop();

    ksys::act::ai::InlineParamPack params;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    params.addVec3(pos, "TargetPos", -1);
    params.addVec3(rot, "TargetRot", -1);
    params.addString(as_name, "DynASName", -1);
    changeChild("振り返る", &params);
}

// NON_MATCHING: register allocation of the two horizontal differences (x / z swap s8 / s9) and the order of their
// stores
bool NPCMove::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000078) {
        _62 = true;
        if (auto* data = static_cast<s32*>(message->getUserData()))
            _68 = *data;

        sead::Vector3f dir = getPlayerPosition();
        dir.x -= mActor->getMtx().m[0][3];
        dir.y = 0.0f;
        dir.z -= mActor->getMtx().m[2][3];
        dir.normalize();

        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, sead::Vector3f(0.0f, 0.0f, 1.0f), dir,
                                   sead::Vector3f::ey);
        dir.set(0.0f, angle * axis.y, 0.0f);
        changeToTurnAround(dir);
    }

    if (_2f0._30)
        return false;
    return _2f0.m2(*message);
}

bool NPCMove::handleAck_(const ksys::MessageAck* ack) {
    if (!_2c0.sub_710070E070(*ack))
        return false;
    if (!ack->isSuccess())
        return false;
    _65 = true;
    return true;
}

}  // namespace uking::ai
