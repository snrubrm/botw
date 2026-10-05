#include "Game/AI/AI/aiRapidAttackAllowSelect.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

s32 sub_71006DEF64(const ksys::act::ActorConstDataAccess* accessor);

namespace uking::ai {

RapidAttackAllowSelect::RapidAttackAllowSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RapidAttackAllowSelect::~RapidAttackAllowSelect() = default;

bool RapidAttackAllowSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the final damage conversion occurs after the life query.
void RapidAttackAllowSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* target = sub_71005D9050(mActor);
    if (!target) {
        changeChild("連打許可", params);
        return;
    }

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(target, &accessor);
    if (accessor.hasProc()) {
        s32 attack = static_cast<ksys::act::PlayerOrEnemy*>(mActor)->getEnemyAtkPower();
        if (attack < 2)
            attack = 1;
        if (auto* weapon = sub_71005D83E8(mActor, *mWeaponIdx_s))
            attack = weapon->getEffectiveAttackPower(mActor);

        s32 damage = f32(attack) - f32(sub_71006DEF64(&accessor));
        if (damage < 2)
            damage = 1;
        if (!(f32(accessor.getLife()) > f32(*mAttackNum_s) * f32(damage))) {
            changeChild("連打不許可", params);
            return;
        }
    }
    changeChild("連打許可", params);
}

void RapidAttackAllowSelect::calc_() {}

bool RapidAttackAllowSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool RapidAttackAllowSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void RapidAttackAllowSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RapidAttackAllowSelect::loadParams_() {
    getStaticParam(&mAttackNum_s, "AttackNum");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
