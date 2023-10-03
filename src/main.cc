#include <memory>
#include <stdexcept>

#include <Application.hh>

int main() {
    auto app{ std::make_unique<Mikoto::Application>() };

    try {
        app->Init();
        app->Run();
        app->Shutdown();
    }
    catch (const std::exception& exception) {

    }

    return 0;
}
