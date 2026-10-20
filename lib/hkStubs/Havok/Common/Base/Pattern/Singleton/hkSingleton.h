#pragma once

template <typename T>
class hkSingleton {
public:
    static T& getInstance() { return *s_instance; }
    static T* getInstancePtr() { return s_instance; }

protected:
    static T* s_instance;
};
