#include "Game/AI/AI/aiLargeEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

LargeEnemyFindPlayer::LargeEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

LargeEnemyFindPlayer::~LargeEnemyFindPlayer() = default;

bool LargeEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void LargeEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void LargeEnemyFindPlayer::calc_() {
    EnemyBaseFindPlayer::calc_();
}

void LargeEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void LargeEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

bool LargeEnemyFindPlayer::m35() {
    if (!sub_710072E1B4(mActor, false))
        return false;
    return EnemyBaseFindPlayer::m35();
}

bool LargeEnemyFindPlayer::m36(bool b) {
    const sead::Vector3f& target = sub_71005D9330(mActor);
    auto* actor = mActor;
    if (!actor)
        return false;

    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    if (b) {
        f32 range = sub_71007320F0(actor, *mWeaponIdx_s);
        if (auto* nav = actor->m45()) {
            const f32 nav_range = nav->_2a8 * nav->_2ac;
            if (nav_range > range)
                range = nav_range;
        }
        sead::Vector3f out;
        if (sub_710072F7AC(actor, pos, target, &out, -1, range))
            return true;
    } else {
        sead::Vector3f out;
        if (sub_710072F7D0(actor, pos, target, &out, -1))
            return true;
    }
    return false;
}

bool LargeEnemyFindPlayer::m37() {
    const sead::Vector3f& target = sub_71005D98D8(mActor);
    auto* actor = mActor;
    if (!actor)
        return false;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    sead::Vector3f out;
    return sub_710072F7D0(actor, pos, target, &out, -1);
}

}  // namespace uking::ai
