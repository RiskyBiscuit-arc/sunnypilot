/**
* The MIT License
 *
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Last updated: July 29, 2024
 */

#include "../../sunnypilot/selfdrive/ui/qt/offroad/settings/settings.h"

#include "selfdrive/ui/qt/network/networking.h"
#include "../../sunnypilot/selfdrive/ui/qt/widgets/scrollview.h"
#include "selfdrive/ui/qt/offroad/developer_panel.h"

TogglesPanelSP::TogglesPanelSP(SettingsWindow *parent) : TogglesPanel(parent) {
  QObject::connect(uiStateSP(), &UIStateSP::uiUpdate, this, &TogglesPanelSP::updateState);
}

void TogglesPanelSP::updateState(const UIStateSP &s) {
  TogglesPanel::updateState(s);
}

SettingsWindowSP::SettingsWindowSP(QWidget *parent) : SettingsWindow(parent) {
  // setup two main layouts
  sidebar_widget = new QWidget;
  QVBoxLayout *sidebar_layout = new QVBoxLayout(sidebar_widget);
  panel_widget = new QStackedWidget();

  // setup layout for close button
  QVBoxLayout *close_btn_layout = new QVBoxLayout;
  close_btn_layout->setContentsMargins(0, 0, 0, 20);

  // close button
  QPushButton *close_btn = new QPushButton(tr("×"));
  close_btn->setStyleSheet(R"(
    QPushButton {
      font-size: 140px;
      padding-bottom: 20px;
      border-radius: 76px;
      background-color: #292929;
      font-weight: 400;
    }
    QPushButton:pressed {
      background-color: #3B3B3B;
    }
  )");
  close_btn->setFixedSize(152, 152);
  close_btn_layout->addWidget(close_btn, 0, Qt::AlignLeft);
  QObject::connect(close_btn, &QPushButton::clicked, this, &SettingsWindow::closeSettings);

  // setup buttons widget
  QWidget *buttons_widget = new QWidget;
  QVBoxLayout *buttons_layout = new QVBoxLayout(buttons_widget);
  buttons_layout->setMargin(0);
  buttons_layout->addSpacing(10);

  // setup panels
  DevicePanel *device = new DevicePanel(this);
  QObject::connect(device, &DevicePanel::reviewTrainingGuide, this, &SettingsWindow::reviewTrainingGuide);

  TogglesPanelSP *toggles = new TogglesPanelSP(this);
  QObject::connect(this, &SettingsWindow::expandToggleDescription, toggles, &TogglesPanel::expandToggleDescription);

  auto networking = new Networking(this);
  QObject::connect(uiState()->prime_state, &PrimeState::changed, networking, &Networking::setPrimeType);

  QList<PanelInfo> panels = {
    PanelInfo("   " + tr("Device"), device, "../../sunnypilot/selfdrive/assets/offroad/icon_home.svg"),
    PanelInfo("   " + tr("Network"), networking, "../assets/offroad/icon_network.png"),
    PanelInfo("   " + tr("Toggles"), toggles, "../../sunnypilot/selfdrive/assets/offroad/icon_toggle.png"),
    PanelInfo("   " + tr("Software"), new SoftwarePanel(this), "../../sunnypilot/selfdrive/assets/offroad/icon_software.png"),
    PanelInfo("   " + tr("Developer"), new DeveloperPanel(this), "../assets/offroad/icon_shell.png"),
  };

  nav_btns = new QButtonGroup(this);
  for (auto &[name, panel, icon] : panels) {
    QPushButton *btn = new QPushButton(name);
    btn->setCheckable(true);
    btn->setChecked(nav_btns->buttons().size() == 0);
    btn->setIcon(QIcon(QPixmap(icon)));
    btn->setIconSize(QSize(70, 70));
    btn->setStyleSheet(R"(
      QPushButton {
        border-radius: 20px;
        width: 400px;
        height: 98px;
        color: #bdbdbd;
        border: none;
        background: none;
        font-size: 50px;
        font-weight: 500;
        text-align: left;
        padding-left: 22px;
      }
      QPushButton:checked {
        background-color: #696868;
        color: white;
      }
      QPushButton:pressed {
        color: #ADADAD;
      }
    )");
    btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    nav_btns->addButton(btn);
    buttons_layout->addWidget(btn, 0, Qt::AlignLeft | Qt::AlignBottom);

    const int lr_margin = (name != ("   " + tr("Network")) || (name != ("   " + tr("sunnypilot")))) ? 50 : 0;  // Network and sunnypilot panel handles its own margins
    panel->setContentsMargins(lr_margin, 25, lr_margin, 25);

    ScrollViewSP *panel_frame = new ScrollViewSP(panel, this);
    panel_widget->addWidget(panel_frame);

    QObject::connect(btn, &QPushButton::clicked, [=, w = panel_frame]() {
      btn->setChecked(true);
      panel_widget->setCurrentWidget(w);
    });
  }
  sidebar_layout->setContentsMargins(50, 50, 25, 50);

  // main settings layout, sidebar + main panel
  QHBoxLayout *main_layout = new QHBoxLayout(this);

  // add layout for close button
  sidebar_layout->addLayout(close_btn_layout);

  // add layout for buttons scrolling
  ScrollViewSP *buttons_scrollview = new ScrollViewSP(buttons_widget, this);
  sidebar_layout->addWidget(buttons_scrollview);

  sidebar_widget->setFixedWidth(500);
  main_layout->addWidget(sidebar_widget);
  main_layout->addWidget(panel_widget);

  setStyleSheet(R"(
    * {
      color: white;
      font-size: 50px;
    }
    SettingsWindow {
      background-color: black;
    }
    QStackedWidget, ScrollViewSP {
      background-color: black;
      border-radius: 30px;
    }
  )");
}
