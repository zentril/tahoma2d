#pragma once

#ifndef TESTCUSTOMTAB_H
#define TESTCUSTOMTAB_H

#include "tfilepath.h"
#include "toonzqt/menubarcommand.h"

#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif
#include <map>
#include <QAction>
#include <QString>

#include "../toonzqt/tdockwindows.h"

class QStackedWidget;
class QSlider;
class TPanel;
class UpdateChecker;
class TopBar;
class StatusBar;
class AboutPopup;
//-----------------------------------------------------------------------------

class Room final : public TMainWindow {
  Q_OBJECT

  TFilePath m_path;
  QString m_name;

public:
#if QT_VERSION >= 0x050500
  Room(QWidget *parent = 0, Qt::WindowFlags flags = 0)
#else
  Room(QWidget *parent = 0, Qt::WFlags flags = 0)
#endif
      : TMainWindow(parent, flags) {
  }

  ~Room() {}

  TFilePath getPath() const { return m_path; }
  void setPath(TFilePath path) { m_path = path; }

  QString getName() const { return m_name; }
  void setName(QString name) { m_name = name; }

  void save();
  std::pair<DockLayout *, DockLayout::State> load(const TFilePath &fp);
  void reload();
};

//-----------------------------------------------------------------------------

class MainWindow final : public QMainWindow {
  Q_OBJECT

  bool m_saveSettingsOnQuit;
  bool m_startupPopupShown = false;
  bool m_shownOnce         = false;
  int m_oldRoomIndex;
  QString m_currentRoomsChoice;
  UpdateChecker *m_updateChecker;

  TopBar *m_topBar;
  StatusBar *m_statusBar;
  AboutPopup *m_aboutPopup;
  QDialog *m_transparencyTogglerWindow;
  QSlider *m_transparencySlider;
  QActionGroup *m_toolsActionGroup;

  QStackedWidget *m_stackedWidget;

  /*-- show layout name in the title bar --*/
  QString m_layoutName;
  std::vector<std::pair<DockLayout *, DockLayout::State>> m_panelStates;

public:
#if QT_VERSION >= 0x050500
  MainWindow(const QString &argumentLayoutFileName, QWidget *parent = 0,
             Qt::WindowFlags flags = 0);
#else
  MainWindow(const QString &argumentLayoutFileName, QWidget *parent = 0,
             Qt::WFlags flags = 0);
#endif
  ~MainWindow();

  void startupFloatingPanels();

  void onQuit();
  void onUndo();
  void onRedo();
  void onNewScene();
  void onLoadScene();
  void onLoadSubScene();
  void resetRoomsLayout();
  void maximizePanel();
  void fullScreenWindow();
  void autofillToggle();
  void onUpgradeTabPro();
  void onAbout();
  void onOpenOnlineManual();
  void onSupportTahoma2D();
  void onOpenWhatsNew();
  void onOpenCommunityForum();
  void onOpenReportABug();
  void checkForUpdates();
  int getRoomCount() const;
  Room *getRoom(int index) const;
  Room *getRoomByName(QString &roomName);

  Room *getCurrentRoom() const;
  void refreshWriteSettings();

  /*-- Animate tool + mode switching shortcuts --*/
  void toggleEditNextMode();
  void toggleEditPosition();
  void toggleEditRotation();
  void toggleEditNextScale();
  void toggleEditNextShear();
  void toggleEditNextCenter();
  void toggleEditNextAll();

  /*-- Selection tool + mode switching shortcuts --*/
  void toggleSelectionNextType();
  void toggleSelectionRectangular();
  void toggleSelectionFreehand();
  void toggleSelectionPolyline();

  /*-- Geometric tool + shape switching shortcuts --*/
  void toggleGeometricNextShape();
  void toggleGeometricRectangle();
  void toggleGeometricCircle();
  void toggleGeometricEllipse();
  void toggleGeometricLine();
  void toggleGeometricPolyline();
  void toggleGeometricArc();
  void toggleGeometricMultiArc();
  void toggleGeometricPolygon();

  /*-- Type tool + style switching shortcuts --*/
  void toggleTypeNextStyle();
  void toggleTypeOblique();
  void toggleTypeRegular();
  void toggleTypeBoldOblique();
  void toggleTypeBold();

