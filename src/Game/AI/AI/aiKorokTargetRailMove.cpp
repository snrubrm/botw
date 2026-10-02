#include "Game/AI/AI/aiKorokTargetRailMove.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

KorokTargetRailMove::KorokTargetRailMove(const InitArg& arg) : KorokRailMove(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (trivial members only);
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
KorokTargetRailMove::~KorokTargetRailMove() { ; }

bool KorokTargetRailMove::init_(sead::Heap* heap) {
    return KorokRailMove::init_(heap);
}

void KorokTargetRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->emitBasicSigOff();
    if (sub_7100EEF034(mActor, 0)) {
        _108 = true;
        KorokRailMove::enter_(params);
    } else {
        changeChild("完全停止");
    }

    _10c.value = *mRotSpd_s;
    _10c.prev_value = *mRotSpd_s;
    sub_710073FA90(&_118, mActor);

    if (*mIsNoAppearEffect_m) {
        _e4 = 1;
        _13c = true;
    } else {
        _e4 = 2;
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        auto* main_body = mActor->getMainBody();
        auto* tgt_body = mActor->getTgtBody();
        if (main_body && tgt_body) {
            main_body->setContactAll();
            main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
            main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
            main_body->setFlag200();
            tgt_body->setContactAll();
            tgt_body->setFlag200();
        }
        _13c = false;
    }
    _144 = true;
    _140 = 0;
    _148 = -1.0f;
}

void KorokTargetRailMove::calc_() {
    sub_710045E380();
    if (auto* damage_manager = sub_710072BA90(mActor)) {
        const s32 type = damage_manager->getField54();
        if (type == 30 || type == 31)
            _e0 = true;
    }
    sub_710045E4FC();
}

void KorokTargetRailMove::sub_710045E380() {
    _10c.updateStats();
    sead::Vector3f dir = getPlayerPosition() - mActor->getMtx().getTranslation();
    if (auto* body = mActor->getMainBody()) {
        sub_710073FA94(&_118, mActor);
        dir.normalize();
        sub_710074006C(&_118, dir, sead::Vector3f::ey, true, 0.16f, _10c.value, _10c.value / 10.0f);
        sub_7100740E8C(_118, body);
    }

    if (_108 && _144) {
        KorokRailMove::calc_();
        if (isCurrentChild("停止"))
            _148 = _148 == -1.0f ? 1.0f : _148 + 1.0f;
        else
            _148 = -1.0f;
    }
}

void KorokTargetRailMove::sub_710045E4FC() {
    if (_e0) {
        mActor->emitBasicSigOn();
        return;
    }

    if (!_144) {
        if (!mActor->checkBasicSig())
            return;

        if (_e4 != 2) {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            xlinkSearchAndEmit(mActor, "Appear", 2, &_e8);
            auto* main_body = mActor->getMainBody();
            auto* tgt_body = mActor->getTgtBody();
            if (main_body && tgt_body) {
                main_body->setContactNone();
                main_body->resetFlag200();
                tgt_body->setContactNone();
                tgt_body->resetFlag200();
            }
        }

        if (_108) {
            if (_148 > -1.0f) {
                sub_710045BD18(sub_710045BA10() - _148);
            } else if (sub_710045BD08()) {
                sub_710045B800();
            } else {
                sub_710045BA20();
            }
        }
        _144 = true;
        return;
    }

    switch (_e4) {
    case 0: {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        auto* main_body = mActor->getMainBody();
        auto* tgt_body = mActor->getTgtBody();
        if (main_body && tgt_body) {
            main_body->setContactNone();
            main_body->resetFlag200();
            tgt_body->setContactNone();
            tgt_body->resetFlag200();
        }
        _e4 = 1;
        break;
    }
    case 1: {
        if (!*mIsNoAppearEffect_m && !mActor->checkBasicSig()) {
            xlinkSearchAndEmit(mActor, "Vanish", 2, &_e8);
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
            auto* main_body = mActor->getMainBody();
            auto* tgt_body = mActor->getTgtBody();
            if (main_body && tgt_body) {
                main_body->setContactAll();
                main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
                main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
                main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
                main_body->setFlag200();
                tgt_body->setContactAll();
                tgt_body->setFlag200();
                main_body->setLinearVelocity(sead::Vector3f::zero);
            }
            changeChild("完全停止");
            _144 = false;
            return;
        }

        const s32 appear_frame = *mKorokTargetAppearFrame_m;
        if (appear_frame < 1 || *mKorokTargetVanishFrame_m < 1)
            return;

        if (_140 >= appear_frame) {
            xlinkSearchAndEmit(mActor, "Vanish", 2, &_e8);
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
            auto* main_body = mActor->getMainBody();
            auto* tgt_body = mActor->getTgtBody();
            if (main_body && tgt_body) {
                main_body->setContactAll();
                main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
                main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
                main_body->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
                main_body->setFlag200();
                tgt_body->setContactAll();
                tgt_body->setFlag200();
            }
            _140 = 0;
            _e4 = 2;
            return;
        }
        ++_140;
        break;
    }
    case 2: {
        if (_13c) {
            if (!*mIsNoAppearEffect_m && !mActor->checkBasicSig()) {
                changeChild("完全停止");
                mActor->getMainBody()->setLinearVelocity(sead::Vector3f::zero);
                _144 = false;
                return;
            }
            if (_140 >= *mKorokTargetVanishFrame_m) {
                xlinkSearchAndEmit(mActor, "Appear", 2, &_e8);
                _140 = 0;
                _e4 = 0;
                return;
            }
        }

        const s32 vanish_frame = *mKorokTargetVanishFrame_m;
        if (!_13c) {
            _140 = vanish_frame - 1;
            _13c = true;
        } else if (vanish_frame != -1) {
            ++_140;
        } else if (_140 == -2) {
            _140 = -1;
        }
        break;
    }
    default:
        break;
    }
}

void KorokTargetRailMove::leave_() {
    if (!_e0)
        xlinkSearchAndEmit(mActor, "Vanish", 2, &_e8);
    if (_108)
        KorokRailMove::leave_();
}

void KorokTargetRailMove::loadParams_() {
    KorokRailMove::loadParams_();
    getStaticParam(&mRotSpd_s, "RotSpd");
    getMapUnitParam(&mKorokTargetAppearFrame_m, "KorokTargetAppearFrame");
    getMapUnitParam(&mKorokTargetVanishFrame_m, "KorokTargetVanishFrame");
    getMapUnitParam(&mIsNoAppearEffect_m, "IsNoAppearEffect");
}

}  // namespace uking::ai
