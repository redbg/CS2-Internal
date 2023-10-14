#pragma once

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hook
{
    using Present_t           = HRESULT(STDMETHODCALLTYPE *)(IDXGISwapChain *This, UINT SyncInterval, UINT Flags);
    uintptr_t presentPtr      = Memory::RelativeRIP(Memory::FindPattern("GameOverlayRenderer64.dll", "\x48\x89\x6C\x24\x18\x48\x89\x74\x24\x20\x41\x56\x48\x83\xEC\x20\x41\x8B\xE8") + 0xAD, 6);
    Present_t originalPresent = *(Present_t *)presentPtr;

    IDXGISwapChain         *pSwapChain           = nullptr;
    ID3D11Device           *pDevice              = nullptr;
    ID3D11DeviceContext    *pDeviceContext       = nullptr;
    ID3D11RenderTargetView *mainRenderTargetView = nullptr;

    HWND    hWnd            = nullptr;
    WNDPROC originalWndProc = nullptr;

    LRESULT MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        return CallWindowProc(originalWndProc, hWnd, msg, wParam, lParam);
    }

    HRESULT STDMETHODCALLTYPE MyPresent(IDXGISwapChain *SwapChain, UINT SyncInterval, UINT Flags)
    {
        static const bool init = [SwapChain]()
        {
            // Get IDXGISwapChain
            pSwapChain = SwapChain;

            // Get ID3D11Device
            pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&pDevice);

            // Get ID3D11DeviceContext
            pDevice->GetImmediateContext(&pDeviceContext);

            // Get ID3D11RenderTargetView
            ID3D11Texture2D *pBackBuffer;
            pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
            pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
            pBackBuffer->Release();

            // Get hWnd
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            hWnd = sd.OutputWindow;

            // Hook WndProc
            originalWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)MyWndProc);

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange; // 不显示鼠标光标

            // Setup Platform/Renderer backends
            ImGui_ImplWin32_Init(hWnd);
            ImGui_ImplDX11_Init(pDevice, pDeviceContext);

            return true;
        }();

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Show Main Window
        GUI::ShowMainWindow();
        CS2::Cheats::Run();

        // Rendering
        ImGui::Render();
        pDeviceContext->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        return originalPresent(SwapChain, SyncInterval, Flags);
    }

    void Initialize()
    {
        printf("%s\n", __FUNCTION__);

        *(Present_t *)presentPtr = MyPresent;
    }

    void Uninitialize()
    {
        printf("%s\n", __FUNCTION__);

        *(Present_t *)presentPtr = originalPresent;

        // UnHook WndProc
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)originalWndProc);

        // Cleanup
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

} // namespace Hook
