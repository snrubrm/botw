#include "Game/AI/AI/aiEnemyHorseRide.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

void Unk_71023e8328::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1 || *a1 >= 1) {
        auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(
            reinterpret_cast<dmg::DamageCallbackInfo*>(a6));
        if (info)
            info->mFlags |= 0x20000;
    }
    if (*a5 != -1 && *a5 < 22)
        *a5 = 22;
}

void Unk_71023e8360::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1 || *a1 >= 1) {
        auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(
            reinterpret_cast<dmg::DamageCallbackInfo*>(a6));
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

void Unk_71023e8398::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1 || *a1 >= 1) {
        auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(
            reinterpret_cast<dmg::DamageCallbackInfo*>(a6));
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

void EnemyHorseRide::leave_() {
    NonPlayerHorseRide::leave_();
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
