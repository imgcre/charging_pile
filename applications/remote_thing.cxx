/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-05     imgcr       the first version
 */

#include "remote_thing.hxx"
#include <config/co.hxx>
#include <stdexcept>

using namespace std;
using namespace Packets;
using namespace Rpcs;

RemoteThing::RemoteThing(shared_ptr<Packet> packet, shared_ptr<Rpc> rpc): packet(packet), rpc(rpc) {
    packet->on<Events::PortAccess>([this](auto p) {
        onPortAccess(p->port);
    });
    packet->on<Events::PortUnplug>([this](auto p) {
       onPortUnplug(p->port);
    });
    packet->on<Events::IcNumber>([this](auto p) {
        onIcNumber(p->port, p->icNumber);
    });
    packet->on<Events::CurrentLimit>([this](auto p) {
       onCurrentLimit(p->port);
    });
}

void RemoteThing::control(int port, int timerId, int minutes) {
    auto r = rpc->invoke<Services::Control>({port, timerId, minutes});
    if(!r) throw runtime_error{"control failed"};
}

void RemoteThing::stop(int port, int timerId) {
    auto r = rpc->invoke<Services::Stop>({port, timerId});
    if(!r) throw runtime_error{"stop failed"};
}

void RemoteThing::config(int currentLimit, int uploadThr, int fuzedThr, int noloadCurrThr) {
    rpc->invoke<Services::Config>({currentLimit, uploadThr, fuzedThr, noloadCurrThr});
}
