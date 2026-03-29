#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

static bool g_ignoreExit = true;

// -----------------------------
// PLAYLAYER (label)
class $modify(MyPlayLayer, PlayLayer) {
public:
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        // No status label is shown per user preference
        return true;
    }
};

// -----------------------------
// PAUSELAYER (bloquear salir)
class $modify(MyPauseLayer, PauseLayer) {

    void onQuit(CCObject* sender) {
        if (g_ignoreExit) return;
        PauseLayer::onQuit(sender);
    }

    // ❌ ELIMINADO onExit incorrecto
};

// -----------------------------
// KEYBOARD (F1 GLOBAL)
class $modify(MyKeyboard, cocos2d::CCKeyboardDispatcher) {

    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool down, bool repeat, double time) {

        if (down && key == cocos2d::KEY_F1) {
            g_ignoreExit = !g_ignoreExit;
            log::info("Toggle GLOBAL: {}", g_ignoreExit);
            return true;
        }

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, repeat, time);
    }
};