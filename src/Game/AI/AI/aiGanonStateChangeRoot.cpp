#include "Game/AI/AI/aiGanonStateChangeRoot.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

// Unnamed global constant (47.0f, .rodata 0x7101e79ee8); also read by GanonBattleRoot::sub_71003E3644. Declaration only.
extern const f32 sUnk_7101e79ee8;

namespace uking::ai {

// NON_MATCHING: register numbering of the two xz differences (the original loads both target components before
// the first subtraction).
void GanonStateChangeRoot::sub_71003EEE18() {
    sead::Vector3f destination;
    {
        sead::Vector3f home;
        mActor->getHomePos(&home);
    }
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f direction(position.x - mTargetPos_d->x, 0.0f, position.z - mTargetPos_d->z);
    direction.normalize();
    destination = position + direction * (sUnk_7101e79ee8 * sUnk_7101e79ee8);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(destination, "DstPos", -1);
    pack.addBool(false, "IsChangeable", -1);
    changeChild("壁に向かう", &pack);
}

GanonStateChangeRoot::GanonStateChangeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonStateChangeRoot::~GanonStateChangeRoot() = default;

bool GanonStateChangeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonStateChangeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        const sead::Vector3f up = sead::Vector3f::ey;
        controller->sub_7100F5EE1C(up * -29.0f);
        controller->sub_7100F5EDE8(up);
    }
    sub_71003EEE18();
    _40 = 600.0f;
}

void GanonStateChangeRoot::changeToWallCling() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    sub_71002C64A0(&pos, mActor);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("壁張り付き", &pack);
}

void GanonStateChangeRoot::calc_() {
    sub_71005DB3EC(mActor);
    if (isCurrentChild("壁に向かう")) {
        sead::Vector3f home;
        mActor->getHomePos(&home);
        const sead::Vector3f& position = mActor->getMtx().getTranslation();
        const f32 dx = position.x - home.x;
        const f32 dz = position.z - home.z;
        if (dx * dx + dz * dz >= (sUnk_7101e79ee8 - 10.0f) * (sUnk_7101e79ee8 - 10.0f))
            changeToWallCling();
        ksys::Timer::update(&_40, -1.0f);
        if (_40 < 0)
            setFailed();
    } else {
        sead::Vector3f pos;
        sub_71002C64A0(&pos, mActor);
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFinished();
    }
}

void GanonStateChangeRoot::leave_() {
    sub_71005DB434(mActor);
}

void GanonStateChangeRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
