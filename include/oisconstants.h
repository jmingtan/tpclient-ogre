#ifndef oisconstants__h
#define oisconstants__h

#include <string.h>
#include <OIS.h>

const char *ois_keyboard[] = {
	"KC_UNASSIGNED",
	"KC_ESCAPE",
	"KC_1",
	"KC_2",
	"KC_3",
	"KC_4",
	"KC_5",
	"KC_6",
	"KC_7",
	"KC_8",
	"KC_9",
	"KC_0",
	"KC_MINUS",    // - on main keyboard
	"KC_EQUALS",
	"KC_BACK",    // backspace
	"KC_TAB",
	"KC_Q",
	"KC_W",
	"KC_E",
	"KC_R",
	"KC_T",
	"KC_Y",
	"KC_U",
	"KC_I",
	"KC_O",
	"KC_P",
	"KC_LBRACKET",
	"KC_RBRACKET",
	"KC_RETURN",    // Enter on main keyboard
	"KC_LCONTROL",
	"KC_A",
	"KC_S",
	"KC_D",
	"KC_F",
	"KC_G",
	"KC_H",
	"KC_J",
	"KC_K",
	"KC_L",
	"KC_SEMICOLON",
	"KC_APOSTROPHE",
	"KC_GRAVE",    // accent
	"KC_LSHIFT",
	"KC_BACKSLASH",
	"KC_Z",
	"KC_X",
	"KC_C",
	"KC_V",
	"KC_B",
	"KC_N",
	"KC_M",
	"KC_COMMA",
	"KC_PERIOD",    // . on main keyboard
	"KC_SLASH",    // / on main keyboard
	"KC_RSHIFT",
	"KC_MULTIPLY",    // * on numeric keypad
	"KC_LMENU",    // left Alt
	"KC_SPACE",
	"KC_CAPITAL",
	"KC_F1",
	"KC_F2",
	"KC_F3",
	"KC_F4",
	"KC_F5",
	"KC_F6",
	"KC_F7",
	"KC_F8",
	"KC_F9",
	"KC_F10",
	"KC_NUMLOCK",
	"KC_SCROLL",    // Scroll Lock
	"KC_NUMPAD7",
	"KC_NUMPAD8",
	"KC_NUMPAD9",
	"KC_SUBTRACT",    // - on numeric keypad
	"KC_NUMPAD4",
	"KC_NUMPAD5",
	"KC_NUMPAD6",
	"KC_ADD",    // + on numeric keypad
	"KC_NUMPAD1",
	"KC_NUMPAD2",
	"KC_NUMPAD3",
	"KC_NUMPAD0",
	"KC_DECIMAL",    // . on numeric keypad
	"KC_OEM_102",    // < > | on UK/Germany keyboards
	"KC_F11",
	"KC_F12",
	"KC_F13",    //                     (NEC PC98)
	"KC_F14",    //                     (NEC PC98)
	"KC_F15",    //                     (NEC PC98)
	"KC_KANA",    // (Japanese keyboard)
	"KC_ABNT_C1",    // / ? on Portugese (Brazilian) keyboards
	"KC_CONVERT",    // (Japanese keyboard)
	"KC_NOCONVERT",    // (Japanese keyboard)
	"KC_YEN",    // (Japanese keyboard)
	"KC_ABNT_C2",    // Numpad . on Portugese (Brazilian) keyboards
	"KC_NUMPADEQUALS",    // = on numeric keypad (NEC PC98)
	"KC_PREVTRACK",    // Previous Track (KC_CIRCUMFLEX on Japanese keyboard)
	"KC_AT",    //                     (NEC PC98)
	"KC_COLON",    //                     (NEC PC98)
	"KC_UNDERLINE",    //                     (NEC PC98)
	"KC_KANJI",    // (Japanese keyboard)
	"KC_STOP",    //                     (NEC PC98)
	"KC_AX",    //                     (Japan AX)
	"KC_UNLABELED",    //                        (J3100)
	"KC_NEXTTRACK",    // Next Track
	"KC_NUMPADENTER",    // Enter on numeric keypad
	"KC_RCONTROL",
	"KC_MUTE",    // Mute
	"KC_CALCULATOR",    // Calculator
	"KC_PLAYPAUSE",    // Play / Pause
	"KC_MEDIASTOP",    // Media Stop
	"KC_VOLUMEDOWN",    // Volume -
	"KC_VOLUMEUP",    // Volume +
	"KC_WEBHOME",    // Web home
	"KC_NUMPADCOMMA",    // , on numeric keypad (NEC PC98)
	"KC_DIVIDE",    // / on numeric keypad
	"KC_SYSRQ",
	"KC_RMENU",    // right Alt
	"KC_PAUSE",    // Pause
	"KC_HOME",    // Home on arrow keypad
	"KC_UP",    // UpArrow on arrow keypad
	"KC_PGUP",    // PgUp on arrow keypad
	"KC_LEFT",    // LeftArrow on arrow keypad
	"KC_RIGHT",    // RightArrow on arrow keypad
	"KC_END",    // End on arrow keypad
	"KC_DOWN",    // DownArrow on arrow keypad
	"KC_PGDOWN",    // PgDn on arrow keypad
	"KC_INSERT",    // Insert on arrow keypad
	"KC_DELETE",    // Delete on arrow keypad
	"KC_LWIN",    // Left Windows key
	"KC_RWIN",    // Right Windows key
	"KC_APPS",    // AppMenu key
	"KC_POWER",    // System Power
	"KC_SLEEP",    // System Sleep
	"KC_WAKE",    // System Wake
	"KC_WEBSEARCH",    // Web Search
	"KC_WEBFAVORITES",    // Web Favorites
	"KC_WEBREFRESH",    // Web Refresh
	"KC_WEBSTOP",    // Web Stop
	"KC_WEBFORWARD",    // Web Forward
	"KC_WEBBACK",    // Web Back
	"KC_MYCOMPUTER",    // My Computer
	"KC_MAIL",    // Mail
	"KC_MEDIASELECT"
};

