//==============================================================================
#include "CEvent.h"
#include "CAppStateGame.h"

#define  LOG_TAG "SDL/APP"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

//==============================================================================
CEvent::CEvent() {
}

//------------------------------------------------------------------------------
CEvent::~CEvent() {
	//Do nothing
}

//==============================================================================

void CEvent::OnEvent(SDL_Event* Event) {

	switch(Event->type) {
		case SDL_WINDOWEVENT: {
			switch(Event->window.event)
			{
				case SDL_WINDOWEVENT_SHOWN:
                break;

                case SDL_WINDOWEVENT_HIDDEN:
                break;

                case SDL_WINDOWEVENT_EXPOSED:
                break;

                case SDL_WINDOWEVENT_MOVED:
                break;

                case SDL_WINDOWEVENT_RESIZED:
                break;

                case SDL_WINDOWEVENT_MINIMIZED:
                    //SDL_Log("SDL_WINDOWEVENT_MINIMIZED");
					//OnMinimize();
                break;

                case SDL_WINDOWEVENT_MAXIMIZED:
                break;

                case SDL_WINDOWEVENT_RESTORED:
                    //SDL_Log("SDL_WINDOWEVENT_RESTORED");
					//OnRestore();
                break;

                case SDL_WINDOWEVENT_ENTER:
                break;

                case SDL_WINDOWEVENT_LEAVE:
                break;

                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    //SDL_Log("SDL_WINDOWEVENT_FOCUS_GAINED");
					OnRestore();
                break;

                case SDL_WINDOWEVENT_FOCUS_LOST:
                    //SDL_Log("SDL_WINDOWEVENT_FOCUS_LOST");
                    OnMinimize();
                break;

                case SDL_WINDOWEVENT_CLOSE:
                break;

                default:
                break;

			}
			break;
		}

		case SDL_KEYDOWN: {
			OnKeyDown(Event->key.keysym);
			break;
		}

		case SDL_KEYUP: {
			OnKeyUp(Event->key.keysym);
			break;
		}
		/*
		case SDL_MOUSEMOTION: {
			OnMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			switch(Event->button.button) {
				case SDL_BUTTON_LEFT: {
					OnLButtonDown(Event->button.x,Event->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT: {
					OnRButtonDown(Event->button.x,Event->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE: {
					OnMButtonDown(Event->button.x,Event->button.y);
					break;
				}
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:	{
			switch(Event->button.button) {
				case SDL_BUTTON_LEFT: {
					OnLButtonUp(Event->button.x, Event->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT: {
					OnRButtonUp(Event->button.x, Event->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE: {
					OnMButtonUp(Event->button.x, Event->button.y);
					break;
				}
			}
			break;
		}
		*/


		// SDL2 ANDROID TOUCH EVENTS
		case SDL_FINGERDOWN: {
			OnTouchedDown(Event->tfinger.x, Event->tfinger.y);
			break;
			}
		case SDL_FINGERUP: {
			OnTouchedUp(Event->tfinger.x, Event->tfinger.y);
			break;
			}
		case SDL_FINGERMOTION: {
			OnTouchedMove(Event->tfinger.x, Event->tfinger.y, Event->tfinger.dx, Event->tfinger.dy);
			break;
			}
		//----------------------------


		case SDL_JOYAXISMOTION: {
			OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
			break;
		}

		case SDL_JOYBALLMOTION: {
			OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
			break;
		}

		case SDL_JOYHATMOTION: {
			OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
			break;
		}
		case SDL_JOYBUTTONDOWN: {
			OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
			break;
		}

		case SDL_JOYBUTTONUP: {
			OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
			break;
		}

		case SDL_QUIT: {
			OnExit();
			break;
		}

		case SDL_SYSWMEVENT: {
			//Ignore
			break;
		}



		default: {
			OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
			break;
		}
	}
}

//------------------------------------------------------------------------------
void CEvent::OnInputFocus() {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnInputBlur() {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnKeyDown(SDL_Keysym sym) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnKeyUp(SDL_Keysym sym) {
	//Pure virtual, do nothing
}

/*
//------------------------------------------------------------------------------
void CEvent::OnMouseFocus() {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMouseBlur() {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMouseWheel(bool Up, bool Down) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnLButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnLButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnRButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnRButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}
*/


//-----------------------------------------------------------------------------
void CEvent::OnTouchedDown(float tX, float tY) {
	//Pure virtual, do nothing
}

//-----------------------------------------------------------------------------
void CEvent::OnTouchedUp(float tX, float tY) {
	//Pure virtual, do nothing
}

//-----------------------------------------------------------------------------
void CEvent::OnTouchedMove(float tX, float tY, float dX, float dY) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnJoyButtonDown(Uint8 which,Uint8 button) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnJoyButtonUp(Uint8 which,Uint8 button) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMinimize() {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnRestore() {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnResize(int w,int h) {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnExpose() {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnExit() {
	//Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnUser(Uint8 type, int code, void* data1, void* data2) {
	//Pure virtual, do nothing
}

//==============================================================================
