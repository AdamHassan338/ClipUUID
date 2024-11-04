#include "inputhandler.h"

std::unordered_set<uint16_t> InputHandler::keys;

InputHandler::InputHandler(QObject *parent)
    : QObject{parent}
{
    hook_set_logger_proc(&InputHandler::logger_proc);
    hook_set_dispatch_proc(&InputHandler::dispatch_proc);
}

void InputHandler::start(){
    startHook();
}

void InputHandler::stop(){
    stopHook();
    emit stopped();
}

bool InputHandler::startHook(){
    int status = hook_run();
    switch (status) {
    case UIOHOOK_SUCCESS:
        // Everything is ok.
        return true;
        break;

        // System level errors.
    case UIOHOOK_ERROR_OUT_OF_MEMORY:
        logger_proc(LOG_LEVEL_ERROR, "Failed to allocate memory. (%#X)", status);
        break;


        // X11 specific errors.
    case UIOHOOK_ERROR_X_OPEN_DISPLAY:
        logger_proc(LOG_LEVEL_ERROR, "Failed to open X11 display. (%#X)", status);
        break;

    case UIOHOOK_ERROR_X_RECORD_NOT_FOUND:
        logger_proc(LOG_LEVEL_ERROR, "Unable to locate XRecord extension. (%#X)", status);
        break;

    case UIOHOOK_ERROR_X_RECORD_ALLOC_RANGE:
        logger_proc(LOG_LEVEL_ERROR, "Unable to allocate XRecord range. (%#X)", status);
        break;

    case UIOHOOK_ERROR_X_RECORD_CREATE_CONTEXT:
        logger_proc(LOG_LEVEL_ERROR, "Unable to allocate XRecord context. (%#X)", status);
        break;

    case UIOHOOK_ERROR_X_RECORD_ENABLE_CONTEXT:
        logger_proc(LOG_LEVEL_ERROR, "Failed to enable XRecord context. (%#X)", status);
        break;


        // Windows specific errors.
    case UIOHOOK_ERROR_SET_WINDOWS_HOOK_EX:
        logger_proc(LOG_LEVEL_ERROR, "Failed to register low level windows hook. (%#X)", status);
        break;


        // Darwin specific errors.
    case UIOHOOK_ERROR_AXAPI_DISABLED:
        logger_proc(LOG_LEVEL_ERROR, "Failed to enable access for assistive devices. (%#X)", status);
        break;

    case UIOHOOK_ERROR_CREATE_EVENT_PORT:
        logger_proc(LOG_LEVEL_ERROR, "Failed to create apple event port. (%#X)", status);
        break;

    case UIOHOOK_ERROR_CREATE_RUN_LOOP_SOURCE:
        logger_proc(LOG_LEVEL_ERROR, "Failed to create apple run loop source. (%#X)", status);
        break;

    case UIOHOOK_ERROR_GET_RUNLOOP:
        logger_proc(LOG_LEVEL_ERROR, "Failed to acquire apple run loop. (%#X)", status);
        break;

    case UIOHOOK_ERROR_CREATE_OBSERVER:
        logger_proc(LOG_LEVEL_ERROR, "Failed to create apple run loop observer. (%#X)", status);
        break;

        // Default error.
    case UIOHOOK_FAILURE:
    default:
        logger_proc(LOG_LEVEL_ERROR, "An unknown hook error occurred. (%#X)", status);
        break;
    }
    return false;
}

bool InputHandler::stopHook(){
    int status = hook_stop();
    switch (status) {
    case UIOHOOK_SUCCESS:
        return true;
        break;

        // System level errors.
    case UIOHOOK_ERROR_OUT_OF_MEMORY:
        logger_proc(LOG_LEVEL_ERROR, "Failed to allocate memory. (%#X)", status);
        break;

    case UIOHOOK_ERROR_X_RECORD_GET_CONTEXT:
        // NOTE This is the only platform specific error that occurs on hook_stop().
        logger_proc(LOG_LEVEL_ERROR, "Failed to get XRecord context. (%#X)", status);
        break;

        // Default error.
    case UIOHOOK_FAILURE:
    default:
        logger_proc(LOG_LEVEL_ERROR, "An unknown hook error occurred. (%#X)", status);
        break;
    }
    return false;
}

bool InputHandler::logger_proc(unsigned int level, const char *format,...) {
    bool status = false;

    va_list args;
    switch (level) {
    case LOG_LEVEL_INFO:
        va_start(args, format);
        status = vfprintf(stdout, format, args) >= 0;
        va_end(args);
        break;

    case LOG_LEVEL_WARN:
    case LOG_LEVEL_ERROR:
        va_start(args, format);
        status = vfprintf(stderr, format, args) >= 0;
        va_end(args);
        break;
    }

    return status;
}

void InputHandler::dispatch_proc(uiohook_event * const event){
    std::unordered_set<uint16_t> currentKeys = InputHandler::keys;
    switch(event->type){
    // case EVENT_KEY_PRESSED:
    //     cout << "key pressed" << endl;
    case EVENT_KEY_PRESSED:
        //cout << "Key Pressed: " << char(event->data.keyboard.keychar) << endl;
        currentKeys.emplace(event->data.keyboard.keycode);
        break;
    case EVENT_KEY_RELEASED:
        //cout << "Key Released: " << char(event->data.keyboard.keychar) << endl;
        currentKeys.erase(event->data.keyboard.keycode);
        break;

    case EVENT_KEY_TYPED:
        //keys.emplace(event->data.keyboard.keycode);
        //cout << "Key Typed: " << char(event->data.keyboard.keychar) << endl;
        break;
    default:
        break;
    }

    if(!InputHandler::keys.empty() && InputHandler::keys==currentKeys){
        return;
    }
    InputHandler::keys = currentKeys;

    if(InputHandler::keys.find(VC_ALT_L)!=InputHandler::keys.end()){
        if(InputHandler::keys.find(VC_U)!=InputHandler::keys.end()){

            qDebug()<< "alt+u";
            InputHandler::getInstance().emitHotkey();
        }
    }

}
