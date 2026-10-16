#include "Game/Actor/AI/aiSiteBossLswordTornadoRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

// 0x71002d2a80 (SiteBoss TU; declared only)
bool sub_71002D2A80();

namespace uking::ai {

SiteBossLswordTornadoRoot::SiteBossLswordTornadoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossLswordTornadoRoot::~SiteBossLswordTornadoRoot() = default;

bool SiteBossLswordTornadoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossLswordTornadoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.reset(0x40000);
    sub_710057DD54();
}

// 0x710057def4
// NON_MATCHING: stack slots of the up / direction vectors (the original keeps the negated up vector in registers
// until the fallback and copies the target through a temporary)
void SiteBossLswordTornadoRoot::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f up = -controller->get70();
    if (up.normalize() < sead::Mathf::epsilon())
        up = sead::Vector3f::ey;
    sub_710073FA94(&_50, mActor);
    sead::Vector3f dir = *mTargetPos_d;
    dir -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();
    if (!isCurrentChild("移動")) {
        sub_710074006C(&_50, dir, up, true, 0.16f, sead::Mathf::pi2(), 0.0f);
        sub_7100740E04(_50, controller);
    }

    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }
    if (isCurrentChild("待機")) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (!enemy || !enemy->getActorPartsActor("SiteBossBigFlameBall0").hasProc())
            return;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor("SiteBossBigFlameBall0"), &accessor);
        if (accessor.isStateSleep() && sub_71002D2A80())
            setFinished();
        return;
    }
    if (!child->isFinished() && !child->isFailed())
        return;
    if (child->isFailed()) {
        setFailed();
        return;
    }
    if (isCurrentChild("火炎渦開始")) {
        sub_710057E398();
    } else if (isCurrentChild("移動")) {
        ksys::act::ai::InlineParamPack params;
        params.addString("SiteBossBigFlameBall0", "PartsName", -1);
        changeChild("火炎渦開始", &params);
    } else if (isCurrentChild("放出")) {
        sub_710057E4F0();
    }
}

// NON_MATCHING: register allocation and the block order around isStateSleep()
void SiteBossLswordTornadoRoot::leave_() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    if (!enemy->getActorPartsActor("SiteBossBigFlameBall0").hasProc())
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->getActorPartsActor("SiteBossBigFlameBall0"), &accessor);
    if (!accessor.isStateSleep())
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr, true);
}

void SiteBossLswordTornadoRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mDestPos_d, "DestPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SiteBossLswordTornadoRoot::sub_710057DD54() {
    _88 = ksys::Timer(90, 90);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(*mDestPos_d, "MoveDstPos", -1);
    params.addInt(0, "RailIndex", -1);
    params.addBool(false, "IsReturnHome", -1);
    params.addBool(false, "IsForceWarp", -1);
    params.addBool(false, "IsPartsActorTgOn", -1);
    params.addBool(false, "IsPartsWarpEffectSync", -1);
    changeChild("移動", &params);
}

// 0x710057e4f0
void SiteBossLswordTornadoRoot::sub_710057E4F0() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(false, "IsResetEndTime", -1);
    changeChild("待機", &pack);
}

// 0x710057e398
void SiteBossLswordTornadoRoot::sub_710057E398() {
    ksys::act::ai::InlineParamPack pack;
    pack.addPointer(nullptr, "AttackActor", ksys::AIDefParamType::BaseProcHandle, -1);
    pack.addBool(false, "IsThrowChildDevice", -1);
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    pack.addString("SiteBossBigFlameBall0", "PartsName", -1);
    changeChild("放出", &pack);
}

}  // namespace uking::ai
