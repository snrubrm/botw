#include "Game/AI/AI/aiDragonFireRoot.h"
#include "Game/Actor/actDragon.h"
#include "Game/gameDragonChallengeMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

// inline-only in the original; name is a guess: whether the dragon is within 500 units (XZ) of the challenge's
// reference position (`_88`); false without a manager. Repeated in sub_7100368674 (twice) and sub_7100367FE4.
static bool isNear(ksys::act::Actor* actor) {
    auto* mgr = DragonChallengeMgr::instance();
    if (!mgr)
        return false;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    const f32 dx = pos.x - mgr->_88.x;
    const f32 dz = pos.z - mgr->_88.z;
    return sead::Mathf::sqrt(dx * dx + dz * dz) <= 500.0f;
}

// inline-only in the original; name is a guess: stores the "DragonFireEffectHolder" actor in the challenge manager
// (and sets the xlink flag 0x200 on it). Repeated in enter_ and sub_7100367FE4.
static void acquireEffectHolder(DragonFireRoot* root) {
    if (DragonChallengeMgr::instance()) {
        if (auto* holder = root->sub_71003687B4()) {
            if (auto* xlink = holder->getXLink())
                xlink->_cc.set(0x200);
            auto* mgr = DragonChallengeMgr::instance();
            mgr->mActor = holder;
            mgr->mProcLink.acquire(holder, false);
        }
    }
}

DragonFireRoot::DragonFireRoot(const InitArg& arg) : DragonRoot(arg) {}

DragonFireRoot::~DragonFireRoot() {
    if (auto* mgr = DragonChallengeMgr::instance()) {
        if (mgr->decrementRef() == 1) {
            ksys::gdt::setFlag_BalladOfHeroRito_Dragon_Passing(false, false);
            if (auto* mgr2 = DragonChallengeMgr::instance())
                mgr2->setAllFlags(false);
        }
    }
}

bool DragonFireRoot::init_(sead::Heap* heap) {
    if (!DragonRoot::init_(heap))
        return false;
    sub_7100367E70();
    return true;
}

void DragonFireRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRoot::enter_(params);
    acquireEffectHolder(this);
}

void DragonFireRoot::sub_7100367FE4() {
    if (!DragonChallengeMgr::instance())
        return;
    const bool effect = ksys::gdt::getFlag_BalladOfHeroRito_DragonEffect(false);
    const bool success = ksys::gdt::getFlag_BalladOfHeroRito_DragonSuccess(false);
    if (!DragonChallengeMgr::instance()->mProcLink.hasProc() && isNear(mActor))
        acquireEffectHolder(this);
    if (DragonChallengeMgr::instance()->_12c == 0) {
        if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
            auto* mgr = DragonChallengeMgr::instance();
            mgr->_12c = dragon->_1f70.isOnBit(28) + 1;
        }
    }
    sub_7100368674();
    const bool is_flag0_set = DragonChallengeMgr::instance()->isFlagSet(0);
    if (!(effect || success) || !is_flag0_set)
        return;

    if (isNear(mActor)) {
        if (!DragonChallengeMgr::instance()->isFlagSet(1)) {
            if (DragonChallengeMgr::instance()) {
                DragonChallengeMgr::instance()->x(1, true);
                DragonChallengeMgr::instance()->x(2, true);
                DragonChallengeMgr::instance()->emitXLink(0);
            }
            DragonChallengeMgr::instance()->setFlag(1);
        }
    } else if (DragonChallengeMgr::instance()->isFlagSet(1)) {
        if (DragonChallengeMgr::instance() && !DragonChallengeMgr::instance()->isFlagSet(2)) {
            DragonChallengeMgr::instance()->x(0, true);
            DragonChallengeMgr::instance()->x(2, true);
            DragonChallengeMgr::instance()->emitXLink(1);
        }
        DragonChallengeMgr::instance()->resetFlag(1);
    }

    if (success && !DragonChallengeMgr::instance()->isFlagSet(2)) {
        if (DragonChallengeMgr::instance()) {
            DragonChallengeMgr::instance()->x(0, true);
            DragonChallengeMgr::instance()->x(1, true);
        }
        DragonChallengeMgr::instance()->setFlag(2);
    }
}

