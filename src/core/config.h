/***************************************************************************
 *   Copyright (C) 2009 - 2012 by Artem 'DOOMer' Galichkin                        *
 *   doomer3d@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include "cmdline.h"
#include "shortcutmanager.h"

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QSize>
#include <QtCore/QHash>
#include <QtCore/QVariant>

//  default values const
const QString DEF_SAVE_NAME = "screen";
const QString DEF_SAVE_FORMAT = "png";
const quint8 DEF_DELAY = 0;
const bool DEF_X11_NODECOR = false;
const quint8 DEF_TRAY_MESS_TYPE = 1;
const quint8 DEF_FILENAME_TO_CLB = 0;
const quint8 DEF_IMG_QUALITY = 80;
const bool DEF_CLOSE_IN_TRAY = false;
const bool DEF_ALLOW_COPIES = true;
const bool DEF_SAVED_SIZE = false;
const bool DEF_ZOOM_AROUND_MOUSE = false;
const int DEF_WND_WIDTH = 480;
const int DEF_WND_HEIGHT = 281;
const int DEF_TIME_TRAY_MESS = 5;
const bool DEF_DATETIME_FILENAME = false;
const bool DEF_AUTO_SAVE = false;
const bool DEF_AUTO_SAVE_FIRST = false;
const QString DEF_DATETIME_TPL = "yyyy-MM-dd-hh-mm-ss";
const bool DEF_SHOW_TRAY = true;

// class worker with conf data
class Config
{
public:
    //type of shortcut
    enum Type {
        globalShortcut = 0,
        localShortcut = 1
    };

    Q_DECLARE_FLAGS(ShortcutType, Type)

    //defination of shortcut

    enum Actions {
        shortcutFullScreen = 0,
        shortcutActiveWnd = 1,
        shortcutAreaSelect = 2,
        shortcutNew = 3,
        shortcutSave = 4,
        shortcutCopy = 5,
        shortcutOptions = 6,
        shortcutHelp = 7,
        shortcutClose = 8
    };

    Q_DECLARE_FLAGS(ShortcutAction, Actions)

    enum AutoCopyFilename {
        nameToClipboardOff = 0,
        nameToClipboardFile = 1,
        nameToClipboardPath = 2
    };

    Q_DECLARE_FLAGS(FilenameToClipboard, AutoCopyFilename)

    /**
     * Get current instance of configuration object
     * @return Pointer on created object
     */
    static Config* instance();

    /**
     * Destroy current Config object
     */
    static void killInstance();
    ~Config();

    static QString getConfigFile();
    static QString getConfigDir();
    
    /**
     * Load configuration data from conf file
     */
    void loadSettings();

    /**
     * Save configuration data to conf file
     */
    void saveSettings();

    /**
     * Reset configuration data from default values
     */
    void setDefaultSettings();

    // save dir
    QString getSaveDir();
    void setSaveDir(QString path);

    // filename default
    QString getSaveFileName();
    void setSaveFileName(QString fileName);

    // save format str
    QString getSaveFormat();
    void setSaveFormat(QString format);

    // default delay
    quint8 getDefDelay();
    void setDefDelay(quint8 sec);

    quint8 getDelay();
    void setDelay(quint8 sec);
    
    quint8 getAutoCopyFilenameOnSaving();
    void setAutoCopyFilenameOnSaving(quint8 val);

    // trayMessages
    quint8 getTrayMessages();
    void setTrayMessages(quint8 type);

    // allow multiple copies
    bool getAllowMultipleInstance();
    void setAllowMultipleInstance(bool val);

    // closing in tray
    bool getCloseInTray();
    void setCloseInTray(bool val);

    // type of screen
    int getTypeScreen();
    void setTypeScreen(quint8 type);

    // saved size on exit
    bool getSavedSizeOnExit();
    void setSavedSizeOnExit(bool val);

    // tume of tray messages
    quint8 getTimeTrayMess();
    void setTimeTrayMess(int src);

    bool getDateTimeInFilename();
    void setDateTimeInFilename(bool val);

    // auto save screenshot
    bool getAutoSave();
    void setAutoSave(bool val);
    
    // umage qualuty
    quint8 getImageQuality();
    void setImageQuality(quint8 qualuty);

    // aoutosave first screenshot
    bool getAutoSaveFirst();
    void setAutoSaveFirst(bool val);

    // size wnd
    QSize getRestoredWndSize();
    void setRestoredWndSize(int w, int h);
    void saveWndSize();

    // get default image save format
    int getDefaultFormatID();
    QString getDirNameDefault();

    // datetime template
    QString getDateTimeTpl();
    void setDateTimeTpl(QString tpl);

    // zoom aroundd mouse
    bool getZoomAroundMouse();
    void setZoomAroundMouse(bool val);

    // show tray icon option
    bool getShowTrayIcon();
    void setShowTrayIcon(bool val);

#ifdef Q_WS_X11
    // no decoration wnd on X11
    bool getNoDecorX11();
    void setNoDecorX11(bool val);
#endif

    // shortcuts


    static QString getSysLang();

    CmdLine* cmdLine();
    ShortcutManager* shortcuts();

private:
    Config();
    Config(const Config &);
    Config& operator=(const Config& );

    static Config *ptrInstance;

    /**
     * Return value on configuration parameter
     *
     * @param String of name key
     * @return QVariant value of configuration parameter
     */
    QVariant value(const QString &key);

    /**
     * Set value on configuration parameter
     *
     * @param String of name key
     * @param String of saved value
     */
    void setValue(const QString& key, QVariant val);

    QSettings *settings;
    QHash<QString, QVariant> confData;

    CmdLine *cmd;
    ShortcutManager *_shortcuts;

    QVector<QString> imageFormats;
};

#endif // CONFIG_H
