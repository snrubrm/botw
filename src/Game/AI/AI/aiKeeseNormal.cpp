#include "Game/AI/AI/aiKeeseNormal.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace uking::ai {

KeeseNormal::KeeseNormal(const InitArg& arg) : EnemyNormal(arg) {}

KeeseNormal::~KeeseNormal() = default;

bool KeeseNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void KeeseNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getHomePos(&_430);
    _43c = _430;
    EnemyNormal::enter_(params);
    _448 = false;
    _44c = ksys::Timer(0, 0, 1);
    setDamageCallbackTiming(mActor, 1, &_460);
}

void KeeseNormal::leave_() {
    if (_458) {
        _458->release();
        _458 = nullptr;
    }
    sub_71005DA114(mActor, &_460);
    EnemyNormal::leave_();
}

void KeeseNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mRoamHeightFromGlowObj_s, "RoamHeightFromGlowObj");
    getMapUnitParam(&mIsCreateOnFace_m, "IsCreateOnFace");
}

bool KeeseNormal::handleMessage_(const ksys::Message& message) {
    if (isChangeable() && _3e0.m2(message))
        return !isCurrentChild("ぶらさがり");
    if (isCurrentChild("ぶらさがり"))
        return false;
    return EnemyNormal::handleMessage_(message);
}

void KeeseNormal::m37() {
    m41();
    _364 = 0;
    if (_448) {
        ksys::act::ai::InlineParamPack params;
        sead::Vector3f pos;
        m48(&pos);
        params.addVec3(pos, "TargetPos", -1);
        changeChild("天井近づき", &params);
    } else {
        ksys::act::ai::InlineParamPack params;
        sead::Vector3f pos;
        m48(&pos);
        params.addVec3(pos, "CentralPos", -1);
        changeChild("待機", &params);
    }
}

void KeeseNormal::m38() {
    m41();
    _364 = 0;
    ksys::act::ai::InlineParamPack params;
    if (_448) {
        params.addVec3(_43c, "TargetPos", -1);
    } else {
        sead::Vector3f pos;
        m48(&pos);
        params.addVec3(pos, "TargetPos", -1);
    }
    changeChild("諦め", &params);
}

void KeeseNormal::m48(sead::Vector3f* pos) {
    if (_488.hasProc()) {
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(&_488, &acc);
        *pos = acc.getPreviousPos();
        pos->y = *mRoamHeightFromGlowObj_s + pos->y;
    } else {
        pos->set(_430);
    }
}

void KeeseNormal::m49(Unk1* out, s32 idx) {
    if (isCurrentChild("連携")) {
        out->_0 = -1;
        return;
    }
    EnemyNormal::m49(out, idx);
}

void KeeseNormal::m50(Unk1* out, s32 idx) {
    if (!isCurrentChild("連携")) {
        EnemyNormal::m50(out, idx);
        return;
    }
    const s32 type = m52(idx);
    switch (type) {
    case 0:
    case 1:
    case 4:
        out->_8 |= 6;
        out->_0 = type;
        out->_4 = 2;
        break;
    default:
        out->_0 = -1;
        break;
    }
}


}  // namespace uking::ai