void DragonFireRoot::sub_7100368674() {
    if (!DragonChallengeMgr::instance())
        return;
    if (isNear(mActor) && !DragonChallengeMgr::instance()->isFlagSet(3)) {
        ksys::gdt::setFlag_BalladOfHeroRito_Dragon_Passing(true, false);
        DragonChallengeMgr::instance()->setFlag(3);
    }
    if (isNear(mActor)) {
        DragonChallengeMgr::instance()->setFlag(4);
    } else if (DragonChallengeMgr::instance()->isFlagSet(4)) {
        ksys::gdt::setFlag_BalladOfHeroRito_Dragon_Passing(false, false);
        DragonChallengeMgr::instance()->resetFlag(4);
    }
}

// NON_MATCHING: the original's loop-internal `return` has no cleanup state machine (the SafeString temporary is
// destroyed before the return); our natural form builds one (different size and prologue register use)
ksys::act::Actor* DragonFireRoot::sub_71003687B4() {
    const sead::SafeString holder_name = "DragonFireEffectHolder";
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        if (auto* object = dragon->sub_710000C440()) {
            if (dragon->_1f70.isOnBit(28))
                object = object->findPlacementLODLinkObject(nullptr);
            if (object) {
                if (auto* links = object->getLinkData()) {
                    auto objects = links->mObjects;
                    for (s32 i = 0; i != objects.size(); ++i) {
                        auto* linked = objects(i);
                        if (!linked)
                            continue;
                        if (holder_name == sead::SafeString(linked->getUnitConfigName()))
                            return linked->tryGetActor(false);
                    }
                }
            }
        }
    }
    return nullptr;
}

bool DragonFireRoot::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!DragonRoot::reenter_(other, true))
        return false;
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        if (auto* mgr = DragonChallengeMgr::instance())
            mgr->_12c = dragon->_1f70.isOnBit(28) + 1;
    }
    return true;
}

void DragonFireRoot::sub_710036899C(sead::Vector3f* pos, sead::Vector3f* view_pos) {
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        sead::Matrix34f mtx;
        if (dragon->sub_71011D57F8(&mtx, "Head")) {
            pos->setMul(mtx, {31.520431518554688f, 13.0f, 24.626461029052734f});
            view_pos->setMul(mtx, {0.0f, 2.0f, 1.0f});
        }
    }
}

// NON_MATCHING: only the order of the two flag tests (the original tests `effect` first, then `!success`; ours
// branches on `success` first)
void DragonFireRoot::m45() {
    DragonRoot::m45();
    const bool effect = ksys::gdt::getFlag_BalladOfHeroRito_DragonEffect(false);
    const bool success = ksys::gdt::getFlag_BalladOfHeroRito_DragonSuccess(false);
    if (!(effect && !success) || !_24c.isOn(8) || !isNear(mActor))
        return;

    sead::Vector3f pos;
    sead::Vector3f view_pos;
    auto* info = sub_71007A255C(mActor, 0);
    if (!info || !info->_c0)
        return;
    const sead::SafeString body_name = info->_c0->getHkBodyName();
    if (!info->sub_71007A1F68(8))
        return;
    if (body_name.findIndex("怨念") != -1)
        return;
    if (body_name.findIndex("角") == -1)
        return;

    sub_710036899C(&pos, &view_pos);
    ksys::gdt::setFlag_BalladOfHeroRito_DragonDemoCameraPos(pos, false);
    ksys::gdt::setFlag_BalladOfHeroRito_DragonDemoCameraViewPos(view_pos, false);
    ksys::gdt::setFlag_BalladOfHeroRito_DragonSuccess(true, false);
    if (DragonChallengeMgr::instance())
        DragonChallengeMgr::instance()->startTimer(60.0f);
}

bool DragonFireRoot::m47() {
    if (DragonChallengeMgr::instance() && DragonChallengeMgr::instance()->isFlagSet(0) &&
        DragonChallengeMgr::instance()->isTimerStopped()) {
        if (DragonChallengeMgr::instance()->updateTimer() && DragonRoot::m47()) {
            DragonChallengeMgr::instance()->resetTimerRate();
            return true;
        }
        return false;
    }
    return DragonRoot::m47();
}

void DragonFireRoot::m42() {
    DragonRoot::m42();
}

void DragonFireRoot::m44(const sead::Vector3f& pos) {
    ksys::act::InstParamPack pack;
    pack->addPosition(pos);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "DragonFlameBall", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, &pack,
        nullptr, 2);
}

}  // namespace uking::ai
