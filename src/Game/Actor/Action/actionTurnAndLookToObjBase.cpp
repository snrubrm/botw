#include "Game/Actor/Action/actionTurnAndLookToObjBase.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

TurnAndLookToObjBase::TurnAndLookToObjBase(const InitArg& arg) : PlayerAction(arg) {}

TurnAndLookToObjBase::~TurnAndLookToObjBase() = default;

bool TurnAndLookToObjBase::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void TurnAndLookToObjBase::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void TurnAndLookToObjBase::leave_() {}

void TurnAndLookToObjBase::loadParams_() {
    getDynamicParam(&mObjectId_d, "ObjectId");
    getDynamicParam(&mFaceId_d, "FaceId");
    getDynamicParam(&mTurnDirection_d, "TurnDirection");
    getDynamicParam(&mIsValid_d, "IsValid");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mPosOffset_d, "PosOffset");
    getDynamicParam(&mTurnPosition_d, "TurnPosition");
}

void TurnAndLookToObjBase::calc_() {}

void TurnAndLookToObjBase::m33() {
    _30 = *mObjectId_d;
    _34 = *mFaceId_d;
    _38.set(sead::Vector3f::zero);
    _68.set(sead::Vector3f::zero);
    _44 = false;
    _45 = *mIsValid_d;
    _48 = mActorName_d;
    _58 = mUniqueName_d;
}

// NON_MATCHING: only the store order of the "" SafeString temporary differs.
bool TurnAndLookToObjBase::m34(ksys::act::BaseProcLink* link, sead::Vector3f* pos,
                               const sead::SafeString& name1, const sead::SafeString& name2) {
    if (!ksys::gdt::Manager::instance()) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return false;
    }

    bool found = false;
    {
        ksys::act::BaseProcMgr::ProcIteratorContext context(
            *ksys::act::BaseProcMgr::instance(),
            ksys::act::BaseProcMgr::ProcFilter::Sleeping |
                ksys::act::BaseProcMgr::ProcFilter::Initializing |
                ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
        while (auto* proc = context.next()) {
            auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
            if (!actor)
                continue;
            if (!(name1 == proc->getName()))
                continue;
            if (!proc->isCalc())
                continue;
            if (!(name2.isEmpty() && !actor->getUniqueName())) {
                if (!actor->getUniqueName())
                    continue;
                if (!(name2 == actor->getUniqueName()))
                    continue;
            }
            link->acquire(proc, false);
            found = true;
        }
    }
    if (found)
        return true;

    ksys::map::Object* obj;
    if (name2.isEmpty())
        obj = ksys::act::findLinkReferenceObj(mActor, name1, "", nullptr);
    else
        obj = ksys::act::findLinkReferenceObj(mActor, name1, name2, nullptr);
    if (!obj)
        return false;
    *pos = sead::Vector3f(obj->getTranslate());
    return true;
}

bool TurnAndLookToObjBase::m35(ksys::act::BaseProcLink* link, sead::Vector3f* pos,
                           const sead::SafeString& name1, const sead::SafeString& name2) {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, name1);
    auto* obj = ksys::act::findLinkReferenceObj(mActor, name1, "", nullptr);
    if (accessor.hasProc()) {
        accessor.linkAcquire(link);
        return true;
    }
    if (!obj)
        return false;
    *pos = sead::Vector3f(obj->getTranslate());
    return true;
}

}  // namespace uking::action
