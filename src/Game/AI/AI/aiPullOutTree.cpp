#include "Game/AI/AI/aiPullOutTree.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"

Unk_7102416670::Unk_7102416670(ksys::act::Actor* actor) : Unk_7102357d20(actor, 0x8000018) {
    sead::ScopedLock<sead::JobQueueLock> lock(&_18.mLock);
    _18.mLink.acquire(actor, false);
}

bool Unk_7102416698::m2(const ksys::Message& message) {
    if (message.getType() != 0x800001a)
        return false;
    _30 = true;
    _18 = message.getSource();
    return true;
}

namespace uking::ai {

PullOutTree::PullOutTree(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PullOutTree::~PullOutTree() = default;

bool PullOutTree::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PullOutTree::enter_(ksys::act::ai::InlineParamPack* params) {
    _48.sub_710070DCC0(mTargetActor_d, true);

    sead::Vector3f target_pos;
    getTargetPos(&target_pos);

    if (sub_710072DDB8(target_pos, mActor->getMtx(), *mTurnAng_s))
        sub_7100532E04();
    else
        sub_7100532CF8();
}

// NON_MATCHING: same shape as SeqTwoLineReachableTargetActionBase::calc_ — the original has the child's vtable
// load hoisted into the condition blocks (the shared body starts with the same isFailed() call as the second
// condition); ours keeps the loads in their blocks
void PullOutTree::calc_() {
    auto* child = getCurrentChild();
    if ((isCurrentChild("回転") || isCurrentChild("移動")) && !mTargetActor_d->hasProc()) {
        setFailed();
        return;
    }

    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
        } else if (isCurrentChild("回転")) {
            sub_7100532E04();
        } else if (isCurrentChild("移動")) {
            if (!_78._30) {
                sub_7100533314();
            } else {
                sub_7100533178();
                _78.x();
            }
        } else if (isCurrentChild("生成待機")) {
            setFailed();
        } else {
            setFinished();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("生成待機") && _78._30) {
            sub_7100533178();
            _78.x();
        } else if (isCurrentChild("移動")) {
            auto* actor = mActor;
            if (!sub_71007A4178(actor, false))
                return;
            const s32 num = sub_71007A425C(actor);
            for (s32 i = 0; i < num; ++i) {
                if (sub_71007A40D0(actor, i)->_50 == *mTargetActor_d) {
                    if (!_78._30) {
                        sub_7100533314();
                    } else {
                        sub_7100533178();
                        _78.x();
                    }
                    return;
                }
            }
        } else if (isCurrentChild("引き抜き中")) {
            if (!mTargetActor_d->hasProc())
                setFailed();
        }
    }
}

void PullOutTree::leave_() {
    _78.x();
    if (mTargetActor_d->hasProcInCalcState()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(mTargetActor_d, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000019),
                            nullptr, false);
    }
}

void PullOutTree::loadParams_() {
    getStaticParam(&mTurnAng_s, "TurnAng");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool PullOutTree::handleMessage_(const ksys::Message& message) {
    return !_78._30 && _78.m2(message);
}

void PullOutTree::getTargetPos(sead::Vector3f* out) const {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(*out);
}

void PullOutTree::sub_7100532CF8() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    getTargetPos(&pos);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &params);
}

void PullOutTree::sub_7100532E04() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    getTargetPos(&pos);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &params);
}

void PullOutTree::sub_7100533314() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    getTargetPos(&pos);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("生成待機", &params);
}

void PullOutTree::sub_7100533178() {
    ksys::act::ai::InlineParamPack params;
    params.addActor(*mTargetActor_d, "TargetActor", -1);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    sead::Vector3f pos;
    pos.setMul(accessor.getActorMtx(),
               ksys::act::GlobalParameter::instance()->getGlobalParam()->mTreeWeaponEquipTransOffset.ref());
    params.addVec3(pos, "TargetPos", -1);
    changeChild("装備", &params);
}

}  // namespace uking::ai
