#include "Game/AI/AI/aiAddDemoCall.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking::ai {

AddDemoCall::AddDemoCall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddDemoCall::~AddDemoCall() = default;

bool AddDemoCall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// inline-only in the original (name is a guess); like callCookingDemo (0x71008bb1e0) the result is returned
// after the metadata is destroyed.
bool AddDemoCall::callDemoEvent() {
    ksys::evt::Metadata metadata(mDemoName_s.cstr(), mEntryPoint_s.cstr(), "");
    ksys::evt::CallArg arg;
    arg.proc = mActor;
    arg.metadata = &metadata;
    return ksys::evt::Manager::instance()->callEvent(arg);
}

void AddDemoCall::callDemo() {
    _98 = callDemoEvent();
}

// NON_MATCHING: register allocation (the original keeps `this` in x20 and params in x19)
void AddDemoCall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mOnlyOne_s) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            if (!enemy->_e84.isOnBit(9)) {
                enemy->_e84.setBit(9);
                callDemo();
                if (*mIsBroadCastOnlyOne_s) {
                    _68.x(mActor);
                    sub_71005E02E0(mActor, &_68, nullptr);
                    _98 = true;
                }
            }
        }
    } else {
        callDemo();
        changeChild("行動", params);
    }
}

void AddDemoCall::calc_() {
    if (_98)
        return;
    callDemo();
}

bool AddDemoCall::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AddDemoCall::isFinished() const {
    return getCurrentChild()->isFinished();
}

void AddDemoCall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddDemoCall::loadParams_() {
    getStaticParam(&mOnlyOne_s, "OnlyOne");
    getStaticParam(&mIsBroadCastOnlyOne_s, "IsBroadCastOnlyOne");
    getStaticParam(&mEntryPoint_s, "EntryPoint");
    getStaticParam(&mDemoName_s, "DemoName");
}

}  // namespace uking::ai
