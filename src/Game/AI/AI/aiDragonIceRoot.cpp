#include "Game/AI/AI/aiDragonIceRoot.h"
#include "Game/Actor/actDragon.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

DragonIceRoot::DragonIceRoot(const InitArg& arg) : DragonRoot(arg) {}

DragonIceRoot::~DragonIceRoot() = default;

bool DragonIceRoot::init_(sead::Heap* heap) {
    if (!DragonRoot::init_(heap))
        return false;

    _3c0 = 99999.0f;
    const s32 num = *mGrudgeBulletMaxNum_s;
    if (num > 0)
        _260._0.tryAllocBuffer(num, heap);
    return true;
}

void DragonIceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRoot::enter_(params);
}

void DragonIceRoot::leave_() {
    DragonRoot::leave_();
}

void DragonIceRoot::loadParams_() {
    DragonRoot::loadParams_();
    getStaticParam(&mGrudgeBulletMaxNum_s, "GrudgeBulletMaxNum");
    getStaticParam(&mGrudgeBulletMinInterval_s, "GrudgeBulletMinInterval");
    getStaticParam(&mGrudgeSmokeTime_s, "GrudgeSmokeTime");
    getStaticParam(&mGrudgeEventRail_pre1stSpeed_s, "GrudgeEventRail_pre1stSpeed");
    getStaticParam(&mGrudgeEventRail_1stSpeed_s, "GrudgeEventRail_1stSpeed");
    getStaticParam(&mGrudgeEventRail_pre2ndSpeed_s, "GrudgeEventRail_pre2ndSpeed");
    getStaticParam(&mGrudgeEventRail_2ndSpeed_s, "GrudgeEventRail_2ndSpeed");
    getStaticParam(&mGrudgeEventRail_pre3rdSpeed_s, "GrudgeEventRail_pre3rdSpeed");
    getStaticParam(&mGrudgeEventRail_3rdSpeed_s, "GrudgeEventRail_3rdSpeed");
    getStaticParam(&mGrudgeEventRail_preEndSpeed_s, "GrudgeEventRail_preEndSpeed");
    getStaticParam(&mGrudgeEventRail_EndSpeed_s, "GrudgeEventRail_EndSpeed");
    getStaticParam(&mGrudgeEventRail_ReturnSpeed_s, "GrudgeEventRail_ReturnSpeed");
    getStaticParam(&mGrudgeBulletRate_s, "GrudgeBulletRate");
    getStaticParam(&mGrudgeEventRail_Start_s, "GrudgeEventRail_Start");
    getStaticParam(&mGrudgeEventRail_pre1st_s, "GrudgeEventRail_pre1st");
    getStaticParam(&mGrudgeEventRail_1st_s, "GrudgeEventRail_1st");
    getStaticParam(&mGrudgeEventRail_pre2nd_s, "GrudgeEventRail_pre2nd");
    getStaticParam(&mGrudgeEventRail_2nd_s, "GrudgeEventRail_2nd");
    getStaticParam(&mGrudgeEventRail_pre3rd_s, "GrudgeEventRail_pre3rd");
    getStaticParam(&mGrudgeEventRail_3rd_s, "GrudgeEventRail_3rd");
    getStaticParam(&mGrudgeEventRail_preEnd_s, "GrudgeEventRail_preEnd");
    getStaticParam(&mGrudgeEventRail_End_s, "GrudgeEventRail_End");
    getStaticParam(&mGrudgeEventRail_ReturnToSky_s, "GrudgeEventRail_ReturnToSky");
    getStaticParam(&mGrudgeBulletActorName_s, "GrudgeBulletActorName");
}

bool DragonIceRoot::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!DragonRoot::reenter_(other, true))
        return false;
    auto* root = sead::DynamicCast<DragonIceRoot>(other);
    if (!root)
        return false;
    if (!sead::DynamicCast<act::Dragon>(root->mActor))
        return false;
    if (!sead::DynamicCast<act::Dragon>(mActor))
        return false;

    _3bc = root->_3bc;
    _3c0 = root->_3c0;
    _3c4 = root->_3c4;
    _3c8 = root->_3c8;
    return true;
}

void DragonIceRoot::m41() {
    DragonRoot::m41();
}

void DragonIceRoot::m44(const sead::Vector3f& pos) {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon || dragon->_1e0c == 3)
        return;

    ksys::act::InstParamPack pack;
    pack->addPosition(pos);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "DragonIceBall", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, &pack,
        nullptr, 2);
}

}  // namespace uking::ai
