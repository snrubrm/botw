#include "KingSystem/System/SeadController.h"

namespace ksys {

static SeadController* sInstance;

// 0x71011f931c
SeadController* SeadController::getInstance() {
    return sInstance;
}

// 0x71011f9328
void SeadController::setInstance(SeadController* controller) {
    sInstance = controller;
}

}  // namespace ksys
