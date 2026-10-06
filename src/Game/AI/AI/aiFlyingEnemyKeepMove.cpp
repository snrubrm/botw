#include "Game/AI/AI/aiFlyingEnemyKeepMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::ai {

FlyingEnemyKeepMove::FlyingEnemyKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FlyingEnemyKeepMove::~FlyingEnemyKeepMove() = default;

bool FlyingEnemyKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FlyingEnemyKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    m36(&pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

// NON_MATCHING: register allocation: the original carries the sum through the loop in integer registers (w22-w24,
// bitcast to float each iteration), so the range and the actor position stay in d8-d11; ours keeps the sum in float
// registers and spills the range and the position x.
bool FlyingEnemyKeepMove::sub_71003D2880(f32 range, sead::Vector3f* out) {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    sead::Vector3f sum = sead::Vector3f::zero;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    s32 count = 0;
    Unk_7102451448 filter;
    do {
        auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
        if (!entry || entry->_a8 > range)
            break;
        sead::Vector3f dir = entry->_88 - pos;
        dir.normalize();
        sum -= dir;
        ++count;
    } while (count < 10);
    if (count >= 1)
        sum *= range / count;
    *out = sum;
    return true;
}

void FlyingEnemyKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyingEnemyKeepMove::loadParams_() {
    getStaticParam(&mParams.mLostDistance_s, "LostDistance");
    getStaticParam(&mParams.mAngleRange_s, "AngleRange");
    getStaticParam(&mParams.mSpaceDistance_s, "SpaceDistance");
    getStaticParam(&mParams.mNearDist_s, "NearDist");
    getStaticParam(&mParams.mFarDist_s, "FarDist");
    getStaticParam(&mParams.mBaseDist_s, "BaseDist");
    getStaticParam(&mParams.mBaseHeight_s, "BaseHeight");
    getStaticParam(&mParams.mLowHeight_s, "LowHeight");
    getStaticParam(&mParams.mHighHeight_s, "HighHeight");
}

void FlyingEnemyKeepMove::m35(sead::Vector3f* out, const sead::Vector3f& dir) {
    if (!out)
        return;
    const auto& mtx = sub_71005D96A8(mActor);
    sead::Vector3f offset = dir;
    offset *= *mParams.mBaseDist_s;
    offset.y += *mParams.mBaseHeight_s;
    out->setMul(mtx, offset);
}

void FlyingEnemyKeepMove::m36(sead::Vector3f* out) {
    out->set(sub_71005D9330(mActor));
    out->y += *mParams.mBaseHeight_s;
}

// NON_MATCHING: the original keeps the direction and the result in one stack vector and multiplies base * dir; the load
// order of the positions and the pack slot also differ.
void FlyingEnemyKeepMove::changeToAdjustPosition() {
    sead::Vector3f target;
    m36(&target);
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f dir(position.x - target.x, 0.0f, position.z - target.z);
    dir.normalize();
    const sead::Vector3f pos = position + dir * *mParams.mBaseDist_s;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("位置調整", &pack);
}

bool FlyingEnemyKeepMove::sub_71003D1F88() {
    sead::Vector3f target;
    m36(&target);
    sead::Vector3f pos;
    sead::Vector3f dir;
    m34(&dir);
    m35(&pos, dir);
    sead::Vector3f to_pos = pos;
    to_pos -= target;
    to_pos.y = 0;
    to_pos.normalize();
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    return sub_710072DCFC(position, target, to_pos, *mParams.mAngleRange_s);
}

bool FlyingEnemyKeepMove::sub_71003D2500() {
    sead::Vector3f target;
    m36(&target);
    const sead::Matrix34f& mtx = mActor->getMtx();
    sead::Vector3f pos(mtx(0, 3), target.y, mtx(2, 3));

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("上昇", &pack);
    return true;
}

bool FlyingEnemyKeepMove::sub_71003D25F8() {
    sead::Vector3f target;
    m36(&target);
    const sead::Matrix34f& mtx = mActor->getMtx();
    sead::Vector3f pos(mtx(0, 3), target.y, mtx(2, 3));

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("下降", &pack);
    return true;
}

}  // namespace uking::ai
