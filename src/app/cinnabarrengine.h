/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2026  Cinnabarr contributors
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 */

#pragma once

// Settings for running as Cinnabarr's headless download engine ("cinnabarr-engine").
// Cinnabarr starts the engine as a child process and is its only client, so the
// engine is reachable on the loopback interface only and only with an API key
// that Cinnabarr passes in the environment.
namespace CinnabarrEngine
{
    // Name of the environment variable that carries the WebUI API key.
    inline constexpr char API_KEY_ENV[] = "CINNABARR_ENGINE_API_KEY";

    // Applies the forced engine settings. Throws RuntimeError if the API key is
    // missing or invalid, because the engine must never run without one.
    void applySettings();
}
