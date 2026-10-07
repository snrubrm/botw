#include "Game/AI/AI/aiLumberjackFallenTree.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <math/seadBoundBox.h>

namespace uking::ai {

void Unk_7102403e48::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a5 != -1)
        *a1 = 0;
}

void Unk_7102403e80::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;
    auto* damage_mgr = sub_710072BA90(_28->getActor());
    if (!damage_mgr)
        return;
    const bool flag = damage_mgr->checkDamageFlags(4);
    sead::Vector3f position;
    damage_mgr->getPosition(&position);
    _28->sub_71004855DC(position);
    if (flag)
        *a1 = 0;
}

LumberjackFallenTree::LumberjackFallenTree(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LumberjackFallenTree::~LumberjackFallenTree() {
    if (_f8)
        _f8->clear();
    _100.sub_7100D786EC();
    _1b8.sub_7100D786EC();
}

// NON_MATCHING: the original loads `mActor` (the second argument) before the virtual slot of `_f8->init` (C++14
// evaluation order of the call; we compile as C++17)
bool LumberjackFallenTree::init_(sead::Heap* heap) {
    bool ok = true;
    if (*mLumberjackType_a == 1) {
        _f8 = new (heap, 8) act::Unk_710244eb00;
        if (_f8)
            ok = _f8->init(heap, mActor);
    }
    return ok & (_100.sub_7100D78564(heap) & _1b8.sub_7100D78564(heap));
}

// NON_MATCHING: only the final `_274 = *mForceSetDropPos_a` differs: the original copies the vector with the z store
// first and one 8 byte store for x / y (a struct copy of `&_274`), ours copies x, y, z one by one
void LumberjackFallenTree::enter_(ksys::act::ai::InlineParamPack* params) {
    _280 = sead::Vector3f::ey;
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        sead::BoundBox3f aabb;
        body->getAabbInLocal(&aabb);
        const f32 height = aabb.getHalfSizeY() + aabb.getHalfSizeY();
        const f32 check_height = height * static_cast<f32>(static_cast<u8>(*mIsCheckHeight_s));
        _270 = height;
        _28c = check_height;
    }
    _100.x(1, 0, *mNoiseLevel_s);
    _100._88 = sead::Vector3f(0, _270, 0);
    _1b8.x(1, 0, *mNoiseLevel_s);

    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(actor);
    if (weapon && weapon->m185()) {
        sub_7100486000(false);
        sub_71004860DC();
    } else if (actor->getMapObject()) {
        sub_7100486000(false);
        sub_71004860DC();
    } else {
        sub_7100486000(true);
        sub_7100486258();
    }
    _274 = *mForceSetDropPos_a;
}

// NON_MATCHING: the order of the loads of the offset / direction vectors (the original loads the offset pointer first
// and the direction's z after the first product)
void LumberjackFallenTree::sub_7100486000(bool standing) {
    if (!_f8)
        return;
    auto* actor = mActor;
    bool flag;
    if (standing) {
        _f8->sub_71006E2440(false);
        const f32 scale = _f8->sub_71006E24D4();
        const auto& offset = *mTerrorOffsetPos4Falling_s;
        const auto& direction = *mMoveDirection_a;
        const sead::Vector3f position(direction.x * (scale + offset.x), offset.y,
                                      direction.z * (scale + offset.z));
        _f8->sub_71006E24B0(position);
        _290 = 0;
        flag = true;
    } else {
        _f8->sub_71006E24B0(sead::Vector3f::zero);
        _f8->sub_71006E2440(true);
        flag = false;
    }
    _295 = flag;
    if (ksys::act::hasTag(actor, 0x80e91296))
        _f8->sub_71006E2024();
    else
        _f8->sub_71006E1FD0();
}

bool LumberjackFallenTree::hasUpdateForPreDeleteCb() {
    return true;
}

bool LumberjackFallenTree::updateForPreDelete() {
    bool ok = true;
    if (_f8)
        ok = _f8->m5() & (_100.sub_7100D786D8() & _1b8.sub_7100D786D8());
    return ok;
}

void LumberjackFallenTree::sub_71004860DC() {
    _294 = true;
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr)) {
            manager->removeDamageCallback(&_38);
            manager->removeDamageCallback(&_68);
        }
    }
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr))
            manager->addDamageCallback(4, &_68);
    }
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.set(0x2000);
    changeChild("丸太化");
}

void LumberjackFallenTree::leave_() {
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr)) {
            manager->removeDamageCallback(&_38);
            manager->removeDamageCallback(&_68);
        }
    }
    if (_f8)
        _f8->sub_71006E2420();
}

void LumberjackFallenTree::loadParams_() {
    getStaticParam(&mToLogAngVel_s, "ToLogAngVel");
    getStaticParam(&mMaxCheckAng_s, "MaxCheckAng");
    getStaticParam(&mCheckDis_s, "CheckDis");
    getStaticParam(&mCheckHeightRate_s, "CheckHeightRate");
    getStaticParam(&mTerrorRegistAng_s, "TerrorRegistAng");
    getStaticParam(&mTerrorUnregistTimelimit_s, "TerrorUnregistTimelimit");
    getStaticParam(&mNoiseLevel_s, "NoiseLevel");
    getStaticParam(&mIsCheckHeight_s, "IsCheckHeight");
    getStaticParam(&mTerrorOffsetPos4Falling_s, "TerrorOffsetPos4Falling");
    getAITreeVariable(&mLumberjackType_a, "LumberjackType");
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
    getAITreeVariable(&mMoveDirection_a, "MoveDirection");
}

void LumberjackFallenTree::sub_7100486258() {
    _294 = false;
    if (auto* damage = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage)) {
            manager->removeDamageCallback(&_38);
            manager->removeDamageCallback(&_68);
        }
    }
    if (auto* damage = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage))
            manager->addDamageCallback(4, &_38);
    }
    _296 = 1;
    auto* xlink = mActor->getXLink();
    auto* user = xlink ? xlink->_50 : nullptr;
    if (user) {
        user->searchAndEmit("felling");
        mFellingHandle = user->searchAndEmit("felling_TreeFall");
    } else {
        _296 = 0;
    }
    if (auto* current_xlink = mActor->getXLink())
        current_xlink->_cc.set(0x2000);
    changeChild("通常");
}

}  // namespace uking::ai
