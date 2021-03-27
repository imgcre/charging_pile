#ifndef CONFIG_OS_HXX_
#define CONFIG_OS_HXX_

#include <rtthread.h>

namespace Config {
class Os {
public:
    static constexpr int
        kThreadDefaultStackSize = 4096,
        kAliIotDeviceThreadPrio = 10,
        kAliIotDeviceThreadStackSize = 4096;

    static const char
        *kAliIotDeviceThreadName;
};
}

enum class Priority {
    High,
    Middle,
    PkgCb,
    Rpc,
};

template<Priority Proi>
struct PriorityTrait {
    //static constexpr rt_uint8_t value = 0;
};

template<>
struct PriorityTrait<Priority::High> {
    static constexpr rt_uint8_t value = 2;
};

template<>
struct PriorityTrait<Priority::Middle> {
    static constexpr rt_uint8_t value = 15;
};

template<>
struct PriorityTrait<Priority::PkgCb> {
    static constexpr rt_uint8_t value = 15;
};

template<>
struct PriorityTrait<Priority::Rpc> {
    static constexpr rt_uint8_t value = 16;
};





#endif /* CONFIG_OS_HXX_ */
