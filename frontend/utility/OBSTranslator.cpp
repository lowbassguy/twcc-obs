/******************************************************************************
    Copyright (C) 2023 by Lain Bailey <lain@obsproject.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "OBSTranslator.hpp"

#include <OBSApp.hpp>

#include <qt-wrappers.hpp>

#include "moc_OBSTranslator.cpp"

QString OBSTranslator::translate(const char *, const char *sourceText, const char *, int) const
{
	const char *out = nullptr;
	QString str(sourceText);
	str.replace(" ", "");
	const QByteArray lookup = str.toUtf8();
	if (!App()->TranslateString(lookup.constData(), &out)) {
		QString text = QString::fromUtf8(sourceText);
		return ApplyTWCCBranding(std::move(text), lookup.constData());
	}

	QString text = QT_UTF8(out);
	return ApplyTWCCBranding(std::move(text), lookup.constData());
}
