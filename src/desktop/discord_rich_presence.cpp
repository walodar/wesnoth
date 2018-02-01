/*
   Copyright (C) 2018 by the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

#include "desktop/discord_rich_presence.hpp"

#include "log.hpp"

#include <discord-rpc.h>

static lg::log_domain log_desktop("desktop");
#define ERR_DU LOG_STREAM(err, log_desktop)
#define LOG_DU LOG_STREAM(info, log_desktop)

namespace desktop
{
namespace
{
const char* DISCORD_APP_ID = "407478227485982720";
const char* STEAM_APP_ID = "599390";

//
// NOTE: These callbacks aren't actually executed unless Discord_RunCallbacks
// is called, since the Discord RPC API is threaded. Right now I don't exactly
// have a logical place to call it, nor do I know how logging is affected by
// threading. Will figure it out.
//
// -- vultraz, 2018-02-02
//

void callback_ready()
{
	LOG_DU << "Discord Rich Presence ready\n";
}

void callback_errored(int /*errorCode*/, const char* message)
{
	ERR_DU << "Discord Rich Presence errored: " << message << "\n";
}

void callback_disconnected(int /*errorCode*/, const char* message)
{
	LOG_DU << "Discord Rich Presence disconnected: " << message << "\n";
}

} // end anon namespace

rich_presence_manager::rich_presence_manager()
{
	DiscordEventHandlers handlers;
	std::memset(&handlers, 0, sizeof(handlers));

	handlers.ready = &callback_ready;
	handlers.errored = &callback_errored;
	handlers.disconnected = &callback_disconnected;

	// TODO: we might want to add the ability to join/observe games directly from
	// Discord in the future, but that requires special approval by Discord. Leaving
	// these callbacks null for now.
	handlers.joinGame = nullptr;
	handlers.spectateGame = nullptr;
	handlers.joinRequest = nullptr;

	Discord_Initialize(DISCORD_APP_ID, &handlers, 1, STEAM_APP_ID);
}

rich_presence_manager::~rich_presence_manager()
{
	Discord_Shutdown();
}

discord_presence::discord_presence()
	: state()
	, details()
	, start_timestamp(0)
	, end_timestamp(0)
	, large_image_key("weslogo") // NOTE: right now we only have one large image.
	, large_image_text()
	, small_image_key()
	, small_image_text()
	, party_id()
	, party_size(0)
	, party_max(0)
	, match_secret()
	, join_secret()
	, spectate_secret()
	, instance(0)
{
}

void discord_presence::send() const
{
	DiscordRichPresence data;
	std::memset(&data, 0, sizeof(data));

	data.state = state.c_str();
	data.details = details.c_str();
	data.startTimestamp = start_timestamp;
	data.endTimestamp = end_timestamp;
	data.largeImageKey = large_image_key.c_str();
	data.largeImageText = large_image_text.c_str();
	data.smallImageKey = small_image_key.c_str();
	data.smallImageText = small_image_text.c_str();
	data.partyId = party_id.c_str();
	data.partySize = party_size;
	data.partyMax = party_max;
	data.matchSecret = match_secret.c_str();
	data.joinSecret = join_secret.c_str();
	data.spectateSecret = spectate_secret.c_str();
	data.instance = instance;

	Discord_UpdatePresence(&data);
}

} // namespace desktop1
