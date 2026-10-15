#include "Game/Actor/AI/aiEnemyTreeWeaponSearchOrBattle.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
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

// NON_MATCHING: temporary pack/argument stack slots and branch layout differ.
void EnemyTreeWeaponSearchOrBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinishedOrFailed()) {
        const bool searching = isCurrentChild("木武器発見") || isCurrentChild("木発見");
        const bool finished = child->isFinished();
        if (!searching) {
            if (finished)
                setFinished();
            else
                setFailed();
        } else if (finished) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("戦闘", &pack);
        } else {
            _60 = false;
            _61 = false;
            const auto position = mActor->getMtx().getTranslation();
            const auto& target = sub_71005D9330(mActor);
            const f32 distance = sead::Vector2f(target.x - position.x, target.z - position.z).length();
            if (!(distance > *mNoSearchDist_s) || !sub_71003C1E20()) {
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
            }
        }
    } else if (child->isChangeable() && isCurrentChild("戦闘")) {
        const auto position = mActor->getMtx().getTranslation();
        const auto& target = sub_71005D9330(mActor);
        const f32 distance = sead::Vector2f(target.x - position.x, target.z - position.z).length();
        if (distance > *mNoSearchDist_s && sub_71003C1E20()) {
            if (_60) {
                ksys::act::ai::InlineParamPack pack;
                pack.addActor(_50, "TargetWeapon", -1);
                changeChild("木武器発見", &pack);
            } else if (_61) {
                ksys::act::ai::InlineParamPack pack;
                pack.addActor(_50, "TargetActor", -1);
                changeChild("木発見", &pack);
            }
        }
    }
    if (isCurrentChild("戦闘")) {
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    } else if (_50.hasProcInCalcState() && sub_71005DBB60(mActor, *mWeaponIdx_s) == -1) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_50, &accessor);
        const auto position = accessor.getActorMtx().getTranslation();
        sub_71005DB1D8(mActor, position);
    } else if (sub_71005D8F28(mActor)) {
        auto* actor = mActor;
        sub_71005DB1D8(actor, sub_71005D9330(actor));
    }
}

void EnemyTreeWeaponSearchOrBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mNoSearchDist_s, "NoSearchDist");
}

}  // namespace uking::ai
