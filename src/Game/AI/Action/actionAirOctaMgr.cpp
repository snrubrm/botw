#include "Game/AI/Action/actionAirOctaMgr.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

AirOctaMgr::AirOctaMgr(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaMgr::~AirOctaMgr() {
    _60.freeBuffer();
}

bool AirOctaMgr::init_(sead::Heap* heap) {
    mActor->mDrawDistanceFlags.set(2);
    if (!mActor || !mActor->getMapObject())
        return true;
    auto* links = mActor->getMapObject()->getLinkData();
    if (!links)
        return true;
    _60.tryAllocBuffer(links->mObjects.size(), heap);
    return true;
}

void AirOctaMgr::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirOctaMgr::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaMgr::loadParams_() {
    getStaticParam(&mLeaveDistance_s, "LeaveDistance");
    getStaticParam(&mLeaveDownY_s, "LeaveDownY");
    getStaticParam(&monGraundEscapeDist_s, "onGraundEscapeDist");
    getStaticParam(&mPlayerLostTime_s, "PlayerLostTime");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mReactHorn_m, "ReactHorn");
}

void AirOctaMgr::calc_() {
    _354 &= ~0x80u;
    if (!sub_7100085C28())
        return;
    if (auto* awareness = mActor->getAwareness()) {
        sub_71000870E0(awareness);
        sub_71000873F4(awareness);
        sub_71000874E8(awareness);
    }
    sub_7100086168();
    sub_7100086484();
}

// NON_MATCHING: the existing filter vtable uses GOT addressing instead of a direct address.
void AirOctaMgr::sub_71000874E8(ksys::act::AwarenessInstance* awareness) {
    if (!awareness)
        return;
    Unk_7102362ed0 filter;
    f32 height = -10000.0f;
    bool found = false;
    for (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter); entry;
         entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&entry->_0.mLink, &accessor) &&
            _70.getId() == accessor.getBalloonHungActorBaseProcID()) {
            const f32 y = accessor.getActorMtx()(1, 3);
            if (y > height)
                height = y;
            found = true;
        }
    }
    if (!_1c0) {
        _128 = height;
        _130 = 0.0f;
    }
    _1c0 = found;
    _12c = height - _128;
    _128 = height;
    _130 += _12c;
}

}  // namespace uking::action

Unk_7102362e80::~Unk_7102362e80() = default;

bool uking::action::Unk_7102362ea8::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.isPlayerProfile();
}

bool uking::action::Unk_7102362ed0::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.isFlyingBalloon();
}

void uking::action::AirOctaMgr::sub_71000873F4(ksys::act::AwarenessInstance* awareness) {
    if (!awareness || !*mReactHorn_m || !(_354 & 2))
        return;

    auto* sensor = awareness->_260(1);
    if (!sensor)
        return;

    const u32 count = sensor->_8.size();
    for (u32 i = 0; i < count; ++i) {
        sensor = awareness->_260(1);
        if (!sensor || sensor->_8.size() < 1)
            continue;

        if (auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0)) {
            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(&entry->_0.mLink, &accessor) && entry->_a4 >= 6.2f) {
                _354 |= 1;
                return;
            }
        }
    }
}
