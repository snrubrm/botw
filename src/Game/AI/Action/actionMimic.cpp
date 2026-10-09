#include "Game/AI/Action/actionMimic.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/System/VFR.h"

// Existing native identity and declaration from EnemyMimicrySelect; final bool is unused.
bool sub_71005DCD84(s32* material, ksys::act::Actor* actor, f32 range, bool unused);

namespace uking::action {

Mimic::Mimic(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Mimic::~Mimic() = default;

void Mimic::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    *mIsStartResetMimicry_a = false;
    _80 = 0;
    playAS(mMimicStartASName_s.cstr(), false, 0, 0, -1.0f);
    mFlags.reset(Flag::Changeable);
}

void Mimic::leave_() {
    if (*mMimicryMaterial_a >= 0)
        sub_71005DD27C(mActor, *mMimicryMaterial_a, 0.0f);
    sub_71005DD34C(mActor, true);
    ActionWithPosAngReduce::leave_();
}

void Mimic::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mMimicTime_s, "MimicTime");
    getStaticParam(&mMimicRate_s, "MimicRate");
    getStaticParam(&mMimicStartASName_s, "MimicStartASName");
    getStaticParam(&mMimicLoopASName_s, "MimicLoopASName");
    getStaticParam(&mMimicEndASName_s, "MimicEndASName");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

void Mimic::calc_() {
    ActionWithPosAngReduce::calc_();
    sub_71001E669C();
}

// NON_MATCHING: timer initialization and material-update loads are scheduled differently.
void Mimic::sub_71001E669C() {
    switch (_80) {
    case 0:
        if (mActor->getASList()->x_4(0, 0)) {
            _80 = 1;
            _84 = 0.0f;
            _88.reset(*mMimicTime_s);
            s32 material = 0;
            if (sub_71005DCD84(&material, mActor, 1.5f, false))
                *mMimicryMaterial_a = material;
            playAS(mMimicLoopASName_s.cstr(), false, 0, 0, -1.0f);
        }
        break;
    case 1:
        if (*mMimicryMaterial_a >= 0) {
            const f32 rate = *mMimicRate_s;
            ksys::VFR::lerp(&_84, 1.0f, rate, rate, rate * 0.1f);
            sub_71005DD27C(mActor, *mMimicryMaterial_a, _84);
        }
        sub_71005DD34C(mActor, false);
        if (*mMimicTime_s < 0) {
            if (!isFinishedAS(0, 0))
                break;
        } else if (!(_88.value <= sead::Mathf::epsilon())) {
            _88.update();
            break;
        }
        _80 = 2;
        playAS(mMimicEndASName_s.cstr(), false, 0, 0, -1.0f);
        sub_71005DD34C(mActor, true);
        break;
    case 2:
        if (*mMimicryMaterial_a >= 0) {
            const f32 rate = *mMimicRate_s;
            ksys::VFR::lerp(&_84, 0.0f, rate, rate, rate * 0.1f);
            sub_71005DD27C(mActor, *mMimicryMaterial_a, _84);
        }
        if (mActor->getASList()->x_4(0, 0))
            setFinished();
        break;
    }
}

}  // namespace uking::action
