#include "Game/AI/Action/actionDemoEnemyReset.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

DemoEnemyReset::DemoEnemyReset(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoEnemyReset::~DemoEnemyReset() = default;

bool DemoEnemyReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoEnemyReset::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getASList()->sub_710115AA68("Noise_Demo"))
        playAS("Noise_Demo", true, 0, 0, -1.0f);
    else
        playAS("Wait", false, 0, 0, -1.0f);

    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* handler = actor->_868) {
            if (handler->sub_71006ED9EC())
                handler->sub_71006EDCB8();
        }
        if (auto* unit = actor->m159()) {
            for (int i = 0; i < 12; ++i)
                unit->m13(i);
        }
        sead::Matrix34f mtx;
        actor->getHomeMtx(&mtx);
        if (actor->getPhysics())
            actor->getPhysics()->setMtxAndScale(mtx, false, false, mActor->getScale().x);
        ksys::act::sub_7100EE5A14(actor, sead::Vector3f::zero);
        ksys::act::sub_7100EE5980(actor, sead::Vector3f::zero);
    }
    _1c = true;
}

void DemoEnemyReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoEnemyReset::loadParams_() {}

void DemoEnemyReset::calc_() {
    if (_1c)
        _1c = false;
    else
        setFinished();
}

}  // namespace uking::action