  /*-- Fill tool + mode switching shortcuts --*/
  void toggleFillNextType();
  void toggleFillNormal();
  void toggleFillRectangular();
  void toggleFillFreehand();
  void toggleFillPolyline();
  void toggleFillNextMode();
  void toggleFillAreas();
  void toggleFillLines();
  void toggleFillLinesAndAreas();

  /*-- Eraser tool + type switching shortcuts --*/
  void toggleEraserNextType();
  void toggleEraserNormal();
  void toggleEraserRectangular();
  void toggleEraserFreehand();
  void toggleEraserPolyline();
  void toggleEraserSegment();

  /*-- Tape tool + type/mode switching shortcuts --*/
  void toggleTapeNextType();
  void toggleTapeNormal();
  void toggleTapeRectangular();
  void toggleTapeNextMode();
  void toggleTapeEndpointToEndpoint();
  void toggleTapeEndpointToLine();
  void toggleTapeLineToLine();

  /*-- Style Picker tool + mode switching shortcuts --*/
  void togglePickStyleNextMode();
  void togglePickStyleAreas();
  void togglePickStyleLines();
  void togglePickStyleLinesAndAreas();

  /*-- RGB Picker tool + type switching shortcuts --*/
  void toggleRGBPickerNextType();
  void toggleRGBPickerNormal();
  void toggleRGBPickerRectangular();
  void toggleRGBPickerFreehand();
  void toggleRGBPickerPolyline();

  /*-- Skeleton tool + mode switching shortcuts --*/
  void ToggleSkeletonNextMode();
  void ToggleSkeletonBuildSkeleton();
  void ToggleSkeletonAnimate();
  void ToggleSkeletonInverseKinematics();

  /*-- Plastic tool + mode switching shortcuts --*/
  void TogglePlasticNextMode();
  void TogglePlasticEditMesh();
  void TogglePlasticPaintRigid();
  void TogglePlasticBuildSkeleton();
  void TogglePlasticAnimate();

  /*-- Brush Tool + mode switching shortcuts --*/
  void ToggleBrushAutoFillOff();
  void ToggleBrushAutoFillOn();

  void onNewVectorLevelButtonPressed();
  void onNewToonzRasterLevelButtonPressed();
  void onNewRasterLevelButtonPressed();
  void clearCacheFolder();

  QString getLayoutName() { return m_layoutName; }

protected:
  void showEvent(QShowEvent *) override;
  void closeEvent(QCloseEvent *) override;
  void readSettings(const QString &layoutFileName);
  void writeSettings();

private:
  /*!Must be call before readSettings().*/
  void defineActions();

  Room *create2DRoom();
  Room *createStopMotionRoom();
  Room *createTimingRoom();
  Room *createFXRoom();
  Room *createBrowserRoom();

  QAction *createAction(const char *id, const QString &name,
                        const QString &defaultShortcut, QString newStatusTip,
                        CommandType type = MenuFileCommandType);
  QAction *createRightClickMenuAction(const char *id, const QString &name,
                                      const QString &defaultShortcut,
                                      QString newStatusTip = "");
  QAction *createMenuFileAction(const char *id, const QString &name,
                                const QString &defaultShortcut,
                                QString newStatusTip = "");
  QAction *createMenuEditAction(const char *id, const QString &name,
                                const QString &defaultShortcut,
                                QString newStatusTip = "");
  QAction *createMenuScanCleanupAction(const char *id, const QString &name,
                                       const QString &defaultShortcut,
                                       QString newStatusTip = "");
  QAction *createMenuLevelAction(const char *id, const QString &name,
                                 const QString &defaultShortcut,
                                 QString newStatusTip = "");
  QAction *createMenuXsheetAction(const char *id, const QString &name,
                                  const QString &defaultShortcut,
                                  QString newStatusTip = "");
  QAction *createMenuCellsAction(const char *id, const QString &name,
                                 const QString &defaultShortcut,
                                 QString newStatusTip = "");
  QAction *createMenuViewAction(const char *id, const QString &name,
                                const QString &defaultShortcut,
                                QString newStatusTip = "");
  QAction *createMenuWindowsAction(const char *id, const QString &name,
                                   const QString &defaultShortcut,
                                   QString newStatusTip = "");

