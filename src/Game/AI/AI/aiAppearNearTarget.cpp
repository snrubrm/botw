#include "Game/AI/AI/aiAppearNearTarget.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

AppearNearTarget::AppearNearTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AppearNearTarget::~AppearNearTarget() = default;

bool AppearNearTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AppearNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsStopFallCheck_a = true;
    _8d = false;
    _8e = false;
    if (*mTeraDist_s > 0.0f && !ksys::StageInfo::sIsDungeon)
        _8d = true;
    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.0f);
        awareness->enable();
    }
    _58 = sead::GlobalRandom::instance()->getU32(10);
    if (mActor->getMapObject()) {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        m37(pos);
        sub_710030DB14();
    } else {
        changeToSpawnPrepare();
    }
    if (auto* damage_mgr = sead::DynamicCast<dmg::DamageManager>(actor->getDamageMgr()))
        damage_mgr->addDamageCallback(3, &_60);
    _88 = 9999.0f;
    _8c = false;
}

bool AppearNearTarget::isChangeable() const {
    return false;
}

bool AppearNearTarget::m36(const sead::Vector3f& pos) {
    return true;
}

void AppearNearTarget::leave_() {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20000);
    if (auto* awareness = actor->getAwareness())
        awareness->disable();
    if (auto* damage_mgr = sead::DynamicCast<dmg::DamageManager>(actor->getDamageMgr()))
        damage_mgr->removeDamageCallback(&_60);

    if (auto* body = mActor->getRigidBodyByName("Ragdoll")) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        for (int i = 0, n = body->getRigidBodies().size(); i < n; ++i) {
            if (auto* rigid_body = body->getRigidBody(i))
                rigid_body->setPosition(pos + sead::Vector3f(0.0f, 0.5f, 0.0f));
        }
    }
    *mIsStopFallCheck_a = false;
}

void AppearNearTarget::loadParams_() {
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mTeraDist_s, "TeraDist");
    getMapUnitParam(&mNearCreateAppearID_m, "NearCreateAppearID");
    getAITreeVariable(&mIsStopFallCheck_a, "IsStopFallCheck");
}

void AppearNearTarget::m34(sead::Vector3f* out) {
    sub_71005D96A8(mActor).getBase(*out, 2);
}

void AppearNearTarget::m35(sead::Vector3f* out) {
    *out = sub_71005D9330(mActor);
}

bool AppearNearTarget::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("湧出"))
        return getCurrentChild()->isFinished();
    return false;
}

void AppearNearTarget::m37(const sead::Vector3f& pos) {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20000);
    sead::Matrix34f mtx;
    m38(&mtx, pos);
    ksys::act::sub_7100EE58C0(mActor, mtx);
    mActor->sub_71011C8B04(mtx);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("湧出", &params);
    if (auto* physics = mActor->getPhysics())
        physics->setMtxAndScale(mtx, false, false, mActor->getScale().x);
    ksys::act::sub_7100EE5980(mActor, sead::Vector3f::zero);
    ksys::act::sub_7100EE5A14(mActor, sead::Vector3f::zero);
}

void AppearNearTarget::m38(sead::Matrix34f* mtx, const sead::Vector3f& pos) {
    sead::Vector3f dir = sub_71005D9330(mActor) - pos;
    dir.y = 0;
    dir.normalize();
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f)
        dir.set(sead::Vector3f::ez);
    ksys::util::sub_71011F00EC(mtx, dir, sead::Vector3f::ey, pos, false);
}

void AppearNearTarget::changeToSpawnPrepare() {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("湧出準備", &pack);
}

void AppearNearTarget::sub_710030DB14() {
    if (ksys::act::hasTag(mActor, 0xA4C7BA34u)) {
        auto* fade = sead::DynamicCast<ui::Fade>(eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade));
        if (fade && fade->isOpened()) {
            _8e = true;
            if (auto* list = mActor->getASList())
                list->sub_710115F228(0.0f);
        }
    }
}

void AppearNearTarget::sub_710030DFEC() {
    if (_8e) {
        auto* fade = sead::DynamicCast<ui::Fade>(eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade));
        if (!fade || !fade->isOpened()) {
            _8e = false;
            if (auto* list = mActor->getASList())
                list->sub_710115F228(1.0f);
        }
    }
}

}  // namespace uking::ai
