#include "Game/Actor/AI/aiNPCMove.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "Game/Actor/aiUnk_7100711020.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/aiUnk_71006F5B14.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/Player/actPlayerInfo.h"
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

// NON_MATCHING: combined sleep-child predicate and shared cleanup branch layout.
void NPCMove::leave_() {
    auto* schedule = mActor->getSchedule();
    if (schedule && _2a8) {
        if (mActor->getRootAi()->isActorGoingBackToRootAi() ||
            testRootAiFlag(ksys::act::ai::RootAiFlag::_5)) {
            _2a8->_104c = 0;
        } else {
            if (schedule->_68 != getName()) {
                _2a8->_104c = 0;
                if ((isCurrentChild("到着") || isCurrentChild("身体を起こす")) &&
                    (sead::SafeString(getName()) == "Sleep" ||
                     sead::SafeString(getName()) == "Sleep2")) {
                    _2a8->_fe8 |= 0x80000;
                }
            }
            sub_71007130BC(mActor, true);
            if (mActor->getAttention()) {
                if (auto* client = mActor->getAttention()->getClientByName("Awake"))
                    client->setEnabled(false);
                if (auto* client = mActor->getAttention()->getClientByName("AwakeLockOn"))
                    client->setEnabled(false);
            }
        }
        ksys::act::x_6(mActor);
        _62 = false;
        _68 = 0;
    }
    if (_78 <= sead::Mathf::epsilon())
        mActor->setFlag(ksys::act::Actor::ActorFlag::_34, false);
}

void NPCMove::loadParams_() {
    getStaticParam(&mTerritoryRange_s, "TerritoryRange");
    getStaticParam(&mDestination_s, "Destination");
    getStaticParam(&mMoveEndASName_s, "MoveEndASName");
}

void NPCMove::changeToTurnAround(const sead::Vector3f& rot) {
    const char* as_name = "Turn";
    if (_61 || _62)
        as_name = _1d0.getStringTop();

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

// The original selects the name with a csel of two addresses (the entries at +0x190 / +0x1a0).
// 0x71004cfc88
bool NPCMove::sub_71004CFC88() {
    const sead::SafeString name =
        wm::callIsRainingOrSnowingOrThunderStorm(true) ? (_60 ? _1a0 : _190) : _190;
    const bool changed = name != mActor->getASList()->sub_710115ECF4(55, 1);
    mActor->getASList()->goLimpFromHeadShotMaybe(55, name, 0);
    mActor->getASList()->goLimpFromHeadShotMaybe(56, name, 0);
    return changed;
}

// NON_MATCHING: as NPCScheduleMove::sub_71004DFA90 (the second distance threshold is a GOT-loaded readonly float)
// 0x71004d4b98
ksys::act::Unk_7100d78e50* NPCMove::sub_71004D4B98() {
    if (_78 <= sead::Mathf::epsilon())
        mActor->setFlag(ksys::act::Actor::ActorFlag::_34, false);
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return nullptr;
    Unk_71024513d0 filter;
    f32 distance = 5.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam())
        distance = global->getGlobalParam()->mNPCOpenDoorDistance.ref();
    auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
    if (entry) {
        if (entry->_a8 < distance) {
            mActor->setFlag(ksys::act::Actor::ActorFlag::_34, true);
        } else {
            if (entry->_a8 <= 4.0f)
                mActor->setFlag(ksys::act::Actor::ActorFlag::_34, true);
            entry = nullptr;
        }
    }
    return entry;
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

// NON_MATCHING: the inline isEqual of the "Act_Wander" comparison is peeled and checks the right string
// for the terminator in the original; ours keeps the generic loop. The destination of the _1028 assignment
// is also addressed after the getName call in the original (ours computes it before).
// 0x71004d00cc
void NPCMove::sub_71004D00CC(bool a1, bool a2) {
    const bool raining = _60 && wm::callIsRainingOrSnowingOrThunderStorm(true);
    // C++14 evaluation order: the original evaluates the destination first
    _2a8->_1028.operator=(getName());
    auto* schedule = mActor->getSchedule();
    schedule->_88 = schedule->_68;
    sub_71004D33E8(false, raining);
    if (_2a8->_104c == 0)
        mActor->getASList()->goLimpFromHeadShotMaybe(
            0x3b, sub_710071300C(raining ? _100 : _fc), 0);
    sub_71004D44B0(false, raining);
    if (schedule->_127 != 0)
        sub_71005D7518(mActor, false);

    if (sead::SafeString(raining ? _260 : _250) == "Act_Wander") {
        sub_71004D4CA4();
        return;
    }

    sead::SafeString as_name = _250;
    const char* child;
    if (raining) {
        as_name = _260;
        child = "雨宿り地点に到着";
    } else {
        if (sead::SafeString(getName()) == "Sleep" ||
            sead::SafeString(getName()) == "Sleep2") {
            if (!(_2a8->_fe8 & 0x100000)) {
                if (_1b0 == "True") {
                    sub_71007130BC(mActor, false);
                    if (auto* attention = mActor->getAttention()) {
                        if (auto* client = attention->getClientByName("Awake"))
                            client->setEnabled(true);
                        if (auto* client = attention->getClientByName("AwakeLockOn"))
                            client->setEnabled(true);
                    }
                }
                mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::InstEvent);
            }
        }
        child = "到着";
    }

    if (_61 || _62) {
        as_name = _1e0;
    } else if (a1) {
        const char* current = mActor->getASList()->sub_710115ECF4(0x3b, 1);
        if (sead::SafeString(current) == "Sit")
            as_name = "Rest";
        else if (sead::SafeString(current) == "SitOnObject")
            as_name = "Act_SitChair_Wait";
        else
            as_name = "Wait";
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addString(as_name, "ASName", -1);
    pack.addBool(raining, "IsRainAnchor", -1);
    pack.addBool(a2, "IsStartSameAS", -1);
    changeChild(child, &pack);
}

// 0x71004d33e8
void NPCMove::sub_71004D33E8(bool a1, bool a2) {
    if (_67) {
        if (sead::SafeString(getName()) != "Sleep" &&
            sead::SafeString(getName()) != "Sleep2") {
            if (_2a8->_1028.getStringTop()[0] != sead::SafeString::cNullChar)
                return;
        }
    }

    sead::SafeString as_name;
    as_name = a1 && _2a8->_1028.getStringTop()[0] == sead::SafeString::cNullChar
                  ? _160
                  : (a2 ? _180 : _170);

    if (as_name == "Hold") {
        _2a8->_1060 = 0;
        sub_7100712E00(mActor);
    } else if (as_name == "Equip") {
        _2a8->_1060 = 1;
        mActor->getASList()->goLimpFromHeadShotMaybe(44, "", 0);
    } else if (as_name == "Invisible") {
        _2a8->_1060 = 2;
        mActor->getASList()->goLimpFromHeadShotMaybe(44, "", 0);
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
    const sead::SafeString as_name = (wm::callIsRainingOrSnowingOrThunderStorm(true) && _60) ? _260 : _250;
    ksys::act::ai::InlineParamPack pack;
    pack.addString(as_name, "WaitASName", -1);
    pack.addVec3(_28c, "BasisPos", -1);
    changeChild("うろつく", &pack);
}

}  // namespace uking::ai
