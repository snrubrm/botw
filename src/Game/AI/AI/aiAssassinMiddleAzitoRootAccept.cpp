#include "Game/AI/AI/aiAssassinMiddleAzitoRootAccept.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking::ai {

AssassinMiddleAzitoRootAccept::AssassinMiddleAzitoRootAccept(const InitArg& arg)
    : AssassinMiddleRoot(arg) {}

AssassinMiddleAzitoRootAccept::~AssassinMiddleAzitoRootAccept() = default;

bool AssassinMiddleAzitoRootAccept::init_(sead::Heap* heap) {
    return AssassinMiddleRoot::init_(heap);
}

void AssassinMiddleAzitoRootAccept::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinMiddleRoot::enter_(params);
}

void AssassinMiddleAzitoRootAccept::calc_() {
    AssassinMiddleRoot::calc_();
}

void AssassinMiddleAzitoRootAccept::leave_() {
    AssassinMiddleRoot::leave_();
}

void AssassinMiddleAzitoRootAccept::loadParams_() {
    AssassinMiddleRoot::loadParams_();
    getStaticParam(&mEntryPoint_s, "EntryPoint");
    getStaticParam(&mDemoName_s, "DemoName");
}

// NON_MATCHING: SafeString member-address scheduling and register allocation differ.
bool AssassinMiddleAzitoRootAccept::handleMessage_(const ksys::Message* message) {
    if (_360.m2(*message)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_360._8, &accessor);
        auto* actor = mActor;
        if (actor->getName() == accessor.getName()) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                if (!enemy->_e84.isOn(0x200)) {
                    const char* demo = mDemoName_s.cstr();
                    ksys::evt::Metadata metadata(demo, mEntryPoint_s.cstr(), "");
                    ksys::evt::Manager::instance()->sub_7100DB0CA0(metadata, mActor);
                    enemy->_e84.set(0x200);
                }
            }
        }
    }
    return AssassinMiddleRoot::handleMessage_(message);
}

}  // namespace uking::ai
