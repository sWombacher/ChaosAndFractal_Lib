#ifndef WINDOW_3D_OBJECT_H_H
#define WINDOW_3D_OBJECT_H_H

#include "window3D.h"
#include "internal.hpp"

#include <thread>

namespace cf {

struct Window3DObject : protected Window3D {
    using Window3D::printWindowUsage;
    using Window3D::MouseButtonEvent;
    using Window3D::disableLighting;
    using Window3D::getWindowHeight;
    using Window3D::getWindowWidth;
    using Window3D::enableLighting;
    using Window3D::drawCylinder;
    using Window3D::forceDisplay;
    using Window3D::MouseButton;
    using Window3D::CameraType;
    using Window3D::drawSphere;
    using Window3D::setMaxFPS;
    using Window3D::setCamera;
    using Window3D::drawAxis;
    using Window3D::drawCube;
    using Window3D::clear;

    static Window3DObject& createWindow3DObject(int* argc, char** argv, int width = 800, int height = 600,
                                                const char* title = "chaos and fractals");
    ~Window3DObject() override = default;

    void setDrawingFunction(std::function<void(Window3DObject&)> function);
    void setKeyboardInputFunction(std::function<void(unsigned char, int, int)> function);
    void setMousePressedMovementFunction(std::function<bool(MouseButton, int, int)> function);
    void setMousePressEvent(std::function<void(MouseButton, MouseButtonEvent, int, int)> function);

    void waitKeyPressed(size_t delay = 0);
    void exit();

  private:
    Window3DObject(int* argc, char** argv, int width = 800, int height = 600, const char* title = "chaos and fractals");
    void draw() override;
    void handleKeyboardInput(unsigned char key, int x, int y) override;
    bool handleMousePressedMovement(MouseButton button, int x, int y) override;
    void handleMousePressEvent(MouseButton button, MouseButtonEvent event, int x, int y) override;

    internal::_ProtectedFunction<void(Window3DObject&)> m_DrawingFunction;
    internal::_ProtectedFunction<void(unsigned char, int, int)> m_KeyboardInput;
    internal::_ProtectedFunction<bool(MouseButton, int, int)> m_MousePressMovement;
    internal::_ProtectedFunction<void(MouseButton, MouseButtonEvent, int, int)> m_MousePressEvent;

    std::timed_mutex m_WaitMutex;
    static std::thread _RenderThread;
};

} // namespace cf

#endif
