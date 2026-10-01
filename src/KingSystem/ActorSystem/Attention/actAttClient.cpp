#include "KingSystem/ActorSystem/Attention/actAttClient.h"

namespace ksys::act {

const sead::SafeString& AttClient::getName() const {
    return mClient->name.ref();
}

void AttClient::resetEnabled() {
    if (mClient)
        mEnabled = mClient->is_valid.ref();
}

void AttClient::enable() {
    mEnabled = true;
}

void AttClient::disable() {
    mEnabled = false;
}

void AttClient::setEnabled(bool enabled) {
    mEnabled = enabled;
}

bool AttClient::isEnabled() const {
    switch (mMode) {
    case 1:
        return true;
    case 0:
        return mEnabled;
    default:
        return false;
    }
}

void AttClient::setCallback(void* callback) {
    mCallback = callback;
}

}  // namespace ksys::act
