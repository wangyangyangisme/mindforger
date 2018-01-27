/*
 urgency_combo_box.h     MindForger thinking notebook

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef M8RUI_URGENCY_COMBO_BOX_H
#define M8RUI_URGENCY_COMBO_BOX_H

#include <QtWidgets>

namespace m8r {

class UrgencyComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit UrgencyComboBox(QWidget* parent);
    UrgencyComboBox(const UrgencyComboBox&) = delete;
    UrgencyComboBox(const UrgencyComboBox&&) = delete;
    UrgencyComboBox &operator=(const UrgencyComboBox&) = delete;
    UrgencyComboBox &operator=(const UrgencyComboBox&&) = delete;
    ~UrgencyComboBox();

    int8_t getValue() {
        return itemData(currentIndex(), Qt::UserRole).value<int>();
    }
};

}
#endif // M8RUI_URGENCY_COMBO_BOX_H
