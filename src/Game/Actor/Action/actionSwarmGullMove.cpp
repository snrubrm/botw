#include "Game/Actor/Action/actionSwarmGullMove.h"
#include <aal/aalListener.h>
#include <aal/aalListenerMgr.h>
#include <aal/aalSystemAccessor.h>
#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2Locator.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710072A944.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

SwarmGullMove::SwarmGullMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwarmGullMove::~SwarmGullMove() {
    _1b0.freeBuffer();
}

bool SwarmGullMove::init_(sead::Heap* heap) {
    return _1b0.tryAllocBuffer(3, heap);
}

void SwarmGullMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwarmGullMove::leave_() {
    sub_71002868BC();
    for (auto& gull : _70) {
        if (gull._0.isAllocatedOrFailed()) {
            gull._0.deleteProc();
            if (gull._10) {
                sub_7100287830(&gull);
                gull._10->m10();
            }
        }
    }
}

void SwarmGullMove::loadParams_() {
    getStaticParam(&mParams.mASName_s, "ASName");
    getMapUnitParam(&mParams.mSubUnitNum_m, "SubUnitNum");
    getMapUnitParam(&mParams.mCreateMaxRadius_m, "CreateMaxRadius");
    getMapUnitParam(&mParams.mCreateMinRadius_m, "CreateMinRadius");
    getMapUnitParam(&mParams.mCreateHeightRange_m, "CreateHeightRange");
    getMapUnitParam(&mParams.mRoundMaxRadius_m, "RoundMaxRadius");
    getMapUnitParam(&mParams.mRoundMinRadius_m, "RoundMinRadius");
    getMapUnitParam(&mParams.mCrySoundIntervalMin_m, "CrySoundIntervalMin");
    getMapUnitParam(&mParams.mCrySoundIntervalMax_m, "CrySoundIntervalMax");
}

void SwarmGullMove::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SwarmGullMove::sub_71002870D4(const sead::Vector3f& pos) {
    f32 distance = 0.0f;
    if (auto* listener_mgr = aal::SystemAccessor::getListenerMgr()) {
        if (auto* listener = listener_mgr->getListener(0)) {
            distance = listener->calcLocalDistance(pos);
            if (distance > 60.0f)
                return false;
        }
    }

    if (!_1b0.isFull()) {
        if (auto* point = _1b0.emplaceBack()) {
            point->distance = distance;
            point->pos = pos;
            return true;
        }
    }

    _1b0.insertionSort(
        [](const CryPoint* a, const CryPoint* b) { return a->distance > b->distance; });

    if (_1b0.size() > 0) {
        auto* farthest = _1b0.back();
        if (farthest && farthest->distance > distance) {
            farthest->distance = distance;
            farthest->pos = pos;
            return true;
        }
    }
    return false;
}

void SwarmGullMove::sub_71002868BC() {
    for (auto& gull : _70) {
        if (!gull._0.isProcReady()) {
            if (gull._0.hasProcCreationFailed())
                gull._0.deleteProcIfFailed();
            continue;
        }

        auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(gull._0.getProc());
        auto* object = gull._10;
        if (!actor || !object)
            continue;

        sead::Matrix34f mtx = object->mMtx;
        sead::Vector3f pos;
        mtx.getTranslation(pos);
        f32 height;
        if (sub_710072C21C(&height, &pos) == 2 && pos.y < height + 0.1f) {
            pos.y = height + 0.1f;
            mtx.setTranslation(pos);
        }
        actor->clearFadeInCreate();
        actor->setMatrix(mtx, nullptr);
        actor->setVelocity(&object->mVelocity, nullptr);
        swarmDropTableStuff(actor);
        gull._0.releaseAndWakeProc();
        object->m10();
    }
}

void SwarmGullMove::sub_7100287290() {
    if (_1b0.size() == 0)
        return;
    if (auto* xlink = mActor->getXLink()) {
        if (auto* user = xlink->_50) {
            xlink2::Locator locator;
            if (user->searchAsset(&locator, "flap")) {
                for (auto& point : _1b0) {
                    xlink2::HandleSLink handle;
                    user->emit(locator, &handle);
                    handle.setPosition(point.pos);
                }
            }
        }
    }
    _1b0.clear();
}

}  // namespace uking::action
