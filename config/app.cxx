#include "app.hxx"
#include <map>
#include <utilities/err.hxx>
#include <ui/ws_screen.hxx>
#include <ui/rgb_light_widget.hxx>
#include <ui/loading_widget.hxx>
#include <ui/state_noti_widget.hxx>

using namespace Config;
using namespace std;
const char
    *App::cloudDeviceName = "with_keyboard",
    *App::cloudProductKey = "a1SvHKhmFbS",
    *App::cloudDeviceSecret = "92b788fb3f8ca58e209c5fa11573fcaf";

namespace Preset {
const int
    WsScreen::kWidth = 5,
    WsScreen::kHeight = 2;

template<> const int RgbLightWidget<0>::zIndex = 0;
template<> const int RgbLightWidget<1>::zIndex = 0;
template<> const int RgbLightWidget<2>::zIndex = 0;
template<> const int RgbLightWidget<3>::zIndex = 0;
template<> const int RgbLightWidget<4>::zIndex = 0;
template<> const int RgbLightWidget<5>::zIndex = 0;
template<> const int RgbLightWidget<6>::zIndex = 0;
template<> const int RgbLightWidget<7>::zIndex = 0;
template<> const int RgbLightWidget<8>::zIndex = 0;
template<> const int RgbLightWidget<9>::zIndex = 0;
const int LoadingWidget::zIndex = 1;
const int StateNotiWidget::zIndex = 0;
}

string getStateStr(State::Value state) {
    switch(state) {
    case State::LoadNotInsert:
        return "load_not_insert";
    case State::LoadInserted:
        return "load_inserted";
    case State::Charging:
        return "charging";
    case State::LoadWaitRemove:
        return "load_wait_remove";
    case State::Error:
        return "error";
    default:
        throw not_implemented{"unknown_state"};
    }
}
