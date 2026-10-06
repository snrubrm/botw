#include "Game/AI/Action/actionDemoBeastGanonGrudgeDrop.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

DemoBeastGanonGrudgeDrop::DemoBeastGanonGrudgeDrop(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoBeastGanonGrudgeDrop::~DemoBeastGanonGrudgeDrop() = default;

bool DemoBeastGanonGrudgeDrop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoBeastGanonGrudgeDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_d.cstr(), true, 0, 0, -1.0f);
    _60 = f32(*mTimer_d);
    auto* creator = ksys::act::ActorCreator::instance();
    if (!creator) {
        setFailed();
        return;
    }

    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    creator->requestCreateActor(mGrudeRainObject_s.cstr(),
                                ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_50, &pack,
                                nullptr, 1);
    _64 = 0;
}

void DemoBeastGanonGrudgeDrop::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoBeastGanonGrudgeDrop::loadParams_() {
    getStaticParam(&mGrudeRainObject_s, "GrudeRainObject");
    getDynamicParam(&mTimer_d, "Timer");
    getDynamicParam(&mASName_d, "ASName");
    getDynamicParam(&mFallPoint1_d, "FallPoint1");
}

void DemoBeastGanonGrudgeDrop::calc_() {
    switch (_64) {
    case 0:
        if (_50.hasProcCreationFailed()) {
            setFailed();
        } else if (_50.isProcReady()) {
            const sead::Vector3f fall_point = *mFallPoint1_d;
            sead::Matrix34f mtx = mActor->getMtx();
            sead::Vector3f pos = fall_point;
            pos.rotate(mtx);
            pos += mtx.getTranslation();
            mtx.setTranslation(pos);
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_50.releaseAndWakeProc())) {
                const sead::Vector3f scale = sead::Vector3f::ones;
                actor->setMatrix(mtx, &scale);
                actor->sub_71011C9964(mActor);
                _64 = 1;
            } else {
                setFailed();
                return;
            }
        }
        break;
    case 1:
        ksys::Timer::update(&_60, -1.0f);
        if (_60 <= 0.0f)
            setFinished();
        break;
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
