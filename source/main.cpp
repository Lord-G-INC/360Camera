#include "syati.h"
#include "kamek/hooks.h"
f32 currentFovModifier = 0.0f;

f64 moveHorizontal (f64 a, f64 b) {
    // Calculate normal result and then subtract 40°-ish
    f64 result = fmod(a, 6.283185482025146) + (MR::testCorePadTriggerLeft(0) || MR::testCorePadButtonLeft(0) ? 0.698132 : -0.698132);
    if (result < 0) 
        result += 6.283185482025146;
    else if (result > 6.283185482025146) 
        result -= 6.283185482025146;
    return result;
}
void moveCloser (Mario *pMario) {
    if (currentFovModifier > -30.0f) 
        currentFovModifier -= 0.5f;
}
void moveVertical () {
    if (MR::testCorePadButtonDown(0) && MR::isPossibleToShiftToFirstPersonCamera() && currentFovModifier < 30.0f) 
        currentFovModifier += 0.5f;

    MR::setFovy(MR::getFovy() + currentFovModifier);
}
bool disableSFX () {
    return false;
}
bool holdCameraBtnLeft () {
    // Normally, the camera functions call MR::testCorePadTriggerLeft,
    // but that only returns true once while MR::testCorePadButtonLeft
    // returns true on every frame Left is held.
    return MR::testCorePadButtonLeft(0);
}
bool holdCameraBtnRight () {
    return MR::testCorePadButtonRight(0);
}
bool holdCameraBtnUp () {
    return MR::testCorePadButtonUp(0);
}
kmCall(0x801180C8, moveHorizontal); // fmod in CameraFollow::startRound
kmCall(0x80389780, moveCloser);
kmBranch(0x803C1C5C, moveVertical);
kmCall(0x8011E118, holdCameraBtnLeft); // return in CameraLocalUtil::testCameraPadTriggerLeft
kmCall(0x8011E168, holdCameraBtnRight); // return in CameraLocalUtil::testCameraPadTriggerRight
kmCall(0x80389708, holdCameraBtnUp);
// ----------------------------------------
// Here we change all instances of the game calling CameraDirector::isPlayableCameraSE
// to be false so that it doesn't play any soundeffects
kmCall(0x80115330, disableSFX);
kmCall(0x801153B0, disableSFX);
kmCall(0x801153D8, disableSFX);
kmCall(0x80115454, disableSFX);
kmCall(0x8011547C, disableSFX);
kmCall(0x801154E4, disableSFX);
kmCall(0x8011551C, disableSFX);
kmCall(0x80115578, disableSFX);
kmCall(0x801155C0, disableSFX);