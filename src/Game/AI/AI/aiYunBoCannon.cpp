#include "Game/AI/AI/aiYunBoCannon.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {


YunBoCannon::YunBoCannon(const InitArg& arg) : GoronCannonBase(arg) {}

YunBoCannon::~YunBoCannon() = default;

bool YunBoCannon::init_(sead::Heap* heap) {
    return GoronCannonBase::init_(heap);
}

// NON_MATCHING: scheduling only (`mov x2, sp` of the "Hole" key temporary is issued before its string address)
void YunBoCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    GoronCannonBase::enter_(params);
    mHoleKey.search(mActor->getModel(), "Hole");
    _232 = 0;
    mStateFlags = 0;
    updateReceiverMaybe();
    mStateFlags &= 0xff98;
    changeChild("待機");
}

void YunBoCannon::calc_() {
    GoronCannonBase::calc_();
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (!mReceiverLink.hasProc())
        updateReceiverMaybe();
    if (mStateFlags & 4)
        mStateFlags &= 0xffef;

    if (*mCannonSpot_m == 0 && ksys::gdt::getFlag_Fire_Relic_CannonReset_For_Bridge(false)) {
        ksys::gdt::setFlag_Fire_Relic_CannonReset_For_Bridge(false, false);
        if (isCurrentChild("装填口開放") || isCurrentChild("装填完了")) {
            mStateFlags &= 0xff98;
            changeChild("待機");
            return;
        }
    }

    if (isCurrentChild("待機")) {
        const bool basic_sig = actor->checkBasicSig();
        u16 flags = mStateFlags;
        if (basic_sig) {
            flags |= 0x40;
            mStateFlags = flags;
            auto* model = actor->getModel();
            sead::Matrix34f mtx = actor->getMtx();
            if (model && mHoleKey.isValid()) {
                model->getUnits()
                    .unsafeAt(mHoleKey.getKey().model_unit_index)
                    ->mModelUnit->getBoneWorldMatrix(&mtx, mHoleKey.getKey().bone_index);
            }
            sendMatrixMessage(mtx, 0x8000063, false);
            flags = mStateFlags;
        }
        if ((flags & 0x41) == 0x41) {
            mStateFlags &= 0xff98;
            changeChild("装填口開放");
            return;
        }
    }

    if (isCurrentChild("装填口開放")) {
        if (actor->checkBasicSig()) {
            if (mStateFlags & 2) {
                mStateFlags &= 0xfffe;
                changeChild("装填完了");
                return;
            }
        } else {
            sead::Matrix34f mtx = actor->getMtx();
            if (auto* anchor = findDestinationAnchor(mReturnAnchorName_s.cstr())) {
                const sead::Vector3f rotate = anchor->getRotate();
                const sead::Vector3f translate = anchor->getTranslate();
                mtx.makeRT(rotate, translate);
            }
            sendMatrixMessage(mtx, 0x8000064, false);
            if (mStateFlags & 0x20) {
                mStateFlags &= 0xff98;
                changeChild("ユン坊離脱");
                return;
            }
        }
    }

    if (isCurrentChild("装填完了")) {
        if (_108 && _109 && !(mStateFlags & 0x10)) {
            sead::Matrix34f mtx = actor->getMtx();
            sendMatrixMessage(mtx, 0x8000066, false);
            sub_710032D5FC();
            mStateFlags &= 0xff98;
            _108 = false;
            _109 = false;
            changeChild("発射");
            return;
        }
        if (!(mStateFlags & 2) || !actor->checkBasicSig()) {
            sead::Matrix34f mtx = actor->getMtx();
            if (auto* anchor = findDestinationAnchor(mReturnAnchorName_s.cstr())) {
                const sead::Vector3f rotate = anchor->getRotate();
                const sead::Vector3f translate = anchor->getTranslate();
                mtx.makeRT(rotate, translate);
            }
            sendMatrixMessage(mtx, 0x8000064, false);
            const u16 flags = mStateFlags;
            mStateFlags = flags | 0x10;
            if (flags & 0x20) {
                mStateFlags &= 0xff98;
                changeChild("装填完了後ユン坊離脱");
                return;
            }
        }
    }

    if (isCurrentChild("発射") || isCurrentChild("ユン坊離脱") ||
        isCurrentChild("装填完了後ユン坊離脱")) {
        if (child->isFinishedOrFailed()) {
            mStateFlags &= 0xff98;
            changeChild("待機");
        }
    }
}