  QAction *createMenuPlayAction(const char *id, const QString &name,
                                const QString &defaultShortcut,
                                QString newStatusTip = "");
  QAction *createMenuRenderAction(const char *id, const QString &name,
                                  const QString &defaultShortcut,
                                  QString newStatusTip = "");
  QAction *createMenuHelpAction(const char *id, const QString &name,
                                const QString &defaultShortcut,
                                QString newStatusTip = "");
  QAction *createRGBAAction(const char *id, const QString &name,
                            const QString &defaultShortcut,
                            QString newStatusTip = "");
  QAction *createFillAction(const char *id, const QString &name,
                            const QString &defaultShortcut,
                            QString newStatusTip = "");
  QAction *createMenuAction(const char *id, const QString &name,
                            QList<QString> list, QString newStatusTip = "");
  QAction *createToggle(const char *id, const QString &name,
                        const QString &defaultShortcut, bool startStatus,
                        CommandType type, QString newStatusTip = "");
  QAction *createToolAction(const char *id, const char *iconName,
                            const QString &name, const QString &defaultShortcut,
                            QString newStatusTip = "");
  QAction *createViewerAction(const char *id, const QString &name,
                              const QString &defaultShortcut,
                              QString newStatusTip = "");
  // For command bar, no shortcut keys
  QAction *createVisualizationButtonAction(const char *id, const QString &name,
                                           QString newStatusTip = "");

  QAction *createMiscAction(const char *id, const QString &name,
                            const char *defaultShortcut,
                            QString newStatusTip = "");
  QAction *createToolOptionsAction(const char *id, const QString &name,
                                   const QString &defaultShortcut,
                                   QString newStatusTip = "");
  QAction *createStopMotionAction(const char *id, const QString &name,
                                  const QString &defaultShortcut,
                                  QString newStatusTip = "");

protected slots:
  void onCurrentRoomChanged(int newRoomIndex);
  void onIndexSwapped(int firstIndex, int secondIndex);
  void insertNewRoom();
  void deleteRoom(int index);
  void renameRoom(int index, const QString name);
  void onMenuCheckboxChanged();

  // make InkCheck and Ink#1Check exclusive.
  void onInkCheckTriggered(bool on);
  void onInk1CheckTriggered(bool on);

  void onUpdateCheckerDone(bool);

  void toggleStatusBar(bool);
  void toggleTransparency(bool);
  void makeTransparencyDialog();

public slots:
  /*--- タイトルにシーン名を入れる ---*/
  void changeWindowTitle();
  /*--- FlipモジュールでタイトルバーにロードしたLevel名を表示 ---*/
  /*--- Cleanupモジュールでタイトルバーに進捗を表示 ---*/
  void changeWindowTitle(QString &);

signals:
  void exit(bool &);
};

class RecentFiles {
  friend class StartupPopup;
  friend class DvDirModelRootNode;
  friend class ProjectPopup;
  friend class ProjectSettingsPopup;
  QList<QString> m_recentScenes;
  QList<QString> m_recentSceneProjects;
  QList<QString> m_recentLevels;
  QList<QString> m_recentFlipbookImages;
  QList<QString> m_recentProjects;

  RecentFiles();

public:
  enum FileType { Scene, Level, Flip, Project, None };

  static RecentFiles *instance();
  ~RecentFiles();

  void addFilePath(QString path, FileType fileType, QString projectName = 0);
  void moveFilePath(int fromIndex, int toIndex, FileType fileType);
  void removeFilePath(int fromIndex, FileType fileType);
  QString getFilePath(int index, FileType fileType) const;
  QString getFileProject(QString fileName) const;
  QString getFileProject(int index) const;
  void clearRecentFilesList(FileType fileType);
  void clearAllRecentFilesList(bool saveNow = true);
  void loadRecentFiles();
  void saveRecentFiles();

  void updateStuffPath(QString oldPath, QString newPath);
  QList<QString> getFilesNameList(FileType fileType);

protected:
  void refreshRecentFilesMenu(FileType fileType);
};

#endif  // TESTCUSTOMTAB_H
