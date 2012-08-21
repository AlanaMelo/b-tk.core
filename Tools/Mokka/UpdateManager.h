/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2012, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UpdateManager_h
#define UpdateManager_h

#include <QObject>
#include <QString>
#include <QStringList>

class UpdateNewVersionDialog;
class UpdateInstallerDialog;
class UpdateController;

class QMessageBox;

class UpdateManagerPrivate;

class UpdateManager: public QObject
{
  Q_OBJECT
  
public:
  UpdateManager(const QString& appVer, const QString& feedUrl = "", const QString& iconPath = "", QWidget* parent = 0);
  virtual ~UpdateManager();
  
  void setIcon(const QString& path);
  void setFeedUrl(const QString& url);
  
public slots:
  void checkUpdate(bool quietNoUpdate = false);
  void finalizeUpdate();

private slots:
  void downloadUpdate();
  void abortDownload();
  void installUpdate();
  void notifyUpdate(const QString& appName, const QString& appCurVer, const QString& appNewVer, const QString& appNote);
  void notifyNoUpdate(const QString& appName, const QString& appCurVer);
  void notifyUpdateError();
  void setDownloadProgress(qint64,qint64);
  void notifyDownloadError();
  void notifyReadyToInstall();
  void notifyInstallationError();
  void restartApplication();
  void resetThread();
  
protected:
  QScopedPointer<UpdateManagerPrivate> d_ptr;
  
private:
  void notifyMessage(QMessageBox* msg, const QString& detail1, const QString& detail2 = "");
  int launchExternalUpdater(const QString& execPath, const QString& params);
  
  Q_DISABLE_COPY(UpdateManager);
  Q_DECLARE_PRIVATE(UpdateManager);
};

#endif