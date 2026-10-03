#include "Game/AI/AI/aiLimitedTimeredActorCreator.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiParam.h"

namespace uking::ai {

LimitedTimeredActorCreator::LimitedTimeredActorCreator(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LimitedTimeredActorCreator::~LimitedTimeredActorCreator() {
    *static_cast<void**>(mGeneratedActorLink_a) = nullptr;
    _a0.freeBuffer();
}

bool LimitedTimeredActorCreator::init_(sead::Heap* heap) {
    _a0.tryAllocBuffer(*mCreateLimit_m, heap);
    _78.mTimer = ksys::Timer(1, 1);
    return true;
}

void LimitedTimeredActorCreator::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_78.mTimer.value <= sead::Mathf::epsilon()) {
        f32 time = *mCreateTimer_s;
        const f32 rand = *mCreateTimerRand_s;
        if (rand > 0.0f)
            time += rand * sead::GlobalRandom::instance()->getF32();
        _78.mTimer = ksys::Timer(time, time);
    }
    *static_cast<void**>(mGeneratedActorLink_a) = nullptr;
    createOneActor();
    changeChild("待機");
}

void LimitedTimeredActorCreator::calc_() {
    if (!(_78.mTimer.value <= sead::Mathf::epsilon()))
        _78.sub_7100D3BCE4();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("生成")) {
            if (_78.mTimer.value <= sead::Mathf::epsilon()) {
                f32 time = *mCreateTimer_s;
                const f32 rand = *mCreateTimerRand_s;
                if (rand > 0.0f)
                    time += rand * sead::GlobalRandom::instance()->getF32();
                _78.mTimer = ksys::Timer(time, time);
            }
            *static_cast<void**>(mGeneratedActorLink_a) = nullptr;
            createOneActor();
            changeChild("待機");
        }
        return;
    }

    if (!child->isChangeable() || !isCurrentChild("待機"))
        return;

    if (_90.isAllocatedOrFailed()) {
        if (_90.isProcReady()) {
            if (_78.mTimer.value <= sead::Mathf::epsilon())
                changeToCreate();
            return;
        }
        if (!_90.hasProcCreationFailed())
            return;
        _90.deleteProc();
    }
    createOneActor();
}

void LimitedTimeredActorCreator::leave_() {
    *static_cast<void**>(mGeneratedActorLink_a) = nullptr;
}

void LimitedTimeredActorCreator::loadParams_() {
    getStaticParam(&mCreateTimer_s, "CreateTimer");
    getStaticParam(&mCreateTimerRand_s, "CreateTimerRand");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getMapUnitParam(&mCreateLimit_m, "CreateLimit");
    getMapUnitParam(&mActorName_m, "ActorName");
    getAITreeVariable(&mGeneratedActorLink_a, "GeneratedActorLink");
}

void LimitedTimeredActorCreator::createOneActor() {
    sead::SafeString name;
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    if (!ksys::eco::getEcosystemActorName(&name, mActorName_m.isEmpty() ? mCreateActorName_s : mActorName_m,
                                          home_pos)) {
        return;
    }

    bool has_free_link = false;
    for (int i = 0, n = _a0.size(); i < n; ++i) {
        if (!_a0[i].mLink.hasProc()) {
            has_free_link = true;
            break;
        }
    }
    if (!has_free_link)
        return;

    if (_90.isAllocatedOrFailed()) {
        if (!_90.hasProcCreationFailed())
            return;
        _90.deleteProc();
    }

    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    ksys::act::ActorCreator::instance()->requestCreateActor(
        name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_90, &pack, nullptr,
        1);
}

void LimitedTimeredActorCreator::changeToCreate() {
    Unk_7102370e70* link = nullptr;
    for (int i = 0, n = _a0.size(); i < n; ++i) {
        if (!_a0[i].mLink.hasProc()) {
            link = &_a0[i];
            break;
        }
    }
    *static_cast<Unk_7102370e70**>(mGeneratedActorLink_a) = link;

    ksys::act::ai::InlineParamPack pack;
    pack.addPointer(&_90, "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    changeChild("生成", &pack);
}

}  // namespace uking::ai
