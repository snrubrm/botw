#include "Game/AI/Action/actionForkASPlayBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASPlayBase::ForkASPlayBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASPlayBase::~ForkASPlayBase() = default;

bool ForkASPlayBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASPlayBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASPlayBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASPlayBase::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mFirstRandomRatio_s, "FirstRandomRatio");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
}

void ForkASPlayBase::calc_() {
    ksys::act::ai::Action::calc_();
}

const char* ForkASPlayBase::m32() {
    return nullptr;
}

bool ForkASPlayBase::isChangeable() const {
    switch (*mChangeableTiming_s) {
    case 2:
        if (mActor->getASList()->x_7(*mTargetBone_s, *mSeqBank_s,
                                     &ksys::as::ASList::Unk2::sub_7101162FE8)) {
            return true;
        }
        break;
    case 3:
        if (!sub_71005DD798(mActor, 22, nullptr, *mTargetBone_s, *mSeqBank_s))
            return true;
        break;
    }
    return ActionBase::isChangeable();
}

}  // namespace uking::action
