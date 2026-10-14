#include "Game/Actor/AI/aiKeeseNormal.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/aiUnk_71006F5B14.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace uking::ai {

KeeseNormal::KeeseNormal(const InitArg& arg) : EnemyNormal(arg) {}

KeeseNormal::~KeeseNormal() = default;

bool KeeseNormal::init_(sead::Heap* heap) {
    if (!EnemyNormal::init_(heap))
        return false;

    auto* actor = mActor;
    sub_71006F5D3C(sub_71006F5694(actor), actor);
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F63700(false);
    return true;
}

void KeeseNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getHomePos(&_430);
    _43c = _430;
    EnemyNormal::enter_(params);
    _448 = false;
    _44c = ksys::Timer(0, 0, 1);
    setDamageCallbackTiming(mActor, 1, &_460);
}

// NON_MATCHING: the SafeString vtable address is kept in a callee-saved register (x22) instead of being recomputed.
void KeeseNormal::calc_() {
    if (!_448 && *mIsCreateOnFace_m) {
        if (_44c.value > 8.0f && (!_458 || !_458->isRequestQueued())) {
            if (!_458)
                _458 = ksys::phys::RayCastForRequest::allocRequest();
            if (_458) {
                sead::Vector3f pos;
                mActor->getMtx().getTranslation(pos);
                sead::Vector3f top = pos;
                top.y += 10.0f;
                _43c = pos;
                sub_710072EC24(_458, pos, top, ksys::phys::RayCast::NormalCheckingMode::_0, 0.0f);
            }
        } else if (_458 && _458->get70() == 1) {
            if (_458->hasHit()) {
                _458->getHitPosition(&_430);
                _448 = true;
            }
            _458->release();
            _458 = nullptr;
            _44c = ksys::Timer(0, 0, 1);
        } else {
            _44c.update();
        }
    }

    sub_710045328C();

    bool landed = false;
    if (isCurrentChild("天井近づき")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            changeChild("ぶらさがり");
            landed = true;
        }
    }
    if (!landed) {
        if (isCurrentChild("ぶらさがり") && getCurrentChild()->isFailed()) {
            _448 = false;
            m37();
        } else if (isCurrentChild("連携")) {
            EnemyNormal::calc_();
        } else if (_448 && getCurrentChild()->isChangeable() && isCurrentChild("待機")) {
            m37();
        } else if (getCurrentChild()->isChangeable() && _3e0._30) {
            changeToCooperate(_3e0._38.mLink);
            _3e0.x();
            return;
        } else {
            EnemyNormal::calc_();
        }
    }

    if (isCurrentChild("待機")) {
        sead::Vector3f pos;
        m48(&pos);
        getCurrentChild()->setDynamicParam(pos, "CentralPos");
    }
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

bool KeeseNormal::handleMessage_(const ksys::Message* message) {
    if (isChangeable() && _3e0.m2(*message))
        return !isCurrentChild("ぶらさがり");
    if (isCurrentChild("ぶらさがり"))
        return false;
    return EnemyNormal::handleMessage_(message);
}

void KeeseNormal::m34() {
    if (!*mIsCreateOnFace_m || mActor->getRootAi()->getI() == 5) {
        EnemyNormal::m34();
        return;
    }

    auto* actor = mActor;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    sead::Vector3f top;
    top.setAdd(pos, sead::Vector3f(0, 5, 0));
    sead::Vector3f hit;
    if (sub_710072EB10(pos, top, ksys::phys::RayCast::NormalCheckingMode::_0, actor, &hit, nullptr,
                       nullptr, 0.0f)) {
        _430 = hit;
        _448 = true;
        changeChild("ぶらさがり");
        return;
    }
    EnemyNormal::m34();
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
        ksys::act::ActorLinkConstDataAccess acc;
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

void KeeseNormal::changeToCooperate(const ksys::act::BaseProcLink& target) {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.0f);

    ksys::act::ai::InlineParamPack pack;
    pack.addActor(target, "TargetActor", -1);
    changeChild("連携", &pack);
}

}  // namespace uking::ai