int ois_keyboard_values[] = {
	OIS::KC_UNASSIGNED,
	OIS::KC_ESCAPE,
	OIS::KC_1,
	OIS::KC_2,
	OIS::KC_3,
	OIS::KC_4,
	OIS::KC_5,
	OIS::KC_6,
	OIS::KC_7,
	OIS::KC_8,
	OIS::KC_9,
	OIS::KC_0,
	OIS::KC_MINUS,    // - on main keyboard
	OIS::KC_EQUALS,
	OIS::KC_BACK,    // backspace
	OIS::KC_TAB,
	OIS::KC_Q,
	OIS::KC_W,
	OIS::KC_E,
	OIS::KC_R,
	OIS::KC_T,
	OIS::KC_Y,
	OIS::KC_U,
	OIS::KC_I,
	OIS::KC_O,
	OIS::KC_P,
	OIS::KC_LBRACKET,
	OIS::KC_RBRACKET,
	OIS::KC_RETURN,    // Enter on main keyboard
	OIS::KC_LCONTROL,
	OIS::KC_A,
	OIS::KC_S,
	OIS::KC_D,
	OIS::KC_F,
	OIS::KC_G,
	OIS::KC_H,
	OIS::KC_J,
	OIS::KC_K,
	OIS::KC_L,
	OIS::KC_SEMICOLON,
	OIS::KC_APOSTROPHE,
	OIS::KC_GRAVE,    // accent
	OIS::KC_LSHIFT,
	OIS::KC_BACKSLASH,
	OIS::KC_Z,
	OIS::KC_X,
	OIS::KC_C,
	OIS::KC_V,
	OIS::KC_B,
	OIS::KC_N,
	OIS::KC_M,
	OIS::KC_COMMA,
	OIS::KC_PERIOD,    // . on main keyboard
	OIS::KC_SLASH,    // / on main keyboard
	OIS::KC_RSHIFT,
	OIS::KC_MULTIPLY,    // * on numeric keypad
	OIS::KC_LMENU,    // left Alt
	OIS::KC_SPACE,
	OIS::KC_CAPITAL,
	OIS::KC_F1,
	OIS::KC_F2,
	OIS::KC_F3,
	OIS::KC_F4,
	OIS::KC_F5,
	OIS::KC_F6,
	OIS::KC_F7,
	OIS::KC_F8,
	OIS::KC_F9,
	OIS::KC_F10,
	OIS::KC_NUMLOCK,
	OIS::KC_SCROLL,    // Scroll Lock
	OIS::KC_NUMPAD7,
	OIS::KC_NUMPAD8,
	OIS::KC_NUMPAD9,
	OIS::KC_SUBTRACT,    // - on numeric keypad
	OIS::KC_NUMPAD4,
	OIS::KC_NUMPAD5,
	OIS::KC_NUMPAD6,
	OIS::KC_ADD,    // + on numeric keypad
	OIS::KC_NUMPAD1,
	OIS::KC_NUMPAD2,
	OIS::KC_NUMPAD3,
	OIS::KC_NUMPAD0,
	OIS::KC_DECIMAL,    // . on numeric keypad
	OIS::KC_OEM_102,    // < > | on UK/Germany keyboards
	OIS::KC_F11,
	OIS::KC_F12,
	OIS::KC_F13,    //                     (NEC PC98)
	OIS::KC_F14,    //                     (NEC PC98)
	OIS::KC_F15,    //                     (NEC PC98)
	OIS::KC_KANA,    // (Japanese keyboard)
	OIS::KC_ABNT_C1,    // / ? on Portugese (Brazilian) keyboards
	OIS::KC_CONVERT,    // (Japanese keyboard)
	OIS::KC_NOCONVERT,    // (Japanese keyboard)
	OIS::KC_YEN,    // (Japanese keyboard)
	OIS::KC_ABNT_C2,    // Numpad . on Portugese (Brazilian) keyboards
	OIS::KC_NUMPADEQUALS,    // = on numeric keypad (NEC PC98)
	OIS::KC_PREVTRACK,    // Previous Track (KC_CIRCUMFLEX on Japanese keyboard)
	OIS::KC_AT,    //                     (NEC PC98)
	OIS::KC_COLON,    //                     (NEC PC98)
	OIS::KC_UNDERLINE,    //                     (NEC PC98)
	OIS::KC_KANJI,    // (Japanese keyboard)
	OIS::KC_STOP,    //                     (NEC PC98)
	OIS::KC_AX,    //                     (Japan AX)
	OIS::KC_UNLABELED,    //                        (J3100)
	OIS::KC_NEXTTRACK,    // Next Track
	OIS::KC_NUMPADENTER,    // Enter on numeric keypad
	OIS::KC_RCONTROL,
	OIS::KC_MUTE,    // Mute
	OIS::KC_CALCULATOR,    // Calculator
	OIS::KC_PLAYPAUSE,    // Play / Pause
	OIS::KC_MEDIASTOP,    // Media Stop
	OIS::KC_VOLUMEDOWN,    // Volume -
	OIS::KC_VOLUMEUP,    // Volume +
	OIS::KC_WEBHOME,    // Web home
	OIS::KC_NUMPADCOMMA,    // , on numeric keypad (NEC PC98)
	OIS::KC_DIVIDE,    // / on numeric keypad
	OIS::KC_SYSRQ,
	OIS::KC_RMENU,    // right Alt
	OIS::KC_PAUSE,    // Pause
	OIS::KC_HOME,    // Home on arrow keypad
	OIS::KC_UP,    // UpArrow on arrow keypad
	OIS::KC_PGUP,    // PgUp on arrow keypad
	OIS::KC_LEFT,    // LeftArrow on arrow keypad
	OIS::KC_RIGHT,    // RightArrow on arrow keypad
	OIS::KC_END,    // End on arrow keypad
	OIS::KC_DOWN,    // DownArrow on arrow keypad
	OIS::KC_PGDOWN,    // PgDn on arrow keypad
	OIS::KC_INSERT,    // Insert on arrow keypad
	OIS::KC_DELETE,    // Delete on arrow keypad
	OIS::KC_LWIN,    // Left Windows key
	OIS::KC_RWIN,    // Right Windows key
	OIS::KC_APPS,    // AppMenu key
	OIS::KC_POWER,    // System Power
	OIS::KC_SLEEP,    // System Sleep
	OIS::KC_WAKE,    // System Wake
	OIS::KC_WEBSEARCH,    // Web Search
	OIS::KC_WEBFAVORITES,    // Web Favorites
	OIS::KC_WEBREFRESH,    // Web Refresh
	OIS::KC_WEBSTOP,    // Web Stop
	OIS::KC_WEBFORWARD,    // Web Forward
	OIS::KC_WEBBACK,    // Web Back
	OIS::KC_MYCOMPUTER,    // My Computer
	OIS::KC_MAIL,    // Mail
	OIS::KC_MEDIASELECT
};

const char *ois_keyboard_modifiers[] = {
	"Shift",
	"Ctrl",
	"Alt"
};

int ois_keyboard_modifiers_values[] = {
	OIS::Keyboard::Shift,
	OIS::Keyboard::Ctrl,
	OIS::Keyboard::Alt
};

int getOISKeyboardConstant(const char* name) {
	int i = 0;
	int length = sizeof(ois_keyboard) / sizeof(char *);
	for (i = 0; i < length; i++) {
		if (strcmp(name, ois_keyboard[i]) == 0)
			return ois_keyboard_values[i];
	}
	return -1;
}

int getOISKeyboardModifierConstant(const char* name) {
	int i = 0;
	int length = sizeof(ois_keyboard_modifiers) / sizeof(char *);
	for (i = 0; i < length; i++) {
		if (strcmp(name, ois_keyboard_modifiers[i]) == 0)
			return ois_keyboard_modifiers_values[i];
	}
	return -1;
}

#endif

