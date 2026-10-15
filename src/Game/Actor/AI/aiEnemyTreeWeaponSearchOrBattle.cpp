#include "Game/Actor/AI/aiEnemyTreeWeaponSearchOrBattle.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <limits>
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

// NON_MATCHING: vector copies, loop branches and registers for the three RTTI tests differ.
bool EnemyTreeWeaponSearchOrBattle::sub_71003C1E20() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness || !sead::DynamicCast<act::Enemy>(actor))
        return false;
    auto* enemy = static_cast<act::Enemy*>(actor);
    _50.reset();
    const auto origin = mActor->getMtx().getTranslation();
    const f32 target_distance = sub_71005D8F28(mActor) ?
        (sub_71005D9330(mActor) - origin).length() : std::numeric_limits<f32>::infinity();
    auto* nav = mActor->m45();
    const f32 radius = nav ? nav->_2a8 * nav->_2ac : 0.1f;
    const f32 weapon_range = sub_71007320F0(mActor, *mWeaponIdx_s);
    Unk_7102451790 filter;
    if (awareness->_260[0]) {
        const bool allow_tagged_tree = enemy->_f54.isOn(4);
        const f32 reach_radius = (radius > weapon_range ? radius : weapon_range) + 2.0f;
        while (awareness->_260[0]) {
            auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_260[0]->_8, &filter);
            if (!entry)
                break;
            auto& link = entry->_0.mLink;
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (!link.hasProc())
                continue;
            const auto position = entry->_58.getTranslation();
            if (!sub_710072CB78(mActor, position, nullptr, reach_radius, -1))
                continue;
            if ((position - origin).length() > target_distance)
                continue;
            const bool is_weapon = link.mId != ksys::act::BaseProcLink::cInvalidId &&
                sead::DynamicCast<act::Weapon>(link.getProc());
            if (is_weapon) {
                auto* candidate = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
                auto* weapon = sead::DynamicCast<act::Weapon>(candidate);
                if (!weapon ||
                    !(enemy->_f54.getDirect() & (1u << (u32(weapon->_cf0) & 31))) ||
                    weapon->hasParentActor_() ||
                    weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
                    continue;
                _50 = link;
                _60 = true;
                _61 = false;
            } else {
                if (!allow_tagged_tree && accessor.hasTag(0xe024e81fu))
                    continue;
                _50 = link;
                _60 = false;
                _61 = true;
                _68.sub_710070DCC0(&_50, true);
            }
            break;
        }
    }
    return _50.hasProc();
}

void EnemyTreeWeaponSearchOrBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mNoSearchDist_s, "NoSearchDist");
}

}  // namespace uking::ai
