/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/sunnypilot/qt/offroad/settings/sunnylink_panel.h"

#include "selfdrive/ui/sunnypilot/qt/util.h"
#include "selfdrive/ui/sunnypilot/qt/widgets/controls.h"

SunnylinkPanel::SunnylinkPanel(QWidget *parent) : QFrame(parent) {
  main_layout = new QStackedLayout(this);
  ListWidget *list = new ListWidget(this, false);

  sunnylinkScreen = new QWidget(this);
  QVBoxLayout *vlayout = new QVBoxLayout(sunnylinkScreen);
  vlayout->setContentsMargins(50, 20, 50, 20);

  QString sunnylinkEnabledBtnDesc = tr("This is the master switch, it will allow you to cutoff any sunnylink requests should you want to do that.");
  sunnylinkEnabledBtn = new ParamControl(
    "SunnylinkEnabled",
    tr("Enable sunnylink"),
    sunnylinkEnabledBtnDesc,
    "");
  list->addItem(sunnylinkEnabledBtn);

  connect(sunnylinkEnabledBtn, &ParamControl::showDescriptionEvent, [=]() {
    //resets the description to the default one for the easter egg
    sunnylinkEnabledBtn->setDescription(sunnylinkEnabledBtnDesc);
  });

  connect(sunnylinkEnabledBtn, &ParamControl::toggleFlipped, [=](bool enabled) {
    if (enabled) {
      auto proud_description = "<font color='SeaGreen'>"+ tr("🎉Welcome back! We're excited to see you've enabled sunnylink again! 🚀")+ "</font>";
      sunnylinkEnabledBtn->showDescription();
      sunnylinkEnabledBtn->setDescription(proud_description);
    } else {
      auto shame_description = "<font color='orange'>"+ tr("👋Not going to lie, it's sad to see you disabled sunnylink 😢, but we'll be here when you're ready to come back 🎉.")+ "</font>";
      sunnylinkEnabledBtn->showDescription();
      sunnylinkEnabledBtn->setDescription(shame_description);
    }

    updateLabels();
  });

  sunnylinkScroller = new ScrollViewSP(list, this);
  vlayout->addWidget(sunnylinkScroller);
  vlayout->addStretch(1);

  main_layout->addWidget(sunnylinkScreen);
}

void SunnylinkPanel::showEvent(QShowEvent *event) {
  updateLabels();
}

void SunnylinkPanel::updateLabels() {
  QString sunnylink_device_id = tr("Device ID") + " " + getSunnylinkDongleId().value_or(tr("N/A"));

  if (sunnylinkEnabledBtn->isToggled()) {
    sunnylinkEnabledBtn->setValue(sunnylink_device_id);
  } else {
    sunnylinkEnabledBtn->setValue("");
  }
}
