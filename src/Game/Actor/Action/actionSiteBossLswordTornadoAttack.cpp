#include "Game/Actor/Action/actionSiteBossLswordTornadoAttack.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace uking::action {

SiteBossLswordTornadoAttack::SiteBossLswordTornadoAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordTornadoAttack::~SiteBossLswordTornadoAttack() = default;

bool SiteBossLswordTornadoAttack::init_(sead::Heap* heap) {
    _58.sub_710073E730(heap, 2, mActor);
    return true;
}

void SiteBossLswordTornadoAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _4c.reset(*mEndTime_s);
    _58._8 = *mVacuumAcc_s;
    _58._c = *mVacuumMaxSpeed_s;
    _58._10 = *mVacuumBaseWeight_s;
    _48 = false;
    mFlags.reset(Flag::Changeable);
}

void SiteBossLswordTornadoAttack::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor("DrawingFlame").hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor("DrawingFlame"), &accessor);
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }
    sub_7100739918(mActor);
}

void SiteBossLswordTornadoAttack::loadParams_() {
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mVacuumAcc_s, "VacuumAcc");
    getStaticParam(&mVacuumMaxSpeed_s, "VacuumMaxSpeed");
    getStaticParam(&mVacuumAngle_s, "VacuumAngle");
    getStaticParam(&mVacuumBaseWeight_s, "VacuumBaseWeight");
}

void SiteBossLswordTornadoAttack::calc_() {
    _4c.update();
    sub_71007398E4(mActor, true);
    _58._28 = 0;
    if (mActor->getASList()->x(59, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        _48 = true;
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            if (enemy->getActorPartsActor("DrawingFlame").hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor("DrawingFlame"), &accessor);
                accessor.setProperties(mActor->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
            }
        }
    }

    if (_48) {
        ksys::world::Manager::instance()->getWeatherMgrUnchecked()->_33c = 4;
        sub_710025FEF0();
    }

    if (_4c.value <= sead::Mathf::epsilon())
        setFinished();
}

// NON_MATCHING: target count/id registers and iterator branch layout differ.
void SiteBossLswordTornadoAttack::sub_710025FEF0() {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return;
    Unk_7102451538 filter;
    auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
    u32 count = 0;
    u32 last_id = 0;
    while (entry && count < 2) {
        auto& link = entry->_0.mLink;
        if (link.hasProcInCalcState()) {
            const u32 id = link.getId();
            if (id != last_id) {
                sub_71002601D4(1.0f, &link);
                ++count;
                last_id = id;
            }
        }
        entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
    }
    while (entry) {
        entry->_0.mLink.hasProcInCalcState();
        entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
    }
}

// NON_MATCHING: the target position copy (stored as ints) and the 0x23bcf28 rate table addressing.
void SiteBossLswordTornadoAttack::sub_71002601D4(f32 rate, ksys::act::BaseProcLink* link) {
    static const f32 sNearRates[] = {0.3f, 0.4f};

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.sub_7100D146D8())
        return;

    sead::Vector3f target_pos = accessor.getActorMtx().getTranslation();
    sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
    actor_pos.y += 5.0f;
    sead::Vector3f dir = actor_pos - target_pos;
    const f32 distance = dir.length();
    if (distance > 0.0f)
        dir *= 1.0f / distance;
    if (distance > 30.0f)
        return;

    f32 max_speed = *mVacuumMaxSpeed_s;
    if (distance < 10.0f)
        max_speed *= sNearRates[0];
    else if (distance < 15.0f)
        max_speed *= sNearRates[1];
    _58._c = max_speed * rate;

    dir *= *mVacuumMaxSpeed_s;
    sead::Quatf rotation;
    rotation.setAxisRadian(sead::Vector3f::ey, *mVacuumAngle_s);
    sead::Matrix34f rotation_mtx;
    rotation_mtx.fromQuat(rotation);
    dir.rotate(rotation_mtx);
    target_pos += dir;
    _58.sub_710073E8C4(link, &target_pos);
}

}  // namespace uking::action
