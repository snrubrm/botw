#include "Game/Actor/aiUnk_71007130BC.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/aiLockedProcLink.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

const sead::SafeString& sub_710071300C(s32 idx) {
    static const sead::SafeString sNames[] = {"", "Crouch", "Sit", "SitOnObject"};
    return sNames[idx];
}

void sub_71007130BC(ksys::act::Actor* actor, bool on) {
    if (!actor)
        return;
    if (on)
        ksys::act::x_6(actor);
    else
        ksys::act::setEnabledTalkAndLockOn(actor, false);
}

void sub_7100713564(ksys::act::Actor* actor, s32 count) {
    if (!actor)
        return;
    const char* name = actor->getName().getStringTop();
    if (auto* info = ksys::act::InfoData::instance()) {
        if (!info->hasTag(name, ksys::act::tags::Unk_0x207CBCE1))
            return;
    }
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;
    const f32 state = count < 3 ? count : 3;
    sead::FormatFixedSafeString<64> key("%s_AttackedState", name);
    manager->setS32(count < 0 ? 0 : s32(state), key);
}

namespace wm {
bool callIsRainingOrSnowingOrThunderStorm(bool a1) {
    return isRainingOrSnowingOrThunderStorm(a1);
}
}  // namespace wm

void sub_71007132E4(ksys::act::Actor* actor) {
    if (!actor)
        return;
    const sead::SafeString on_flag =
        actor->getParam()->getRes().mGParamList->getNpc()->mOnFlagWhenDelete.ref();
    const sead::SafeString off_flag =
        actor->getParam()->getRes().mGParamList->getNpc()->mOffFlagWhenDelete.ref();
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;
    if (!on_flag.isEmpty())
        manager->setBool(true, on_flag);
    if (!off_flag.isEmpty())
        manager->setBool(false, off_flag);
}

void sub_71007136BC(ksys::act::Actor* actor) {
    if (!actor)
        return;
    const char* name = actor->getName().getStringTop();
    auto* info = ksys::act::InfoData::instance();
    if (info && !info->hasTag(name, ksys::act::tags::Unk_0x207CBCE1))
        return;
    auto* manager = ksys::gdt::Manager::instance();
    sead::FormatFixedSafeString<64> reward("%s_Reward", name);
    bool received = false;
    if (!manager)
        return;
    auto& param = manager->getParam();
    const bool found =
        param.get().getBuffer()->getBool(&received, reward, param.shouldCheckPermissions(), true);
    if (received && found) {
        sead::FormatFixedSafeString<64> saved("%s_Saved", name);
        manager->setBool(true, saved);
    }
}

// NON_MATCHING: local static array initialization and destructor registration differ.
void sub_7100713780(ksys::act::Actor* actor, bool saved) {
    if (!actor)
        return;
    const sead::SafeString name = actor->getName();
    if (auto* info = ksys::act::InfoData::instance()) {
        if (!info->hasTag(name.getStringTop(), ksys::act::tags::Unk_0x207CBCE1))
            return;
    }
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;
    static const sead::SafeString sSavedFlagNames[] = {
        "AttackedNPC_Set1_Saved", "AttackedNPC_Set2_Saved", "AttackedNPC_Set3_Saved",
        "AttackedNPC_Set4_Saved", "AttackedNPC_Set5_Saved", "AttackedNPC_Set6_Saved",
        "AttackedNPC_Set7_Saved", "AttackedNPC_Set8_Saved",
    };
    if (name == "Npc_Attacked_001") {
        manager->setBool(saved, sSavedFlagNames[5]);
        if (!saved)
            manager->setBool(false, "AttackedNPC_Set6_Wander");
    } else if (name == "Npc_Attacked_002") {
        manager->setBool(saved, sSavedFlagNames[7]);
    } else if (name == "Npc_Attacked_003") {
        manager->setBool(saved, sSavedFlagNames[3]);
    } else if (name == "Npc_Attacked_004") {
        manager->setBool(saved, sSavedFlagNames[1]);
    } else if (name == "Npc_Attacked_005") {
        manager->setBool(saved, sSavedFlagNames[4]);
    } else if (name == "Npc_Attacked_006") {
        manager->setBool(saved, sSavedFlagNames[2]);
    } else if (name == "Npc_Attacked_007") {
        manager->setBool(saved, sSavedFlagNames[7]);
    } else if (name == "Npc_Attacked_008" || name == "Npc_Attacked_009") {
        manager->setBool(saved, sSavedFlagNames[0]);
    } else if (name == "Npc_Attacked_010") {
        manager->setBool(saved, sSavedFlagNames[1]);
    } else if (name == "Npc_Attacked_011") {
        manager->setBool(saved, sSavedFlagNames[2]);
    } else if (name == "Npc_Attacked_012") {
        manager->setBool(saved, sSavedFlagNames[6]);
    }
}

// NON_MATCHING: the public inline flag writer passes true for the callee's unused fourth argument.
void sub_71007130D4(ksys::act::Actor* actor) {
    if (!actor)
        return;
    sead::SafeString name = actor->getName();
    ksys::act::getSameGroupActorName(&name, actor);
    sead::FixedSafeString<128> flag;
    flag.format("%s_DispNameFlag", name.cstr());
    ksys::gdt::Manager::instance()->setBool(true, flag, false, false);
}

void sub_71007133A8(ksys::act::Actor* actor, const ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (link->hasProc() && ksys::act::acquireActor(link, &accessor)) {
        const auto& position = accessor.getPreviousPos2();
        if (auto* npc = sead::DynamicCast<uking::act::NPC>(actor))
            npc->_103c = position;
    }
}

void sub_7100713488(ksys::act::Actor* actor, const sead::Vector3f& position) {
    if (auto* npc = sead::DynamicCast<uking::act::NPC>(actor))
        npc->_103c = position;
}

// NON_MATCHING: clang keeps the accessor's address in x21 (frame 0x50 vs 0x40); the logic, order
// and calls match.
void sub_7100713FF4(ksys::act::Actor* actor, ksys::act::Actor* ride_actor) {
    if (!actor || !ride_actor)
        return;
    const sead::SafeString ride_anim = ride_actor->getASList()->x_1(1, 0);
    if (ride_anim == "Dislike" || ride_anim == "Slip") {
        const sead::SafeString& anim = actor->getASList()->x_1(1, 0);
        if (anim == "Face_C_Detect")
            return;
        actor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "Face_C_Detect", 1, 0, true);
    } else {
        actor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "Face_C_Default", 1, 0, true);
    }
}

void sub_710071418C(ksys::act::Actor* actor, uking::ai::LockedProcLinkMaybe* payload) {
    if (!actor)
        return;
    if (!sead::IsDerivedFrom<uking::act::NPC>(actor))
        return;
    auto* npc = static_cast<uking::act::NPC*>(actor);
    if (npc->_fe8 & 0x10000)
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&npc->_f70, &accessor))
        return;

    payload->mLock.lock();
    payload->mLink.acquire(npc, false);
    payload->_50 = 0.0f;
    npc->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800009), payload,
                     true);
    payload->mLock.unlock();
}

