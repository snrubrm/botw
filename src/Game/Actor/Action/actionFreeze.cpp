#include "Game/Actor/Action/actionFreeze.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include <prim/seadStringUtil.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"

namespace uking::action {

Freeze::Freeze(const InitArg& arg) : StopBase(arg) {}

Freeze::~Freeze() = default;

bool Freeze::init_(sead::Heap* heap) {
    _68.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    setupCRBOffsetUnit(_68);
    return true;
}

void Freeze::enter_(ksys::act::ai::InlineParamPack* params) {
    _70 = false;
    StopBase::enter_(params);
    auto* actor = mActor;
    if (auto* as_list = actor->getASList()) {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD798(actor, 40, &query, 0, 0)) {
            s32 idx = 0;
            if (sead::StringUtil::tryParseS32(&idx, query.name,
                                              sead::StringUtil::CardinalNumber::BaseAuto)) {
                playerOrEnemyDropWeapon(mActor, &sead::Vector3f::zero, idx, false, false, nullptr,
                                        false);
            }
        }
        as_list->sub_710115F228(0.0f);
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            if (enemy->_e84.isOnBit(20) && !as_list->_14.isValid()) {
                as_list->sub_710115BAF8(mTransBoneKey_s);
                _70 = true;
            }
        }
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(0x200000);
    if (auto* physics = mActor->getPhysics())
        physics->getFlags().set(ksys::phys::InstanceSet::Flag::_20000);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F6321C(true);
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.set(0x800);
    if (auto* bone_control = mActor->getBoneControl())
        bone_control->sub_7100D82FB4();
    _30 = true;
    if (*mIsChangeInAir_s)
        _34.changeMotionType(mActor->getCharacterController(), ksys::act::MotionType::_1);
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_68._0))
        unit->_8.sub_attach(mActor);
    sub_71005D9974(mActor, 2, true);
}

void Freeze::leave_() {
    StopBase::leave_();
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (*mIsKeepFreeze_a) {
        *mIsKeepFreeze_a = false;
        if (_70 && as_list)
            as_list->sub_710115CD0C();
    } else {
        if (auto* poe = sead::DynamicCast<ksys::act::PlayerOrEnemy>(actor))
            poe->m149(3);
        if (as_list) {
            as_list->sub_710115F228(1.0f);
            if (_70)
                as_list->sub_710115CD0C();
        }
        if (auto* physics = mActor->getPhysics())
            physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
        if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
            if (dynamic_actor->_868)
                dynamic_actor->_868->sub_71006EE018();
        }
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F6321C(false);
        if (auto* xlink = mActor->getXLink())
            xlink->_cc.reset(0x800);
        if (auto* bone_control = mActor->getBoneControl())
            bone_control->sub_7100D82FC4();
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e84.reset(0x200000);
    }
    if (*mIsChangeInAir_s)
        _34.resetMotionType(mActor->getCharacterController());
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_68._0))
        unit->_8.sub_detach(mActor);
    sub_71005D9974(mActor, 2, false);
}

void Freeze::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mIsChangeInAir_s, "IsChangeInAir");
    getStaticParam(&mTransBoneKey_s, "TransBoneKey");
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void Freeze::calc_() {
    StopBase::calc_();
    if (_30) {
        sub_7100738428(mActor, 0.0f);
        sub_7100738AA8(mActor, 0.0f);
        _30 = false;
    } else if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (dynamic_actor->_868)
            dynamic_actor->_868->sub_71006EDFBC();
    }
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (actor && !actor->m151(3))
        setFinished();
}

}  // namespace uking::action
