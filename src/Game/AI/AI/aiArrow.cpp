#include "Game/AI/AI/aiArrow.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"

namespace uking::ai {

// NON_MATCHING: the original zeroes 0xf0-0x198 with one memset; ours stores the first xlink handle
// separately (memset from 0x110)
Arrow::Arrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Arrow::~Arrow() {
    _f0.fadeXLink();
    _110.fadeXLink();
    _130.fadeXLink();
    _150.fadeXLink();
    sub_7100463940();
}

void Arrow::sub_7100463940() {
    if (_170.sub_7101241AD8(0))
        xlink::fade(_170.mELink, -1);
}

bool Arrow::init_(sead::Heap* heap) {
    spawnElectricWaterBall();
    return true;
}

void Arrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool Arrow::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void Arrow::leave_() {
    if (_1a8.isAllocatedOrFailed())
        _1a8.deleteProc();
    sub_7100463940();
}

void Arrow::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mStickTime_s, "StickTime");
    getStaticParam(&mGroundHitTime_s, "GroundHitTime");
    getStaticParam(&mKillFireTime_s, "KillFireTime");
}

void Arrow::spawnElectricWaterBall() {
    if (_b9 || _1a8.isAllocatedOrFailed())
        return;

    auto* chemical = mActor->sub_71011D8A44(0);
    if (!chemical)
        return;

    if (!(((chemical->mMaterial->attribute.ref() & 0x108) == 0x108 && !(chemical->_be & 4)) ||
          chemical->_1b8 > 0.0f))
        return;

    ksys::act::InstParamPack pack;
    pack->add(0, "AttackPower");
    pack->add(1.0f, "ScaleTime");
    pack->add(0.0f, "Range");
    ksys::act::ActorCreator::addScale(pack, 1.0f);
    pack->addResourceLane(2);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "ElectricWaterBall", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_1a8, &pack,
        nullptr, 2);
}

void Arrow::m37() {
    _150.fadeXLink();
    _130.fadeXLink();
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->_c0 != 4)
            chemical->sub_7100D909A4();
    }
    sub_7100463940();
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2c, false);
    mActor->setFlag(ksys::act::Actor::ActorFlag::_20, true);
    changeChild("爆発");
}

bool Arrow::m38() {
    auto* chemical = mActor->getChemicalStuff();
    if (!chemical)
        return false;
    return chemical->mMaterial->attribute.ref() & 0x10;
}

void Arrow::m39() {
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D90FF0(false);
}

}  // namespace uking::ai
