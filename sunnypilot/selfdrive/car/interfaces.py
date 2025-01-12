"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

from opendbc.car import Bus, structs
from opendbc.car.can_definitions import CanRecvCallable, CanSendCallable
from opendbc.car.car_helpers import can_fingerprint
from opendbc.car.hyundai.radar_interface import RADAR_START_ADDR
from opendbc.car.hyundai.values import HyundaiFlags, DBC as HYUNDAI_DBC
from opendbc.sunnypilot.car.hyundai.values import HyundaiFlagsSP


def setup_car_interface_sp(CP: structs.CarParams, params):
  if CP.carName == 'hyundai':
    if CP.flags & HyundaiFlags.MANDO_RADAR and CP.radarUnavailable:
      CP.sunnypilotFlags |= HyundaiFlagsSP.ENABLE_RADAR_TRACKS.value
      if params.get_bool("HyundaiRadarPoints"):
        CP.radarUnavailable = False


def initialize_car_interface_sp(CP: structs.CarParams, params, can_recv: CanRecvCallable, can_send: CanSendCallable):
  if CP.carName == 'hyundai':
    if CP.sunnypilotFlags & HyundaiFlagsSP.ENABLE_RADAR_TRACKS:
      _, fingerprint = can_fingerprint(can_recv)
      radar_unavailable = RADAR_START_ADDR not in fingerprint[1] or Bus.radar not in HYUNDAI_DBC[CP.carFingerprint]

      radar_points = params.get_bool("HyundaiRadarPoints")
      radar_points_persistent = params.get_bool("HyundaiRadarPointsPersistent")

      params.put_bool_nonblocking("HyundaiRadarPointsConfirmed", radar_points)

      if not radar_points_persistent:
        params.put_nonblocking("HyundaiRadarPoints", not radar_unavailable)
        params.put_nonblocking("HyundaiRadarPointsPersistent", True)
