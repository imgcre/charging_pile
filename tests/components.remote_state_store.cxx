/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-03     imgcr       the first version
 */

#ifdef TEST_REMOTE_STATE_STORE

#ifndef UPPER_END
#error "this test is only for upper end"
#endif

#include <rtthread.h>
#include <components/remote_state_store.hxx>
#include <utilities/mp.hxx>
#include <config/bsp.hxx>

int init_test_remote_state_store() {
    for(auto i = 0; i < Config::Bsp::kPortNum; i++) {
        magic_switch<Config::Bsp::kPortNum>{}([&](auto v){
            auto remote = Preset::RemoteStateStore<decltype(v)::value>::get();
            remote->oState += [i](auto state) {
                if(!state) return;
                rt_kprintf("state[%d] -> %d\n", i, *state);
            };
        }, i);
    }
    return RT_EOK;
}

INIT_APP_EXPORT(init_test_remote_state_store);


#endif

