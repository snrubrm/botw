#include "Game/AI/Action/actionForkClothOnOffASPlay.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

ForkClothOnOffASPlay::ForkClothOnOffASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkClothOnOffASPlay::~ForkClothOnOffASPlay() = default;

bool ForkClothOnOffASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: same logic; the original computes the `cloth_set && cloth_set->_60 < 1.0f` test as a bool (`cset`) that is
// tested together with the LodState flag (`ldr x; tbz #1`, AS branch first), we branch on the compare directly and load the
// flag byte.
void ForkClothOnOffASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* lod = mActor->getLodState();
    if (lod) {
        auto* physics = mActor->getPhysics();
        if (physics) {
            const char* name;
            auto* cloth_set = physics->getClothSet();
            bool cloth_off = false;
            if (cloth_set)
                cloth_off = cloth_set->_60 < 1.0f;
            if (!cloth_off && lod->mFlags8.isOn(2)) {
                lod->mFlags10.set(2);
                name = mASName_s.cstr();
            } else {
                physics->getFlags().set(ksys::phys::InstanceSet::Flag::_20000);
                name = mClothOffASName_s.cstr();
            }
            playAS(name, *mIsIgnoreSame_s, *mTargetBone_s, *mSeqBank_s, -1.0f);
        }
    }

    if (*mChangeableTiming_s == 0)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
}

void ForkClothOnOffASPlay::leave_() {
    if (auto* physics = mActor->getPhysics())
        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.reset(2);
}

void ForkClothOnOffASPlay::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mClothOffASName_s, "ClothOffASName");
}

// NON_MATCHING: same code and control flow as ForkASPlayBase::calc_ (m); the original loads the 0x30 member pointer before the
// 0x38 one and evaluates the case-2 arguments in the other order
void ForkClothOnOffASPlay::calc_() {
    switch (*mChangeableTiming_s) {
    case 2:
        if (mActor->getASList()->x_7(*mTargetBone_s, *mSeqBank_s,
                                     &ksys::as::ASList::Unk2::sub_7101162FE8)) {
            mFlags.set(Flag::Changeable);
        } else {
            mFlags.reset(Flag::Changeable);
        }
        break;
    case 3:
        if (sub_71005DD798(mActor, 22, nullptr, *mTargetBone_s, *mSeqBank_s))
            mFlags.reset(Flag::Changeable);
        else
            mFlags.set(Flag::Changeable);
        break;
    }

    if (isFinishedAS(*mTargetBone_s, *mSeqBank_s)) {
        switch (*mEndState_s) {
        case 2:
            mFlags.set(Flag::Changeable);
            break;
        case 1:
            setFinished();
            break;
        }
    }
}

}  // namespace uking::action
