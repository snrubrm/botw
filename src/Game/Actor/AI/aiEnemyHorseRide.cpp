#include "Game/Actor/AI/aiEnemyHorseRide.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseRider.h"

namespace uking::ai {

void Unk_71023e8328::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (*a5 != -1 || *a1 >= 1) {
        auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6);
        if (info)
            info->mFlags |= 0x20000;
    }
    if (*a5 != -1 && *a5 < 22)
        *a5 = 22;
}

void Unk_71023e8360::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (*a5 != -1 || *a1 >= 1) {
        auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6);
        if (info)
            info->mFlags |= 0x20000;
    }
    switch (*a5) {
    case 7:
    case 8:
        *a5 = 22;
        break;
    case 6:
        *a5 = -1;
        break;
    case 19:
        *a5 = 22;
        break;
    default:
        break;
    }
}

void Unk_71023e8398::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (*a5 != -1 || *a1 >= 1) {
        auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6);
        if (info)
            info->mFlags |= 0x20000;
    }
    if (*a5 != -1 || *a1 >= 1)
        *a5 = 22;
}

EnemyHorseRide::EnemyHorseRide(const InitArg& arg) : RideHorseNonPlayer(arg) {}

EnemyHorseRide::~EnemyHorseRide() = default;

bool EnemyHorseRide::init_(sead::Heap* heap) {
    return RideHorseNonPlayer::init_(heap);
}

void EnemyHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    setUpRiderAnimation();
    auto* actor = mActor;
    RideHorseNonPlayer::enter_(params);

    if (auto* damage_mgr = actor->getDamageMgr()) {
        damage_mgr->addDamageCallback(4, &_f8);
        damage_mgr->addDamageCallback(1, &_120);
        damage_mgr->addDamageCallback(5, &_148);
    }

    sub_71005DDA44(actor);

    if (auto* nav = actor->m45()) {
        if (auto* ride_info = actor->getPlayerRideInfo()) {
            auto* horse = sead::DynamicCast<ksys::act::Actor>(ride_info->_18.getProc(nullptr, ride_info->mActor));
            if (horse) {
                if (auto* horse_nav = horse->m45()) {
                    sead::Vector3f horse_pos;
                    horse->getMtx().getTranslation(horse_pos);
                    sead::Matrix34f inv;
                    sead::Matrix34CalcCommon<f32>::inverse(inv, mActor->getMtx());
                    sead::Vector3f pos;
                    pos.setMul(inv, horse_pos);
                    if (!pos.isNan()) {
                        auto lock = sead::makeScopedLock(nav->_1e0);
                        nav->_284 = pos;
                    }
                    nav->sub_7100F7D1CC(horse_nav);
                }
            }
        }
    }

    if (auto* bone_control = sub_71005DB0EC(actor)) {
        const auto* rider = actor->getParam()->getRes().mGParamList->getHorseRider();
        s32 idx = bone_control->sub_7100D89124(rider->mSpineNode.ref());
        if (idx >= 0) {
            bone_control->sub_7100D89AC4(sead::Mathf::deg2rad(rider->mRotLimit.ref()), idx);
            bone_control->sub_7100D89A20(sead::Mathf::deg2rad(rider->mRotLimit.ref()), idx);
        }
    }
}

