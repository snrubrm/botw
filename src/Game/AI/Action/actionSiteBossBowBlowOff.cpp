#include "Game/AI/Action/actionSiteBossBowBlowOff.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

// 0x71002d17d4 (declared only; placeholder name, signature from SiteBossBowBlowOff::sub_7100256C34): tests whether
// `pos` is within `range` of `home` + `offset` (xz distance and y; `flag` selects the alternative test).
bool sub_71002D17D4(ksys::act::Actor* actor, const sead::Vector3f* home, const sead::Vector3f* pos,
                    const sead::Vector3f* range, const sead::Vector3f* offset, bool flag);

namespace uking::action {

SiteBossBowBlowOff::SiteBossBowBlowOff(const InitArg& arg) : SiteBossBlowOff(arg) {}

SiteBossBowBlowOff::~SiteBossBowBlowOff() = default;

bool SiteBossBowBlowOff::init_(sead::Heap* heap) {
    return SiteBossBlowOff::init_(heap);
}

void SiteBossBowBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossBlowOff::enter_(params);
    if (auto* body = mActor->getMainBody()) {
        body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        body->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
    }
    if (auto* cc = mActor->getCharacterController()) {
        if (auto* physics = mActor->getPhysics()) {
            auto* handler = physics->get188(0);
            if (auto* body = cc->sub_7100F61A34())
                body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityNoHit, handler);
        }
    }
    playAS("DownWaitMaterial", false, 2, 0, -1.0f);
}

void SiteBossBowBlowOff::leave_() {
    SiteBossBlowOff::leave_();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_1558.setBit(3);
        boss->sub_71002CFD04(false);
    }
    if (auto* body = mActor->getMainBody())
        body->setContactNone();
}

void SiteBossBowBlowOff::loadParams_() {
    SiteBossBlowOff::loadParams_();
    getStaticParam(&mAddForceRecoverTime_s, "AddForceRecoverTime");
    getStaticParam(&mIsRemoveCharacterController_s, "IsRemoveCharacterController");
    getStaticParam(&mForceRecoverDist_s, "ForceRecoverDist");
    getStaticParam(&mForceRecoverOffset_s, "ForceRecoverOffset");
}

void SiteBossBowBlowOff::calc_() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss && boss->_1558.isOnBit(7))
        return;
    if (m36()) {
        _160 = ksys::Timer(0.0f, 0.0f);
        if (_ec == 1)
            setFinished();
    }
    SiteBossBlowOff::calc_();
}

// NON_MATCHING: the original returns `!within` (`eor w8, w0, #1`) in the within-range path and loads ForceRecoverDist.y
// before ForceRecoverOffset.y.
bool SiteBossBowBlowOff::sub_7100256C34() {
    sead::Vector3f home;
    mActor->getHomePos(&home);
    auto* actor = mActor;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    auto* boss = sead::DynamicCast<act::SiteBoss>(actor);
    const bool is_kind_4 = boss && (boss->_1534 & ~3) == 4;
    if (sub_71002D17D4(mActor, &home, &pos, mForceRecoverDist_s, mForceRecoverOffset_s, is_kind_4))
        return false;
    return (mForceRecoverOffset_s->y - mForceRecoverDist_s->y) + home.y > pos.y;
}

bool SiteBossBowBlowOff::m36() {
    bool result = SiteBossBlowOff::m36();
    result |= sub_7100256C34();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        result |= boss->_1500 <= boss->_14c8._34;
        result |= boss->_1508 <= boss->_1504;
    }
    return result;
}

s32 SiteBossBowBlowOff::m37() {
    const s32 time = SiteBossBlowOff::m37();
    int level = getNumberOfDeadBlights();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534 & ~3;
        if (kind == 4)
            level = 3;
        else if (kind == 8)
            level = 4;
    }
    return time + *mAddForceRecoverTime_s * level;
}

}  // namespace uking::action
