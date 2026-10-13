#include "Game/AI/AI/aiGerudoQueenBattle.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadDelegate.h>
#include "Game/AI/aiUnk_710073033C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorNameSearch.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"

namespace uking::ai {

GerudoQueenBattle::GerudoQueenBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GerudoQueenBattle::~GerudoQueenBattle() {
    if (_50.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_50, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        _50.reset();
    }
    if (_60.hasProc())
        _60.reset();
    if (_70.hasProc())
        _70.reset();
    if (_80) {
        ksys::act::sub_7100EBA4AC(_80);
        _80 = nullptr;
    }
    if (_118) {
        mActor->sub_71011DA868(&_118[0]);
        mActor->sub_71011DA868(&_118[1]);
        mActor->sub_71011DA868(&_118[2]);
        delete[] _118;
    }
}

// NON_MATCHING: register numbering (the original keeps `this` in x20 and `&_70` in x19)
bool GerudoQueenBattle::sub_71003F4648() {
    if (!_70.hasProc())
        return false;
    const bool in_range = sub_710073033C(
        mActor, &_70, ksys::world::Manager::instance()->getEnvMgrUnchecked()->get6b548());
    if (!isCurrentChild("雷攻撃無効化"))
        return false;
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    const bool riding = player.isRidingSandSeal();
    return in_range && riding;
}

// NON_MATCHING: the separate-TU search destructor call changes stack storage and return scheduling.
bool GerudoQueenBattle::sub_71003F3E44(ksys::act::BaseProcMgr* mgr) {
    ksys::act::BaseProc* result = nullptr;
    ksys::act::ActorNearestSearch search("RougeSuna", mActor, &result, sead::Vector3f::zero);
    sead::Delegate1<ksys::act::ActorNearestSearch, ksys::act::BaseProc*> callback(
        &search, &ksys::act::ActorNearestSearch::sub_7100EDC9E8);
    mgr->forEachProc("Animal_SunazarashiSP_B", callback,
                    ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
    if (!result)
        return false;
    _60.acquire(result, false);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_60, &accessor);
    accessor.sub_7100D14F94(_80);
    const sead::Vector3f direction =
        accessor.getActorMtx().getTranslation() - mActor->getMtx().getTranslation();
    sub_71003F4910(sead::Mathf::atan2Idx(direction.x, direction.z));
    return true;
}

// NON_MATCHING: the matrix snapshot is scalarized; vector loads and float registers differ.
void GerudoQueenBattle::sub_71003F4910(u32 angle) {
    const sead::Matrix34f transform = mActor->getMtx();
    sead::Vector3f forward = transform.getBase(2);
    forward.normalize();
    sead::Vector2f horizontal(forward.x, forward.z);
    if (horizontal.length() == 0.0f) {
        sead::Vector3f up = transform.getBase(1);
        up.normalize();
        horizontal.set(up.x, up.z);
    }
    sead::Matrix33f rotation;
    rotation.makeRIdx(0, angle - sead::Mathf::atan2Idx(horizontal.x, horizontal.y), 0);
    mActor->mMtx.setMul(rotation, transform);
    mActor->nullsub_4648();
}

bool GerudoQueenBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GerudoQueenBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GerudoQueenBattle::leave_() {
    mActor->emitBasicSigOff();
    _40.fade();
    _80->sub_7100EBB518();
    mActor->resetConnectedCalcChild(false);
}

void GerudoQueenBattle::loadParams_() {
    getStaticParam(&mRetireFrame_s, "RetireFrame");
}

bool GerudoQueenBattle::handleMessage_(const ksys::Message* message) {
    const auto type = message->getType();
    switch (type) {
    case ksys::MessageType(0x08000085):
    case ksys::MessageType(0x08000086):
    case ksys::MessageType(0x08000087):
    case ksys::MessageType(0x08000088):
    case ksys::MessageType(0x08000089):
    case ksys::MessageType(0x0800008a):
    case ksys::MessageType(0x0800008b):
    case ksys::MessageType(0x0800008c):
        _fc = type;
        _f8 = true;
        return true;
    case ksys::MessageType(0x0800008d):
        if (_80)
            _80->sub_7100EBB624();
        break;
    case ksys::MessageType(0x0800008e):
        if (_80)
            _80->_60.set(0x10);
        break;
    case ksys::MessageType(0x0800008f):
        if (_80)
            _80->sub_7100EBB60C();
        break;
    case ksys::MessageType(0x08000090):
        if (_88)
            _88 = false;
        if (_89) {
            _80->sub_7100EBB518();
            _89 = false;
        }
        if (_60.hasProc())
            _60.reset();
        break;
    default:
        break;
    }
    return false;
}

}  // namespace uking::ai
