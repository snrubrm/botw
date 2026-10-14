#include "Game/Actor/AI/aiEnemyTreeWeaponSearchOrBattle.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyTreeWeaponSearchOrBattle::EnemyTreeWeaponSearchOrBattle(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

EnemyTreeWeaponSearchOrBattle::~EnemyTreeWeaponSearchOrBattle() = default;

bool EnemyTreeWeaponSearchOrBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyTreeWeaponSearchOrBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->m45() || !sead::DynamicCast<act::Enemy>(mActor)) {
        setFailed();
        return;
    }

    _60 = false;
    _61 = false;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const auto& target = sub_71005D9330(mActor);
    if (!(sead::Vector2f(target.x - pos.x, target.z - pos.z).length() > *mNoSearchDist_s) ||
        !sub_71003C1E20()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("戦闘", &pack);
    } else if (_60) {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(_50, "TargetWeapon", -1);
        changeChild("木武器発見", &pack);
    } else if (_61) {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(_50, "TargetActor", -1);
        changeChild("木発見", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("戦闘", &pack);
    }
}

void EnemyTreeWeaponSearchOrBattle::leave_() {
    if (_50.hasProc())
        _80.sub_710070DCC0(&_50, true);
    sub_71005DB3EC(mActor);
}

void EnemyTreeWeaponSearchOrBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mNoSearchDist_s, "NoSearchDist");
}

}  // namespace uking::ai
