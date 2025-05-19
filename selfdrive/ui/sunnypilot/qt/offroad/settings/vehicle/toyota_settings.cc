/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/sunnypilot/qt/offroad/settings/vehicle/toyota_settings.h"

#include <list>

ToyotaSettings::ToyotaSettings(QWidget *parent) : BrandSettingsInterface(parent) {

    toyotaFlipACC = new ParamControlSP(
    "CustomAccFlipIncrements",
    tr("Flip ACC Controls"),
    tr("Flips the Short & Long press ACC increment values."),
    "",
    parent);
    list->addItem(toyotaFlipACC);
}

void ToyotaSettings::updateSettings() {
}
