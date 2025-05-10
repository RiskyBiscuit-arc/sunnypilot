/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/sunnypilot/qt/offroad/settings/vehicle/hyundai_settings.h"

HyundaiSettings::HyundaiSettings(QWidget *parent) : BrandSettingsInterface(parent) {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0, 0, 0, 0);

  ListWidget *list = new ListWidget(this, false);

  main_layout->addWidget(list);
}

void HyundaiSettings::updateSettings() {
}
