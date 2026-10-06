#include "Game/AI/Action/actionAssassinBossIronBallAtkWithRot.h"
#include <math/seadMatrix.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

AssassinBossIronBallAtkWithRot::AssassinBossIronBallAtkWithRot(const InitArg& arg)
    : AssassinBossIronBallAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AssassinBossIronBallAtkWithRot::~AssassinBossIronBallAtkWithRot() {
    ;
}

bool AssassinBossIronBallAtkWithRot::init_(sead::Heap* heap) {
    if (!AssassinBossIronBallAttack::init_(heap))
        return false;
    return _90.init(heap);
}

void AssassinBossIronBallAtkWithRot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinBossIronBallAttack::enter_(params);
    _90.enter(params);
    _f8 = (sead::GlobalRandom::instance()->getU32() & 2) ? 1 : -1;
}

void AssassinBossIronBallAtkWithRot::leave_() {
    AssassinBossIronBallAttack::leave_();
    _90.leave();
}

void AssassinBossIronBallAtkWithRot::loadParams_() {
    AssassinBossIronBallAttack::loadParams_();
    _90.loadParams();
    getStaticParam(&mAddAngle_s, "AddAngle");
    getStaticParam(&mCentralAnchorName_s, "CentralAnchorName");
}

// NON_MATCHING: instruction scheduling / one extra instruction in the rotation
void AssassinBossIronBallAtkWithRot::calc_() {
    AssassinBossIronBallAttack::calc_();

    const sead::Vector3f& target = sub_71005D9330(mActor);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f dir = target - pos;
    const sead::Vector3f angle = *mAddAngle_s * f32(_f8);
    sead::Matrix33f rot;
    rot.makeR(angle);
    _90._5c = pos + rot * dir;
    _90.calc();
}

void AssassinBossIronBallAtkWithRot::m32(sead::Vector3f* angle) {
    *angle = *mAddAngle_s * f32(_f8);
}

void AssassinBossIronBallAtkWithRot::m33(sead::Vector3f* pos) {
    if (auto* obj = ksys::act::findLinkReferenceObj(mActor, mCentralAnchorName_s,
                                                    sead::SafeString::cEmptyString, nullptr)) {
        const sead::Vector3f translate = obj->getTranslate();
        *pos = translate;
    } else {
        mActor->getMtx().getTranslation(*pos);
    }
}

}  // namespace uking::action
