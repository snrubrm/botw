#include "Game/gameMaskController.h"
#include "KingSystem/System/SeadController.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(MaskController)

MaskController::MaskController() = default;

MaskController::~MaskController() {
    _40.unregister();
    for (auto*& controller : mControllers) {
        delete controller;
        controller = nullptr;
    }
    mControllers.freeBuffer();
}

int MaskController::handleMessage(const ksys::Message* message) {
    switch (message->getBrokerId()) {
    case 2:
        switch (message->getType()) {
        case 0x6800006:
            static_cast<ksys::SeadController*>(getController(ControllerIdx::_0))->sub_7100D9DB04(true);
            break;
        case 0x6800009:
            static_cast<ksys::SeadController*>(getController(ControllerIdx::_0))->sub_7100D9DB04(false);
            break;
        }
        return 1;
    case 4:
        return 1;
    case u32(-1):
        return 0;
    default:
        return 0;
    }
}

sead::Controller* MaskController::getController(ControllerIdx idx) {
    return mControllers(idx);
}

sead::ControllerWrapperBase* MaskController::sub_71008BCA40() {
    return &_40;
}

}  // namespace uking
