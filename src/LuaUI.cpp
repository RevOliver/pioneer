#include "LuaUI.h"
#include "LuaObject.h"
#include "LuaUtils.h"
#include "Pi.h"
#include "ShipCpanel.h"

/*
 * Interface: UI
 *
 * User interface functions.
 */

/*
 * Function: Message
 *
 * Post a message to the player's control panel.
 *
 * Availability:
 *
 *  alpha 10
 *
 * Status:
 *
 *  experimental
 */
static int l_ui_message(lua_State *l)
{
	std::string from = luaL_checkstring(l, 1);
	std::string msg = luaL_checkstring(l, 2);
	Pi::cpan->MsgLog()->Message(from, msg);
	return 0;
}

/*
 * Function: ImportantMessage
 *
 * Post an important message to the player's control panel. The only
 * difference between this and <Message> is that if multiple messages arrive
 * at the same time, the important ones will be shown first.
 *
 * Availability:
 *
 *  alpha 10
 *
 * Status:
 *
 *  experimental
 */
static int l_ui_important_message(lua_State *l)
{
	std::string from = luaL_checkstring(l, 1);
	std::string msg = luaL_checkstring(l, 2);
	Pi::cpan->MsgLog()->ImportantMessage(from, msg);
	return 0;
}

void LuaUI::Register()
{
	lua_State *l = Pi::luaManager.GetLuaState();

	LUA_DEBUG_START(l);

	static const luaL_reg methods[] = {
		{ "Message",          l_ui_message           },
		{ "ImportantMessage", l_ui_important_message },
		{ 0, 0 }
	};

	luaL_register(l, "UI", methods);
	lua_pop(l, 1);

	LUA_DEBUG_END(l, 0);
}