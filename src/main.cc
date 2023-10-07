#include <memory>
#include <stdexcept>

#include <Logger.hh>
#include <Application.hh>

int main() {
    auto app{ std::make_unique<Mikoto::Application>() };

    try {
        app->Init();
        app->Run();
        app->Shutdown();
    }
    catch (const std::exception& exception) {
        using namespace Mikoto;
        MKT_APP_LOGGER_ERROR("Exception. what(): {}", exception.what());
    }

    return 0;
}
