#include "Game/AI/AI/aiEscapeFromTargetFront.h"
#include <cmath>
#include "Game/Actor/actCameraUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace ksys {
// Source namespace inferred from the CameraMgr helper family; declarations only.
f32 sub_7100D8C888();
f32 sub_7100D8C8FC();
}

namespace uking::ai {

EscapeFromTargetFront::EscapeFromTargetFront(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EscapeFromTargetFront::~EscapeFromTargetFront() = default;

bool EscapeFromTargetFront::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EscapeFromTargetFront::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = 0;
    const int dir = m34();
    const sead::Vector3f& target_pos = sub_71005D9330(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    pack.addInt(dir, "RotDir", -1);
    changeChild("回転移動", &pack);
}

// NON_MATCHING: Actor position loads precede the target getter, and finish paths share an epilogue.
void EscapeFromTargetFront::calc_() {
    ksys::Timer::update(&_58, 1.0f);
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        setFinished();
        return;
    }
    if (child->isChangeable()) {
        if (_58 >= f32(*mMaxTime_s)) {
            setFinished();
            return;
        }
        if (_58 >= f32(*mMinTime_s)) {
            sead::Vector3f front;
            sub_71003C8338(&front);
            sead::Vector3f direction = mActor->getMtx().getTranslation() - sub_71005D9330(mActor);
            direction.y = 0;
            direction.normalize();
            auto* link = sub_71005D9050(mActor);
            f32 angle;
            if (link && *mUseCameraFrontByTargetPlayer_s && ksys::act::isPlayerProfile(link)) {
                const f32 fovy = ksys::sub_7100D8C888();
                angle = sub_7100924C08(fovy, ksys::sub_7100D8C8FC()) * 0.5f;
            } else {
                angle = *mFrontAngle_s;
            }
            if (!(direction.dot(front) >= std::cos(angle))) {
                setFinished();
                return;
            }
        }
    }
    child = getCurrentChild();
    child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

void EscapeFromTargetFront::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EscapeFromTargetFront::loadParams_() {
    getStaticParam(&mMaxTime_s, "MaxTime");
    getStaticParam(&mMinTime_s, "MinTime");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mUseCameraFrontByTargetPlayer_s, "UseCameraFrontByTargetPlayer");
}

// NON_MATCHING: the original evaluates `link != nullptr` and the flag together (`cmp x0, #0; ccmp w8, #0, #4, ne`,
// the flag load before the null test); ours branches on the link first. Everything after matches in structure.
void EscapeFromTargetFront::sub_71003C8338(sead::Vector3f* out) {
    sead::Vector3f v;
    auto* link = sub_71005D9050(mActor);
    if (link && *mUseCameraFrontByTargetPlayer_s && ksys::act::isPlayerProfile(link)) {
        ksys::sub_7100D8C7FC(&v);
        v.y = 0;
        v.normalize();
    } else {
        const auto& mtx = sub_71005D96A8(mActor);
        v.x = mtx.m[0][2];
        v.y = 0.0f;
        v.z = mtx.m[2][2];
        v.normalize();
    }
    *out = v;
}

// NON_MATCHING: the target keeps branches for the 1/-1/0 result (select here) and swaps d8/d9
int EscapeFromTargetFront::m34() {
    sead::Vector3f front;
    sub_71003C8338(&front);
    const sead::Vector3f& target_pos = sub_71005D9330(mActor);
    sead::Vector3f dir = mActor->getMtx().getTranslation() - target_pos;
    dir.y = 0;
    dir.normalize();
    const f32 cross = dir.x * front.z - dir.z * front.x;
    if (cross > 0.0871557f)
        return 1;
    if (cross < -0.0871557f)
        return -1;
    return 0;
}

}  // namespace uking::ai