// Makes the root and spine bones partial bones of the upper / lower body AS slots and starts HorseWait on the
// lower body slot (once).
// NON_MATCHING: the original passes a second argument (0) to ASList::sub_710115EA64 (see calc_), and the
// HorseWait string object sits at sp instead of sp + 8.
void EnemyHorseRide::setUpRiderAnimation() {
    if (_f0)
        return;
    auto* actor = mActor;
    if (!actor->getModel())
        return;
    auto* rider = sead::DynamicCast<Unk_7102357ab0>(actor->getPlayerRideInfo());
    if (!rider)
        return;
    const auto root = actor->getModel()->searchBone(rider->getRootNodeName());
    const auto spine = actor->getModel()->searchBone(rider->getSpineNodeName());
    if (!root.isValid() || !spine.isValid())
        return;

    {
        auto* as_list = actor->getASList();
        const s32 slot = *mUpperBodyASSlot_s;
        as_list->sub_710115C9E0(slot);
        as_list->mSlots[slot].sub_7101165008(root, 3, true);
        as_list->mSlots[slot].sub_7101165008(spine, 0, true);
        as_list->mSlots[slot].sub_7101164E38(false);
    }
    {
        auto* as_list = actor->getASList();
        const s32 slot = *mLowerBodyASSlot_s;
        as_list->sub_710115C9E0(slot);
        as_list->mSlots[slot].sub_7101165008(root, 0, true);
        as_list->mSlots[slot].sub_7101165008(spine, 3, true);
        as_list->mSlots[slot].sub_7101164E38(false);
    }
    if (auto* as_list = actor->getASList()) {
        as_list->sub_710115EA64(0);
        as_list->startAnimationMaybe(-1.0f, -1.0f, "HorseWait", *mLowerBodyASSlot_s, 0, true);
    }
    _f0 = true;
}

// NON_MATCHING: the original passes a second argument (0) to ASList::sub_710115EA64, which the callee does not read;
// the declared signature has one parameter.
void EnemyHorseRide::calc_() {
    // Stops riding: m34, releases the upper body AS slot and changes to 復帰.
    const auto stopRiding = [this] {
        m34();
        if (_f0) {
            auto* owner = mActor;
            if (owner->getModel()) {
                owner->getASList()->sub_710115B01C(*mLowerBodyASSlot_s, 0, true);
                owner->getASList()->sub_710115C11C();
                _f0 = false;
            }
        }
    };

    if (isCurrentChild("乗る")) {
        auto* actor = mActor;
        if (auto* ride_info = actor->getPlayerRideInfo()) {
            if (!ride_info->_18.hasProc()) {
                stopRiding();
                changeChild("復帰");
                return;
            }
            ksys::act::ActorLinkConstDataAccess horse;
            ksys::act::acquireActor(&ride_info->_18, &horse);
            auto* options = horse.getHorseOptions();
            if (!options ||
                int(act::Unk_7100e8b2b8::Unk8(options->act::Unk_7100e8b2b8::_8.load() & 0xff)) == 0 ||
                horse.getLife() < 1) {
                stopRiding();
                if (auto* damage_mgr = actor->getDamageMgr()) {
                    damage_mgr->removeDamageCallback(&_f8);
                    damage_mgr->removeDamageCallback(&_120);
                    damage_mgr->removeDamageCallback(&_148);
                }
                changeChild("復帰");
            } else if (auto* as_list = actor->getASList()) {
                as_list->sub_710115EA64(int(horse.sub_7100D144EC()));
            }
            return;
        }
    } else {
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed())
            return;
    }
    setFailed();
}

void EnemyHorseRide::leave_() {
    RideHorseNonPlayer::leave_();
    auto* actor = mActor;
    if (auto* damage_mgr = actor->getDamageMgr()) {
        damage_mgr->removeDamageCallback(&_f8);
        damage_mgr->removeDamageCallback(&_120);
        damage_mgr->removeDamageCallback(&_148);
    }
    if (_f0) {
        auto* owner = mActor;
        if (owner->getModel()) {
            owner->getASList()->sub_710115B01C(*mLowerBodyASSlot_s, 0, true);
            owner->getASList()->sub_710115C11C();
            _f0 = false;
        }
    }
    sub_71005DDA94(actor);
    if (auto* nav = actor->m45()) {
        if (!sead::Vector3f::zero.isNan()) {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav->_284 = sead::Vector3f::zero;
        }
        nav->sub_7100F7D2C8();
    }
    if (auto* bone_control = sub_71005DB0EC(actor)) {
        bone_control->sub_7100D89FD8();
        bone_control->sub_7100D89F60();
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.resetBit(13);
}

void EnemyHorseRide::loadParams_() {
    RideHorseNonPlayer::loadParams_();
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
}

bool EnemyHorseRide::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003)
        m34();
    return false;
}

void EnemyHorseRide::m34() {
    if (mActor->isDelete())
        return;
    RideHorseNonPlayer::m34();
}

}  // namespace uking::ai
