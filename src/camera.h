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

    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow) { 
        sf::Vector2f windowWorldOffset =
            mViewCenterWorld / mWorldUnitsPerPixel -
            mWindowSize * 0.5f;  // convert world coords to pixel coords and find diff
        //std::cout << "Offset: " << windowWorldOffset << "\n";

        return {(pWindow.x + windowWorldOffset.x) * mWorldUnitsPerPixel, (pWindow.y + windowWorldOffset.y) * mWorldUnitsPerPixel}; 
    };

    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld) { 
        sf::Vector2f windowWorldOffset =
            mViewCenterWorld / mWorldUnitsPerPixel -
            mWindowSize * 0.5f;  // convert world coords to pixel coords and find diff
        //std::cout << "Offset: " << windowWorldOffset << "\n";


        return {pWorld.x / mWorldUnitsPerPixel - windowWorldOffset.x,
                pWorld.y / mWorldUnitsPerPixel - windowWorldOffset.y}; 
    };

    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent) { 
        return windowToWorld(mWindowSize * pWindowPercent); 
    };

    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld) { 
        return worldToWindow(pWorld) / mWindowSize; 
    };

    void translateWorld(const sf::Vector2f& deltaWorld) {
        mViewCenterWorld += deltaWorld;
    };

    void translateWindow(const sf::Vector2f& deltaScreen) {
        mViewCenterWorld += windowToWorld(deltaScreen);
    };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) {
        mViewCenterWorld += windowPercentToWorld(deltaScreenPercent);
    };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) {
        sf::Vector2f translationWorld = pWorld - windowToWorld(pWindow);
        translateWorld(translationWorld);
    };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) {
        sf::Vector2f translationWorld = pWorld - windowPercentToWorld(pWindowPercent);
        translateWorld(translationWorld);
    };

    void setCameraCenter(const sf::Vector2f& pWorld) { 
        mViewCenterWorld = pWorld;
    };

    sf::Vector2f getCameraCenter() const { return mViewCenterWorld; };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
