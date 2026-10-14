#include "Game/Actor/AI/aiReferenceNPCViewWithDynAS.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include <cmath>

namespace uking::ai {

ReferenceNPCViewWithDynAS::ReferenceNPCViewWithDynAS(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReferenceNPCViewWithDynAS::~ReferenceNPCViewWithDynAS() = default;

bool ReferenceNPCViewWithDynAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: stack slot of `pos` (the original places it below the param pack)
void ReferenceNPCViewWithDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    if (!sub_710053B7B4(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addString(mParams.mDynASKey_d, "DynASKey", -1);
        changeChild("待機", &pack);
    } else if (sub_710053B8F4(pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addString(mParams.mDynASKey_d, "DynASKey", -1);
        changeChild("待機", &pack);
    } else {
        sub_710053BB30(pos);
    }
}

void ReferenceNPCViewWithDynAS::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReferenceNPCViewWithDynAS::loadParams_() {
    getDynamicParam(&mParams.mDynASKey_d, "DynASKey");
    getStaticParam(&mParams.mTurnStartAngle_s, "TurnStartAngle");
    getStaticParam(&mParams.mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mParams.mDynASKey_d, "DynASKey");
}

bool ReferenceNPCViewWithDynAS::isFinished() const {
    return isCurrentChild("待機") && getCurrentChild()->isFinished();
}

// NON_MATCHING: the original loads the object count and buffer pointer once before the loop (signed index loop)
bool ReferenceNPCViewWithDynAS::sub_710053B7B4(sead::Vector3f* pos) {
    if (_58.hasProcInCalcState()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_58, &accessor);
        accessor.getActorMtx().getTranslation(*pos);
        return true;
    }

    auto* obj = mActor->getMapObject();
    if (!obj)
        return false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (auto* data = obj->getLinkData()) {
        for (auto* linked : data->mObjects) {
            if (!linked)
                continue;
            linked->getActorWithAccessor(accessor);
            if (ksys::act::isNPCProfile(accessor)) {
                accessor.linkAcquire(&_58);
                accessor.getActorMtx().getTranslation(*pos);
                return true;
            }
        }
    }
    return false;
}

// NON_MATCHING: regalloc (the original keeps the front vector in integer registers) and store order of `up`
bool ReferenceNPCViewWithDynAS::sub_710053B8F4(const sead::Vector3f& pos) {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f front(mtx(0, 2), 0, mtx(2, 2));
    front.normalize();

    sead::Vector3f up;
    if (auto* controller = mActor->getCharacterController()) {
        up = -controller->get70();
        if (up.normalize() < sead::Mathf::epsilon())
            up = sead::Vector3f::ey;
    } else {
        up = sead::Vector3f::ey;
    }

    sead::Vector3f dir = pos;
    dir -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.y = 0;
    dir.normalize();
    return front.dot(dir) >= std::cos(*mParams.mTurnStartAngle_s);
}

// 0x710053bb30
void ReferenceNPCViewWithDynAS::sub_710053BB30(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addString(mParams.mDynASKey_d, "DynASKey", -1);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

}  // namespace uking::ai