// NON_MATCHING: the original computes `this + 0x1f0` after the payload lock; ours before (register assignment)
bool YunBoCannon::updateReceiverMaybe() {
    auto* actor = mActor;
    mLinkSender._18.y(actor);
    mReceiverLink.reset();
    sub_71005E02E0(actor, &mLinkSender, &mReceiverLink);
    if (mReceiverLink.hasProcInCalcState())
        return true;
    mReceiverLink.reset();
    return false;
}

void YunBoCannon::sendMatrixMessage(const sead::Matrix34f& mtx, u32 type, bool a3) {
    auto* actor = mActor;
    if (!mReceiverLink.hasProc())
        return;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&mMatrixSender._18.mLock);
        mMatrixSender._18._0.acquire(actor, false);
        mMatrixSender._18._10 = mtx;
    }
    mMatrixSender._10 = ksys::MessageType(type);

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&mReceiverLink, &accessor);
    if (accessor.hasProc()) {
        if (a3)
            mMatrixSender.sub_710070DFD8(accessor, true);
        else
            mMatrixSender.sub_710070DD78(accessor, true);
    }
}

// NON_MATCHING: the shared `mStateFlags = mStateFlags & 0xff98` / store tail is merged differently (one extra strh)
bool YunBoCannon::handleMessage_(const ksys::Message* message) {
    auto* actor = mActor;
    switch (message->getType()) {
    case 0x800005e:
        if (mStateFlags & 0x40) {
            mStateFlags |= 1;
            break;
        }
        [[fallthrough]];
    case 0x8000063:
        mStateFlags &= 0xff98;
        break;
    case 0x8000060:
        mStateFlags |= 0x20;
        break;
    case 0x8000068: {
        sead::Matrix34f mtx = actor->getMtx();
        if (auto* anchor = findDestinationAnchor(mReturnAnchorName_s.cstr())) {
            const sead::Vector3f rotate = anchor->getRotate();
            const sead::Vector3f translate = anchor->getTranslate();
            mtx.makeRT(rotate, translate);
        }
        sendMatrixMessage(mtx, 0x8000065, true);
        break;
    }
    case 0x800005f:
        mStateFlags |= 2;
        break;
    case 0x8000061:
        mStateFlags |= 4;
        break;
    default:
        break;
    }
    return false;
}

// NON_MATCHING: scheduling only (the "TargetPosition" key temporary and the root AI address, as in m36)
void YunBoCannon::m35(ksys::act::Actor* actor, ksys::act::Actor* ball) {
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    if (auto* anchor = findDestinationAnchor(mReturnAnchorName_s.cstr())) {
        const sead::Vector3f rotate = anchor->getRotate();
        const sead::Vector3f translate = anchor->getTranslate();
        sead::Matrix34f mtx;
        mtx.makeRT(rotate, translate);
        mtx.getTranslation(pos);
    }
    ball->getRootAi()->getMapUnitParams().setAITreeVariable(
        "TargetPosition", ksys::AIDefParamType::Vec3, pos);
}

void YunBoCannon::leave_() {
    GoronCannonBase::leave_();
}

// NON_MATCHING: same instructions; the SafeString key temporary (adrp/stp) and the actor loads are scheduled
// differently
void YunBoCannon::m36(ksys::act::Actor* ball) {
    const int cannon_spot = *mCannonSpot_m;
    ball->getRootAi()->getMapUnitParams().setAITreeVariable("CannonSpot", ksys::AIDefParamType::Int,
                                                            cannon_spot);
}

void YunBoCannon::loadParams_() {
    GoronCannonBase::loadParams_();
    getStaticParam(&mReturnAnchorName_s, "ReturnAnchorName");
    getMapUnitParam(&mCannonSpot_m, "CannonSpot");
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
