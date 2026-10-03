#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::act {

namespace {
void forwardX17ToParts(ksys::act::Actor* actor, ksys::act::Unk117* arg) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return;
    auto* enemy = static_cast<Enemy*>(actor);
    for (auto* part : enemy->_1128.mList) {
        if (auto* part_actor =
                sead::DynamicCast<ksys::act::Actor>(part->mLink.getProc(nullptr, nullptr)))
            part_actor->x_17(arg);
    }
}
}  // namespace

void SiteBoss::m117(ksys::act::Unk117* arg) {
    forwardX17ToParts(this, arg);
}

// NON_MATCHING: member types incomplete
SiteBoss::~SiteBoss() = default;

void SiteBoss::m63() {
    _14c8._30.makeAllZero();
    _1558.makeAllZero();
    _1538 = getMaxLife();
    getHomePos(&_2318);
    _1554 = 1000.0f;
    _1544 = 4;
    Enemy::m63();
}

void SiteBoss::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
}

bool SiteBoss::isGuard() {
    if ((_14c8._30.getDirect() & 0x226) == 2 && !isSlowTimeMaybe())
        return true;
    return Enemy::isGuard();
}

void SiteBoss::x_1(bool a1, bool a2, bool skip_flag) {
    if (a1)
        _1558.set(3);
    else
        _1558.reset(1);
    sub_71002D1B18(a1);
    if (!skip_flag) {
        if (a2)
            _14c8._30.set(0x10);
        else
            _14c8._30.reset(0x10);
    }
}

void SiteBoss::x_5(bool on) {
    _1558.change(0x10, on);
    sub_71002D1B18(on);
}

bool SiteBoss::sub_71002D33D0(f32 value) const {
    return _1554 < value;
}

void SiteBoss::x_2(Enemy* boss, ksys::act::Actor* sender) {
    if (!boss)
        return;
    for (auto* part : boss->_1128.mList) {
        auto& link = part->mLink;
        if (!link.hasProc())
            continue;
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(&link, &acc);
        sender->sendMessage(*acc.getMessageTransceiverId(), ksys::MessageType(0x800002f), nullptr, true);
    }
}

void SiteBoss::sub_71002D3498(Enemy* boss, ksys::act::Actor* sender) {
    if (!boss)
        return;
    for (auto* part : boss->_1128.mList) {
        auto& link = part->mLink;
        if (!link.hasProc())
            continue;
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(&link, &acc);
        if (acc.isStateCalc())
            sender->sendMessage(*acc.getMessageTransceiverId(), ksys::MessageType(0x8000030), nullptr, true);
    }
}

void SiteBoss::sub_71002D3624(SiteBoss* boss, const sead::SafeString& part) {
    if (!boss)
        return;
    if (!boss->_1128.getActorPartsActor(part).hasProc())
        return;
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(&boss->_1128.getActorPartsActor(part), &acc);
    boss->sendMessage(*acc.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr, true);
}

bool SiteBoss::sub_71002D3804(ksys::act::Actor* actor, const sead::SafeString& part) {
    auto* boss = sead::DynamicCast<SiteBoss>(actor);
    if (!boss)
        return false;
    if (!boss->_1128.getActorPartsActor(part).hasProc())
        return false;
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(&boss->_1128.getActorPartsActor(part), &acc);
    return acc.isStateCalc();
}

void SiteBoss::sub_71002D38EC(const sead::SafeString& name) {
    _2328 = name;
}

}  // namespace uking::act

int getNumberOfDeadBlights() {
    int count = 0;
    if (ksys::gdt::getFlag_Die_PGanonWind())
        ++count;
    if (ksys::gdt::getFlag_Die_PGanonWater())
        ++count;
    if (ksys::gdt::getFlag_Die_PGanonFire())
        ++count;
    if (ksys::gdt::getFlag_Die_PGanonElectric())
        ++count;
    return count;
}

int getNumberOfClearedRemains() {
    int count = 0;
    if (ksys::gdt::getFlag_Clear_RemainsWind())
        ++count;
    if (ksys::gdt::getFlag_Clear_RemainsWater())
        ++count;
    if (ksys::gdt::getFlag_Clear_RemainsFire())
        ++count;
    if (ksys::gdt::getFlag_Clear_RemainsElectric())
        ++count;
    return count;
}
