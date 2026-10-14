#include "KingSystem/ActorSystem/actActorNameSearch.h"
#include <cfloat>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSystem.h"

namespace ksys::act {

ActorNearestSearch::ActorNearestSearch(const char* unique_name, Actor* actor, BaseProc** result,
                                     const sead::Vector3f& origin)
    : mOrigin(origin), mClosestDistance(0.0f), mCount(0), mUniqueName(unique_name), mActor(actor),
      mResult(result) {
    mName = sead::SafeString::cEmptyString;
    if (mActor) {
        mName = mActor->getName();
        auto* gparam = mActor->getParam()->getRes().mGParamList;
        if (gparam && gparam->getSystem()) {
            const auto& group_name = gparam->getSystem()->mSameGroupActorName.ref();
            if (!group_name.isEmpty())
                mName = group_name;
        }
        mActor->getMtx().getTranslation(mOrigin);
    }
    mClosestDistance = FLT_MAX;
}

void ActorNearestSearch::sub_7100EDC810(BaseProc* proc) {
    if (!proc || !mResult)
        return;
    auto* actor = sead::DynamicCast<Actor>(proc);
    if (!actor || actor->getActorFlags2().isOn(Actor::ActorFlag2::_200))
        return;
    if (!isWeaponOrArmor(actor) && !actor->getMapObject())
        return;
    if (mUniqueName.isEmpty()) {
        const f32 distance = (mOrigin - actor->getMtx().getTranslation()).length();
        if (!(distance < mClosestDistance))
            return;
        *mResult = proc;
        mClosestDistance = distance;
    } else {
        const char* unique_name = actor->getUniqueName();
        if (!unique_name || mUniqueName != unique_name)
            return;
        *mResult = proc;
    }
    ++mCount;
}

void ActorNearestSearch::sub_7100EDC9E8(BaseProc* proc) {
    if (!proc || !mResult)
        return;
    auto* actor = sead::DynamicCast<Actor>(proc);
    if (!actor || !mActor)
        return;
    const f32 distance =
        (mActor->getMtx().getTranslation() - actor->getMtx().getTranslation()).length();
    if (distance < mClosestDistance) {
        *mResult = proc;
        mClosestDistance = distance;
    }
}

}  // namespace ksys::act
