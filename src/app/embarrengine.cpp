/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2026  Embarr contributors
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

#include "embarrengine.h"

#include <QCoreApplication>
#include <QString>

#include "base/exceptions.h"
#include "base/global.h"
#include "base/preferences.h"
#include "base/settingvalue.h"
#include "base/utils/apikey.h"

void EmbarrEngine::applySettings()
{
    const QString apiKey = qEnvironmentVariable(API_KEY_ENV);
    if (!Utils::APIKey::isValid(apiKey))
    {
        throw RuntimeError(QCoreApplication::translate("EmbarrEngine"
            , "%1 is missing or invalid. embarr-engine must be started by Embarr.").arg(QString::fromLatin1(API_KEY_ENV)));
    }

    auto *pref = Preferences::instance();

    // Private API for Embarr only: loopback, plain HTTP, API key required.
    pref->setWebUIEnabled(true);
    pref->setWebUIAddress(u"127.0.0.1"_s);
    pref->setUPnPForWebUIPort(false);
    pref->setWebUIHttpsEnabled(false);
    pref->setAltWebUIEnabled(false);
    pref->setWebUILocalAuthEnabled(true);
    pref->setWebUIAuthSubnetWhitelistEnabled(false);
    pref->setWebUIApiKey(apiKey);

    // Embarr searches indexers itself.
    pref->setSearchEnabled(false);

    // Embarr downloads straight to the final library path: incomplete files keep
    // the ".!qB" suffix, and unwanted files are never moved into a visible folder.
    SettingValue<bool> {u"BitTorrent/Session/AddExtensionToIncompleteFiles"_s} = true;
    SettingValue<bool> {u"BitTorrent/Session/UseUnwantedFolder"_s} = false;
}
