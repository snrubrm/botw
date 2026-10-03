#include "Game/AI/Behavior/behaviorNeckParamChange.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

NeckParamChange::NeckParamChange(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NeckParamChange::~NeckParamChange() = default;

bool NeckParamChange::m6(sead::Heap* heap) {
    return true;
}

void NeckParamChange::Saved::sub_710062CB24(ksys::act::Unk_7100d860d8* unit) {
    if (!unit)
        return;
    f32 value = unit->sub_7100D87BE4() ? unit->sub_7100D8A5BC() : unit->sub_7100D8A37C();
    _0 = value > 0 ? value : -value;
    value = unit->sub_7100D87BE4() ? unit->sub_7100D8A64C() : unit->sub_7100D8A40C();
    _4 = value > 0 ? value : -value;
    value = unit->sub_7100D87BE4() ? unit->sub_7100D8A49C() : unit->sub_7100D8A25C();
    _8 = value > 0 ? value : -value;
    value = unit->sub_7100D87BE4() ? unit->sub_7100D8A52C() : unit->sub_7100D8A2EC();
    _c = value > 0 ? value : -value;
    _10 = unit->_9c;
    _14 = unit->_a4;
    _1c = unit->_90;
    _20 = unit->sub_7100D88EC8();
}

void NeckParamChange::Saved::sub_710062CD74(ksys::act::Unk_7100d860d8* unit) {
    if (!unit)
        return;
    unit->sub_7100D8971C(_0);
    unit->sub_7100D8977C(_4);
    unit->sub_7100D89618(_8);
    unit->sub_7100D8969C(_c);
    unit->sub_7100D8A9D0(_10);
    unit->sub_7100D8A9EC(_14);
    unit->sub_7100D8A830(_1c, false);
    unit->sub_7100D8A904(_20, false);
    unit->sub_7100D8AAB8();
    unit->sub_7100D8AB00();
}

void NeckParamChange::m7() {
    auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl());
    if (!unit)
        return;
    if (*mULimit_s >= 0.0f)
        unit->sub_7100D8971C(*mULimit_s);
    if (*mDLimit_s >= 0.0f)
        unit->sub_7100D8977C(*mDLimit_s);
    if (*mLLimit_s >= 0.0f)
        unit->sub_7100D89618(*mLLimit_s);
    if (*mRLimit_s >= 0.0f)
        unit->sub_7100D8969C(*mRLimit_s);
    if (*mRotRatio_s >= 0.0f)
        unit->sub_7100D8A9D0(*mRotRatio_s);
    if (*mRetRotRatio_s >= 0.0f)
        unit->sub_7100D8A9EC(*mRetRotRatio_s);
    if (*mMinRotate_s >= 0.0f)
        unit->sub_7100D8AA08(*mMinRotate_s);
    if (*mMaxRotate_s >= 0.0f)
        unit->sub_7100D8AA60(*mMaxRotate_s);
    unit->sub_7100D8A830(*mOffsetLR_s, false);
    unit->sub_7100D8A904(*mOffsetUD_s, false);
}

void NeckParamChange::m8() {
    auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl());
    if (!unit)
        return;
    _78.sub_710062CB24(unit);
    if (*mULimit_s >= 0.0f)
        unit->sub_7100D8971C(*mULimit_s);
    if (*mDLimit_s >= 0.0f)
        unit->sub_7100D8977C(*mDLimit_s);
    if (*mLLimit_s >= 0.0f)
        unit->sub_7100D89618(*mLLimit_s);
    if (*mRLimit_s >= 0.0f)
        unit->sub_7100D8969C(*mRLimit_s);
    if (*mRotRatio_s >= 0.0f)
        unit->sub_7100D8A9D0(*mRotRatio_s);
    if (*mRetRotRatio_s >= 0.0f)
        unit->sub_7100D8A9EC(*mRetRotRatio_s);
    if (*mMinRotate_s >= 0.0f)
        unit->sub_7100D8AA08(*mMinRotate_s);
    if (*mMaxRotate_s >= 0.0f)
        unit->sub_7100D8AA60(*mMaxRotate_s);
    unit->sub_7100D8A830(*mOffsetLR_s, false);
    unit->sub_7100D8A904(*mOffsetUD_s, false);
}

void NeckParamChange::m9() {
    _78.sub_710062CD74(ksys::act::sub_7100D82FFC(mActor->getBoneControl()));
}

void NeckParamChange::loadParams() {
    getStaticParam(&mULimit_s, "ULimit");
    getStaticParam(&mDLimit_s, "DLimit");
    getStaticParam(&mLLimit_s, "LLimit");
    getStaticParam(&mRLimit_s, "RLimit");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRetRotRatio_s, "RetRotRatio");
    getStaticParam(&mMinRotate_s, "MinRotate");
    getStaticParam(&mMaxRotate_s, "MaxRotate");
    getStaticParam(&mOffsetLR_s, "OffsetLR");
    getStaticParam(&mOffsetUD_s, "OffsetUD");
}

}  // namespace uking::behavior
