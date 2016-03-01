/*
 *  This file is part of nzbget. See <http://nzbget.net>.
 *
 *  Copyright (C) 2007-2016 Andrey Prygunkov <hugbug@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef QUEUESCRIPT_H
#define QUEUESCRIPT_H

#include "DownloadInfo.h"
#include "ScriptConfig.h"

class QueueScriptCoordinator
{
public:
	enum EEvent
	{
		qeFileDownloaded, // lowest priority
		qeUrlCompleted,
		qeNzbAdded,
		qeNzbDownloaded,
		qeNzbDeleted // highest priority
	};

	~QueueScriptCoordinator();
	void Stop() { m_stopped = true; }
	void InitOptions();
	void EnqueueScript(NzbInfo* nzbInfo, EEvent event);
	void CheckQueue();
	bool HasJob(int nzbId, bool* active);
	int GetQueueSize();

private:
	class QueueItem
	{
	public:
		QueueItem(int nzbId, ScriptConfig::Script* script, EEvent event) :
			m_nzbId(nzbId), m_script(script), m_event(event) {}
		int GetNzbId() { return m_nzbId; }
		ScriptConfig::Script* GetScript() { return m_script; }
		EEvent GetEvent() { return m_event; }
	private:
		int m_nzbId;
		ScriptConfig::Script* m_script;
		EEvent m_event;
	};

	typedef std::list<QueueItem*> Queue;

	Queue m_queue;
	Mutex m_queueMutex;
	QueueItem* m_curItem = nullptr;
	bool m_hasQueueScripts = false;
	bool m_stopped = false;

	void StartScript(NzbInfo* nzbInfo, QueueItem* queueItem);
	NzbInfo* FindNzbInfo(DownloadQueue* downloadQueue, int nzbId);
	bool UsableScript(ScriptConfig::Script& script, NzbInfo* nzbInfo, EEvent event);
};

extern QueueScriptCoordinator* g_QueueScriptCoordinator;

#endif
