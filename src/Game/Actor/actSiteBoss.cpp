#include "Game/Actor/actSiteBoss.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::act {

Unk_71025ae680* SiteBoss::m178(sead::Heap* heap) {
    return new (heap) Unk_710244fee8(this);
}

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

// NON_MATCHING: the original loads the vtable pointer separately in each branch (ours hoists the common load)
void SiteBoss::sub_71002CFD04(bool on) {
    if (auto* x = _1250) {
        if (auto* y = x->_18) {
            if (on)
                y->m0();
            else
                y->m1();
        }
    }
}

void SiteBoss::initMaybe() {
    sub_71002CFD04(false);
    if (auto* body = findPhysicsBodyByName(sub_71007A250C()->cstr(), "BgSensor")) {
        if (!body->isAddedToWorld()) {
            body->addToWorld();
            body->setContactAll();
            body->setFlag1000000();
        }
    }
    Enemy::initMaybe();
}

void SiteBoss::sub_71002D223C() {
    if (_1558.isOnBit(4))
        _2338 = ksys::eft::searchAndEmitELink(this, "Elec_Sword");
    if (_1558.isOnBit(5))
        _2348 = ksys::eft::searchAndEmitELink(this, "Elec_Shield");
}

void SiteBoss::sub_71002D1FD4() {
    if (_1558.isOnBit(5))
        _2348.fade();
}

void SiteBoss::sub_71002D22B8() {
    _2358.fade();
}

void SiteBoss::sub_71002D23F0() {
    if (_2368.isActive())
        return;
    ksys::eft::sub_710105DDB8(this, "Elec_Sword", &_2368);
}

void SiteBoss::sub_71002D2420() {
    _2368.fade();
}

// NON_MATCHING: the original does not shrink-wrap the prologue and keeps `this` in x19 from the entry
void SiteBoss::sub_71002D2390() {
    if (_2358.isActive())
        return;
    _2358 = ksys::eft::searchAndEmitELink(this, "LightShield");
}

void SiteBoss::sub_71002D2A5C(s32 bit, bool on) {
    if (mASList)
        mASList->x_2(0x42, bit, on, false);
}

void SiteBoss::sub_71002D2A1C(const char* name) {
    if (mASList)
        mASList->goLimpFromHeadShotMaybe(0x2f, name, 0);
}

void SiteBoss::m117(ksys::act::Unk117* arg) {
    forwardX17ToParts(this, arg);
}

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

// NON_MATCHING: same instructions, scheduled differently (the original computes `fire & 1` before the
// select for water; the sum order of the four flags is not recoverable)
s32 SiteBoss::getMaxLife() {
    const u32 life = Enemy::getMaxLife();
    const u32 half = life / 2;
    const bool wind = ksys::gdt::getFlag_Die_PGanonWind(false);
    const bool water = ksys::gdt::getFlag_Die_PGanonWater(false);
    const bool fire = ksys::gdt::getFlag_Die_PGanonFire(false);
    const bool electric = ksys::gdt::getFlag_Die_PGanonElectric(false);
    s32 num_ganons;
    if ((_1534 & ~3) == 4) {
        num_ganons = 3;
    } else if ((_1534 & ~3) == 8) {
        num_ganons = 4;
    } else {
        num_ganons = 0;
        if (wind)
            ++num_ganons;
        if (water)
            ++num_ganons;
        num_ganons += fire;
        num_ganons += electric;
    }
    return life + num_ganons * half;
}

void SiteBoss::x_6(bool on) {
    _1558.change(0x20, on);
    if (auto* chemical = sub_71011D8A54("ShieldChemical")) {
        chemical->sub_7100D90F60(!on);
        chemical->sub_7100D91098(false);
    }
}

void SiteBoss::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
}

bool SiteBoss::isGuard() {
    if ((_14c8._30.getDirect() & 0x226) == 2 && !isSlowTimeMaybe())
        return true;
    return Enemy::isGuard();
}

bool SiteBoss::isGuardJust() {
    if ((_14c8._30.getDirect() & 0x226) == 2 && mActorFlags2.isOn(ActorFlag2::_10000000))
        return true;
    return PlayerOrEnemy::isGuardJust();
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

// 0x71002d1f2c (lane1 s43): always false.
bool sub_71002D1F2C(uking::act::SiteBoss* boss) {
    return false;
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
