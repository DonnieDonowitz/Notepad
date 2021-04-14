#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QMenu>
#include <QPrinter>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>
#include <QPrintDialog>
#include <QToolBar>
#include <QComboBox>
#include <QFont>
#include <QIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

public slots:
	void onNewTriggered();
	void onOpenTriggered();
	void onSaveAsTriggered();
	void onPrintTriggered();

	void onBoldTriggered();
	void onItalicTriggered();
	void onUnderlinedTriggered();

private:
    Ui::MainWindowClass *ui;
	QMenu *fileMenu, *editMenu;
	QString currFile = "";
	QTextEdit *editor;
	QToolBar *format;

	void setupFileMenu();
	void setupEditMenu();
	void setupFormatToolbar();
};
