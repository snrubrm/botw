#include "Game/AI/AI/aiKorokPotRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::ai {

KorokPotRootAI::KorokPotRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokPotRootAI::~KorokPotRootAI() = default;

bool KorokPotRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokPotRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getHomeMtx(&_58);
    _88 = true;
    _89 = false;
    _8c = 0;
    if (*mIsCrayShot_m) {
        mActor->getMainBody()->setMaxImpulse(100.0f);
        mActor->getMainBody()->setGravityFactor(0.3f);
    }
}

// NON_MATCHING: the original loads CrayLaunchAngularSpeed before the GlobalRandom instance for the first
// getF32Range (C++14 evaluation order of the object expression); one instruction pair swapped.
void KorokPotRootAI::calc_() {
    if (!*mIsCrayShot_m) {
        if (auto* manager = sub_710072BA90(mActor)) {
            const s32 type = manager->getField54();
            manager->getField50();
            if ((type | 1) == 0x1f)
                mActor->emitBasicSigOn();
        }
        return;
    }

    if (!_88) {
        if (mActor->checkBasicSig()) {
            auto* body = mActor->getMainBody();
            auto* tgt_body = mActor->getTgtBody();
            if (body && tgt_body) {
                body->setContactAll();
                body->setFlag200();
                tgt_body->setContactAll();
                tgt_body->setFlag200();
                body->clearEntityMotionFlag4(false);
                _8c = 5.0f;
            }
            _88 = true;
        } else if (auto* manager = sub_710072BA90(mActor)) {
            const s32 type = manager->getField54();
            const u32 value = manager->getField50();
            if (value < 5) {
                if ((type | 1) == 0x1f) {
                    mActor->emitBasicSigOn();
                    return;
                }
                _89 = true;
            } else if ((type | 1) == 0x1f && value == 6) {
                mActor->emitBasicSigOn();
            }
        }
        return;
    }

    if (_8c > 0.0f) {
        _8c -= 1.0f;
        if (_8c <= 0.0f) {
            mActor->sub_71011CCB1C(1.0f);
            if (auto* body = mActor->getMainBody()) {
                mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
                body->changeMotionType(ksys::phys::MotionType::Keyframed);
                body->setLinearVelocity(sead::Vector3f::zero);
                body->setTransform(_58);
            }
        } else {
            mActor->sub_71011CCB1C(_8c * 0.2f);
        }
    }

    if (!mActor->checkBasicSig()) {
        auto* body = mActor->getMainBody();
        auto* tgt_body = mActor->getTgtBody();
        if (body && tgt_body) {
            body->setLinearVelocity(sead::Vector3f::zero);
            body->setAngularVelocity(sead::Vector3f::zero);
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            body->setContactNone();
            body->resetFlag200();
            tgt_body->setContactNone();
            tgt_body->resetFlag200();
            body->clearEntityMotionFlag4(true);
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
            body->applyLinearImpulse(_58.getBase(1) * *mCrayLaunchSpeed_m * *mCrayLaunchSpeedRate_s);
            const sead::Vector3f angular(sead::GlobalRandom::instance()->getF32Range(
                                             -*mCrayLaunchAngularSpeed_s, *mCrayLaunchAngularSpeed_s),
                                         sead::GlobalRandom::instance()->getF32Range(
                                             -*mCrayLaunchAngularSpeed_s, *mCrayLaunchAngularSpeed_s),
                                         sead::GlobalRandom::instance()->getF32Range(
                                             -*mCrayLaunchAngularSpeed_s, *mCrayLaunchAngularSpeed_s));
            body->setAngularVelocity(angular);
        }
        _88 = false;
    }
}

void KorokPotRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokPotRootAI::loadParams_() {
    getStaticParam(&mCrayLaunchSpeedRate_s, "CrayLaunchSpeedRate");
    getStaticParam(&mCrayLaunchAngularSpeed_s, "CrayLaunchAngularSpeed");
    getMapUnitParam(&mCrayLaunchSpeed_m, "CrayLaunchSpeed");
    getMapUnitParam(&mIsCrayShot_m, "IsCrayShot");
}

}  // namespace uking::ai
