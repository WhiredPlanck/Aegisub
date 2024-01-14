// Copyright (c) 2013, Thomas Goyne <plorkyeran@aegisub.org>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// Aegisub Project http://www.aegisub.org/

#include <libaegisub/path.h>

#include <libaegisub/exception.h>
#include <libaegisub/util_osx.h>

#include <boost/filesystem/operations.hpp>
#include <pwd.h>

namespace {
#ifndef __APPLE__
std::string home_dir() {
	const char *env = getenv("HOME");
	if (env) return env;

	if ((env = getenv("USER")) || (env = getenv("LOGNAME"))) {
		if (passwd *user_info = getpwnam(env))
			return user_info->pw_dir;
	}

	throw agi::EnvironmentError("Could not get home directory. Make sure HOME is set.");
}

std::string xdg_dir(const std::string &environment_variable,
                    const std::string &fallback_directory)
{
	const char *env = getenv(environment_variable.c_str());
	if (env && *env) return env;
	return fallback_directory;
}
#endif
}

namespace agi {
void Path::FillPlatformSpecificPaths() {
#ifndef __APPLE__
	agi::fs::path home = home_dir();
	agi::fs::path prev_dir = home/".aegisub";
	if (!boost::filesystem::exists(prev_dir))
	{
		agi::fs::path xdg_config_home = xdg_dir("XDG_CONFIG_HOME", (home/".config").string());
		agi::fs::path xdg_cache_home = xdg_dir("XDG_CACHE_HOME", (home/".cache").string());
		agi::fs::path xdg_state_home = xdg_dir("XDG_STATE_HOME", (home/".local/state").string());
		SetToken("?user", xdg_config_home/"Aegisub");
		SetToken("?local", xdg_cache_home/"Aegisub");
		SetToken("?state", xdg_state_home/"Aegisub");
	} else {
		SetToken("?user", prev_dir);
	    SetToken("?local", prev_dir);
		SetToken("?state", prev_dir);
	}
	SetToken("?data", P_DATA);
	SetToken("?dictionary", "/usr/share/hunspell");
#else
	agi::fs::path app_support = agi::util::GetApplicationSupportDirectory();
	SetToken("?user", app_support/"Aegisub");
	SetToken("?local", app_support/"Aegisub");
	SetToken("?state", app_support/"Aegisub");
	SetToken("?data", agi::util::GetBundleSharedSupportDirectory());
	SetToken("?dictionary", agi::util::GetBundleSharedSupportDirectory() + "/dictionaries");
#endif
	SetToken("?temp", boost::filesystem::temp_directory_path());
}

}
