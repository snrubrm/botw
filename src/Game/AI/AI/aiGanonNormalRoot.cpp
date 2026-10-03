#include "Game/AI/AI/aiGanonNormalRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/AI/aiAwarenessFilters.h"

namespace uking::ai {

GanonNormalRoot::GanonNormalRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonNormalRoot::~GanonNormalRoot() = default;

bool GanonNormalRoot::init_(sead::Heap* heap) {
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "Enemy_Ganon_Lsword_Weapon", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &_38[0], nullptr, nullptr, 1);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "Enemy_Ganon_Sword_Weapon_FL", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &_38[1], nullptr, nullptr, 1);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "Enemy_Ganon_Sword_Weapon_MR", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &_38[2], nullptr, nullptr, 1);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "Enemy_Ganon_Sword_Weapon_FR", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &_38[3], nullptr, nullptr, 1);
    return true;
}

// NON_MATCHING: our clang computes the Enemy cast once for both branches (csel + one store path);
// the original keeps a separate cast/store per branch
void GanonNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003ED718(0);
    sub_71003ED718(1);
    sub_71003ED718(2);
    sub_71003ED718(3);
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();

    if (sub_71003ED9B0()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e90 = 4;
        changeChild("発見");
    } else {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e90 = 1;
        changeChild("未発見");
    }
}

void GanonNormalRoot::calc_() {
    if (sub_71005DB7E4(mActor, 2))
        sub_71005DB5C0(mActor, 2);
    if (sub_71005DB7E4(mActor, 3))
        sub_71005DB5C0(mActor, 3);

    if (isCurrentChild("未発見") && sub_71003ED9B0()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e90 = 4;
        changeChild("発見");
    }
}

void GanonNormalRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonNormalRoot::loadParams_() {}

// NON_MATCHING: the original materialises &entry->_58 before the getHomePos call (register/scheduling only)
bool GanonNormalRoot::sub_71003ED9B0() {
    auto* target = sub_71005D9050(mActor);
    if (target && target->hasProc())
        return true;

    auto* awareness = mActor->getAwareness();
    if (!awareness || awareness->_300 == 0)
        return false;

    Unk_7102451678 filter;
    auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
    if (!entry || entry->_a0 == 0)
        return false;

    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    sub_71005D8DE8(mActor, entry->_0.mLink, &entry->_58, nullptr);
    return true;
}

}  // namespace uking::ai
