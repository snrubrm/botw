#include "Game/Actor/AI/aiRemainsWindBatteryAttack.h"
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Utils/MathUtil.h"
#include <gsys/gsysModel.h>
#include "KingSystem/Map/mapObjectLink.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::ai {

RemainsWindBatteryAttack::RemainsWindBatteryAttack(const InitArg& arg)
    : GuardianCommonBeamAttack(arg) {}

RemainsWindBatteryAttack::~RemainsWindBatteryAttack() {
    for (s32 i = 0; i < 5; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38[i], &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool RemainsWindBatteryAttack::init_(sead::Heap* heap) {
    if (!GuardianCommonBeamAttack::init_(heap))
        return false;
    auto* actor = mActor;
    ksys::act::InstParamPack pack;
    ksys::act::ActorCreator::setCreatePriorityState1(pack, actor);
    for (s32 i = 0; i < 5; ++i) {
        auto* created = ksys::act::ActorCreator::instance()->createActor(
            "GuardianBeam_RemainsWind", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
            &pack, true, false);
        if (!created)
            continue;
        if (auto* beam = sead::DynamicCast<act::Beam>(created)) {
            beam->sub_7100002DA8(actor);
            beam->sub_7100003804(actor, "Head");
        }
        _38[i].acquire(created, false);
    }
    if (actor->getModel())
        _88.search(actor->getModel(), "Head");
    return true;
}

void RemainsWindBatteryAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianCommonBeamAttack::enter_(params);
    changeChild("待機");
}

void RemainsWindBatteryAttack::leave_() {
    GuardianCommonBeamAttack::leave_();
}

void RemainsWindBatteryAttack::loadParams_() {
    GuardianCommonBeamAttack::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// 0x710054cc78
// NON_MATCHING: the 発射 / 待機 choice is a csel here; the original branches into the shared changeChild call
void RemainsWindBatteryAttack::calc_() {
    GuardianCommonBeamAttack::calc_();
    // discarded expression: the original evaluates it (the flag load stays) without using the result
    mActor->get1a0() || (mActor->getMapObject() &&
                         mActor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000));
    auto* child = getCurrentChild();
    isCurrentChild("チャージ");
    if (!child)
        return;
    if (child->isFinished() || child->isFailed()) {
        if (!child->isFinished()) {
            changeChild("待機");
            return;
        }
        if (isCurrentChild("待機")) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("照準準備", &params);
        } else if (isCurrentChild("照準準備")) {
            sub_710054CFB0(false);
        } else if (isCurrentChild("照準")) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("チャージ", &params);
        } else if (isCurrentChild("チャージ")) {
            changeChild(sub_710054D19C() ? "発射" : "待機");
        } else if (isCurrentChild("発射")) {
            sub_710054CFB0(false);
        } else {
            changeChild("待機");
        }
    } else if (isCurrentChild("照準") || isCurrentChild("照準準備")) {
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

// 0x710054cfb0
void RemainsWindBatteryAttack::sub_710054CFB0(bool prepare) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild(prepare ? "照準準備" : "照準", &params);
    if (prepare)
        return;
    if (!ksys::act::isPlayerProfile(&sub_71005D94AC(mActor)))
        return;
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return;
    for (auto*& linked : object->getLinkData()->mObjects) {
        if (!linked)
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        linked->getActorWithAccessor(accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800000e), nullptr);
    }
}

// 0x710054d19c
bool RemainsWindBatteryAttack::sub_710054D19C() {
    const s32 index = sub_710054D36C();
    if (index < 0)
        return false;
    sead::Vector3f pos;
    if (_88.isValid()) {
        sead::Matrix34f bone_mtx;
        mActor->getModel()->getBoneWorldMatrix(_88.getKey(), &bone_mtx);
        bone_mtx.getTranslation(pos);
    } else {
        mActor->getMtx().getTranslation(pos);
    }
    sead::Vector3f dir = *mTargetPos_d - pos;
    const f32 distance = dir.length();
    if (distance > 0.0f)
        dir *= 1.0f / distance;
    else
        mActor->getMtx().getBase(dir, 0);
    sead::Matrix34f mtx;
    ksys::util::sub_71011F0260(&mtx, dir, sead::Vector3f::ey, pos, false);
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_38[index], &accessor);
    const bool ok = accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
    act::sub_7100003B1C(accessor, distance);
    return ok;
}

// 0x710054d36c
s32 RemainsWindBatteryAttack::sub_710054D36C() {
    for (s32 i = 0; i < 5; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38[i], &accessor);
        if (accessor.isStateSleep())
            return i;
    }
    return -1;
}

}  // namespace uking::ai
