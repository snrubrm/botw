#include "Game/Framework/gameSystemStruct1.h"

namespace uking::frm {

SystemStruct1* SystemStruct1::sInstance = nullptr;

SystemStruct1* SystemStruct1::getInstance() {
    return sInstance;
}

void SystemStruct1::setInstance(SystemStruct1* instance) {
    sInstance = instance;
}

}  // namespace uking::frm
