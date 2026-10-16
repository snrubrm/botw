#include <algorithm>
#include "Game/Actor/AI/aiStalPartNormal.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

bool sub_710001AAA8(const ksys::act::ActorLinkConstDataAccess& accessor, const sead::SafeString& name);

namespace uking::ai {

StalPartNormal::StalPartNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartNormal::~StalPartNormal() = default;

bool StalPartNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        _f4 = !body->hasFlag(ksys::phys::RigidBody::Flag::_2000000);
        body->clearFlag2000000(false);
    }
    _e8.previous_value = 0;
    _e8.value = 0;
    _e8.rate = 0;
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0))
        sub_71005A7750();
    else
        _58.reset();

    if (_58.hasProc()) {
        sub_7100738CB0(mActor, &_58);
        sub_71005A7854();
    } else if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        sub_7100738DC8(mActor);
        _58.reset();
        changeChild("待機");
    } else {
        _58.reset();
        changeChild("行動禁止");
    }
    ksys::act::enableAttClient(mActor, "UsePick");
    ksys::act::enableAttClient(mActor, "NoticeDo");
    ksys::act::enableAttClient(mActor, "NameBalloon");
}

void StalPartNormal::sub_71005A7750() {
    if (!_58.hasProcInCalcState())
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    const char* name = sub_71007251D0();
    if (!enemy)
        name = sub_71007251DC();
    if (sub_710001AAA8(accessor, name)) {
        sub_7100738DC8(mActor);
        _58.reset();
    }
}

void StalPartNormal::leave_() {
    sub_7100738DC8(mActor);
    if (auto* body = mActor->getMainBody())
        body->clearFlag2000000(_f4);
    ksys::act::enableAttClient(mActor, "UsePick");
    ksys::act::enableAttClient(mActor, "NoticeDo");
    ksys::act::enableAttClient(mActor, "NameBalloon");
}

void StalPartNormal::loadParams_() {
    getStaticParam(&mParams.mTerritoryArea_s, "TerritoryArea");
    getStaticParam(&mParams.mCatchArea_s, "CatchArea");
    getStaticParam(&mParams.mWaitTimer_s, "WaitTimer");
    getStaticParam(&mParams.mTgtOffset_s, "TgtOffset");
}

