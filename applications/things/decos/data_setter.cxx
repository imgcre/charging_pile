#include <config/bsp.hxx>
#include <components/persistent_storage_preset.hxx>
#include "data_setter.hxx"

using namespace std;
using namespace Things::Decos;

DataSetter::DataSetter(outer_t* outer): Base(outer) {
    timer.onRun += [this] {
        {
            auto guard = getLock();
            params.refresh();
        }
        auto willEmit = false;
        auto port = rt_uint8_t{};
        {
            auto guard = getLock();
            port = currPort;
            willEmit = specs[port].count.updateAndCheck();
            currPort++;
            currPort %= Config::Bsp::kPortNum;
        }
        if(willEmit) {
            emitPortData(InnerPort{port});
        }
    };
}

void DataSetter::emitPortData(InnerPort port) {
    auto& info = getInfo(port);
    this->outer->onCurrentData(CurrentData {
        port: port,
        timerId: info.timerId,
        leftMinutes: info.leftSeconds / 60,
        state: info.charger->stateStore->oState.value().value_or(State::Error),
        current: info.charger->multimeterChannel->current.value().value_or(0),
        voltage: info.charger->multimeterChannel->voltage.value().value_or(0),
        consumption: info.consumption,
        fuse: CurrentData::Fuse::Normal,
    });
}

void DataSetter::init() {
    timer.start();
}

void DataSetter::query() {
    auto guard = getLock();
    for(rt_uint8_t i = 0; i < Config::Bsp::kPortNum; i++) {
        specs[i].count.retrigger();
    }
}

void DataSetter::onStateChanged(InnerPort port, State::Value state) {
    auto charger = getInfo(port).charger;
    auto& spec = specs[port.get()];
    auto guard = getLock();
    switch(state) {
    case State::Charging:
    case State::LoadWaitRemove:
        spec.prevCurrMiA = charger->multimeterChannel->current.value().value_or(0);
        spec.count.retrigger();
        break;
    default:
        break;
    };
}

void DataSetter::onCurrentChanged(InnerPort port, int value) {
    auto charger = getInfo(port).charger;
    auto& spec = specs[port.get()];
    auto& prevCurrMiA = spec.prevCurrMiA;
    auto guard = getLock();
    if(*charger->stateStore->oState != State::Charging || params == nullopt) {
        return;
    }
    if(abs(value - prevCurrMiA) >= params->currDiffThrMiA) {
        prevCurrMiA = value;
        spec.count.retrigger();
    }
}

void DataSetter::config(DevConfig conf) {
    params.save({conf.uploadThr});
}
