//******************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose:
//
//******************************************************************************

#ifndef INC_CAUTOCONNECTOR_H
#define INC_CAUTOCONNECTOR_H

#include "..\CCritSec\CCritSec.h"
#include "..\CTablemap\CTablemap.h"


class CAutoConnector {
 public:
	CAutoConnector();
	~CAutoConnector();
 public:
	bool Connect(HWND targetHWnd);
	void Disconnect(CString reason_for_disconnection);
	bool IsConnected();
	double TimeSincelast_failed_attempt_to_connect(); // seconds
 public:
	// public accessors
	const HWND attached_hwnd()    { return _attached_hwnd; }
 private:
	int SelectTableMapAndWindow(int Choices);
	int SelectTableMapAndWindowAutomatically(int Choices);
	void LoadScraperDLL();
	void WriteLogTableReset(CString event_and_reason);
 private:
	void Check_TM_Against_All_Windows_Or_TargetHWND(int tablemap_index, HWND targetHWnd);
  void CheckIfWindowMatchesMoreThanOneTablemap(HWND hwnd);
 private:
	#define ENT CSLock lock(m_critsec);
	void set_attached_hwnd(const HWND h) { ENT _attached_hwnd = h; }
	#undef ENT
 private:
	void FailedToConnectBecauseNoWindowInList();
	void FailedToConnectProbablyBecauseAllTablesAlreadyServed();
	void GoIntoPopupBlockingMode();
 private:
	// private variables - use public accessors and public mutators to address these
	HWND		  _attached_hwnd; // Table that we are attached to
	CCritSec	m_critsec;
 private:
	// Mutex used for cross-instance autoconnector coordination
	CMutex	*_autoconnector_mutex;
};

extern  CAutoConnector *p_autoconnector;

#endif INC_CAUTOCONNECTOR_H