// 0x71005a79bc
// NON_MATCHING: the original compares the actor name with an inline byte loop on its C string (no virtual
// cstr calls); scheduling of the target position copy.
void StalPartNormal::calc_() {
    auto* child = getCurrentChild();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (!(_e8.value <= sead::Mathf::epsilon()))
        _e8.update();
    sub_71005A7750();

    if (_68._30) {
        if (child->isChangeable() && _68._38.mLink.hasProc()) {
            if (!_58.hasProc()) {
                _58 = _68._38.mLink;
                sub_7100738CB0(mActor, &_58);
                _f5 = false;
                if (mActor->getName() == "Enemy_Giant_Bone_Eye")
                    _f5 = ksys::gdt::getFlag_IsInHyruleCastleArea();
            } else if (!(_58 == _68._38.mLink)) {
                ksys::act::BaseProcLink link;
                link = _68._38.mLink;
                ksys::act::ActorLinkConstDataAccess new_target;
                ksys::act::ActorLinkConstDataAccess old_target;
                ksys::act::acquireActor(&link, &new_target);
                ksys::act::acquireActor(&_58, &old_target);
                const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
                const sead::Vector3f new_pos = new_target.getActorMtx().getTranslation();
                const sead::Vector3f old_pos = old_target.getActorMtx().getTranslation();
                if ((new_pos - actor_pos).squaredLength() < (old_pos - actor_pos).squaredLength()) {
                    _58 = link;
                    sub_7100738CB0(mActor, &_58);
                }
            }
            if (isCurrentChild("待機")) {
                _68.x();
                sub_71005A815C();
                return;
            }
        }
        _68.x();
    }

    if (!_58.hasProc()) {
        ksys::act::enableAttClient(mActor, "UsePick");
        ksys::act::enableAttClient(mActor, "NoticeDo");
        ksys::act::enableAttClient(mActor, "NameBalloon");
    }

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("気づき")) {
            if (_58.hasProc()) {
                sub_71005A815C();
                return;
            }
            sub_7100738DC8(mActor);
            _58.reset();
            changeChild("待機");
            return;
        }
        if (isCurrentChild("行動禁止")) {
            sub_7100738DC8(mActor);
            _58.reset();
            changeChild("待機");
            return;
        }
        if (isCurrentChild("移動") && child->isFailed() && _58.hasProc()) {
            sub_71005A82F8();
        } else if (_58.hasProc()) {
            sub_71005A815C();
        } else {
            sub_7100738DC8(mActor);
            _58.reset();
            changeChild("待機");
        }
    }

    if (!isCurrentChild("移動") && !isCurrentChild("気づき") && !isCurrentChild("ジャンプ"))
        return;

    if (!_58.hasProc()) {
        sub_7100738DC8(mActor);
        _58.reset();
        changeChild("待機");
        return;
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    sead::Vector3f target = accessor.getActorMtx().getTranslation();
    target = accessor.getActorMtx() * *mParams.mTgtOffset_s;
    if (_e8.value <= sead::Mathf::epsilon()) {
        const f32 dx = target.x - pos.x;
        const f32 dz = target.z - pos.z;
        f32 upper = *mParams.mCatchArea_s;
        if (dx * dx + dz * dz < upper * upper) {
            f32 lower = -upper;
            sead::Vector3f min;
            sead::Vector3f max;
            if (accessor.getAabb(&min, &max)) {
                const f32 height = max.y - min.y;
                upper = std::max(upper, height * (mActor->get68f() ? 0.9f : 0.45f));
                lower = std::min(lower, height * (_f5 ? -4.0f : -0.3f));
            }
            const f32 dy = pos.y - target.y;
            if (dy >= lower && dy <= upper) {
                _b8._18.y(mActor);
                if (accessor.isStateCalc()) {
                    _b8.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
                    _e8 = ksys::Timer(*mParams.mWaitTimer_s, *mParams.mWaitTimer_s);
                    ksys::act::disableAttClient(mActor, "UsePick");
                    ksys::act::disableAttClient(mActor, "NoticeDo");
                    ksys::act::disableAttClient(mActor, "NameBalloon");
                }
                child->setDynamicParam(target, "TargetPos");
                return;
            }
        }
        ksys::act::enableAttClient(mActor, "UsePick");
        ksys::act::enableAttClient(mActor, "NoticeDo");
        ksys::act::enableAttClient(mActor, "NameBalloon");
    }
    child->setDynamicParam(target, "TargetPos");
}

bool StalPartNormal::handleMessage_(const ksys::Message* message) {
    if (_e8.value <= sead::Mathf::epsilon() && !_68._30 && !isCurrentChild("行動禁止") &&
        _68.m2(*message)) {
        if (_58 == _68._38.mLink)
            _68.x();
        return true;
    }
    return false;
}

// NON_MATCHING: register allocation of the Matrix34 * Vector3 product only (the ldp pairs of the matrix columns come out swapped)
// 0x71005a7854
void StalPartNormal::sub_71005A7854() {
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    pack.addVec3(accessor.getActorMtx() * *mParams.mTgtOffset_s, "TargetPos", -1);
    changeChild("気づき", &pack);
}

// NON_MATCHING: register allocation of the Matrix34 * Vector3 product only (the ldp pairs of the matrix columns come out swapped)
// 0x71005a815c
void StalPartNormal::sub_71005A815C() {
    if (isCurrentChild("待機")) {
        sub_71005A7854();
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    pack.addVec3(accessor.getActorMtx() * *mParams.mTgtOffset_s, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: register allocation of the Matrix34 * Vector3 product only (the ldp pairs of the matrix columns come out swapped)
// 0x71005a82f8
void StalPartNormal::sub_71005A82F8() {
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    pack.addVec3(accessor.getActorMtx() * *mParams.mTgtOffset_s, "TargetPos", -1);
    changeChild("ジャンプ", &pack);
}

}  // namespace uking::ai
