#include <iostream>
#include <thread>
#include <chrono>
#include "parsec-vdd.h"

using namespace parsec_vdd;
using namespace std::literals::chrono_literals;

bool checkDriverStatus(){
    DeviceStatus status = QueryDeviceStatus(&VDD_CLASS_GUID, VDD_HARDWARE_ID);
    if (status != DEVICE_OK) {
        std::cout << "Device is not ready." << std::endl;
        return false;
    }else{
        return true;
    }
}

bool startVirtualDisplay(){
    HANDLE vdd = OpenDeviceHandle(&VDD_ADAPTER_GUID);
    if (vdd == nullptr || vdd == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to obtain the device handle." << std::endl;
        return false;
    }

    int index = VddAddDisplay(vdd);
    if (index < 0) {
        std::cout << "Failed to add a virtual display." << std::endl;
        CloseDeviceHandle(vdd);
        return false;
    }

    bool running = true;

    // Side thread for updating vdd.
    std::thread updater([&running, vdd] {
        while (running) {
            VddUpdate(vdd);
            std::this_thread::sleep_for(100ms);
        }
    });

    std::cout << "Virtual display added successfully." << std::endl;
    while(1){
    }
    return true;
}

int main() {
    bool isDriverStatusOk=checkDriverStatus();
    if(isDriverStatusOk){
        startVirtualDisplay();
    }
}
