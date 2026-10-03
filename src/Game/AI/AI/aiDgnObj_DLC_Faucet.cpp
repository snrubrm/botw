#include "Game/AI/AI/aiDgnObj_DLC_Faucet.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

DgnObj_DLC_Faucet::DgnObj_DLC_Faucet(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_Faucet::~DgnObj_DLC_Faucet() = default;

bool DgnObj_DLC_Faucet::init_(sead::Heap* heap) {
    auto* tgt_body = mActor->getTgtBody();
    _58 = !tgt_body;
    if (tgt_body) {
        auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
        if (!actor)
            return false;
        actor->_a70 = &_60;
    }
    return true;
}

void DgnObj_DLC_Faucet::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        sead::Matrix34f mtx;
        body->getTransform(&mtx);
        body->setGravityFactor(0);
        _44.x = mtx(0, 1);
        _44.y = mtx(1, 1);
        _44.z = mtx(2, 1);
    }
    _84 = false;
}

void DgnObj_DLC_Faucet::calc_() {
    if (_58)
        sub_7100360230();
    else
        sub_710036052C(nullptr);
}

void DgnObj_DLC_Faucet::sub_7100360230() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;

    sead::Vector3f w;
    body->getAngularVelocity(&w);
    const f32 speed = w.normalize();
    if (speed > 1) {
        if (_54 != 1 && !_84) {
            ksys::eft::searchAndEmitSLink(mActor, "StartMoveFast", false);
            _84 = true;
        }
        _54 = 1;
        body->setAngularVelocity(w * 3, sead::Mathf::epsilon());
        return;
    }

    if (speed <= 0.02f) {
        _54 = 0;
        body->setAngularVelocity(w * 0, sead::Mathf::epsilon());
        _50 = 60;
        _84 = false;
        return;
    }

    if (_54 == 3) {
        body->setAngularVelocity(w * 0, sead::Mathf::epsilon());
        _84 = false;
        return;
    }
    _54 = 2;
    sead::Matrix34f mtx;
    body->getTransform(&mtx);
    const sead::Vector3f y{mtx(0, 1), mtx(1, 1), mtx(2, 1)};
    const f32 dot = y.dot(_44);
    sead::Vector3f cross;
    cross.setCross(_44, y);
    const f32 angle = sead::Mathf::atan2(cross.length(), dot);
    if (--_50 <= 0) {
        if (sead::Mathf::abs(angle + sead::Mathf::deg2rad(120)) < sead::Mathf::deg2rad(18) ||
            sead::Mathf::abs(angle) < sead::Mathf::deg2rad(18) ||
            sead::Mathf::abs(angle - sead::Mathf::deg2rad(120)) < sead::Mathf::deg2rad(18)) {
            _54 = 3;
            body->setAngularVelocity(w * 0, sead::Mathf::epsilon());
            _84 = false;
            return;
        }
    }
    if (speed == 0)
        _84 = false;
}

void DgnObj_DLC_Faucet::sub_710036052C(ksys::act::Unk_71006dc134* arg) {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    if (!mActor->checkBasicSig())
        return;

    sead::Vector3f z;
    mActor->getMtx().getBase(z, 2);
    const sead::Vector3f up = sead::Vector3f::ey;
    const f32 dot = z.dot(up);
    sead::Vector3f impulse{-(up.x * dot), -(up.y * dot), -(up.z * dot)};
    const f32 y = up.y * dot;
    if (y > -0.0f) {
        _80 = sead::Mathf::min(1.0f, _80 + 0.01f);
        if (y < 0.999f) {
            const f32 mass = body->getMass();
            impulse *= mass;
            impulse *= 0.3f;
            impulse *= _80;
            body->applyLinearImpulse(impulse);
        }
    } else {
        _80 = 0;
    }
}

}  // namespace uking::ai
