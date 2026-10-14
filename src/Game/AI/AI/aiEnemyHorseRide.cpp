#include "Game/AI/AI/aiEnemyHorseRide.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Utils/Thread/Message.h"

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

EnemyHorseRide::EnemyHorseRide(const InitArg& arg) : NonPlayerHorseRide(arg) {}

EnemyHorseRide::~EnemyHorseRide() = default;

bool EnemyHorseRide::init_(sead::Heap* heap) {
    return NonPlayerHorseRide::init_(heap);
}

void EnemyHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    NonPlayerHorseRide::enter_(params);
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
    NonPlayerHorseRide::leave_();
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
    NonPlayerHorseRide::loadParams_();
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
    NonPlayerHorseRide::m34();
}

}  // namespace uking::ai
