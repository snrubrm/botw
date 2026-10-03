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
    _158.search(mActor->getModel(), "Hole");
    _232 = 0;
    _230 = 0;
    sub_710060F440();
    _230 &= 0xff98;
    changeChild("待機");
}

void YunBoCannon::calc_() {
    GoronCannonBase::calc_();
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (!_220.hasProc())
        sub_710060F440();
    if (_230 & 4)
        _230 &= 0xffef;

    if (*mCannonSpot_m == 0 && ksys::gdt::getFlag_Fire_Relic_CannonReset_For_Bridge(false)) {
        ksys::gdt::setFlag_Fire_Relic_CannonReset_For_Bridge(false, false);
        if (isCurrentChild("装填口開放") || isCurrentChild("装填完了")) {
            _230 &= 0xff98;
            changeChild("待機");
            return;
        }
    }

    if (isCurrentChild("待機")) {
        const bool basic_sig = actor->checkBasicSig();
        u16 flags = _230;
        if (basic_sig) {
            flags |= 0x40;
            _230 = flags;
            auto* model = actor->getModel();
            sead::Matrix34f mtx = actor->getMtx();
            if (model && _158.isValid()) {
                model->getUnits()
                    .unsafeAt(_158.getKey().model_unit_index)
                    ->mModelUnit->getBoneWorldMatrix(&mtx, _158.getKey().bone_index);
            }
            sub_710060FAE0(mtx, 0x8000063, false);
            flags = _230;
        }
        if ((flags & 0x41) == 0x41) {
            _230 &= 0xff98;
            changeChild("装填口開放");
            return;
        }
    }

    if (isCurrentChild("装填口開放")) {
        if (actor->checkBasicSig()) {
            if (_230 & 2) {
                _230 &= 0xfffe;
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
            sub_710060FAE0(mtx, 0x8000064, false);
            if (_230 & 0x20) {
                _230 &= 0xff98;
                changeChild("ユン坊離脱");
                return;
            }
        }
    }

    if (isCurrentChild("装填完了")) {
        if (_108 && _109 && !(_230 & 0x10)) {
            sead::Matrix34f mtx = actor->getMtx();
            sub_710060FAE0(mtx, 0x8000066, false);
            sub_710032D5FC();
            _230 &= 0xff98;
            _108 = false;
            _109 = false;
            changeChild("発射");
            return;
        }
        if (!(_230 & 2) || !actor->checkBasicSig()) {
            sead::Matrix34f mtx = actor->getMtx();
            if (auto* anchor = findDestinationAnchor(mReturnAnchorName_s.cstr())) {
                const sead::Vector3f rotate = anchor->getRotate();
                const sead::Vector3f translate = anchor->getTranslate();
                mtx.makeRT(rotate, translate);
            }
            sub_710060FAE0(mtx, 0x8000064, false);
            const u16 flags = _230;
            _230 = flags | 0x10;
            if (flags & 0x20) {
                _230 &= 0xff98;
                changeChild("装填完了後ユン坊離脱");
                return;
            }
        }
    }

    if (isCurrentChild("発射") || isCurrentChild("ユン坊離脱") ||
        isCurrentChild("装填完了後ユン坊離脱")) {
        if (child->isFinishedOrFailed()) {
            _230 &= 0xff98;
            changeChild("待機");
        }
    }
}

// NON_MATCHING: the original computes `this + 0x1f0` after the payload lock; ours before (register assignment)
bool YunBoCannon::sub_710060F440() {
    auto* actor = mActor;
    _1f0._18.y(actor);
    _220.reset();
    sub_71005E02E0(actor, &_1f0, &_220);
    if (_220.hasProcInCalcState())
        return true;
    _220.reset();
    return false;
}

void YunBoCannon::sub_710060FAE0(const sead::Matrix34f& mtx, u32 type, bool a3) {
    auto* actor = mActor;
    if (!_220.hasProc())
        return;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_190._18.mLock);
        _190._18._0.acquire(actor, false);
        _190._18._10 = mtx;
    }
    _190._10 = ksys::MessageType(type);

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_220, &accessor);
    if (accessor.hasProc()) {
        if (a3)
            _190.sub_710070DFD8(accessor, true);
        else
            _190.sub_710070DD78(accessor, true);
    }
}

// NON_MATCHING: the shared `_230 = _230 & 0xff98` / store tail is merged differently (one extra strh)
bool YunBoCannon::handleMessage_(const ksys::Message& message) {
    auto* actor = mActor;
    switch (message.getType()) {
    case 0x800005e:
        if (_230 & 0x40) {
            _230 |= 1;
            break;
        }
        [[fallthrough]];
    case 0x8000063:
        _230 &= 0xff98;
        break;
    case 0x8000060:
        _230 |= 0x20;
        break;
    case 0x8000068: {
        sead::Matrix34f mtx = actor->getMtx();
        if (auto* anchor = findDestinationAnchor(mReturnAnchorName_s.cstr())) {
            const sead::Vector3f rotate = anchor->getRotate();
            const sead::Vector3f translate = anchor->getTranslate();
            mtx.makeRT(rotate, translate);
        }
        sub_710060FAE0(mtx, 0x8000065, true);
        break;
    }
    case 0x800005f:
        _230 |= 2;
        break;
    case 0x8000061:
        _230 |= 4;
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
