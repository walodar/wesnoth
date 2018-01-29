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

#pragma once

#include <cstdint>
#include <string>

namespace desktop
{
class rich_presence_manager
{
public:
	rich_presence_manager();
	~rich_presence_manager();
};

/**
 *
 */
struct discord_presence
{
	discord_presence();

	void send() const;

	std::string state;   /* max 128 bytes */
	std::string details; /* max 128 bytes */

	int64_t start_timestamp;
	int64_t end_timestamp;

	std::string large_image_key;  /* max 32 bytes */
	std::string large_image_text; /* max 128 bytes */
	std::string small_image_key;  /* max 32 bytes */
	std::string small_image_text; /* max 128 bytes */
	std::string party_id;         /* max 128 bytes */

	int party_size;
	int party_max;

	std::string match_secret;    /* max 128 bytes */
	std::string join_secret;     /* max 128 bytes */
	std::string spectate_secret; /* max 128 bytes */

	int8_t instance;
};

} // namespace desktop
