#include <iostream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Devices.Bluetooth.Advertisement.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Devices::Bluetooth::Advertisement;

fire_and_forget StartAdvertising()
{
    try
    {
        // 創建廣播者
        BluetoothLEAdvertisementPublisher advertiser;

        // 設置廣播數據
        BluetoothLEAdvertisement advertisement;
        advertisement.LocalName(L"MyBLEDevice");  // 設置您想要顯示的設備名稱

        // 可以添加一些自定義數據（可選）
        // DataSection customSection;
        // customSection.Data(array_view<const uint8_t>{1, 2, 3, 4});
        // advertisement.DataSections().Append(customSection);

        advertiser.Advertisement(advertisement);

        // 開始廣播
        advertiser.Start();

        std::wcout << L"Started advertising. Your device should now be discoverable." << std::endl;

        // 保持廣播運行
        while (true)
        {
            co_await resume_after(std::chrono::seconds(1));
        }
    }
    catch (const hresult_error& ex)
    {
        std::wcerr << L"Error: " << ex.message().c_str() << std::endl;
    }
}

int main()
{
    init_apartment();
    StartAdvertising();

    // 保持應用程序運行
    while (true)
    {
        Sleep(1000);
    }

    return 0;
}