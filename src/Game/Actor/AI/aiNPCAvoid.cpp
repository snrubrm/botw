#include "Game/Actor/AI/aiNPCAvoid.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/aiUnk_71024f1658.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

NPCAvoid::NPCAvoid(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAvoid::~NPCAvoid() = default;

void NPCAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCAvoid::leave_() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        if (*mTargetTerrorLevel_s != 5)
            npc->_1048 = 3;
        npc->_fe8 &= ~0x10000000;
    }
    sub_71005D7518(mActor, true);
}

void NPCAvoid::loadParams_() {
    getStaticParam(&mTargetTerrorLevel_s, "TargetTerrorLevel");
    getStaticParam(&mReleaseCrouchTime_s, "ReleaseCrouchTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mIsSitting_d, "IsSitting");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

bool NPCAvoid::isChangeable() const {
    return isCurrentChild("アラート") || isCurrentChild("脅威解除");
}

// 0x71004c2a4c
bool NPCAvoid::sub_71004C2A4C() {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    const sead::Vector3f start = mActor->getMtx().getTranslation();
    const sead::Vector3f dir = -sead::Vector3f::ey;
    query.setStartAndDisplacementScaled(start, dir, 10.0f);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return true;
    sead::Vector3f hit;
    query.getHitPosition(&hit);
    return mActor->getMtx().getTranslation().y - hit.y > 2.0f;
}

// 0x71004c22d4
// NON_MATCHING: register allocation and the shape of the free slot search loop.
void NPCAvoid::sub_71004C22D4() {
    auto* awareness = mActor->getAwareness();
    if (!awareness || !awareness->_260[2])
        return;
    const s32 num = awareness->_260[2]->_8.size();
    if (num < 1)
        return;

    s32 slot = 0;
    for (s32 i = 0; i < num; ++i) {
        auto* sensor = awareness->_260[2];
        if (!sensor || i >= sensor->_8.size())
            continue;
        auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, i);
        if (!entry || s32(entry->_a4) != 5)
            continue;

        const auto& link = entry->_0.mLink;
        bool known = false;
        for (const auto& registered : _110) {
            if (registered == link) {
                known = true;
                break;
            }
        }
        if (known)
            continue;

        while (true) {
            if (slot > 9)
                return;
            auto& registered = _110[slot++];
            if (!registered.hasProc()) {
                registered = link;
                break;
            }
        }
        if (slot > 9)
            return;
    }
}

// NON_MATCHING: one branch: ours clears w0 before the kind test and shares the return block.
// 0x71004c24ac
bool NPCAvoid::sub_71004C24AC(sead::Vector3f* pos) {
    auto* chemical = mActor->getChemicalStuff();
    if (!chemical)
        return false;
    if (!sub_71007A2604(mActor))
        return false;
    auto* info = sub_71007A255C(mActor, 0);
    if (!info)
        return false;
    Unk_7100739634Result result;
    result.kind = 0;
    result._4 = 0;
    result._8 = 0;
    result._c = 0;
    result._10 = 0;
    result._14 = -1;
    result._18 = false;
    if (sub_7100739634(&result, chemical, info, nullptr) && result.kind == 4) {
        if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
            npc->_e30._10.getTranslation(*pos);
            return true;
        }
    }
    return false;
}

// 0x71004c25d4
void NPCAvoid::sub_71004C25D4(bool skip_clear_message) {
    if (!skip_clear_message && *mTargetTerrorLevel_s == 5)
        sub_7100711FAC(mActor, "ClearTerrorGuardian");
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        npc->_1048 = 3;
        if (npc->_840 && npc->_840->sub_7100EEBB74())
            npc->_9d8.copy(npc->_840->sub_7100EEEE88(mActor));
    }
    changeChild("脅威解除");
}

// 0x71004c15dc
void NPCAvoid::sub_71004C15DC(const sead::Vector3f& target) {
    ksys::act::setEnabledTalkAndLockOn(mActor, false);
    _ac = ksys::Timer(1800.0f, 1800.0f);
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, "", 0);

    ksys::act::ai::InlineParamPack pack;
    auto* npc = sead::DynamicCast<act::NPC>(mActor);
    if (npc && npc->_fe8 & 0x8000000) {
        if (sub_71004C2A4C()) {
            npc->_fe8 |= 0x10000000;
            changeChild("潜る");
            return;
        }
        pack.addVec3(target, "TargetPos", -1);
        pack.addVec3(*mTargetVel_d, "TargetVel", -1);
        changeChild("泳いで逃げる", &pack);
    } else {
        pack.addVec3(target, "TargetPos", -1);
        pack.addVec3(*mTargetVel_d, "TargetVel", -1);
        changeChild("逃走", &pack);
    }
}

}  // namespace uking::ai
