/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/sunnypilot/qt/offroad/settings/device_panel.h"

#include "common/watchdog.h"
#include "selfdrive/ui/qt/offroad/driverview.h"
#include "selfdrive/ui/qt/qt_window.h"

DevicePanelSP::DevicePanelSP(SettingsWindowSP *parent) : DevicePanel(parent) {
  QGridLayout *device_grid_layout = new QGridLayout();
  device_grid_layout->setSpacing(30);
  device_grid_layout->setHorizontalSpacing(5);
  device_grid_layout->setVerticalSpacing(25);

  std::vector<std::pair<QString, QString>> device_btns = {
    {"dcamBtn", tr("Driver Camera Preview")},
    {"retrainingBtn", tr("Training Guide")},
    {"regulatoryBtn", tr("Regulatory")},
    {"translateBtn", tr("Language")},
  };

  for (int i = 0; i < device_btns.size(); i++) {
    auto *btn = new PushButtonSP(device_btns[i].second, 720, this);
    device_grid_layout->addWidget(btn, i / 2, i % 2);
    buttons[device_btns[i].first] = btn;
  }

  connect(buttons["dcamBtn"], &PushButtonSP::clicked, [this]() {
    buttons["dcamBtn"]->setEnabled(false);
    DriverViewDialog driver_view(this);
    driver_view.exec();
    buttons["dcamBtn"]->setEnabled(true);
  });

  connect(buttons["retrainingBtn"], &PushButtonSP::clicked, [=]() {
    if (ConfirmationDialog::confirm(tr("Are you sure you want to review the training guide?"), tr("Review"), this)) {
      emit reviewTrainingGuide();
    }
  });

  if (Hardware::TICI()) {
    connect(buttons["regulatoryBtn"], &PushButtonSP::clicked, [=]() {
      const std::string txt = util::read_file("../assets/offroad/fcc.html");
      ConfirmationDialog::rich(QString::fromStdString(txt), this);
    });
  } else {
    buttons["regulatoryBtn"]->setEnabled(false);
  }

  connect(buttons["translateBtn"], &PushButtonSP::clicked, [=]() {
    QMap<QString, QString> langs = getSupportedLanguages();
    QString selection = MultiOptionDialog::getSelection(tr("Select a language"), langs.keys(), langs.key(uiState()->language), this);
    if (!selection.isEmpty()) {
      // put language setting, exit Qt UI, and trigger fast restart
      params.put("LanguageSetting", langs[selection].toStdString());
      qApp->exit(18);
      watchdog_kick(0);
    }
  });

  addItem(device_grid_layout);
}
