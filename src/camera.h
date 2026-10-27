#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {}

    // TODO: all of these:
    //a Convert window pixels to world coords
    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow) { return { mViewCenterWorld + (pWindow - mWindowSize / 2.f) * mWorldUnitsPerPixel }; };
    //b Convert world coords to window pixels
    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld) { return { (pWorld - mViewCenterWorld) / mWorldUnitsPerPixel + mWindowSize / 2.f }; };
    //c Convert normalized window coords to world coords
    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent) { return { windowToWorld(pWindowPercent * mWindowSize) }; };
    //d Convert normalized world coords to window coords
    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld) { return { worldToWindow(pWorld) / mWindowSize }; };
    //e Translate the camera in world units. moves the camera center by a world-coordinate displacement
    void translateWorld(const sf::Vector2f& deltaWorld) { mViewCenterWorld += deltaWorld; };
    //f Translate the camera in screen pixels. moves the camera center by a displacement measured in screen pixels, converted to world units
    void translateWindow(const sf::Vector2f& deltaScreen) { translateWorld(deltaScreen * mWorldUnitsPerPixel); };
    //g Translate the camera by a % of window size. does the same using a percentage of the window dimensions
    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) { translateWindow(deltaScreenPercent * mWindowSize); };
    //h Place a world point at a specified window pos. places a specified world point at a specified screen pixel
    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) { mViewCenterWorld = pWorld - (pWindow - mWindowSize / 2.f) * mWorldUnitsPerPixel; };
    //i Place a world point at a normalized window pos. does the same using normalized screen coordinates
    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) { setCamera(pWorld, pWindowPercent * mWindowSize); };
    //j Place a world point at the center of the window. places the specified world point at the screen center
    void setCameraCenter(const sf::Vector2f& pWorld) { mViewCenterWorld = pWorld; };
    //k Get the world-coord camera center. returns the current center
    sf::Vector2f getCameraCenter() const { return { mViewCenterWorld }; };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
