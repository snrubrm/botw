#include "Game/AI/AI/aiNPCMove.h"
#include "Game/AI/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/actNPC.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

// 0x71004d11f4
void NPCMove::sub_71004D11F4() {
    const sead::SafeString name = "Standing";
    auto* cc = mActor->getCharacterController();
    auto* physics = mActor->getPhysics();
    if (cc && physics) {
        const s32 idx = physics->sub_7100FBE7F0(name);
        if (idx >= 0)
            cc->sub_7100F5F270(idx);
    }
    sub_71005D7518(mActor, false);
    if (_2a8->_fe8 & 0x200000) {
        sub_71006F5584(mActor);
        changeChild("ベッドから起きる", nullptr);
    } else {
        changeChild("起きる", nullptr);
    }
}

// 0x71004d44b0
// NON_MATCHING: only the operand order / condition of the last csel (state select) differs
void NPCMove::sub_71004D44B0(bool a1, bool a2) {
    sub_71005D7518(mActor, true);
    _2a8->_fe8 &= ~0x100;
    _2a8->_1050 = true;
    auto* awareness = mActor->getAwareness();
    if (awareness)
        awareness->sub_7100D7E9BC(2);
    const s32* state;
    if (sead::SafeString(getName()) == "Meeting") {
        state = &_f4;
    } else {
        state = a1 ? &_e8 : &_ec;
        if (a2)
            state = &_f0;
    }
    const s32 value = *state;
    switch (value) {
    case 1:
        _2a8->_1050 = false;
        break;
    case 2:
        _2a8->_fe8 &= ~0x80;
        _2a8->_1050 = false;
        if (awareness)
            awareness->sub_7100D7EAE4(2);
        break;
    case 5:
        _2a8->_fe8 &= ~0x80;
        if (awareness)
            awareness->sub_7100D7EAE4(2);
        break;
    case 6:
        _2a8->_1050 = false;
        [[fallthrough]];
    case 3:
        _2a8->_fe8 |= 0x100;
        break;
    default:
        break;
    }
    _2a8->_1070 = value;
}

// 0x71004d4ca4
// NON_MATCHING: the original keeps a SafeString copy of the selected AS name on the stack (vtable + string pointer
// stores before the param pack) and selects the _120 entry with a csel of two addresses
void NPCMove::sub_71004D4CA4() {
    _66 = true;
    sub_71004D44B0(true, false);
    const sead::SafeString as_name = (wm::callIsRainingOrSnowingOrThunderStorm(true) && _60) ? _120[20] : _120[19];
    ksys::act::ai::InlineParamPack pack;
    pack.addString(as_name, "WaitASName", -1);
    pack.addVec3(_28c, "BasisPos", -1);
    changeChild("うろつく", &pack);
}

}  // namespace uking::ai
