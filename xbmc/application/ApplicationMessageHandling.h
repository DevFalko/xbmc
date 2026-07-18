/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "application/AppInboundProtocol.h"

#include <memory>

class CApplication;
class CFileItem;
class CGUIMessage;
namespace KODI::MESSAGING
{
class ThreadMessage;
}

class CApplicationMessageHandling : public CAppInboundProtocol
{
public:
  explicit CApplicationMessageHandling(CApplication& app);
  ~CApplicationMessageHandling();

  void OnApplicationMessage(KODI::MESSAGING::ThreadMessage* pMsg);
  bool OnMessage(const CGUIMessage& message);

private:
  CApplication& m_app;

#ifdef TARGET_ANDROID
  bool m_androidSkinUnloadedForDisplayDestroy{false};
  // Video playback captured when the Android surface is torn down during playback (screen
  // lock, PiP/rotation, incoming call) so it can be resumed at the same position once the
  // surface and render system are back. See the TMSG_DISPLAY_DESTROY/SETUP handlers.
  std::unique_ptr<CFileItem> m_androidResumeItem;
  // True while a surface loss is being survived in place (player kept alive + paused, kill-switch
  // enabled) rather than closed. Set on TMSG_DISPLAY_DESTROY, consumed on TMSG_DISPLAY_SETUP.
  bool m_androidSurviveSurfaceLossActive{false};
#endif
};
